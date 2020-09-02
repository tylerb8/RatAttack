#include "menu.hpp"
#include "game.hpp"
#include "instruct.hpp"
#include <iostream>

int main() {
	// Main window setup
	RenderWindow window(VideoMode(1000, 700), "Rat-Attack", Style::Default);

	Menu menu(window.getSize().x, window.getSize().y);
	Instruct instruct(window.getSize().x, window.getSize().y);
	Game game(&window);

	// While game window is still open
	while(window.isOpen()) {
		Event event;
		// while there are pending events...
		while(window.pollEvent(event)) {
			// move selected menu up
			if(event.type == Event::KeyPressed && event.key.code ==Keyboard::Up) 
				menu.moveUp();

			// move selected menu down
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Down) 
				menu.moveDown();

			// If selected Item was selected
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Return) {
				// Determine which was selected
				switch (menu.GetPressedItem()) {
					// PLAY
					case 0:
						std::cout << "Play was selected" << std::endl;
						// While game window is still open
						while(window.isOpen()) {
							// while there are pending events
							while(window.pollEvent(event)) {
								// if closed button was selected close window
								if(event.type == Event::Closed) 
									window.close();
								// if 'escape' button was selected close window
								if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) 
									window.close();
							}
							// Play game if none were selected
							game.Update();
							game.Draw();
						}
						break;
					
					// INSTRUCTIONS
					case 1:
						std::cout << "Instruction was selected" << std::endl;
						// While game window is still open
						while(window.isOpen()) {
							// while there are pending events
							while(window.pollEvent(event)) {
								// if closed button was selected close window
								if(event.type == Event::Closed) 
									window.close();
								// if 'escape' button was selected close window
								if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) 
									window.close();
								// If 'Enter' was selected
								if(event.type == Event::KeyPressed && event.key.code == Keyboard::Return) { 
									// While game window is still open
									while(window.isOpen()) {
										// while there are pending events
										while(window.pollEvent(event)) {
											// if closed button was selected close window
											if(event.type == Event::Closed) 
												window.close();
											// if 'escape' button was selected close window
											if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) 
												window.close();
										}
										// Play game if none were selected
										game.Update();
										game.Draw();
									}
								}
							}	
							// Display Instrutions if none were selected
							window.clear();
							instruct.draw(window);
							window.display();
						}
						break;

					// EXIT
					case 2:
						// Close window
						window.close();
						break;
				}
			// if closed button was selected close window
			if(event.type == Event::Closed) 
				window.close();
			}

			// Display Main Menu
			window.clear();
			menu.draw(window);
			window.display();
		}
	}
	return 0;
}
