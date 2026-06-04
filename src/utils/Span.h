#pragma once

#include <array>
#include <cstddef>
#include <type_traits>
#include <vector>

#if __cplusplus >= 202002L
#include <span>
#else
namespace std {
template <typename T>
class span {
public:
    using element_type = T;
    using value_type = std::remove_cv_t<T>;
    using size_type = std::size_t;
    using pointer = T*;
    using reference = T&;

    constexpr span() noexcept : data_(nullptr), size_(0) {}
    constexpr span(pointer data, size_type size) noexcept : data_(data), size_(size) {}

    template <size_t N>
    constexpr span(std::array<value_type, N>& data) noexcept
        : data_(data.data()), size_(N) {}

    template <size_t N>
    constexpr span(const std::array<value_type, N>& data) noexcept
        : data_(data.data()), size_(N) {}

    constexpr span(std::vector<value_type>& data) noexcept
        : data_(data.data()), size_(data.size()) {}

    constexpr span(const std::vector<value_type>& data) noexcept
        : data_(data.data()), size_(data.size()) {}

    constexpr pointer data() const noexcept { return data_; }
    constexpr size_type size() const noexcept { return size_; }
    constexpr bool empty() const noexcept { return size_ == 0; }
    constexpr pointer begin() const noexcept { return data_; }
    constexpr pointer end() const noexcept { return data_ + size_; }
    constexpr reference operator[](size_type index) const noexcept { return data_[index]; }

private:
    pointer data_;
    size_type size_;
};
} // namespace std
#endif
