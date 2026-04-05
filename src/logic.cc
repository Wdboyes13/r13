#include <GLFW/glfw3.h>
#include <r13.h>
#include <cstdint>
#include <random>

uint64_t R13::get_delta_time() {
    const uint64_t current_time = glfwGetTime() * 1000;
    const uint64_t delta_time = current_time - frame_times.back();
    frame_times.push_back(current_time);
    return delta_time;
}

int64_t R13::get_random(int64_t min, int64_t max) {
    if (max == 0) {
        max = std::numeric_limits<int64_t>::max();
    }
    if (min == 0) {
        min = std::numeric_limits<int64_t>::min();
    }

    std::uniform_int_distribution<int64_t> dist(min, max);
    return dist(rng);
}

int R13::get_fps() {
    if (frame_times.size() < 2) {
        return 0;
    }

    const uint64_t current_time = glfwGetTime() * 1000;
    while (!frame_times.empty() && current_time - frame_times.front() > 1000) {
        frame_times.erase(frame_times.begin());
    }

    return static_cast<int>(frame_times.size());
}