#pragma once

#include <cstdint>

class IReplacement {
public:
    virtual ~IReplacement() = default;

    virtual void on_frame_access(uint32_t frame) = 0;

    virtual uint32_t select_victim() const = 0;

    virtual void on_frame_evict(uint32_t frame) = 0;

    virtual void register_frame(uint32_t frame) = 0;
};
