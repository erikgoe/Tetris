#include "Game.h"

Game::Game( sf::Vector2f screen_size ) {
    board = std::make_shared<Board>( board_size );
    Figure::block_size = ( screen_size.x ) / ( board_size.x + 2 );
}

void Game::create_new_figure() {
    rand.seed( std::random_device()() );
    std::uniform_int_distribution<int> distribution( 0, (int) FigureType::count - 1 );

    if ( next_figure == FigureType::count )
        next_figure = (FigureType) distribution( rand );

    current_figure = std::make_shared<Figure>( next_figure, board_size.x / 2 - 1 );
    next_figure = (FigureType) distribution( rand );
}

void Game::next_step() {
    if ( !current_figure ) {
        create_new_figure();
        if ( board->contains( *current_figure ) ) {
            // restart game
            board = std::make_shared<Board>( board_size );
            current_figure = nullptr;
        }
    } else {
        // Move current token down
        current_figure->move_down();

        bool stop_figure = false;

        if ( board->contains( *current_figure ) ) {
            // stop block
            board->add( *current_figure );
            current_figure = nullptr;
        }
    }
}

void Game::draw( sf::RenderTarget &target ) {
    sf::Vector2f board_offset( Figure::block_size, 96 );

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
