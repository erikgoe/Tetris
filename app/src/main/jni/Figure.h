#pragma once

#include "SFML/Graphics.hpp"
#include <list>
#include <functional>

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

sf::Color get_figure_color( FigureType type );


struct Figure {
    static float block_size;

    std::list<sf::Vector2i> pieces;
    sf::Color color;
    sf::Vector2i position; // index position of the whole figure (top-left bounds)

    Figure( FigureType type, int x_position );

    void move_down();

    /// Moves the figure only when possible
    void move_delta( int x_delta, int board_width, std::function<bool( const sf::Vector2i & )> collision_detector );

    void draw( sf::RenderTarget &target, const sf::Vector2f &board_offset );
};
