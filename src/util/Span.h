#pragma once

#include <cstddef>
#include <type_traits>

#if __cplusplus < 202002L
namespace std {
    constexpr std::size_t dynamic_extent = static_cast<std::size_t>(-1);

    template <typename T>
    class span {
    public:
        using element_type = T;
        using value_type = std::remove_cv_t<T>;
        using size_type = std::size_t;
        using pointer = T*;
        using reference = T&;

        constexpr span() noexcept : data_(nullptr), size_(0) {}
        constexpr span(pointer data, size_type size) : data_(data), size_(size) {}

        template <size_t N>
        constexpr span(T (&array)[N]) noexcept : data_(array), size_(N) {}

        constexpr pointer data() const noexcept { return data_; }
        constexpr size_type size() const noexcept { return size_; }
        constexpr pointer begin() const noexcept { return data_; }
        constexpr pointer end() const noexcept { return data_ + size_; }
        constexpr reference operator[](size_type index) const { return data_[index]; }

    private:
        pointer data_;
        size_type size_;
    };
} // namespace std
#else
#include <span>
#endif
