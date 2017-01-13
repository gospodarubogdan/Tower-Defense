#include "GameState.hpp"
#include "Constants.hpp"
#include "SoundManager.hpp"

#include "MoveSystem.hpp"
#include "DrawSystem.hpp"

#include "Button.hpp"

#include <fstream>

GameState::GameState(StateManager &stack, States::Context context)
	: State(stack, context)
	, entityManager(context, gameData)
	, gameData()
	, camera(context)
	, hud(context, gameData)
	, map(TILE_SIZE, TILE_WORLD_SIZE)
	, grid(*context.window)
	, selected(false)
	, currentLevel(0)
{
	context.textureManager->loadFromFile("mapSheet", "data/mapnospace.png");
	context.textureManager->loadFromFile("mob", "data/animtest.png");
	context.textureManager->loadFromFile("singleTarget", "data/singletarget.png");
	context.textureManager->loadFromFile("splash", "data/splash.png");
	context.textureManager->loadFromFile("frost", "data/frost.png");
	context.textureManager->loadFromFile("bullet", "data/bullet.png");
	context.textureManager->loadFromFile("healthBar", "data/healthbar.png");


	context.soundManager->loadFromFile("upgrade", "data/sfx/upgrade.wav");
	context.soundManager->loadFromFile("sell", "data/sfx/sell.wav");

	context.textureManager->getTexture("mapSheet").setSmooth(true);
	map.setTexture(context.textureManager->getTexture("mapSheet"));

	placement.setSize({ TILE_SIZE * 2, TILE_SIZE * 2 });
	placement.setOrigin(0.f, TILE_SIZE * 2);
	placement.setFillColor(sf::Color(0, 0, 0, 150));

	range.setRadius(150.f);
	range.setOrigin(range.getRadius(), range.getRadius());
	range.setPosition(placement.getPosition().x + TILE_SIZE, placement.getPosition().y - TILE_SIZE);
	range.setFillColor(sf::Color::Transparent);
	range.setOutlineThickness(2.f);
	range.setOutlineColor(sf::Color::Red);

	sf::RenderWindow &window = *getContext().window;

	auto upgrade = std::make_shared<gui::Button>();// (*getContext().soundPlayer);
	upgrade->setTexture(getContext().textureManager->getTexture("buttonGreen"));
	upgrade->setPosition({ 630.f, 490.f });
	upgrade->setFont(*getContext().font);
	upgrade->setText("Upgrade");
	upgrade->setCallback([this]()
	{
		getContext().cursor->setTexture(getContext().textureManager->getTexture("cursorUpgrade"));
		action = Action::Upgrade;
	});

	auto sell = std::make_shared<gui::Button>();// (*getContext().soundPlayer);
	sell->setTexture(getContext().textureManager->getTexture("buttonGreen"));
	sell->setPosition({ 630.f, 550.f });
	sell->setFont(*getContext().font);
	sell->setText("Sell");
	sell->setCallback([this]()
	{
		getContext().cursor->setTexture(getContext().textureManager->getTexture("cursorSell"));
		action = Action::Sell;
	});
	container.addWidget(upgrade);
	container.addWidget(sell);

	action = Action::None;

	gameData.lives = 30;
	gameData.gold = 500;

	hud.init();
	readGameData();
	createLevelEntities();
}

