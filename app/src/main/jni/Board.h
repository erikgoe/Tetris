#pragma once

#include "Figure.h"

class Board {
    std::list<Figure> figures;
    std::vector<std::vector<bool>> field; // first y then x

public:
    Board( const sf::Vector2i &size ) {
        field.resize( size.y );
        for ( auto &f : field ) {
            f.resize( size.x, false );
        }
    }

    bool is_on_solid( const Figure &figure );

    void add( const Figure &figure );

    void draw( sf::RenderTarget &target, const sf::Vector2f &board_offset );
};
