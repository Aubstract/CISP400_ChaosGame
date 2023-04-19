//Chaos game with Aubrey Fields and William Garica-Cortes
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace sf;
using namespace std;

RectangleShape getMidpoint(float x1, float y1, float x2, float y2)
{
	float x = (x1 + x2) / 2.0;
	float y = (y1 + y2) / 2.0;

	RectangleShape z;
	z.setSize(Vector2f(1, 1));
	z.setOutlineColor(Color::Red);
	z.setOutlineThickness(2);
	z.setPosition(x, y);

	return z;

}

double getX(vector <RectangleShape> lastPoint, int index)
{
	return lastPoint.at(index).getPosition().x;
}

double getY(vector <RectangleShape> lastPoint, int index)
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
	int numPoints = 0;
	RectangleShape currentPoint;
	RectangleShape point;
	currentPoint.setSize(Vector2f(1, 1));
	currentPoint.setOutlineColor(Color::White);
	currentPoint.setOutlineThickness(2);
	vector <RectangleShape> points;
	srand(time(0));
	bool stop = false;

	/*
	****************************************
	Set up the text
	****************************************
	*/

	Font font;
	if (!font.loadFromFile("fonts\\IMMORTAL.ttf"))
	{

	}
	Text text;

	text.setFont(font);

	text.setString("Please click any three points on the screen");

	text.setCharacterSize(24);

	text.setFillColor(Color::White);

	/*
	****************************************
	Set up the display
	****************************************
	*/

	VideoMode vm(1920, 1080);

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
					if (numPoints < 4)
					{
						numPoints++;
						cout << "The left mouse button was pressed" << endl;
						cout << "Mouse x: " << event.mouseButton.x << endl;
						cout << "Mouse y: " << event.mouseButton.y << endl;

						point.setSize(Vector2f(1, 1));
						point.setOutlineColor(Color::White);
						point.setOutlineThickness(2);
						point.setPosition(event.mouseButton.x, event.mouseButton.y);
						points.push_back(point);

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
			stop = true;
		}
		if (!stop && numPoints > 3)
		{

			/*Mark the starting position*/
			currentPoint.setPosition(getX(points, points.size() - 1), getY(points, points.size() - 1));


			/*Get the midpoint the lastpoint and a random starting point*/
			int whichPoint = rand() % 3;
			cout << whichPoint << endl;

			/*Make a new Rectangle Shape and add it to the points vector*/
			RectangleShape newPoint;
			newPoint = getMidpoint(currentPoint.getPosition().x, currentPoint.getPosition().y, getX(points, whichPoint), getY(points, whichPoint));

			cout << newPoint.getPosition().x << " " << newPoint.getPosition().y << endl;
			points.push_back(newPoint);
			cout << "Size of points: " << points.size() << endl;
		}

		window.display();

	}

	return 0;
}
