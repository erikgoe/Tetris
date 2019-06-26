#include "Game.h"

Game::Game( sf::Vector2f screen_size ) {
    board = std::make_shared<Board>( board_size );
    Figure::block_size = ( screen_size.x ) / ( board_size.x + 2 );
    board_offset = sf::Vector2f( Figure::block_size, Figure::block_size * 2.f );
    spawn_x = board_size.x / 2 - 1;
}

void Game::create_new_figure() {
    rand.seed( std::random_device()() );
    std::uniform_int_distribution<int> distribution( 0, (int) FigureType::count - 1 );

    if ( next_figure == FigureType::count )
        next_figure = (FigureType) distribution( rand );

    current_figure = std::make_shared<Figure>( next_figure, spawn_x );
    next_figure = (FigureType) distribution( rand );
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
    }
}

void Game::next_step() {
    // If current exists now
    if ( current_figure ) {
        if ( board->is_on_solid( *current_figure ) ) {
            if ( current_figure->position.y == 0 ) {
                // restart the game
                board = std::make_shared<Board>( board_size );
                current_figure = nullptr;
            } else {
                // stop block
                board->add( *current_figure );
                current_figure = nullptr;
            }
        }
    }
    if ( current_figure ) {
        // Move current token down
        current_figure->move_down();
    }
    if ( !current_figure ) {
        create_new_figure();
        if(board->collides(*current_figure)) {
            // early collision => end game
            board = std::make_shared<Board>( board_size );
            current_figure = nullptr;
        }
    }
}

void Game::draw( sf::RenderTarget& target ) {
    // Game board
    board->draw( target, board_offset );
    if ( current_figure )
        current_figure->draw( target, board_offset );

    // Border
    sf::RectangleShape rect( sf::Vector2f( board_size ) * Figure::block_size );
    rect.setFillColor( sf::Color::Transparent );
    rect.setOutlineColor( sf::Color::White );
    rect.setOutlineThickness( 5 );
    rect.setPosition( board_offset );
    target.draw( rect );
}
