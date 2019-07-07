#pragma once

#include <memory>
#include "Tone.h"

std::shared_ptr<Melody> create_basic_right_hand_melody( const GeneratorFunction &generator = default_tone_generator );
