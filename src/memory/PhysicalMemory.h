#pragma once

#include <cstddef>
#include <cstdint>
#include <deque>
#include <optional>
#include <vector>

#include "utils/Span.h"

class PhysicalMemory {
public:
    explicit PhysicalMemory(size_t num_frames, size_t frame_size);

    std::optional<uint32_t> allocate_frame();

    void free_frame(uint32_t frame);

    bool   has_free_frames() const noexcept;
    size_t frame_count() const noexcept;
    size_t frame_size() const noexcept;

    void read_frame(uint32_t frame, std::span<uint8_t> dest) const;

    void write_frame(uint32_t frame, std::span<const uint8_t> src);

private:
    size_t frame_size_;
    std::vector<uint8_t> memory_;
    std::deque<uint32_t> free_frames_;
};
