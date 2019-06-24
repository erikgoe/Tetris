#include <cmath>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "math.h"
#include "Game.h"

int main( int argc, char* argv[] ) {
    sf::VideoMode screen( sf::VideoMode::getDesktopMode() );

    sf::RenderWindow window( screen, "", sf::Style::Fullscreen );
    window.setFramerateLimit( 30 );

    sf::View view = window.getDefaultView();

    bool active = true;

    // Game data
    Game game( sf::Vector2f( screen.width, screen.height ) );
    sf::Clock game_timer;

    while ( window.isOpen() ) {
        sf::Event event;

        while ( active ? window.pollEvent( event ) : window.waitEvent( event ) ) {
            switch ( event.type ) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if ( event.key.code == sf::Keyboard::Escape )
                    window.close();
                break;
            case sf::Event::Resized:
                view.setSize( event.size.width, event.size.height );
                view.setCenter( event.size.width / 2, event.size.height / 2 );
                window.setView( view );
                break;

            case sf::Event::MouseLeft:
                active = false;
                break;
            case sf::Event::MouseEntered:
                active = true;
                break;
            }
        }

        if ( game_timer.getElapsedTime().asSeconds() > 0.5f ) {
            game_timer.restart();
            game.next_step();
        }

        if ( active ) {
            window.clear( sf::Color( 127, 127, 127 ) );

            game.draw( window );

            window.display();
        } else {
            sf::sleep( sf::milliseconds( 100 ) );
        }
    }
}
