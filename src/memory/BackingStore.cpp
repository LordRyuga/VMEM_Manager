#include "memory/BackingStore.h"

#include <stdexcept>

BackingStore::BackingStore(const std::filesystem::path& path, size_t page_size)
    : file_(path, std::ios::in | std::ios::out | std::ios::binary),
      page_size_(page_size) {
    if (!file_.is_open()) {
        throw std::runtime_error("failed to open backing store: " + path.string());
    }
}

BackingStore::~BackingStore() {
    if (file_.is_open()) {
        file_.close();
    }
}

void BackingStore::load_page(uint32_t swap_offset, std::span<uint8_t> dest) const {
    if (dest.size() < page_size_) {
        throw std::invalid_argument("destination span too small");
    }

    std::streamoff offset = static_cast<std::streamoff>(swap_offset) *
                            static_cast<std::streamoff>(page_size_);
    file_.seekg(offset, std::ios::beg);
    if (!file_) {
        throw std::runtime_error("failed to seek backing store for read");
    }

    file_.read(reinterpret_cast<char*>(dest.data()), static_cast<std::streamsize>(page_size_));
    if (!file_) {
        throw std::runtime_error("failed to read backing store page");
    }
}

void BackingStore::store_page(uint32_t swap_offset, std::span<const uint8_t> src) {
    if (src.size() != page_size_) {
        throw std::invalid_argument("source span must match page size");
    }

    std::streamoff offset = static_cast<std::streamoff>(swap_offset) *
                            static_cast<std::streamoff>(page_size_);
    file_.seekp(offset, std::ios::beg);
    if (!file_) {
        throw std::runtime_error("failed to seek backing store for write");
    }

    file_.write(reinterpret_cast<const char*>(src.data()),
                static_cast<std::streamsize>(page_size_));
    if (!file_) {
        throw std::runtime_error("failed to write backing store page");
    }

    file_.flush();
}
