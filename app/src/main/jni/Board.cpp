#include "Board.h"

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
    figures.push_back( figure );
    for ( auto &p : figure.pieces ) {
        field[p.y][p.x] = true;
    }
}

void Board::draw( sf::RenderTarget &target, const sf::Vector2f &board_offset ) {
    for ( auto &f : figures ) {
        f.draw( target, board_offset );
    }
}
