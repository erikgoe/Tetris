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

    /// Moves the figure only when possible. Returns true when moved
    bool move_delta( int x_delta, int board_width, std::function<bool( const sf::Vector2i & )> collision_detector );

    /// Returns true when any block is in the first row
    bool touches_ceiling();

    /// Rotates only when possible
    void rotate_left( std::function<bool( const sf::Vector2i & )> collision_detector, const sf::Vector2i &board_size );
    /// Rotates only when possible
    void rotate_right( std::function<bool( const sf::Vector2i & )> collision_detector, const sf::Vector2i &board_size );

    /// Removes elements on this row and moves once above it
    void remove_row( int y );

    // set the alpha color value
    void set_transparency( int alpha );

    void draw( sf::RenderTarget &target, const sf::Vector2f &board_offset );
};
