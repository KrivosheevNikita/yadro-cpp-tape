#ifndef CONFIG_H
#define CONFIG_H

#include <chrono>
#include <cstddef>
#include <filesystem>
#include <string>

class DelaySettings {
public:
    std::chrono::milliseconds readDelay{ 0 };
    std::chrono::milliseconds writeDelay{ 0 };
    std::chrono::milliseconds moveDelay{ 0 };
    std::chrono::milliseconds rewindDelay{ 0 };
};

class Config {
public:
    std::size_t memoryLimitBytes{ 1024 }; 
    DelaySettings delays{};
    std::filesystem::path tmpDir{ "tmp" };
    static Config load(const std::filesystem::path& path);
};

#endif