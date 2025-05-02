#ifndef TAPEFILE_H
#define TAPEFILE_H

#include "Tape.h"
#include "Config.h"

#include <fstream>

class TapeFile : public ITape {
public:
    TapeFile(const std::string& path, std::ios::openmode mode, const DelaySettings& delays);

    ~TapeFile() override = default;

    bool  read(int32_t& value) override;
    void  write(int32_t  value) override;
    void  moveLeft()  override;      
    void  moveRight() override;      
    void  rewindToStart() override;
    bool  isEof() const override;

    void  flush();

private:
    void delay(const std::chrono::milliseconds& d) const;

    std::fstream  fs;  
    DelaySettings _delays;
};

#endif