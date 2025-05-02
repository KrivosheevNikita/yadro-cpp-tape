#include "Sorter.h"

#include <algorithm>
#include <fstream>
#include <filesystem>
#include <stdexcept>

Sorter::Sorter(const Config& config) : _config(config) {}

void Sorter::sort(std::unique_ptr<ITape> input, std::unique_ptr<ITape> output)
{
    std::vector<std::filesystem::path> runs;
    Initial(input.get(), runs);
    merge(runs, output.get());

    for (auto& p : runs)
        std::filesystem::remove(p);
}

void Sorter::Initial(ITape* input, std::vector<std::filesystem::path>& runFiles)
{
    size_t B = _config.memoryLimitBytes / sizeof(int32_t);
    if (B == 0)
        throw std::runtime_error("Not enough memory");

    std::vector<int32_t> buf;
    buf.reserve(B);

    int32_t v;
    size_t idx = 0;

    while (input->read(v)) 
    {
        buf.push_back(v);

        if (buf.size() == B || input->isEof()) 
        {
            std::sort(buf.begin(), buf.end());

            auto path = _config.tmpDir / ("run_" + std::to_string(idx++));

            std::ofstream f(path);
            if (!f)
                throw std::runtime_error("Can't open file");

            for (auto x : buf)
                f << x << std::endl;
            f.close();

            buf.clear();
            runFiles.push_back(path);
        }
    }
}

void Sorter::merge(const std::vector<std::filesystem::path>& runFiles, ITape* output)
{
    struct Run {
        std::ifstream file;
        int32_t       val;
        bool          has = false;
    };

    std::vector<Run> runs;
    runs.reserve(runFiles.size());

    for (auto& p : runFiles) 
    {
        Run r;
        r.file.open(p);
        if (!r.file)
            throw std::runtime_error("Can't open file");
        if (r.file >> r.val)
            r.has = true;
        runs.push_back(std::move(r));
    }

    while (true) 
    {
        size_t minI = runs.size();
        for (size_t i = 0; i != runs.size(); ++i) 
        {
            if (runs[i].has &&
                (minI == runs.size() || runs[i].val < runs[minI].val))
            {
                minI = i;
            }
        }
        if (minI == runs.size())
            break; 

        output->write(runs[minI].val);

        if (runs[minI].file >> runs[minI].val)
            runs[minI].has = true;
        else
            runs[minI].has = false;
    }
}
