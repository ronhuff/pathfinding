

int main()
{

	SomeApplObj obj;

	sf::RenderWindow window(...);

	bool closed = false;

	while (!obj.IsDone() && !closed )
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				closed = true;
		}

		obj.Update();

		window.clear();

		obj.Render(window);

		window.display();

	}

	window.close();
}