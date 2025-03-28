#include <iostream>
#include <SFML/Graphics.hpp>
#include "menu.h"


int main() {

        sf::RenderWindow window(sf::VideoMode(600, 600), "Game");
        Menu menu(window.getSize().x, window.getSize().y);
        


        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;
                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;
                    case sf::Keyboard::Enter:
                        switch (menu.GetPressedItem()) {
                        case 0:
                            std::cout << "PLAY button has been pressed\n";
                            break;
                        case 1:
                            std::cout << "Options button has been pressed\n";
                            break;
                        case 2:
                            window.close();
                            break;
                        }
                        break;
                    }
                }
            }

            window.clear();
        
            menu.draw(window);

            window.display();
        }

        return 0;
 }

