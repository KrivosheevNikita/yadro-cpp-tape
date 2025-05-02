#include "TapeFile.h"
#include <thread>
#include <stdexcept>

TapeFile::TapeFile(const std::string& path, std::ios::openmode mode, const DelaySettings& delays)
    : fs(path, mode), _delays(delays)
{
    if (!fs)
        throw std::runtime_error("Can't open file: " + path);

}

bool TapeFile::read(int32_t& value)
{
    delay(_delays.readDelay);
    return static_cast<bool>(fs >> value);  
}

void TapeFile::write(int32_t value)
{
    delay(_delays.writeDelay);
    fs << value << std::endl;  
}

void TapeFile::moveRight() 
{ 
    delay(_delays.moveDelay); 
}
void TapeFile::moveLeft() 
{ 
    delay(_delays.moveDelay); 
}

void TapeFile::rewindToStart()
{
    delay(_delays.rewindDelay);
    fs.clear();                        
    fs.seekg(0, std::ios::beg);
    fs.seekp(0, std::ios::beg);
}

bool TapeFile::isEof() const
{
    return fs.eof();
}

void TapeFile::flush() 
{ 
    fs.flush(); 
}

void TapeFile::delay(const std::chrono::milliseconds& d) const
{
    if (d.count() > 0)
        std::this_thread::sleep_for(d);
}
