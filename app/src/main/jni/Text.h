#pragma once
#include "SFML/Graphics.hpp"
#include <list>

class BlockCharacter {
    std::vector<std::vector<sf::RectangleShape>> rects;

public:
    BlockCharacter();

    void set_char( char c, float char_width, const sf::Vector2f &pos, const sf::Color &color );

    void draw( sf::RenderTarget &target );
};

class BlockText {
    std::vector<BlockCharacter> chars;
    sf::Color color;

public:
    void set_color( const sf::Color &color ) { this->color = color; }
    void set_text( const std::string &text, float width, const sf::Vector2f &pos );
    void draw( sf::RenderTarget &target );
};
