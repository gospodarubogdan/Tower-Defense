#include "GameState.hpp"
#include "Constants.hpp"

#include "MoveSystem.hpp"
#include "DrawSystem.hpp"

GameState::GameState(StateManager &stack, States::Context context)
	: State(stack, context)
	, entityManager(&textureManager)
	, camera(context)
	, hud(*context.window)
	, map(TILE_SIZE, TILE_WORLD_SIZE)
	, grid(*context.window)
	, selected(false)
{
	//map.loadFromCSV("data/mapValues.csv");
	//map.loadSheet("data/mapsheet.png");
	textureManager.loadFromFile("mapSheet", "data/mapnospace.png");
	textureManager.loadFromFile("mob", "data/test.png");
	textureManager.loadFromFile("turret", "data/tower.png");
	textureManager.loadFromFile("bullet", "data/bullet.png");

	textureManager.getTexture("mapSheet").setSmooth(true);
	map.setTexture(textureManager.getTexture("mapSheet"));

	/*entityManager.registerComponent<PositionComponent>(Components::ID::PositionComponent);
	entityManager.registerComponent<VelocityComponent>(Components::ID::VelocityComponent);
	entityManager.registerComponent<RenderComponent>(Components::ID::RenderComponent);
	entityManager.registerComponent<MoveComponent>(Components::ID::MoveComponent);
	entityManager.registerComponent<RangeComponent>(Components::ID::RangeComponent);
	entityManager.registerComponent<TargetableComponent>(Components::ID::TargetableComponent);
	entityManager.registerComponent<ShootComponent>(Components::ID::ShootComponent);
	entityManager.registerComponent<TargetComponent>(Components::ID::TargetComponent);

	shootsystem.setManager(&entityManager);
	ms.setManager(&entityManager);
	ds.setManager(&entityManager);*/

	for (int i = 0; i < 10; i++)
	{
		auto &entity = entityManager.createEntity();
		entity.addComponent(Components::ID::PositionComponent);
		entity.addComponent(Components::ID::VelocityComponent);
		entity.addComponent(Components::ID::AIComponent);
		entity.addComponent(Components::ID::RenderComponent);
		entity.addComponent(Components::ID::TargetableComponent);

		auto pos = static_cast<PositionComponent*>(entity.getComponent(Components::ID::PositionComponent));
		pos->x = 222;
		pos->y = i * -50;

		auto vel = static_cast<VelocityComponent*>(entity.getComponent(Components::ID::VelocityComponent));
		vel->speed = 80.f;

		auto render = static_cast<RenderComponent*>(entity.getComponent(Components::ID::RenderComponent));
		render->sprite.setTexture(textureManager.getTexture("mob"));
		render->sprite.setOrigin(sf::Vector2f(64.f, 64.f) / 2.f);

		auto hp = static_cast<TargetableComponent*>(entity.getComponent(Components::ID::TargetableComponent));
		hp->health = 100;

		//ms.addEntity(entity);
		//ds.addEntity(entity);
	}

	placement.setSize({ TILE_SIZE * 2, TILE_SIZE * 2 });
	placement.setOrigin(0.f, TILE_SIZE * 2);
	placement.setFillColor(sf::Color(0, 0, 0, 150));

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

	if (selected)
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(*getContext().window);
		sf::Vector2f worldPos = getContext().window->mapPixelToCoords(pixelPos, camera.getView());
	
		placement.setPosition(std::floor(worldPos.x / TILE_SIZE) * TILE_SIZE, 
			std::floor(worldPos.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE);
	
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
	if (selected) getContext().window->draw(placement);

	getContext().window->setView(hud.getView());
	getContext().window->draw(hud);
}

void GameState::placeTower()
{
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
	render->sprite.setTexture(textureManager.getTexture("turret"));

	auto range = static_cast<RangeComponent*>(entity.getComponent(Components::ID::RangeComponent));
	range->range.setRadius(100.f);
	range->range.setOrigin(range->range.getRadius() / 2, range->range.getRadius() / 2);
	range->range.setPosition(pos->x, pos->y);
	range->range.setFillColor(sf::Color(0, 0, 0, 100));

	auto shoot = static_cast<ShootComponent*>(entity.getComponent(Components::ID::ShootComponent));
	shoot->attackSpeed = 1.f;

	//ds.addEntity(entity);
}

bool GameState::validPosition()
{
	return true;

	int x = placement.getPosition().x / TILE_SIZE;
	int y = (placement.getPosition().y - placement.getSize().y / 2) / TILE_SIZE;
	const int dx[] = { 1, 1, 0, 0 };
	const int dy[] = { -1, 0, -1, 0 };
	//x++;
	std::cout << placement.getPosition().x << ' ' << placement.getPosition().y << std::endl;
	std::cout << x << ' ' << y << std::endl;
	Tile &temp = grid.getTile(x * MAP_HEIGHT + y);
	std::cout << temp.getPosition().x << ' ' << temp.getPosition().y << std::endl << std::endl;
	/*for (int i = 0; i < 4; i++)
	{
		std::cout << x + dx[i] << ' ' << y + dy[i] << std::endl;
		Tile &temp = grid.getTile((x + dx[i]) * MAP_WIDTH + y + dy[i]);
		if (temp.getState() == Tile::Type::Invalid)
			return false;
	}*/

	return true;
}
