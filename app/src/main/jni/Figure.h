#pragma once

#include "SFML/Graphics.hpp"
#include <list>


enum class FigureType {
    I,
    J,
    L,
    O,
    S,
    T,
    Z,

    count
};

sf::Color get_figure_color(FigureType type);


struct Figure {
    static float block_size;

    std::list<sf::Vector2i> pieces;
    sf::Color color;

    Figure( FigureType type, int x_position );

    void move_down();

    void draw( sf::RenderTarget &target, const sf::Vector2f &board_offset );
};
