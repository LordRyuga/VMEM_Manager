#include "memory/BackingStore.h"

#include <stdexcept>

BackingStore::BackingStore(const std::filesystem::path& path, size_t page_size)
    : file_(), page_size_(page_size) {
    if (page_size_ == 0) {
        throw std::invalid_argument("page_size must be greater than zero");
    }
    file_.open(path, std::ios::in | std::ios::out | std::ios::binary);
    if (!file_.is_open()) {
        throw std::runtime_error("Failed to open backing store: " + path.string());
    }
}

BackingStore::~BackingStore() {
    if (file_.is_open()) {
        file_.close();
    }
}

void BackingStore::load_page(uint32_t swap_offset, std::span<uint8_t> dest) const {
    if (dest.size() < page_size_) {
        throw std::invalid_argument("destination span is too small");
    }
    std::streamoff position =
        static_cast<std::streamoff>(swap_offset) * static_cast<std::streamoff>(page_size_);
    file_.seekg(position, std::ios::beg);
    file_.read(reinterpret_cast<char*>(dest.data()), static_cast<std::streamsize>(page_size_));
    if (!file_) {
        throw std::runtime_error("Failed to read from backing store");
    }
}

void BackingStore::store_page(uint32_t swap_offset, std::span<const uint8_t> src) {
    if (src.size() != page_size_) {
        throw std::invalid_argument("source span size must match page size");
    }
    std::streamoff position =
        static_cast<std::streamoff>(swap_offset) * static_cast<std::streamoff>(page_size_);
    file_.seekp(position, std::ios::beg);
    file_.write(reinterpret_cast<const char*>(src.data()), static_cast<std::streamsize>(page_size_));
    file_.flush();
    if (!file_) {
        throw std::runtime_error("Failed to write to backing store");
    }
}
