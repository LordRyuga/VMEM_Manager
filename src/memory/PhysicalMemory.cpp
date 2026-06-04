#include "memory/PhysicalMemory.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>

PhysicalMemory::PhysicalMemory(size_t num_frames, size_t frame_size)
    : frame_size_(frame_size),
      memory_(num_frames * frame_size),
      free_frames_() {
    for (size_t i = 0; i < num_frames; ++i) {
        free_frames_.push_back(static_cast<uint32_t>(i));
    }
}

std::optional<uint32_t> PhysicalMemory::allocate_frame() {
    if (free_frames_.empty()) {
        return std::nullopt;
    }

    uint32_t frame = free_frames_.front();
    free_frames_.pop_front();
    return frame;
}

void PhysicalMemory::free_frame(uint32_t frame) {
    auto existing = std::find(free_frames_.begin(), free_frames_.end(), frame);
    assert(existing == free_frames_.end());
    free_frames_.push_back(frame);
}

bool PhysicalMemory::has_free_frames() const noexcept {
    return !free_frames_.empty();
}

size_t PhysicalMemory::frame_count() const noexcept {
    if (frame_size_ == 0) {
        return 0;
    }
    return memory_.size() / frame_size_;
}

size_t PhysicalMemory::frame_size() const noexcept {
    return frame_size_;
}

void PhysicalMemory::read_frame(uint32_t frame, std::span<uint8_t> dest) const {
    if (frame >= frame_count()) {
        throw std::out_of_range("frame index out of range");
    }
    if (dest.size() < frame_size_) {
        throw std::invalid_argument("destination span too small");
    }

    size_t offset = static_cast<size_t>(frame) * frame_size_;
    std::copy_n(memory_.begin() + static_cast<std::ptrdiff_t>(offset),
                static_cast<std::ptrdiff_t>(frame_size_),
                dest.begin());
}

void PhysicalMemory::write_frame(uint32_t frame, std::span<const uint8_t> src) {
    if (frame >= frame_count()) {
        throw std::out_of_range("frame index out of range");
    }
    if (src.size() != frame_size_) {
        throw std::invalid_argument("source span must match frame size");
    }

    size_t offset = static_cast<size_t>(frame) * frame_size_;
    std::copy_n(src.begin(),
                static_cast<std::ptrdiff_t>(frame_size_),
                memory_.begin() + static_cast<std::ptrdiff_t>(offset));
}
