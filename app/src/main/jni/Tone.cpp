#include "Tone.h"
#include <memory>

float get_frequency( Note::Tones tone ) {
    if ( tone == Note::C3 )
        return 130.8128;
    else if ( tone == Note::D3 )
        return 146.8324;
    else if ( tone == Note::E3 )
        return 164.8138;
    else if ( tone == Note::F3 )
        return 174.6141;
    else if ( tone == Note::G3 )
        return 195.9977;
    else if ( tone == Note::Ab3 )
        return 207.6523;
    else if ( tone == Note::A3 )
        return 220.0000;
    else if ( tone == Note::B3 )
        return 246.9417;

    else if ( tone == Note::C4 )
        return 261.6256;
    else if ( tone == Note::D4 )
        return 293.6648;
    else if ( tone == Note::E4 )
        return 329.6276;
    else if ( tone == Note::F4 )
        return 349.2282;
    else if ( tone == Note::G4 )
        return 391.9954;
    else if ( tone == Note::Ab4 )
        return 415.3047;
    else if ( tone == Note::A4 )
        return 440.0000;
    else if ( tone == Note::Bb4 )
        return 466.1638;
    else if ( tone == Note::B4 )
        return 493.8833;

    else if ( tone == Note::C5 )
        return 523.2511;
    else if ( tone == Note::D5 )
        return 587.3295;
    else if ( tone == Note::E5 )
        return 659.2551;
    else if ( tone == Note::F5 )
        return 698.4565;
    else if ( tone == Note::G5 )
        return 783.9909;
    else if ( tone == Note::Ab5 )
        return 830.6094;
    else if ( tone == Note::A5 )
        return 880.0000;
    else if ( tone == Note::Bb5 )
        return 932.3275;
    else if ( tone == Note::B5 )
        return 987.7666;
    else
        return 1.;
}

void add_sawtooth_tone( std::vector<s16> &samples, size_t samples_offset, size_t sample_rate, float tone_frequency,
                        const sf::Time &duration, float volume ) {
    float period_length = static_cast<float>( sample_rate ) / tone_frequency;
    u64 slope = ( 2 << 14 ) / period_length;
    size_t sample_count = duration.asSeconds() * sample_rate;

    u64 curr_val = 2 << 14;
    for ( size_t i = samples_offset;
          i < samples.size() && ( i < sample_count + samples_offset ||
                                  std::abs( static_cast<s32>( curr_val % ( 2 << 15 ) ) - ( 2 << 14 ) ) > slope );
          i++ ) {
        samples[i] += ( static_cast<s32>( curr_val % ( 2 << 15 ) ) - ( 2 << 14 ) ) * volume;
        curr_val += slope;
    }
}

void add_square_tone( std::vector<s16> &samples, size_t samples_offset, size_t sample_rate, float tone_frequency,
                      const sf::Time &duration, float volume ) {
    u64 half_period_length = static_cast<float>( sample_rate ) / ( tone_frequency * 2 );
    size_t sample_count = duration.asSeconds() * sample_rate;

    for ( size_t i = samples_offset; i < samples.size() && i < sample_count + samples_offset; i++ ) {
        samples[i] += ( i / half_period_length % 2 ? ( 2 << 14 ) : -( 2 << 14 ) ) * volume;
    }
}

void add_triangle_tone( std::vector<s16> &samples, size_t samples_offset, size_t sample_rate, float tone_frequency,
                        const sf::Time &duration, float volume ) {
    float period_length = static_cast<float>( sample_rate ) / tone_frequency;
    s32 slope = ( 2 << 14 ) / period_length * 2;
    size_t sample_count = duration.asSeconds() * sample_rate;

    s32 curr_val = 0;
    for ( size_t i = samples_offset;
          i < samples.size() && ( i < sample_count + samples_offset || std::abs( curr_val ) > slope ); i++ ) {
        samples[i] += curr_val * volume;
        if ( std::abs( curr_val + slope ) > ( 2 << 14 ) )
            slope = -slope;
        curr_val += slope;
    }
}


std::shared_ptr<sf::SoundBuffer> Melody::generate_melody( const sf::Time &beat_duration, unsigned int sample_rate ) {
    // Calculate melody length
    float beat_duration_seconds = beat_duration.asSeconds();
    size_t max_beat_count = 0;
    for ( auto &line : note_lines ) {
        size_t beat_count = 0;
        float beat_frac = 0;
        for ( auto &note : line ) {
            beat_frac += note.beat_frac;
            while ( beat_frac > 1 ) {
                beat_count++;
                beat_frac -= 1;
            }
        }
        max_beat_count = std::max( beat_count + 1, max_beat_count );
    }
    size_t samples = max_beat_count * beat_duration_seconds * sample_rate;

    // Create empty buffer
    std::vector<s16> buffer( samples, 0 );

    // Translate notes
    auto generator = tone_generators.begin();
    for ( auto &line : note_lines ) {
        size_t samples_offset = 0;
        for ( auto &note : line ) {
            ( *generator )( buffer, samples_offset, sample_rate, get_frequency( note.tone ),
                            sf::seconds( beat_duration_seconds * note.beat_frac ), 0.2 );
            samples_offset += note.beat_frac * beat_duration_seconds * sample_rate;
        }
        generator++;
    }

    // Create sound
    auto sound_buffer = std::unique_ptr<sf::SoundBuffer>( new sf::SoundBuffer() );
    sound_buffer->loadFromSamples( &buffer[0], samples, 1, sample_rate );

    return sound_buffer;
}
