//Chaos game by Aubrey Fields and William Garica-Cortes
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace sf;
using namespace std;

CircleShape getPosBetweenPoints(CircleShape current, CircleShape vertex, float ratio)
{
	float x1 = current.getPosition().x;
	float y1 = current.getPosition().y;

	float x2 = vertex.getPosition().x;
	float y2 = vertex.getPosition().y;

	float x3 = x1 + ((x2 - x1) * ratio);
	float y3 = y1 + ((y2 - y1) * ratio);

	CircleShape newPoint;
	newPoint.setPosition(x3, y3);

	return newPoint;
}

int main()
{
	/*
	****************************************
	Init values
	****************************************
	*/
	const int POINTS_PER_FRAME = 50;

	bool inputFinished = false;

	float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;

	float ratio;
	int numVertices = 0;
	int colorCounter = 0;
	int frameCounter = 0;

	CircleShape currentPoint;
	CircleShape point;
	vector <CircleShape> points;

	Color rainbow[6] = { Color::Red, Color::Yellow, Color::Green, Color::Cyan, Color::Blue, Color::Magenta };
	Color frameColor = rainbow[colorCounter];
	
	srand(time(0));

	
	/*
	****************************************
	Set up the text
	****************************************
	*/

	Font font;
	if (!font.loadFromFile("fonts/KOMIKAP_.ttf"))
	{
		cout << "couldnt find font..." << endl;
	}

	Text text;
	text.setFont(font);
	text.setString("- Left click to place vertices\n- Then right click to start the game.\n- Press Esc to quit.");
	text.setCharacterSize(20);
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

		while (window.pollEvent(event))
		{
			switch (event.type)
			{

			case Event::Closed:
				window.close();
				break;

			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left)
				{
					if (!inputFinished)
					{
						numVertices++;

						point.setRadius(1);
						point.setOutlineColor(frameColor);
						point.setFillColor(frameColor);
						point.setOutlineThickness(1);
						point.setPosition(event.mouseButton.x, event.mouseButton.y);
						points.push_back(point);
					}
				}
				else if (event.mouseButton.button == Mouse::Right)
				{
					if (!inputFinished)
					{
						inputFinished = true;
						ratio = static_cast<float>(numVertices) / (numVertices + 3);

						point.setRadius(1);
						point.setOutlineColor(frameColor);
						point.setFillColor(frameColor);
						point.setOutlineThickness(1);
						point.setPosition(event.mouseButton.x, event.mouseButton.y);
						points.push_back(point);	
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

		// Generate new points
		if (inputFinished)
		{
			for (int i = 0; i < POINTS_PER_FRAME; i++)
			{
				/*Current point is the most recently generated one*/
				currentPoint = points.back();

				/*Choose a random vertex (the initial points)*/
				int randInt = rand() % numVertices;
				CircleShape randVertex = points.at(randInt);

				/* Make a new Circleshape and calculate it's position between 
				the current point and the random vertex */
				CircleShape newPoint;
				newPoint = getPosBetweenPoints(currentPoint, randVertex, ratio);
				newPoint.setRadius(1);
				newPoint.setFillColor(frameColor);
				newPoint.setOutlineColor(frameColor);
				newPoint.setOutlineThickness(1);

				/* Add the new point to the points vector*/
				points.push_back(newPoint);
			}
		}

		// Update color
		if (frameCounter % 20 == 0)
		{
			frameColor = rainbow[colorCounter];
			colorCounter++;
			if (colorCounter >= 6)
			{
				colorCounter = 0;
			}

			for (unsigned int i = 0; i < points.size(); i++)
			{
				points.at(i).setFillColor(frameColor);
				points.at(i).setOutlineColor(frameColor);
			}
		}

		// Draw points
		for (unsigned int i = 0; i < points.size(); i++)
		{
			window.draw(points.at(i));
		}

		frameCounter++;
		window.display();
	}

	return 0;
}
