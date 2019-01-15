#include "Game.hpp"
#include "SplashState.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>

/*
	Constructor that will create a window based on the inputs
	and run the game.
*/
Game::Game(int width, int height, std::string title)
{
	// set a random seed
	srand(time(NULL));
	// create the window
	_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	
	// add the first state, the splash screen.
	_data->machine.AddState(StateRef(new SplashState(this->_data)));
	
	// run the game
	this->Run();


		// for testing
		/*
		std::cout << "TESTING GAME CPP" << std::endl;
		sf::CircleShape shape(100.f);
		shape.setFillColor(sf::Color::Green);
		while (this->_data->window.isOpen())
		{
		sf::Event event;
		while (this->_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->_data->window.close();
		}

		std::cout << "drawing shape" << std::endl;
		sf::RectangleShape windowBackground(sf::Vector2f(100.0f, 100.0f));
		

		this->_data->window.clear();
		this->_data->window.draw(shape);
		this->_data->window.draw(windowBackground);
		this->_data->window.display();
		}
		*/
	
}


/*
	The game loop.
	
*/
void Game::Run()
{
	float newTime, frameTime, interpolation;
	float currentTime = this->_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (this->_data->window.isOpen())
	{
		this->_data->machine.ProcessStateChanges();
		newTime = this->_clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			this->_data->machine.GetActiveState()->HandleInput();
			this->_data->machine.GetActiveState()->Update(dt);
			accumulator -= dt;
		}

		interpolation = accumulator / dt;
		this->_data->machine.GetActiveState()->Draw(interpolation);
	}
}



/**** not used ****/
Game::~Game()
{
}
