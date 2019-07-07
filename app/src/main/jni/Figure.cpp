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
    } else {
        return sf::Color::Black;
    }
}

float Figure::block_size{ 10.f };

Figure::Figure( FigureType type, int x_position ) {
    position = sf::Vector2i( x_position, 0 );
    if ( type == FigureType::I ) {
        pieces.push_back( sf::Vector2i( x_position - 1, 0 ) );
        pieces.push_back( sf::Vector2i( x_position, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 1, 0 ) );
        pieces.push_back( sf::Vector2i( x_position + 2, 0 ) );
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
bool Figure::touches_ceiling() {
    for ( auto &p : pieces ) {
        if ( p.y == 0 )
            return true;
    }
    return false;
}

void Figure::rotate_left( std::function<bool( const sf::Vector2i & )> collision_detector,
                          const sf::Vector2i &board_size ) {
    // rotate around position + (1, 1)

    // first test the impact
    std::list<sf::Vector2i> temp_pieces;
    for ( auto &p : pieces ) {
        sf::Vector2i new_p( p.y - position.y + position.x, -p.x + position.x + position.y + 1 );
        if ( new_p.x < 0 || new_p.x >= board_size.x || new_p.y < 0 || new_p.y >= board_size.y ||
             collision_detector( new_p ) ) {
            return; // abort rotation
        }
        temp_pieces.push_back( new_p );
    }

    pieces = temp_pieces;
}
void Figure::rotate_right( std::function<bool( const sf::Vector2i & )> collision_detector,
                           const sf::Vector2i &board_size ) {
    // rotate around position + (1, 1)

    // first test the impact
    std::list<sf::Vector2i> temp_pieces;
    for ( auto &p : pieces ) {
        sf::Vector2i new_p( -p.y + position.y + 1 + position.x, p.x - position.x + position.y );
        if ( new_p.x < 0 || new_p.x >= board_size.x || new_p.y < 0 || new_p.y >= board_size.y ||
             collision_detector( new_p ) ) {
            return; // abort rotation
        }
        temp_pieces.push_back( new_p );
    }

    pieces = temp_pieces;
}

void Figure::remove_row( int y ) {
    if ( position.y <= y )
        position.y++;

    pieces.remove_if( [&]( const sf::Vector2i &p ) { return p.y == y; } );
    for ( auto itr = pieces.begin(); itr != pieces.end(); itr++ ) {
        if ( itr->y < y )
            itr->y++;
    }
}

void Figure::set_transparency( int alpha ) {
    color.a = alpha;
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
