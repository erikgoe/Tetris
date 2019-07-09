#pragma once
#include "Tone.h"
#include "Melodies.h"
#include <atomic>
#include <map>
#include <thread>
#include <iostream>

class SoundManager {
    std::map<float, std::shared_ptr<sf::SoundBuffer>> buffers;

    sf::Mutex mx;
    std::list<float> query;
    std::atomic_bool running;
    std::shared_ptr<sf::Thread> thread;

    void thread_routine() {
        while ( running ) {
            // Copy query
            std::list<float> local_query;
            {
                sf::Lock lock( mx );

                // Only query tasks which have not been executed earlier
                for ( auto q : query ) {
                    if ( buffers.find( q ) != buffers.end() ) {
                        query.remove( q );
                    }
                }

                if ( !query.empty() ) {
                    local_query = query;
                }
            }

            // Generate music
            for ( auto &q : local_query ) {
                std::cout << "Creating level\n";
                generate_level_music( q );
            }

            // Empty query
            {
                sf::Lock lock( mx );
                for ( size_t i = 0; i < local_query.size(); i++ ) {
                    query.pop_front();
                }
            }

            sf::sleep( sf::milliseconds( 100 ) );
        }
    }


    void generate_level_music( float speed ) {
        auto melody = std::make_shared<Melody>();
        melody->change_tone_generator( add_triangle_tone );
        create_basic_right_hand_melody( melody );

        auto b = melody->generate_melody( sf::seconds( speed * 2.f ), 44100 );

        sf::Lock lock( mx );
        buffers[speed] = b;
    }

public:
    SoundManager() {
        running = true;
        thread = std::make_shared<sf::Thread>( &SoundManager::thread_routine, this );
        thread->launch();
    }
    ~SoundManager() {
        running = false;
        thread->wait();
    }

    void query_level( float speed ) {
        sf::Lock lock( mx );
        query.push_back( speed );
    }

    std::shared_ptr<sf::SoundBuffer> get_level_music( float speed ) {
        bool found = false;
        // TODO busy waiting
        while ( true ) {
            {
                sf::Lock lock( mx );
                if ( buffers.find( speed ) != buffers.end() ) {
                    return buffers[speed];
                } else if ( !found ) {
                    // Was not created before
                    for ( auto &q : query ) {
                        if ( q == speed )
                            found = true;
                    }
                    if ( !found ) {
                        query_level( speed );
                    }
                }
            }
            std::this_thread::yield();
        }
    }
};
