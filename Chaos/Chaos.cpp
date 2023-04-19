//Chaos game with Aubrey Fields and William Garica-Cortes
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace sf;
using namespace std;

CircleShape getMidpoint(float x1, float y1, float x2, float y2, float r)
{
	float x;
	float y;

	if (x1 > x2)
	{
		x = (x1 - x2)* r;
	}
	else
	{
		x = (x2 - x1) * r;
	}

	if (y1 > y2)
	{
		y = (y1 - y2) * r;
	}
	else
	{
		y = (y2 - y1) * r;
	}

	//float x = (sqrt(pow(x2-x1, 2) + pow(y2-y1, 2))) * r;
	//float y = (y2 + y1) * r;

	CircleShape z;
	//z.setSize(Vector2f(1, 1));
	z.setRadius(1);
	z.setOutlineColor(Color::Red);
	z.setOutlineThickness(2);
	z.setPosition(x, y);

	return z;

}

double getX(vector <CircleShape> lastPoint, int index)
{
	return lastPoint.at(index).getPosition().x;
}

double getY(vector <CircleShape> lastPoint, int index)
{
	return lastPoint.at(index).getPosition().y;
}

int main()
{
	/*
	****************************************
	Value holders
	****************************************
	*/
	bool pause = false;
	const int POINTS_PER_FRAME = 5;
	float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;
	float r = 0.5;
	int numPoints = 0;
	CircleShape currentPoint;
	CircleShape point;
	//currentPoint.setSize(Vector2f(1, 1));
	point.setRadius(1);
	currentPoint.setOutlineColor(Color::White);
	currentPoint.setOutlineThickness(2);
	vector <CircleShape> points;
	srand(time(0));
	bool inputFinished = false;

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

						//point.setSize(Vector2f(1, 1));
						point.setRadius(1);
						point.setOutlineColor(Color::Yellow);
						point.setOutlineThickness(2);
						point.setPosition(event.mouseButton.x, event.mouseButton.y);
						points.push_back(point);

					}
				}
				else if (event.mouseButton.button == Mouse::Right)
				{
					if (!inputFinished)
					{
						r = static_cast<float>(numPoints) / (numPoints + 3);
						cout << "The value of r is: " << fixed << r << endl;
						cout << "The right mouse button was pressed" << endl;
						cout << "Mouse x: " << event.mouseButton.x << endl;
						cout << "Mouse y: " << event.mouseButton.y << endl;

						//point.setSize(Vector2f(1, 1));
						point.setRadius(1);
						point.setOutlineColor(Color::White);
						point.setOutlineThickness(2);
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


		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}


		/*
		****************************************
		Display
		****************************************
		*/

		window.clear();

		window.draw(text);

		{
			for (int i = 0; i < points.size(); i++)
			{
				window.draw(points.at(i));
			}
		}

		/*Keybind to stop the program if you want*/
		if (Keyboard::isKeyPressed(Keyboard::F))
		{
			pause = true;
		}

		if (inputFinished && !pause)
		{
			for (int i = 0; i < POINTS_PER_FRAME; i++)
			{
				/*Mark the starting position*/
				currentPoint.setPosition(getX(points, points.size() - 1), getY(points, points.size() - 1));


				/*Get the midpoint the lastpoint and a random starting point*/
				int whichPoint = rand() % numPoints;
				cout << "Random point: " << whichPoint << endl;

				/*Make a new Rectangle Shape and add it to the points vector*/
				CircleShape newPoint;
				newPoint = getMidpoint(currentPoint.getPosition().x, currentPoint.getPosition().y, getX(points, whichPoint), getY(points, whichPoint), r);

				cout << "New point X: " << newPoint.getPosition().x << endl;
				cout << "New point y: " << newPoint.getPosition().y << endl;
				points.push_back(newPoint);
				//cout << "Size of points: " << points.size() << endl;
			}
		}

		window.display();

	}

	return 0;
}
