#include "Game.h"

Game::Game( const sf::Vector2f& screen_size ) {
    board = std::make_shared<Board>( board_size );
    this->screen_size = screen_size;
    Figure::block_size = ( screen_size.x ) / ( board_size.x + 5 );
    board_offset = sf::Vector2f( Figure::block_size, Figure::block_size * 2.f );
    spawn_x = board_size.x / 2 - 1;
}

void Game::create_new_figure() {
    rand.seed( std::random_device()() );
    std::uniform_int_distribution<int> distribution( 0, (int) FigureType::count - 1 );

    if ( next_figure == nullptr )
        next_figure_type = (FigureType) distribution( rand );

    current_figure = std::make_shared<Figure>( next_figure_type, spawn_x );
    next_figure_type = (FigureType) distribution( rand );

    next_figure = std::make_shared<Figure>( next_figure_type, board_size.x + 1 );
    next_figure->move_down();
    next_figure->rotate_right( []( const sf::Vector2i& ) { return false; }, board_size + sf::Vector2i( 5, 0 ) );
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
            board = std::make_shared<Board>( board_size );
            current_figure = nullptr;
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
}
void Game::rotate_right() {
    if ( current_figure )
        current_figure->rotate_right( [&]( const sf::Vector2i& position ) { return board->is_occupied( position ); },
                                      board_size );
}

void Game::draw( sf::RenderTarget& target ) {
    // Game board
    board->draw( target, board_offset );
    if ( current_figure )
        current_figure->draw( target, board_offset );
    if ( next_figure )
        next_figure->draw( target, board_offset );

    // Border
    sf::RectangleShape rect( sf::Vector2f( board_size ) * Figure::block_size );
    rect.setFillColor( sf::Color::Transparent );
    rect.setOutlineColor( sf::Color::White );
    rect.setOutlineThickness( 5 );
    rect.setPosition( board_offset );
    target.draw( rect );

    // Button fields
    sf::VertexArray va( sf::PrimitiveType::Lines, 4 );
    va[0] =
        sf::Vertex( sf::Vector2f( screen_size.x * 2 / 5, board_offset.y + ( board_size.y + 1 ) * Figure::block_size ) );
    va[1] = sf::Vertex( sf::Vector2f( screen_size.x * 2 / 5, screen_size.y - Figure::block_size ) );
    va[2] =
        sf::Vertex( sf::Vector2f( screen_size.x * 3 / 5, board_offset.y + ( board_size.y + 1 ) * Figure::block_size ) );
    va[3] = sf::Vertex( sf::Vector2f( screen_size.x * 3 / 5, screen_size.y - Figure::block_size ) );

    target.draw( va );
}
