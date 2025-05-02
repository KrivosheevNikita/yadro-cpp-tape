#include "Config.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

Config Config::load(const std::filesystem::path& path) {
    Config cfg;
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Cannot open config: " + path.string());
    json j; in >> j;
    cfg.memoryLimitBytes = j.value("memoryLimitBytes", cfg.memoryLimitBytes);
    auto d = j["delays"];
    cfg.delays.readDelay = std::chrono::milliseconds(d.value("read", 0));
    cfg.delays.writeDelay = std::chrono::milliseconds(d.value("write", 0));
    cfg.delays.moveDelay = std::chrono::milliseconds(d.value("move", 0));
    cfg.delays.rewindDelay = std::chrono::milliseconds(d.value("rewind", 0));
    cfg.tmpDir = j.value("tmpDir", cfg.tmpDir.string());
    return cfg;
}