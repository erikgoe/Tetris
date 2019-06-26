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
    sf::Vector2f touch_begin;
    bool touch_moved = false;

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

            case sf::Event::TouchBegan:
                if ( event.touch.finger == 0 ) {
                    touch_begin = sf::Vector2f( event.touch.x, event.touch.y );
                }
                break;
            case sf::Event::TouchEnded:
                if ( event.touch.finger == 0 ) {
                    if ( !touch_moved )
                        game.touch( sf::Vector2f( event.touch.x, event.touch.y ) );
                    touch_moved = false;
                }
                break;
            case sf::Event::TouchMoved:
                if ( event.touch.finger == 0 ) {
                    int delta = ( event.touch.x - touch_begin.x ) / Figure::block_size;
                    game.move_figure( delta );
                    touch_begin.x += delta * Figure::block_size;
                    if ( delta != 0 )
                        touch_moved = true;
                }
                break;
            }
        }

        if ( active ) {
            if ( game_timer.getElapsedTime().asSeconds() > 1.5f ) {
                game_timer.restart();
                game.next_step();
            } else {
                if ( game.micro_step() )
                    game_timer.restart();
            }

            window.clear( sf::Color( 127, 127, 127 ) );

            game.draw( window );

            window.display();
        } else {
            sf::sleep( sf::milliseconds( 100 ) );
        }
    }
}
