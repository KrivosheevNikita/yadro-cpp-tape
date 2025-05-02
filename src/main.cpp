#include "Config.h"
#include "Sorter.h"
#include "TapeFile.h"
#include <filesystem>
#include <iostream>

int main(int argc, char** argv) 
{
    if (argc < 4) 
    {
        std::cerr << "Usage: " << argv[0] << " <config.json> <input.txt> <output.txt>\n";
        return 1;
    }
    try 
    {
        auto cfg = Config::load(argv[1]);
        std::filesystem::create_directories(cfg.tmpDir);
        auto inTape = std::make_unique<TapeFile>(argv[2], std::ios::in, cfg.delays);
        auto outTape = std::make_unique<TapeFile>(argv[3], std::ios::out | std::ios::trunc, cfg.delays);
        Sorter sorter(cfg);
        sorter.sort(std::move(inTape), std::move(outTape));
        std::cout << "Successfully sorted" << std::endl;
    }
    catch (const std::exception& ex) 
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}