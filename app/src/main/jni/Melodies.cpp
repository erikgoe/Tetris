#include "Melodies.h"

void create_basic_right_hand_melody( std::shared_ptr<Melody> &melody ) {
    for ( int i = 0; i < 2; i++ ) {
        melody->add_note( Note{ Note::E5, 1. / 4 } );
        melody->add_note( Note{ Note::B4, 1. / 8 } );
        melody->add_note( Note{ Note::C5, 1. / 8 } );
        melody->add_note( Note{ Note::D5, 1. / 4 } );
        melody->add_note( Note{ Note::C5, 1. / 8 } );
        melody->add_note( Note{ Note::B4, 1. / 8 } );
        melody->add_note( Note{ Note::A4, 1. / 4 } );
        melody->add_note( Note{ Note::A4, 1. / 8 } );
        melody->add_note( Note{ Note::C5, 1. / 8 } );
        melody->add_note( Note{ Note::E5, 1. / 4 } );
        melody->add_note( Note{ Note::D5, 1. / 8 } );
        melody->add_note( Note{ Note::C5, 1. / 8 } );
        melody->add_note( Note{ Note::B4, 3. / 8 } );
        // melody->add_note( Note{ Note::B4, 1. / 8 } );
        melody->add_note( Note{ Note::C5, 1. / 8 } );
        melody->add_note( Note{ Note::D5, 1. / 4 } );
        melody->add_note( Note{ Note::E5, 1. / 4 } );
        melody->add_note( Note{ Note::C5, 1. / 4 } );
        melody->add_note( Note{ Note::A4, 1. / 4 } );
        melody->add_note( Note{ Note::A4, 1. / 4 } );
        melody->add_note( Note{ Note::PAUSE, 1. / 4 } );

        melody->add_note( Note{ Note::PAUSE, 1. / 8 } );
        melody->add_note( Note{ Note::D5, 1. / 4 } );
        melody->add_note( Note{ Note::F5, 1. / 8 } );
        melody->add_note( Note{ Note::A5, 1. / 4 } );
        melody->add_note( Note{ Note::G5, 1. / 8 } );
        melody->add_note( Note{ Note::F5, 1. / 8 } );
        melody->add_note( Note{ Note::E5, 3. / 8 } );
        melody->add_note( Note{ Note::C5, 1. / 8 } );
        melody->add_note( Note{ Note::E5, 1. / 4 } );
        melody->add_note( Note{ Note::D5, 1. / 8 } );
        melody->add_note( Note{ Note::C5, 1. / 8 } );
        melody->add_note( Note{ Note::B4, 1. / 4 } );
        melody->add_note( Note{ Note::B4, 1. / 8 } );
        melody->add_note( Note{ Note::C5, 1. / 8 } );
        melody->add_note( Note{ Note::D5, 1. / 4 } );
        melody->add_note( Note{ Note::E5, 1. / 4 } );
        melody->add_note( Note{ Note::C5, 1. / 4 } );
        melody->add_note( Note{ Note::A4, 1. / 4 } );
        melody->add_note( Note{ Note::A4, 1. / 4 } );
        melody->add_note( Note{ Note::PAUSE, 1. / 4 } );
    }

    melody->add_note( Note{ Note::E5, 1. / 2 } );
    melody->add_note( Note{ Note::C5, 1. / 2 } );
    melody->add_note( Note{ Note::D5, 1. / 2 } );
    melody->add_note( Note{ Note::B4, 1. / 2 } );
    melody->add_note( Note{ Note::C5, 1. / 2 } );
    melody->add_note( Note{ Note::A4, 1. / 2 } );
    melody->add_note( Note{ Note::Ab4, 1. / 1 - 1. / 32 } );
    melody->add_note( Note{ Note::PAUSE, 1. / 32 } );
    melody->add_note( Note{ Note::E5, 1. / 2 } );
    melody->add_note( Note{ Note::C5, 1. / 2 } );
    melody->add_note( Note{ Note::D5, 1. / 2 } );
    melody->add_note( Note{ Note::B4, 1. / 2 } );
    melody->add_note( Note{ Note::C5, 1. / 4 } );
    melody->add_note( Note{ Note::E5, 1. / 4 } );
    melody->add_note( Note{ Note::A5, 1. / 2 } );
    melody->add_note( Note{ Note::Ab5, 3. / 4 } );
    melody->add_note( Note{ Note::PAUSE, 1. / 4 } );
}
