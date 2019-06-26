#pragma once

#include "Board.h"
#include <memory>
#include <random>

class Game {
    std::shared_ptr<Board> board;
    std::default_random_engine rand;

    std::shared_ptr<Figure> current_figure;
    FigureType next_figure = FigureType::count;

    sf::Vector2f screen_size;
    sf::Vector2i board_size = sf::Vector2i( 10, 15 );
    sf::Vector2f board_offset;
    float spawn_x;
    bool pull_block = false;

public:
    Game( const sf::Vector2f &screen_size );

    void create_new_figure();

    int get_current_figure_x_position();
    void move_figure( int block_delta );
    void next_step();
    /// Returns true if the micro step was accepted
    bool micro_step();
    void touch( const sf::Vector2f &position );

    void draw( sf::RenderTarget &target );
};