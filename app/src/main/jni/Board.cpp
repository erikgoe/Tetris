#include "Board.h"

bool Board::is_full_row( int y ) {
    for ( auto v : field[y] ) {
        if ( !v )
            return false;
    }
    return true;
}

bool Board::remove_row( int y ) {
    // Remove from fields
    for ( int i = y; i > 0; i-- ) {
        field[i] = field[i - 1];
    }
    for ( int i = 0; i < field[0].size(); i++ ) {
        field[0][i] = false;
    }

    // Remove row from figures
    for ( auto &f : figures ) {
        f.remove_row( y );
    }
    figures.remove_if( []( const Figure &f ) { return f.pieces.empty(); } );
}

bool Board::is_on_solid( const Figure &figure ) {
    for ( auto &p : figure.pieces ) {
        if ( p.y + 1 >= field.size() || field[p.y + 1][p.x] ) {
            return true;
        }
    }
    return false;
}
bool Board::collides( const Figure &figure ) {
    for ( auto &p : figure.pieces ) {
        if ( p.y >= field.size() || field[p.y][p.x] ) {
            return true;
        }
    }
    return false;
}
bool Board::is_occupied( const sf::Vector2i &position ) {
    return field[position.y][position.x];
}

void Board::add( const Figure &figure ) {
    std::vector<int> rows_to_remove;

    figures.push_back( figure );
    for ( auto &p : figure.pieces ) {
        field[p.y][p.x] = true;

        if ( is_full_row( p.y ) ) {
            // remove row
            rows_to_remove.push_back( p.y );
        }
    }

    // Remove rows
    std::sort( rows_to_remove.begin(), rows_to_remove.end() );
    for ( auto &r : rows_to_remove ) {
        remove_row( r );
    }
}

void Board::draw( sf::RenderTarget &target, const sf::Vector2f &board_offset ) {
    for ( auto &f : figures ) {
        f.draw( target, board_offset );
    }
}