bool GameState::handleEvent(const sf::Event &event)
{
	camera.handleEvent(event);
	hud.handleEvent(event);
	container.handleWidgetsEvent(event);

	sf::Vector2i mousePos = sf::Mouse::getPosition(*getContext().window);
	if (event.type == sf::Event::MouseButtonPressed
		&& event.key.code == sf::Mouse::Left)
	{
		if (mousePos.y < 480 && selected && validPosition())
		{
			placeTower(tower);
			selected = false;
			hud.resetTowerType();
		}
		else if (action != Action::None)
		{
			sf::Vector2f worldPos = getContext().window->mapPixelToCoords(mousePos, camera.getView());
			Entity *entity = entityManager.getEntity(static_cast<sf::Vector2i>(worldPos));
			if (entity)
			{
				getContext().cursor->setTexture(getContext().textureManager->getTexture("cursorNormal"));
				auto cost = static_cast<GoldComponent*>(entity->getComponent(Components::ID::GoldComponent));
				
				if (action == Action::Upgrade)
				{
					if (gameData.gold >= cost->gold)
						upgradeEntity(entity);
					else {};
					action = Action::None;
				}
				else
				{
					getContext().soundManager->play("sell");

					auto pos = static_cast<PositionComponent*>(entity->getComponent(Components::ID::PositionComponent));

					gameData.gold += 40;
					freeTiles({ pos->x, pos->y });

					entityManager.requestEntityRemoval(entity->getID());

					action = Action::None;
				}
			}
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed
		&& event.key.code == sf::Mouse::Right)
	{
		getContext().cursor->setTexture(getContext().textureManager->getTexture("cursorNormal"));
		action = Action::None;
		selected = false;
		hud.resetTowerType();
	}
	else if (event.type == sf::Event::KeyPressed
		&& event.key.code == sf::Keyboard::Escape)
	{
		pushState(States::ID::Pause);
	}

	return false;
}

bool GameState::update(sf::Time dt)
{
	camera.update(dt);
	hud.update(dt);
	container.updateWidgets(dt);

	if (gameData.lives <= 0)
	{
		// gameover
	}

	sf::Vector2i pixelPos = sf::Mouse::getPosition(*getContext().window);
	if (selected)
	{
		sf::Vector2f worldPos = getContext().window->mapPixelToCoords(pixelPos, camera.getView());
	
		placement.setPosition(std::floor(worldPos.x / TILE_SIZE) * TILE_SIZE, 
			std::floor(worldPos.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE);

		range.setPosition(placement.getPosition().x + TILE_SIZE, placement.getPosition().y - TILE_SIZE);
	}
	else
	{
		tower = hud.getTowerType(pixelPos);
		if (tower != Tower::Type::None)
			selected = true;
	}

	waitingTime += dt;
	if (waitingTime.asSeconds() >= 5.f)
	{
		if (!levelsData[currentLevel].levelOver)
		{
			entityManager.update(dt);
		}
		else
		{
			waitingTime = sf::Time::Zero;
			currentLevel++;
			createLevelEntities();
		}
	}
	else entityManager.applyChanges();

	return false;
}

void GameState::draw()
{
	getContext().window->setView(camera.getView());

	grid.draw();
	entityManager.draw(*getContext().window);
	if (selected)
	{
		getContext().window->draw(placement);
		getContext().window->draw(range);
	}

	getContext().window->draw(hud);
	getContext().window->draw(container);
}

void GameState::placeTower(Tower::Type type)
{
	switch (type)
	{
	case Tower::Type::Frost:
		if (gameData.gold < upgrades[2].cost[0])
			return;
		gameData.gold -= upgrades[2].cost[0];
		break;
	case Tower::Type::SingleTarget:
		if (gameData.gold < upgrades[0].cost[0])
			return;
		gameData.gold -= upgrades[0].cost[0];
		break;
	case Tower::Type::Splash:
		if (gameData.gold < upgrades[1].cost[0])
			return;
		gameData.gold -= upgrades[1].cost[0];
		break;
	}

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
	entity.addComponent(Components::ID::SelectableComponent);
	entity.addComponent(Components::ID::PositionComponent);
	entity.addComponent(Components::ID::RenderComponent);
	entity.addComponent(Components::ID::RangeComponent);
	entity.addComponent(Components::ID::ShootComponent);
	entity.addComponent(Components::ID::DamageComponent);
	entity.addComponent(Components::ID::TargetComponent);
	entity.addComponent(Components::ID::UpgradeComponent);
	entity.addComponent(Components::ID::GoldComponent);
	
	auto upgrade = static_cast<UpgradeComponent*>(entity.getComponent(Components::ID::UpgradeComponent));
	int &index = upgrade->upgrade;
	
	auto cost = static_cast<GoldComponent*>(entity.getComponent(Components::ID::GoldComponent));
	auto shoot = static_cast<ShootComponent*>(entity.getComponent(Components::ID::ShootComponent));
	auto render = static_cast<RenderComponent*>(entity.getComponent(Components::ID::RenderComponent));
	auto dmg = static_cast<DamageComponent*>(entity.getComponent(Components::ID::DamageComponent));
	if (type == Tower::Type::Splash)
	{
		entity.addComponent(Components::ID::SplashComponent);

		render->sprite.setTexture(getContext().textureManager->getTexture("splash"));
		shoot->attackSpeed = upgrades[1].attackSpeed[index];
		dmg->damage = upgrades[1].damage[index];
		cost->gold = upgrades[1].cost[index + 1];
	}
	else if (type == Tower::Type::Frost)
	{
		entity.addComponent(Components::ID::SlowComponent);
		entity.addComponent(Components::ID::SplashComponent);

		render->sprite.setTexture(getContext().textureManager->getTexture("frost"));
		shoot->attackSpeed = upgrades[2].attackSpeed[index];
		dmg->damage = upgrades[2].damage[index];
		cost->gold = upgrades[2].cost[index + 1];
	}
	else
	{
		render->sprite.setTexture(getContext().textureManager->getTexture("singleTarget"));
		shoot->attackSpeed = upgrades[0].attackSpeed[index];
		dmg->damage = upgrades[0].damage[index];
		cost->gold = upgrades[0].cost[index + 1];
	}

	index++;

	auto bounding = static_cast<SelectableComponent*>(entity.getComponent(Components::ID::SelectableComponent));
	bounding->box.setPosition(placement.getPosition().x,
		placement.getPosition().y - placement.getSize().y);
	bounding->box.setSize(placement.getSize());

	auto pos = static_cast<PositionComponent*>(entity.getComponent(Components::ID::PositionComponent));
	pos->x = placement.getPosition().x;
	pos->y = placement.getPosition().y - placement.getSize().y;

	auto range = static_cast<RangeComponent*>(entity.getComponent(Components::ID::RangeComponent));
	range->range.setRadius(150.f);
	range->range.setOrigin(range->range.getRadius(), range->range.getRadius());
	range->range.setPosition(pos->x + TILE_SIZE, pos->y + TILE_SIZE);
	range->range.setFillColor(sf::Color::Transparent);
	range->range.setOutlineThickness(2.f);
	range->range.setOutlineColor(sf::Color::Red);
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

void GameState::freeTiles(const sf::Vector2f &position)
{
	int x = position.x / TILE_SIZE;
	int y = (position.y + placement.getSize().y / 2) / TILE_SIZE;
	const int dx[] = { 1, 1, 0, 0 };
	const int dy[] = { -1, 0, -1, 0 };

	for (int k = 0; k < 4; k++)
	{
		int i = y + dy[k];
		int j = x + dx[k];

		Tile &temp = grid.getTile(i, j);
		temp.setState(Tile::Type::Valid);
	}
}

void GameState::createLevelEntities()
{
	for (int i = 0; i < levelsData[currentLevel].numberOfMinions; i++)
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
		pos->y = (i+1) * -100;

		auto vel = static_cast<VelocityComponent*>(entity.getComponent(Components::ID::VelocityComponent));
		vel->speed = levelsData[currentLevel].movementSpeed;

		auto render = static_cast<RenderComponent*>(entity.getComponent(Components::ID::RenderComponent));
		render->sprite.setTexture(getContext().textureManager->getTexture("mob"));
		render->sprite.setTextureRect({ 0,0,32,32 });
		render->sprite.setOrigin(sf::Vector2f(32.f, 32.f) / 2.f);

		auto hp = static_cast<HealthComponent*>(entity.getComponent(Components::ID::HealthComponent));
		hp->health = levelsData[currentLevel].hp;
		//hp->healthBar.setTexture(getContext().textureManager->getTexture("healthBar"));
		hp->healthBar.setFillColor(sf::Color::Green);
		hp->healthBar.setSize({ 32, 10 });
		hp->healthBar.setPosition(pos->x - 16, pos->y - 26);
	}

	entityManager.setLevelData(levelsData[currentLevel]);
}

void GameState::readGameData()
{
	std::ifstream fin("data/leveldata.txt");

	for (int i = 0; i < 10; i++)
	{
		World::LevelData level;
		fin >> level.numberOfMinions
			>> level.goldPerMinion
			>> level.hp
			>> level.immuneToSlow
			>> level.movementSpeed;

		level.levelOver = false;
		levelsData.push_back(level);
	}

	fin.close();

	fin.open("data/upgradedata.txt");

	Tower::Type temp = Tower::Type::SingleTarget;
	for (int i = 0; i < 3; i++)
	{
		World::UpgradeData tempData;
		for (int j = 0; j < 3; j++)
		{
			fin >> tempData.damage[j]
				>> tempData.cost[j]
				>> tempData.attackSpeed[j];

			tempData.attackSpeed[j] = 1.f / tempData.attackSpeed[j];
		}

		upgrades.push_back(tempData);
		temp = Tower::Type::Splash;
		if (i == 2) temp = Tower::Type::Frost;
	}

	std::cout << upgrades[0].cost[2];
	//std::cout << upgrades[temp].cost << std::endl;

	fin.close();
}

void GameState::upgradeEntity(Entity *entity)
{
	auto dmg = static_cast<DamageComponent*>(entity->getComponent(Components::ID::DamageComponent));
	auto shoot = static_cast<ShootComponent*>(entity->getComponent(Components::ID::ShootComponent));
	auto cost = static_cast<GoldComponent*>(entity->getComponent(Components::ID::GoldComponent));
	auto upgrade = static_cast<UpgradeComponent*>(entity->getComponent(Components::ID::UpgradeComponent));

	int &index = upgrade->upgrade;
	if (index > 2) return;

	getContext().soundManager->play("upgrade");
	gameData.gold -= cost->gold;

	if (entity->hasComponent(Components::ID::SlowComponent))
	{
		dmg->damage = upgrades[2].damage[index];
		shoot->attackSpeed= upgrades[2].attackSpeed[index];

		if(index < 2)
			cost->gold = upgrades[2].cost[index + 1];
	}
	else if (entity->hasComponent(Components::ID::SplashComponent))
	{
		dmg->damage = upgrades[1].damage[index];
		shoot->attackSpeed = upgrades[1].attackSpeed[index];

		if(index < 2)
		cost->gold = upgrades[1].cost[index + 1];
	}
	else
	{
		dmg->damage = upgrades[0].damage[index];
		shoot->attackSpeed = upgrades[0].attackSpeed[index];

		if(index < 2)
			cost->gold = upgrades[0].cost[index + 1];
	}

	index++;
}
