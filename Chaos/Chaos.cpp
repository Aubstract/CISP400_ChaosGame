//Chaos game with Aubrey Fields and William Garica-Cortes
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace sf;
using namespace std;

CircleShape getPosBetweenPoints(CircleShape current, CircleShape vertex, float ratio, Color frameColor)
{
	float x1 = current.getPosition().x;
	float y1 = current.getPosition().y;

	float x2 = vertex.getPosition().x;
	float y2 = vertex.getPosition().y;

	float x3 = x1 + ((x2 - x1) * ratio);
	float y3 = y1 + ((y2 - y1) * ratio);

	CircleShape z;
	z.setRadius(1);
	z.setFillColor(frameColor);
	z.setOutlineColor(frameColor);
	z.setOutlineThickness(1);
	z.setPosition(x3, y3);

	return z;

}

int main()
{
	/*
	****************************************
	Init values
	****************************************
	*/
	const int POINTS_PER_FRAME = 50;

	bool pause = false;
	bool inputFinished = false;

	float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;

	float ratio;
	int numPoints = 0;
	int colorCounter = 0;
	int frameCounter = 0;

	vector <CircleShape> points;

	CircleShape currentPoint;
	CircleShape point;

	Color rainbow[6] = { Color::Red, Color::Yellow, Color::Green, Color::Cyan, Color::Blue, Color::Magenta };
	Color frameColor = rainbow[colorCounter];
	
	srand(time(0));

	
	/*
	****************************************
	Set up the text
	****************************************
	*/

	Font font;
	font.loadFromFile("fonts\\IMMORTAL.ttf");

	Text text;
	text.setFont(font);
	text.setString("Left click to place vertices (at least 3)\nThen right click to start the game.\nPress Esc to quit.");
	text.setCharacterSize(24);
	text.setFillColor(Color::White);

	/*
	****************************************
	Set up the display
	****************************************
	*/

	VideoMode vm(width, height);

	RenderWindow window(vm, "Chaos Game", Style::Default);

	Event event;

	/*
	****************************************
	Display
	****************************************
	*/

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*Keybind to pause the program if you want*/
		if (Keyboard::isKeyPressed(Keyboard::F))
		{
			pause = true;
		}

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				cout << "Closed Chaos Game" << endl;
				break;

			case Event::Resized:
				cout << "New width: " << event.size.width << endl;
				cout << "New height: " << event.size.height << endl;
				break;

			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left)
				{
					if (!inputFinished)
					{
						numPoints++;

						cout << "The left mouse button was pressed" << endl;
						cout << "Mouse x: " << event.mouseButton.x << endl;
						cout << "Mouse y: " << event.mouseButton.y << endl;

						point.setRadius(1);
						point.setOutlineColor(Color::Yellow);
						point.setFillColor(Color::Yellow);
						point.setOutlineThickness(1);
						point.setPosition(event.mouseButton.x, event.mouseButton.y);
						points.push_back(point);

					}
				}
				else if (event.mouseButton.button == Mouse::Right)
				{
					if (!inputFinished)
					{
						ratio = static_cast<float>(numPoints) / (numPoints + 3);
						cout << "The value of ratio is: " << fixed << ratio << endl;

						cout << "The right mouse button was pressed" << endl;
						cout << "Mouse x: " << event.mouseButton.x << endl;
						cout << "Mouse y: " << event.mouseButton.y << endl;

						point.setRadius(1);
						point.setOutlineColor(Color::White);
						point.setFillColor(Color::White);
						point.setOutlineThickness(1);
						point.setPosition(event.mouseButton.x, event.mouseButton.y);
						points.push_back(point);
						inputFinished = true;
					}
				}
				break;

			default:
				break;
			}
		}


		/*
		****************************************
		Display
		****************************************
		*/

		window.clear();

		window.draw(text);

		if (frameCounter % 10 == 0)
		{
			frameColor = rainbow[colorCounter];
			colorCounter++;
			if (colorCounter >= 6)
			{
				colorCounter = 0;
			}

			for (int i = 0; i < points.size(); i++)
			{
				points.at(i).setFillColor(frameColor);
				points.at(i).setOutlineColor(frameColor);
			}
		}
		

		// TODO: Speed this up somehow??
		for (int i = 0; i < points.size(); i++)
		{
			window.draw(points.at(i));
		}

		if (inputFinished && !pause)
		{
			for (int i = 0; i < POINTS_PER_FRAME; i++)
			{
				/*Current point is the most recently generated one*/
				currentPoint = points.back();

				/*Choose a random vertex (the initial points)*/
				int randInt = rand() % numPoints;
				CircleShape randVertex = points.at(randInt);
				cout << "Random point: " << randInt << endl;

				/* Make a new Circleshape and calculate it's position between 
				the current point and the random vertex */
				CircleShape newPoint;
				newPoint = getPosBetweenPoints(currentPoint, randVertex, ratio, frameColor);

				cout << "New point X: " << newPoint.getPosition().x << endl;
				cout << "New point y: " << newPoint.getPosition().y << endl;

				/* Add the new point to the points vector*/
				points.push_back(newPoint);
				cout << "Size of points: " << points.size() << endl;
			}
		}

		frameCounter++;
		window.display();
	}

	return 0;
}
