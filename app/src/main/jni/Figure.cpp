#include "Figure.h"

int sgn( int x ) {
    return ( x > 0 ) - ( x < 0 );
}

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
    position = sf::Vector2i( x_position, 0 );
    if ( type == FigureType::I ) {
        pieces.push_back( sf::Vector2i( x_position, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 2, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 3, 0 ) );
    } else if ( type == FigureType::J ) {
        pieces.push_back( sf::Vector2i( x_position, 0 ) );
        pieces.push_back( sf::Vector2i( x_position, 1 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 1 ) );
        pieces.push_back( sf::Vector2i( x_position + 2, 1 ) );
    } else if ( type == FigureType::L ) {
        pieces.push_back( sf::Vector2i( x_position + 2, 0 ) );
        pieces.push_back( sf::Vector2i( x_position, 1 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 1 ) );
        pieces.push_back( sf::Vector2i( x_position + 2, 1 ) );
    } else if ( type == FigureType::O ) {
        pieces.push_back( sf::Vector2i( x_position, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 0 ) );
        pieces.push_back( sf::Vector2i( x_position, 1 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 1 ) );
    } else if ( type == FigureType::S ) {
        pieces.push_back( sf::Vector2i( x_position + 1, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 2, 0 ) );
        pieces.push_back( sf::Vector2i( x_position, 1 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 1 ) );
    } else if ( type == FigureType::T ) {
        pieces.push_back( sf::Vector2i( x_position + 1, 0 ) );
        pieces.push_back( sf::Vector2i( x_position, 1 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 1 ) );
        pieces.push_back( sf::Vector2i( x_position + 2, 1 ) );
    } else if ( type == FigureType::Z ) {
        pieces.push_back( sf::Vector2i( x_position, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 1 ) );
        pieces.push_back( sf::Vector2i( x_position + 2, 1 ) );
    }
    color = get_figure_color( type );
}

void Figure::move_down() {
    for ( auto &p : pieces ) {
        p.y++;
    }
    position.y++;
}
void Figure::move_delta( int x_delta, int board_width,
                         std::function<bool( const sf::Vector2i & )> collision_detector ) {
    // Limit x_delta with collsision detection
    for ( auto &p : pieces ) {
        for ( int delta = 0; delta - x_delta != 0; ) {
            delta += sgn( x_delta );

            // limit delta by the borders
            if ( p.x + delta < 0 || p.x + delta >= board_width ) {
                x_delta = delta - sgn( x_delta );
                break;
            }

            // Already limit x_delta when a collision is detected
            if ( collision_detector( p + sf::Vector2i( delta, 0 ) ) ) {
                x_delta = delta - sgn( x_delta );
                break;
            }
        }
    }

    for ( auto &p : pieces ) {
        p.x += x_delta;
    }

    position.x += x_delta;
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
