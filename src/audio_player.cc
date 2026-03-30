#define R13_PRIVATE_ACCESS

#include <miniaudio.h>
#include <r13priv/classes.h>

#include <string>

AudioPlayer::~AudioPlayer() {
    clear_queue();
    uninit_pending_sound(current_sound);

    if (engine != NULL) {
        ma_engine_uninit(engine.get());
        engine.reset();
    }

    if (resource_mgr != NULL) {
        ma_resource_manager_uninit(resource_mgr.get());
        resource_mgr.reset();
    }
}

bool AudioPlayer::load_file_queue(const std::string& path) {
    ma_result result = ensure_engine();
    if (result != MA_SUCCESS) {
        return false;
    }

    PendingSound queued_sound;
    if (!make_sound_from_resource_name(path, queued_sound, false)) {
        return false;
    }

    audio_queue.push(std::move(queued_sound));
    return true;
}

bool AudioPlayer::load_file(const std::string& path) {
    ma_result result = ensure_engine();
    if (result != MA_SUCCESS) {
        return false;
    }

    stop();
    uninit_pending_sound(current_sound);

    if (!make_sound_from_resource_name(path, current_sound, false)) {
        return false;
    }

    reset_playback_state();
    return true;
}

bool AudioPlayer::load_file_memory(const unsigned char* data, size_t len) {
    ma_result result = ensure_engine();
    if (result != MA_SUCCESS) {
        return false;
    }

    if (data == NULL || len == 0) {
        return false;
    }

    stop();
    uninit_pending_sound(current_sound);

    const std::string resource_name = "__r13_mem_" + std::to_string(++memory_resource_counter);
    result = ma_resource_manager_register_encoded_data(resource_mgr.get(), resource_name.c_str(), data, len);
    if (result != MA_SUCCESS) {
        return false;
    }

    if (!make_sound_from_resource_name(resource_name, current_sound, true)) {
        ma_resource_manager_unregister_data(resource_mgr.get(), resource_name.c_str());
        return false;
    }

    reset_playback_state();
    return true;
}

bool AudioPlayer::load_file_memory_queue(const unsigned char* data, size_t len) {
    ma_result result = ensure_engine();
    if (result != MA_SUCCESS) {
        return false;
    }

    if (data == NULL || len == 0) {
        return false;
    }

    const std::string resource_name = "__r13_mem_" + std::to_string(++memory_resource_counter);
    result = ma_resource_manager_register_encoded_data(resource_mgr.get(), resource_name.c_str(), data, len);
    if (result != MA_SUCCESS) {
        return false;
    }

    PendingSound queued_sound;
    if (!make_sound_from_resource_name(resource_name, queued_sound, true)) {
        ma_resource_manager_unregister_data(resource_mgr.get(), resource_name.c_str());
        return false;
    }

    audio_queue.push(std::move(queued_sound));
    return true;
}

void AudioPlayer::clear_queue() {
    while (!audio_queue.empty()) {
        uninit_pending_sound(audio_queue.front());
        audio_queue.pop();
    }
}

void AudioPlayer::skip_current() {
    stop();
    uninit_pending_sound(current_sound);
    reset_playback_state();

    if (!audio_queue.empty()) {
        current_sound = std::move(audio_queue.front());
        audio_queue.pop();
        ma_sound_start(current_sound.sound.get());
    }
}

void AudioPlayer::play() {
    if (current_sound.sound) {
        if (paused) {
            ma_sound_set_start_time_in_pcm_frames(current_sound.sound.get(), paused_frames);
            paused = false;
            paused_frames = 0;
        }
        ma_sound_start(current_sound.sound.get());
    }
}

void AudioPlayer::pause() {
    if (current_sound.sound) {
        paused_frames = ma_sound_get_time_in_pcm_frames(current_sound.sound.get());
        ma_sound_stop(current_sound.sound.get());
        paused = true;
    }
}

void AudioPlayer::stop() {
    if (current_sound.sound) {
        ma_sound_stop(current_sound.sound.get());
    }
}

void AudioPlayer::loop() {
    if (current_sound.sound) {
        ma_sound_set_looping(current_sound.sound.get(), true);
    }
}

void AudioPlayer::unloop() {
    if (current_sound.sound) {
        ma_sound_set_looping(current_sound.sound.get(), false);
    }
}

void AudioPlayer::set_volume(float volume) {
    if (current_sound.sound) {
        ma_sound_set_volume(current_sound.sound.get(), volume);
    }
}

ma_result AudioPlayer::ensure_engine() {
    if (resource_mgr == NULL) {
        resource_mgr = std::make_unique<ma_resource_manager>();

        ma_resource_manager_config resource_config = ma_resource_manager_config_init();
        ma_result result = ma_resource_manager_init(&resource_config, resource_mgr.get());
        if (result != MA_SUCCESS) {
            resource_mgr.reset();
            return result;
        }
    }

    if (engine == NULL) {
        engine = std::make_unique<ma_engine>();

        ma_engine_config engine_config = ma_engine_config_init();
        engine_config.pResourceManager = resource_mgr.get();
        ma_result result = ma_engine_init(&engine_config, engine.get());
        if (result != MA_SUCCESS) {
            engine.reset();
            return result;
        }
    }

    return MA_SUCCESS;
}

bool AudioPlayer::make_sound_from_resource_name(const std::string& resource_name, PendingSound& out_sound, bool is_memory) {
    auto sound = std::make_unique<ma_sound>();

    ma_result result = ma_sound_init_from_file(
        engine.get(),
        resource_name.c_str(),
        MA_SOUND_FLAG_STREAM,
        NULL,
        NULL,
        sound.get());
    if (result != MA_SUCCESS) {
        return false;
    }

    out_sound.sound = std::move(sound);
    out_sound.resource_name = resource_name;
    out_sound.is_memory = is_memory;
    return true;
}

void AudioPlayer::uninit_pending_sound(PendingSound& pending_sound) {
    if (pending_sound.sound) {
        ma_sound_uninit(pending_sound.sound.get());
        pending_sound.sound.reset();
    }

    if (pending_sound.is_memory && !pending_sound.resource_name.empty() && resource_mgr != NULL) {
        ma_resource_manager_unregister_data(resource_mgr.get(), pending_sound.resource_name.c_str());
    }

    pending_sound.resource_name.clear();
    pending_sound.is_memory = false;
}

void AudioPlayer::reset_playback_state() {
    paused = false;
    paused_frames = 0;
}
