#pragma once
#include "SFML/Graphics.hpp"
#include <list>

class BlockCharacter {
    std::vector<std::vector<sf::RectangleShape>> rects;

public:
    BlockCharacter();

    void set_char( char c, float char_width, const sf::Vector2f &pos );

    void draw( sf::RenderTarget &target );
};

class BlockText {
    std::vector<BlockCharacter> chars;

public:
    void set_text( const std::string &text, float width, const sf::Vector2f &pos );
    void draw( sf::RenderTarget &target );
};
