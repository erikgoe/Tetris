#pragma once

#include "Board.h"
#include "Text.h"
#include <memory>
#include <random>

class Game {
    std::shared_ptr<Board> board;
    std::default_random_engine rand;

    std::shared_ptr<Figure> current_figure;
    FigureType next_figure_type = FigureType::count;
    std::shared_ptr<Figure> next_figure;
    std::shared_ptr<Figure> shadow_figure;

    sf::Vector2f text_pos;
    BlockText end_label;
    BlockText points_text;
    BlockText rows_text;
    BlockText level_text;
    BlockText points_label;
    BlockText rows_label;
    BlockText level_label;

    sf::Vector2f screen_size;
    sf::Vector2i board_size = sf::Vector2i( 10, 20 );
    sf::Vector2f board_offset;
    float spawn_x;
    bool pull_block = false;

    int points = 0;
    int level = 1;
    int cleared_rows = 0;

    int game_over_timer = 0;

    void create_new_figure();
    void update_shadow();
    void increase_points( int count );
    void restart_game();

public:
    Game( const sf::Vector2f &screen_size );

    int get_current_figure_x_position();

    void move_figure( int block_delta );
    void next_step(bool main_step = true);
    /// Returns true if the micro step was accepted
    bool micro_step();
    void touch( const sf::Vector2f &position );
    void pull_block_down();
    void rotate_left();
    void rotate_right();

    void draw( sf::RenderTarget &target );
};
