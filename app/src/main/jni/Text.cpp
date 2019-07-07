#include "Text.h"
#include "Figure.h"

const int CHAR_W = 3;
const int CHAR_H = 5;

BlockCharacter::BlockCharacter() {
    rects.resize( CHAR_W );
    for ( int x = 0; x < CHAR_W; x++ ) {
        rects[x].resize( CHAR_H );
        for ( int y = 0; y < CHAR_H; y++ ) {
            rects[x][y] = sf::RectangleShape();
        }
    }
}

void BlockCharacter::set_char( char c, float char_width, const sf::Vector2f &pos, const sf::Color &color ) {
    // Update rects
    float block_width = char_width / ( CHAR_W + 1 );
    for ( int x = 0; x < CHAR_W; x++ ) {
        for ( int y = 0; y < CHAR_H; y++ ) {
            rects[x][y].setPosition( pos + block_width * sf::Vector2f( x, y ) );
            rects[x][y].setSize( sf::Vector2f( block_width, block_width ) );
            rects[x][y].setFillColor( sf::Color::Transparent );
        }
    }

    // Define which rects to show
    auto set = [&]( int x, int y ) { rects[x][y].setFillColor( color ); };
    if ( c == '0' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == '1' ) {
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == '2' ) {
        set( 0, 0 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 2 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 4 );
    } else if ( c == '3' ) {
        set( 0, 0 );
        set( 0, 2 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 2 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == '4' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 1, 2 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == '5' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 2 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == '6' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 2 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == '7' ) {
        set( 0, 0 );
        set( 1, 0 );
        set( 1, 3 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
    } else if ( c == '8' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 2 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == '9' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 2 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == 'A' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 2 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == 'B' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 2 );
        set( 1, 4 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == 'C' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 4 );
    } else if ( c == 'D' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 4 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
    } else if ( c == 'E' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 2 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 2 );
        set( 2, 4 );
    } else if ( c == 'F' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 2 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 2 );
    } else if ( c == 'G' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 2 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 2 );
        set( 2, 3 );
    } else if ( c == 'H' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 2 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == 'I' ) {
        set( 1, 0 );
        set( 1, 2 );
        set( 1, 3 );
        set( 1, 4 );
    } else if ( c == 'J' ) {
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == 'K' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 2 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == 'L' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 4 );
        set( 2, 4 );
    } else if ( c == 'M' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 1 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == 'N' ) {
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 1 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == 'O' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == 'P' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 2 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
    } else if ( c == 'Q' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 1, 0 );
        set( 1, 2 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == 'R' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 2 );
        set( 1, 3 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 4 );
    } else if ( c == 'S' ) {
        set( 0, 1 );
        set( 0, 4 );
        set( 1, 0 );
        set( 1, 2 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 3 );
    } else if ( c == 'T' ) {
        set( 1, 0 );
        set( 1, 1 );
        set( 1, 2 );
        set( 1, 3 );
        set( 1, 4 );
        set( 0, 0 );
        set( 2, 0 );
    } else if ( c == 'U' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == 'V' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
    } else if ( c == 'W' ) {
        set( 0, 1 );
        set( 0, 2 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 3 );
        set( 2, 1 );
        set( 2, 2 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == 'X' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 3 );
        set( 0, 4 );
        set( 1, 2 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 3 );
        set( 2, 4 );
    } else if ( c == 'Y' ) {
        set( 0, 0 );
        set( 0, 1 );
        set( 0, 2 );
        set( 1, 3 );
        set( 1, 4 );
        set( 2, 0 );
        set( 2, 1 );
        set( 2, 2 );
    } else if ( c == 'Z' ) {
        set( 0, 0 );
        set( 0, 3 );
        set( 1, 0 );
        set( 1, 2 );
        set( 1, 4 );
        set( 2, 1 );
        set( 2, 4 );
    }
}

void BlockCharacter::draw( sf::RenderTarget &target ) {
    for ( auto &c : rects ) {
        for ( auto &r : c ) {
            target.draw( r );
        }
    }
}

void BlockText::set_text( const std::string &text, float width, const sf::Vector2f &pos ) {
    size_t char_count = text.size();
    float char_width = std::min( width / char_count, Figure::block_size );
    chars.resize( char_count );
    for ( size_t i = 0; i < char_count; i++ ) {
        chars[i].set_char( text[i], char_width, pos + sf::Vector2f( i, 0 ) * char_width, color );
    }
}
void BlockText::draw( sf::RenderTarget &target ) {
    for ( auto &c : chars ) {
        c.draw( target );
    }
}
