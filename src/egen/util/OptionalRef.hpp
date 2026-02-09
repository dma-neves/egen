#pragma once

namespace egen
{

template <typename T>
struct OptionalRef
{
    constexpr OptionalRef() noexcept : ptr_(nullptr) {}
    constexpr OptionalRef(T& ref) noexcept : ptr_(std::addressof(ref)) {}

    constexpr bool has_value() const noexcept { return ptr_ != nullptr; }
    constexpr explicit operator bool() const noexcept { return has_value(); }

    constexpr T& value() const {
        assert(ptr_);
        return *ptr_;
    }

    constexpr T& operator*() const { return value(); }
    constexpr T* operator->() const { return ptr_; }

    constexpr void reset() noexcept { ptr_ = nullptr; }

private:
    T* ptr_;
};

}