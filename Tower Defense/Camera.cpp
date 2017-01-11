#include "Camera.hpp"
#include "Constants.hpp"
#include <iostream>

Camera::Camera(States::Context context)
	: context(context)
	, dragging(false)
{
	windowSize = context.window->getSize();
	view.setSize(windowSize.x, windowSize.y); //480
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	//view.setViewport({ 0.f, 0.f, 1.f, 1.f });

	context.window->setView(view);


	std::cout << windowSize.x << ' ' << windowSize.y << std::endl;
}

void Camera::handleEvent(const sf::Event &event)
{
	if (event.type == sf::Event::MouseButtonPressed
		&& event.key.code == sf::Mouse::Right)
	{
		initialMousePos = sf::Mouse::getPosition(*context.window);
		dragging = true;
	}
	else if (event.type == sf::Event::MouseButtonReleased
		&& event.key.code == sf::Mouse::Right)
	{
		dragging = false;
	}
	//else if (event.type == sf::Event::MouseWheelMoved)
	//{
	//	int factor = 1 + event.mouseWheel.delta;// *-0.1f;
	//	std::cout << "mousewheel: " << event.mouseWheel.delta << std::endl;
	//	std::cout << factor << std::endl;
	//	std::cout << view.getSize().x << ' ' << view.getSize().y << std::endl;
	//	view.zoom(factor);
	//	if (view.getSize().x > 1280) view.setSize({ 1280, view.getSize().y });
	//	if (view.getSize().y > 960) view.setSize({ view.getSize().x, 960 });

	//	if (view.getSize().x < 160) view.setSize({ 160, view.getSize().y });
	//	if (view.getSize().y < 120) view.setSize({ view.getSize().x, 120 });
	//	
	//	view.setSize(std::floor(view.getSize().x), std::floor(view.getSize().y));
	//	view.setCenter({ std::floor(view.getCenter().x), std::floor(view.getCenter().y) });

	//	context.window->setView(view);
	//}
}

void Camera::update(sf::Time dt)
{
	if (dragging)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*context.window);
		sf::Vector2f worldPos = context.window->mapPixelToCoords(mousePos, view);
		//std::cout << worldPos.x << ' ' << worldPos.y << std::endl;

		int temp = initialMousePos.x - mousePos.x;

		view.move(initialMousePos.x - mousePos.x, initialMousePos.y - mousePos.y);
		/*std::cout << temp;
		if (temp % 2) temp += temp % 2;
		std::cout << ' ' << temp << std::endl;*/

		/*if(temp < 0) view.move(20, initialMousePos.y - mousePos.y);
		else if(temp > 0) view.move(-20, initialMousePos.y - mousePos.y);*/

		//view.move(temp, initialMousePos.y - mousePos.y);

		initialMousePos = mousePos;
		//view.setCenter(std::floor(view.getCenter().x), std::floor(view.getCenter().y));

		if (view.getCenter().x - view.getSize().x / 2 < 0) view.setCenter(view.getSize().x / 2, view.getCenter().y);
		else if(view.getCenter().x + view.getSize().x / 2 > MAP_WIDTH * TILE_WORLD_SIZE) view.setCenter(MAP_WIDTH * TILE_WORLD_SIZE - view.getSize().x / 2, view.getCenter().y);


		if (view.getCenter().y - view.getSize().y / 2 < 0) view.setCenter(view.getCenter().x, view.getSize().y / 2);
		else if (view.getCenter().y + view.getSize().y / 2 > MAP_HEIGHT * TILE_WORLD_SIZE + 150) view.setCenter(view.getCenter().x, (MAP_HEIGHT * TILE_WORLD_SIZE + 150) - view.getSize().y / 2);
		
		context.window->setView(view);
	}
	

	//sf::Vector2i mousePos = sf::Mouse::getPosition(*context.window);
	////std::cout << mousePos.x << ' ' << mousePos.y << std::endl;

	//if (mousePos.x < 0) mousePos.x = 0;
	//else if (mousePos.x > windowSize.x) mousePos.x = windowSize.x;

	//if (mousePos.y < 0) mousePos.y = 0;
	//else if (mousePos.y > windowSize.y) mousePos.y = windowSize.y;

	//sf::Mouse::setPosition(mousePos, *context.window);

	//if (mousePos.x == 0) view.move(-50 * dt.asSeconds(), 0);
	//else if (mousePos.x == windowSize.x) view.move(50 * dt.asSeconds(), 0);

	//if (mousePos.y == 0) view.move(0, -50 * dt.asSeconds());
	//else if (mousePos.y == windowSize.y) view.move(0, 50 * dt.asSeconds());

	//context.window->setView(view);
}

void Camera::draw()
{
	float x = view.getCenter().x;
	float y = view.getCenter().y;

	x = std::floor(x);
	y = std::floor(y);

	std::cout << x << ' ' << y << std::endl;

	view.setCenter(x, y);
}

const sf::View &Camera::getView()
{
	return view;
}
