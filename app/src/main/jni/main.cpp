#include <cmath>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "math.h"
#include "Game.h"
#include "Tone.h"
#include "Melodies.h"

struct SoundManager {
    std::map<int, std::shared_ptr<Melody>> melodies;
    std::map<int, std::shared_ptr<sf::SoundBuffer>> buffers;

    void generate_level_music( float speed ) {
        if ( buffers.find( speed ) == buffers.end() ) {
            auto melody = std::make_shared<Melody>();
            melody->change_tone_generator( add_triangle_tone );
            create_basic_right_hand_melody( melody );
            buffers[speed] = melody->generate_melody( sf::seconds( speed * 2.f ), 44100 );
        }
    }
};

int main( int argc, char* argv[] ) {
#ifdef SFML_SYSTEM_ANDROID
    sf::VideoMode screen( sf::VideoMode::getDesktopMode() );
    auto window_style = sf::Style::Fullscreen;
#else
    sf::VideoMode screen( 450, 800 );
    auto window_style = sf::Style::Default;
#endif

    sf::RenderWindow window( screen, "Tetris", window_style );
    window.setFramerateLimit( 30 );

    sf::View view = window.getDefaultView();

    bool active = true;
    sf::Vector2f touch_begin;
    bool touch_moved = false;

    // Game data
    Game game( sf::Vector2f( screen.width, screen.height ) );
    sf::Clock game_timer;
    sf::Clock sound_timer;
    float elapsed_time = 0;
    float game_speed = 1.f; // seconds of a tick
    int level = 1;

    // Music
    SoundManager s_mgr;
    s_mgr.generate_level_music( game_speed );
    sf::Sound sound;

    sound.setBuffer( *s_mgr.buffers[game_speed] );
    sound.setLoop( true );
    sound.play();
    game_timer.restart();

    while ( window.isOpen() ) {
        sf::Event event;

        while ( active ? window.pollEvent( event ) : window.waitEvent( event ) ) {
            switch ( event.type ) {
            case sf::Event::Closed:
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

            // Touch control
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

            // Keyboard control
            case sf::Event::KeyPressed:
                if ( event.key.code == sf::Keyboard::Escape ) {
                    window.close();
                } else if ( event.key.code == sf::Keyboard::A ) {
                    game.move_figure( -1 );
                } else if ( event.key.code == sf::Keyboard::D ) {
                    game.move_figure( 1 );
                } else if ( event.key.code == sf::Keyboard::S ) {
                    game.pull_block_down();
                } else if ( event.key.code == sf::Keyboard::Q ) {
                    game.rotate_left();
                } else if ( event.key.code == sf::Keyboard::E ) {
                    game.rotate_right();
                }
                break;

            // Mouse Control
            case sf::Event::MouseButtonPressed:
                touch_begin = sf::Vector2f( event.mouseButton.x, event.mouseButton.y );
                break;
            case sf::Event::MouseButtonReleased:
                if ( !touch_moved )
                    game.touch( sf::Vector2f( event.mouseButton.x, event.mouseButton.y ) );
                touch_moved = false;
                touch_begin = sf::Vector2f();
                break;
            case sf::Event::MouseMoved:
                if ( touch_begin != sf::Vector2f() ) {
                    int delta = ( event.mouseMove.x - touch_begin.x ) / Figure::block_size;
                    game.move_figure( delta );
                    touch_begin.x += delta * Figure::block_size;
                    if ( delta != 0 )
                        touch_moved = true;
                }
                break;
            }
        }

        if ( active ) {
            elapsed_time += game_timer.restart().asSeconds();
            if ( elapsed_time > game_speed ) {
                elapsed_time -= game_speed;
                game.next_step();
            } else {
                game.micro_step();
            }

            // Select music
            if ( level != game.get_level() ) {
                float old_game_speed = game_speed;
                sf::Time old_offset = sound.getPlayingOffset();
                level = game.get_level();
                game_speed = std::pow( 0.9, level / 10 );
                
                s_mgr.generate_level_music( game_speed );
                sound.setBuffer( *s_mgr.buffers[game_speed] );
                sound.setPlayingOffset( old_offset );
                sound.play();
            }

            window.clear( sf::Color( 127, 127, 127 ) );

            game.draw( window );

            window.display();
        } else {
            sf::sleep( sf::milliseconds( 100 ) );
        }
    }
}
