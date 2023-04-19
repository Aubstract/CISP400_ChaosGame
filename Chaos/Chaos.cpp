//Chaos game by Aubrey Fields and William Garica-Cortes
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

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
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	Text text;
	//text.setPosition(width / 3, 0);
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
						numPoints++;

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
						ratio = static_cast<float>(numPoints) / (numPoints + 3);
						inputFinished = true;

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
		

		// TODO: Speed this up somehow??
		for (unsigned int i = 0; i < points.size(); i++)
		{
			window.draw(points.at(i));
		}

		if (inputFinished)
		{
			for (int i = 0; i < POINTS_PER_FRAME; i++)
			{
				/*Current point is the most recently generated one*/
				currentPoint = points.back();

				/*Choose a random vertex (the initial points)*/
				int randInt = rand() % numPoints;
				CircleShape randVertex = points.at(randInt);

				/* Make a new Circleshape and calculate it's position between 
				the current point and the random vertex */
				CircleShape newPoint;
				newPoint = getPosBetweenPoints(currentPoint, randVertex, ratio, frameColor);

				/* Add the new point to the points vector*/
				points.push_back(newPoint);
			}
		}

		frameCounter++;
		window.display();
	}

	return 0;
}
