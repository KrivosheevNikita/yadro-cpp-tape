#ifndef TAPE_H
#define TAPE_H

#include <cstdint>

class ITape {
public:
    virtual ~ITape() = default;
    virtual bool read(int32_t& value) = 0;   
    virtual void write(int32_t value) = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    virtual void rewindToStart() = 0;
    virtual bool isEof() const = 0;
};

#endif