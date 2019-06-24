#include "Figure.h"

sf::Color get_figure_color( FigureType type ) {
    if ( type == FigureType::I ) {
        return sf::Color::Cyan;
    } else if ( type == FigureType::J ) {
        return sf::Color::Blue;
    } else if ( type == FigureType::L ) {
        return sf::Color( 255, 165, 0 );
    } else if ( type == FigureType::O ) {
        return sf::Color::Yellow;
    } else if ( type == FigureType::S ) {
        return sf::Color::Green;
    } else if ( type == FigureType::T ) {
        return sf::Color::Magenta;
    } else if ( type == FigureType::Z ) {
        return sf::Color::Red;
    }
}

float Figure::block_size{ 10.f };

Figure::Figure( FigureType type, int x_position ) {
    if ( type == FigureType::I ) {
        pieces.push_back( sf::Vector2i( x_position, -1 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, -1 ) );
        pieces.push_back( sf::Vector2i( x_position + 2, -1 ) );
        pieces.push_back( sf::Vector2i( x_position + 3, -1 ) );
    } else if ( type == FigureType::J ) {
        pieces.push_back( sf::Vector2i( x_position, -1 ) );
        pieces.push_back( sf::Vector2i( x_position, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 2, 0 ) );
    } else if ( type == FigureType::L ) {
        pieces.push_back( sf::Vector2i( x_position + 2, -1 ) );
        pieces.push_back( sf::Vector2i( x_position, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 2, 0 ) );
    } else if ( type == FigureType::O ) {
        pieces.push_back( sf::Vector2i( x_position, -1 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, -1 ) );
        pieces.push_back( sf::Vector2i( x_position, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 0 ) );
    } else if ( type == FigureType::S ) {
        pieces.push_back( sf::Vector2i( x_position + 1, -1 ) );
        pieces.push_back( sf::Vector2i( x_position + 2, -1 ) );
        pieces.push_back( sf::Vector2i( x_position, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 0 ) );
    } else if ( type == FigureType::T ) {
        pieces.push_back( sf::Vector2i( x_position + 1, -1 ) );
        pieces.push_back( sf::Vector2i( x_position, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 2, 0 ) );
    } else if ( type == FigureType::Z ) {
        pieces.push_back( sf::Vector2i( x_position, -1 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, -1 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 2, 0 ) );
    }
    color = get_figure_color( type );
}

void Figure::move_down() {
    for ( auto &p : pieces ) {
        p.y++;
    }
}

void Figure::draw( sf::RenderTarget &target, const sf::Vector2f &board_offset ) {
    static float border_size = 3;
    sf::RectangleShape rect( sf::Vector2f( block_size - border_size * 2.f, block_size - border_size * 2.f ) );
    rect.setFillColor( color );
    rect.setOutlineColor( sf::Color( 127, 127, 127 ) );
    rect.setOutlineThickness( border_size );

    for ( auto &p : pieces ) {
        rect.setPosition( board_offset + sf::Vector2f( p ) * block_size );
        target.draw( rect );
    }
}
