#include "GameState.hpp"
#include "Constants.hpp"

#include "MoveSystem.hpp"
#include "DrawSystem.hpp"

GameState::GameState(StateManager &stack, States::Context context)
	: State(stack, context)
	, entityManager(context)
	, camera(context)
	, hud(context)
	, map(TILE_SIZE, TILE_WORLD_SIZE)
	, grid(*context.window)
	, selected(false)
{
	//map.loadFromCSV("data/mapValues.csv");
	//map.loadSheet("data/mapsheet.png");
	context.textureManager->loadFromFile("mapSheet", "data/mapnospace.png");
	context.textureManager->loadFromFile("mob", "data/animtest.png");
	context.textureManager->loadFromFile("turret", "data/tower2.png");
	context.textureManager->loadFromFile("bullet", "data/bullet.png");
	context.textureManager->loadFromFile("healthBar", "data/healthbar.png");

	context.textureManager->getTexture("mapSheet").setSmooth(true);
	map.setTexture(context.textureManager->getTexture("mapSheet"));

	for (int i = 0; i < 10; i++)
	{
		auto &entity = entityManager.createEntity();
		entity.addComponent(Components::ID::PositionComponent);
		entity.addComponent(Components::ID::VelocityComponent);
		entity.addComponent(Components::ID::AIComponent);
		entity.addComponent(Components::ID::RenderComponent);
		entity.addComponent(Components::ID::HealthComponent);
		entity.addComponent(Components::ID::DirectionComponent);
		entity.addComponent(Components::ID::AnimationComponent);

		auto pos = static_cast<PositionComponent*>(entity.getComponent(Components::ID::PositionComponent));
		pos->x = 222;
		pos->y = i * -100;

		auto vel = static_cast<VelocityComponent*>(entity.getComponent(Components::ID::VelocityComponent));
		vel->speed = 70.f;

		auto render = static_cast<RenderComponent*>(entity.getComponent(Components::ID::RenderComponent));
		render->sprite.setTexture(getContext().textureManager->getTexture("mob"));
		render->sprite.setTextureRect({ 0,0,32,32 });
		render->sprite.setOrigin(sf::Vector2f(32.f, 32.f) / 2.f);

		auto hp = static_cast<HealthComponent*>(entity.getComponent(Components::ID::HealthComponent));
		hp->health = 100;
		hp->healthBar.setTexture(getContext().textureManager->getTexture("healthBar"));
		hp->healthBar.setPosition(pos->x - 16, pos->y - 26);

		//ms.addEntity(entity);
		//ds.addEntity(entity);
	}

	placement.setSize({ TILE_SIZE * 2, TILE_SIZE * 2 });
	placement.setOrigin(0.f, TILE_SIZE * 2);
	placement.setFillColor(sf::Color(0, 0, 0, 150));

	range.setRadius(100.f);
	range.setOrigin(range.getRadius(), range.getRadius());
	range.setPosition(placement.getPosition().x + TILE_SIZE, placement.getPosition().y - TILE_SIZE);
	range.setFillColor(sf::Color::Transparent);
	range.setOutlineThickness(2.f);
	range.setOutlineColor(sf::Color::Red);

	//hud.setPosition(0.f, 400.f);
}

bool GameState::handleEvent(const sf::Event &event)
{
	camera.handleEvent(event);

	sf::Vector2i mousePos = sf::Mouse::getPosition(*getContext().window);
	if (event.type == sf::Event::MouseButtonPressed
		&& event.key.code == sf::Mouse::Left)
	{
		if (selected && validPosition())
		{
			placeTower();
			selected = false;
		}
		else
		{
			tower = hud.getTowerType(mousePos);
			if (tower != Tower::Type::None)
				selected = true;
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed
		&& event.key.code == sf::Mouse::Right)
	{
		selected = false;
	}

	return false;
}

bool GameState::update(sf::Time dt)
{
	camera.update(dt);
	//ms.update(dt);
	entityManager.update(dt);
	hud.update(dt);

	if (selected)
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(*getContext().window);
		sf::Vector2f worldPos = getContext().window->mapPixelToCoords(pixelPos, camera.getView());
	
		placement.setPosition(std::floor(worldPos.x / TILE_SIZE) * TILE_SIZE, 
			std::floor(worldPos.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE);

		range.setPosition(placement.getPosition().x + TILE_SIZE, placement.getPosition().y - TILE_SIZE);
	}

	return false;
}

void GameState::draw()
{
	//getContext().window->draw(map);
	getContext().window->setView(camera.getView());

	grid.draw();
	//ds.draw(*getContext().window);
	entityManager.draw(*getContext().window);
	if (selected)
	{
		getContext().window->draw(placement);
		getContext().window->draw(range);
	}

	getContext().window->setView(hud.getView());
	getContext().window->draw(hud);
}

void GameState::placeTower()
{
	int x = (placement.getPosition().x) / TILE_SIZE;
	int y = (placement.getPosition().y - placement.getSize().y / 2) / TILE_SIZE;
	const int dx[] = { 1, 1, 0, 0 };
	const int dy[] = { -1, 0, -1, 0 };

	for (int k = 0; k < 4; k++)
	{
		int i = y + dy[k];
		int j = x + dx[k];

		Tile &temp = grid.getTile(i, j);
		temp.setState(Tile::Type::Invalid);
	}

	auto &entity = entityManager.createEntity();
	entity.addComponent(Components::ID::PositionComponent);
	entity.addComponent(Components::ID::RenderComponent);
	entity.addComponent(Components::ID::RangeComponent);
	entity.addComponent(Components::ID::ShootComponent);
	entity.addComponent(Components::ID::TargetComponent);

	auto pos = static_cast<PositionComponent*>(entity.getComponent(Components::ID::PositionComponent));
	pos->x = placement.getPosition().x;
	pos->y = placement.getPosition().y - placement.getSize().y;

	auto render = static_cast<RenderComponent*>(entity.getComponent(Components::ID::RenderComponent));
	render->sprite.setTexture(getContext().textureManager->getTexture("turret"));

	auto range = static_cast<RangeComponent*>(entity.getComponent(Components::ID::RangeComponent));
	range->range.setRadius(100.f);
	range->range.setOrigin(range->range.getRadius(), range->range.getRadius());
	range->range.setPosition(pos->x + TILE_SIZE, pos->y + TILE_SIZE);
	range->range.setFillColor(sf::Color::Transparent);
	range->range.setOutlineThickness(2.f);
	range->range.setOutlineColor(sf::Color::Red);

	auto shoot = static_cast<ShootComponent*>(entity.getComponent(Components::ID::ShootComponent));
	shoot->attackSpeed = 1.f;

	//ds.addEntity(entity);
}

bool GameState::validPosition()
{
	int x = (placement.getPosition().x) / TILE_SIZE;
	int y = (placement.getPosition().y - placement.getSize().y / 2) / TILE_SIZE;
	const int dx[] = { 1, 1, 0, 0 };
	const int dy[] = { -1, 0, -1, 0 };

	for (int k = 0; k < 4; k++)
	{
		int i = y + dy[k];
		int j = x + dx[k];
		if (i < 0 || i > MAP_HEIGHT || j < 0 || j > MAP_WIDTH)
			continue;

		Tile &temp = grid.getTile(i, j);
		if (temp.getState() == Tile::Type::Invalid)
			return false;
	}

	return true;
}
