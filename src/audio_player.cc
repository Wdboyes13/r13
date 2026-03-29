#include <miniaudio.h>
#include <r13.h>

bool AudioPlayer::load_file(const std::string& path) {
    ma_result result;

    if (engine == NULL) {
        engine = std::make_unique<ma_engine>();
        result = ma_engine_init(NULL, engine.get());
        if (result != MA_SUCCESS) {
            return false;
        }
    }

    if (sound != NULL) {
        ma_sound_uninit(sound.get());
        sound.reset();
    }

    sound = std::make_unique<ma_sound>();
    result = ma_sound_init_from_file(engine.get(), path.c_str(), 0, NULL, NULL, sound.get());
    if (result != MA_SUCCESS) {
        return false;
    }

    return true;
}

void AudioPlayer::play() {
    if (paused) {
        ma_sound_set_start_time_in_pcm_frames(
            sound.get(),
            paused_frames);
        paused = false;
        paused_frames = 0;
    }
    ma_sound_start(sound.get());
}

void AudioPlayer::pause() {
    paused_frames = ma_sound_get_time_in_pcm_frames(sound.get());
    ma_sound_stop(sound.get());
    paused = true;
}

void AudioPlayer::stop() {
    ma_sound_stop(sound.get());
}