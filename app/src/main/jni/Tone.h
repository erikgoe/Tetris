#pragma once

#include "SFML/Audio.hpp"
#include <list>
#include <functional>
#include <memory>

using s16 = sf::Int16;
using s32 = sf::Int32;
using u64 = sf::Uint64;

/// Add a new tone in sawtooth form to an existing sound buffer.
void add_sawtooth_tone( std::vector<s16> &samples, size_t samples_offset, size_t sample_rate, float tone_frequency,
                        const sf::Time &duration, float volume );

/// Add a new tone in square form to an existing sound buffer.
void add_square_tone( std::vector<s16> &samples, size_t samples_offset, size_t sample_rate, float tone_frequency,
                      const sf::Time &duration, float volume );

/// Add a new tone in triangle form to an existing sound buffer.
void add_triangle_tone( std::vector<s16> &samples, size_t samples_offset, size_t sample_rate, float tone_frequency,
                        const sf::Time &duration, float volume );

// Represents a simple note
struct Note {
    enum Tones {
        PAUSE,

        C3,
        D3,
        E3,
        F3,
        G3,
        Ab3,
        A3,
        B3,

        C4,
        D4,
        E4,
        F4,
        G4,
        Ab4,
        A4,
        Bb4,
        B4,

        C5,
        D5,
        E5,
        F5,
        G5,
        Ab5,
        A5,
        Bb5,
        B5,

    } tone;

    float beat_frac; // time fraction of a whole beat
};

using GeneratorFunction = std::function<void( std::vector<s16> &, size_t, size_t, float, const sf::Time &, float )>;
const GeneratorFunction default_tone_generator = add_sawtooth_tone;

/// Represents a melody with multiple lines of notes
class Melody {
    std::list<std::vector<Note>> note_lines; // multiple lines of notes
    std::list<GeneratorFunction> tone_generators;

public:
    Melody( size_t estimated_note_count = 16 ) { next_line( estimated_note_count ); }

    void add_note( const Note &note ) { note_lines.back().push_back( note ); }

    void next_line( size_t estimated_note_count = 16 ) {
        note_lines.push_back( std::vector<Note>() );
        note_lines.back().reserve( estimated_note_count );
        tone_generators.push_back( default_tone_generator );
    }

    void change_tone_generator( const GeneratorFunction &generator ) { tone_generators.back() = generator; }

    std::shared_ptr<sf::SoundBuffer> generate_melody( const sf::Time &beat_duration, unsigned int sample_rate );
};
