#pragma once

class NonCopyable {
public:
    NonCopyable() = default;
    ~NonCopyable() = default;

protected:
    NonCopyable(const NonCopyable&) = delete;
    const NonCopyable& operator=(const NonCopyable&) = delete;
};