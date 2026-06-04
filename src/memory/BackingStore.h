#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>

#include "utils/Span.h"

class BackingStore {
public:
    explicit BackingStore(const std::filesystem::path& path, size_t page_size);
    ~BackingStore();

    void load_page(uint32_t swap_offset, std::span<uint8_t> dest) const;

    void store_page(uint32_t swap_offset, std::span<const uint8_t> src);

private:
    mutable std::fstream file_;
    size_t page_size_;
};
