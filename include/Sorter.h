#ifndef SORTER_H
#define SORTER_H

#include "Tape.h"
#include "Config.h"

#include <memory>
#include <filesystem>
#include <vector>

class Sorter {
public:
    Sorter(const Config& config);
    void sort(std::unique_ptr<ITape> input, std::unique_ptr<ITape> output);

private:
    void Initial(ITape* input, std::vector<std::filesystem::path>& runFiles);
    void merge(const std::vector<std::filesystem::path>& runFiles, ITape* output);
    const Config& _config;
};

#endif