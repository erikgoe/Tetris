#pragma once

#include "Board.h"
#include <memory>
#include <random>

class Game {
    sf::Vector2i board_size = sf::Vector2i( 10, 15 );
    std::shared_ptr<Board> board;
    std::shared_ptr<Figure> current_figure;
    FigureType next_figure = FigureType::count;
    std::default_random_engine rand;

public:
    Game( sf::Vector2f screen_size );

    void create_new_figure();

    void next_step();

    void draw( sf::RenderTarget &target );
};
