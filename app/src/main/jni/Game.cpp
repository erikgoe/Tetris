#include "Game.h"

const int LEFT_PADDING = 3;

void Game::create_new_figure() {
    rand.seed( std::random_device()() );
    std::uniform_int_distribution<int> distribution( 0, (int) FigureType::count - 1 );

    if ( next_figure == nullptr )
        next_figure_type = (FigureType) distribution( rand );

    current_figure = std::make_shared<Figure>( next_figure_type, spawn_x );
    update_shadow();
    next_figure_type = (FigureType) distribution( rand );

    next_figure = std::make_shared<Figure>( next_figure_type, board_size.x + 1 );
    next_figure->move_down();
    next_figure->rotate_right( []( const sf::Vector2i& ) { return false; }, board_size + sf::Vector2i( 5, 0 ) );
}

void Game::update_shadow() {
    shadow_figure = std::make_shared<Figure>( *current_figure );

    while ( !board->is_on_solid( *shadow_figure ) ) {
        shadow_figure->move_down();
    }
    shadow_figure->set_transparency( 60 );
}
void Game::increase_points( int count ) {
    if ( count > 0 )
        points += std::pow( 1.8, count ) + std::log2( level + 1 ) * std::pow( count, 1.5 );
    cleared_rows += count;
    level = std::pow( static_cast<float>( cleared_rows ) / 3.f, 2 ) + 1;

    // Update Scoreboard
    float text_width = LEFT_PADDING * Figure::block_size;

    points_text.set_text( std::to_string( points ), text_width, text_pos + sf::Vector2f( 0, Figure::block_size * 1 ) );
    level_text.set_text( std::to_string( level ), text_width, text_pos + sf::Vector2f( 0, Figure::block_size * 4 ) );
    rows_text.set_text( std::to_string( cleared_rows ), text_width,
                        text_pos + sf::Vector2f( 0, Figure::block_size * 7 ) );
}
void Game::restart_game() {
    board = std::make_shared<Board>( board_size );
    current_figure = nullptr;
    points = 0;
    level = 1;
    cleared_rows = 0;
    increase_points( 0 ); // just initialize
}

Game::Game( const sf::Vector2f& screen_size ) {
    this->screen_size = screen_size;
    Figure::block_size = ( screen_size.x ) / ( board_size.x + 2 + LEFT_PADDING );
    board_offset = sf::Vector2f( Figure::block_size, Figure::block_size * 2.f );
    spawn_x = board_size.x / 2 - 1;


    text_pos = sf::Vector2f( board_size.x * Figure::block_size + board_offset.x * 1.5f,
                             board_offset.y * 1.5f + 4 * Figure::block_size );
    float text_width = LEFT_PADDING * Figure::block_size / 8;

    end_label.set_color( sf::Color::White );
    end_label.set_text( "GAME OVER", text_width * 30,
                        screen_size * 0.5f - sf::Vector2f( text_width * 10, Figure::block_size ) );
    points_label.set_text( "POINTS", text_width * 6, text_pos );
    level_label.set_text( "LEVEL", text_width * 5, text_pos + sf::Vector2f( 0, Figure::block_size * 3 ) );
    rows_label.set_text( "CLEARED", text_width * 7, text_pos + sf::Vector2f( 0, Figure::block_size * 6 ) );

    restart_game();
}

int Game::get_current_figure_x_position() {
    if ( current_figure )
        return current_figure->position.x;
    else
        return spawn_x;
}

void Game::move_figure( int block_delta ) {
    if ( current_figure ) {
        current_figure->move_delta( block_delta, board_size.x,
                                    [&]( const sf::Vector2i& position ) { return board->is_occupied( position ); } );
        update_shadow();
    }
}

void Game::next_step() {
    if ( game_over_timer == 1 ) {
        game_over_timer = 0;
        restart_game();
    } else if ( game_over_timer > 0 ) {
        game_over_timer--;
    } else {
        // If current exists now
        if ( current_figure ) {
            if ( board->is_on_solid( *current_figure ) ) {
                if ( current_figure->position.y == 0 ) {
                    game_over_timer = 3;
                } else {
                    // stop block
                    board->add( *current_figure, [&]( int row_count ) { increase_points( row_count ); } );
                    current_figure = nullptr;
                    pull_block = false;
                }
            }
        }
        if ( current_figure ) {
            // Move current token down
            current_figure->move_down();
        }
        if ( !current_figure ) {
            create_new_figure();
            if ( board->collides( *current_figure ) ) {
                // early collision => end game
                game_over_timer = 3;
            }
        }
    }
}
bool Game::micro_step() {
    if ( pull_block ) {
        next_step();
        return true;
    } else
        return false;
}

void Game::touch( const sf::Vector2f& position ) {
    if ( position.y > board_offset.y + board_size.y * Figure::block_size ) {
        int action = position.x * 5 / screen_size.x;
        if ( action <= 1 ) {
            rotate_left();
        } else if ( action >= 3 ) {
            rotate_right();
        } else {
            pull_block_down();
        }
    }
}
void Game::pull_block_down() {
    pull_block = true;
}
void Game::rotate_left() {
    if ( current_figure )
        current_figure->rotate_left( [&]( const sf::Vector2i& position ) { return board->is_occupied( position ); },
                                     board_size );
    update_shadow();
}
void Game::rotate_right() {
    if ( current_figure )
        current_figure->rotate_right( [&]( const sf::Vector2i& position ) { return board->is_occupied( position ); },
                                      board_size );
    update_shadow();
}

void Game::draw( sf::RenderTarget& target ) {
    // Game board
    board->draw( target, board_offset );
    if ( current_figure )
        current_figure->draw( target, board_offset );
    if ( shadow_figure )
        shadow_figure->draw( target, board_offset );

    // Border
    sf::RectangleShape rect( sf::Vector2f( board_size ) * Figure::block_size );
    rect.setFillColor( sf::Color::Transparent );
    rect.setOutlineColor( sf::Color::White );
    rect.setOutlineThickness( 5 );
    rect.setPosition( board_offset );
    target.draw( rect );

    // Left panel
    if ( next_figure )
        next_figure->draw( target, board_offset );
    points_text.draw( target );
    level_text.draw( target );
    rows_text.draw( target );
    points_label.draw( target );
    level_label.draw( target );
    rows_label.draw( target );

    // Button fields
    sf::VertexArray va( sf::PrimitiveType::Lines, 4 );
    va[0] =
        sf::Vertex( sf::Vector2f( screen_size.x * 2 / 5, board_offset.y + ( board_size.y + 1 ) * Figure::block_size ) );
    va[1] = sf::Vertex( sf::Vector2f( screen_size.x * 2 / 5, screen_size.y - Figure::block_size ) );
    va[2] =
        sf::Vertex( sf::Vector2f( screen_size.x * 3 / 5, board_offset.y + ( board_size.y + 1 ) * Figure::block_size ) );
    va[3] = sf::Vertex( sf::Vector2f( screen_size.x * 3 / 5, screen_size.y - Figure::block_size ) );

    // Game over
    if ( game_over_timer > 0 ) {
        end_label.draw( target );
    }

    target.draw( va );
}
