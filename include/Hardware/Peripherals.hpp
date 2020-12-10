
#include <fstream>
#include <string>
#include <termios.h>

class Serial{

public:

    Serial(const char* port);

    uint8_t Receive();
    void Send(uint8_t data);

private:

    uint8_t port;

};

class I2C{

public:

    I2C(uint8_t address);

    uint8_t Receive();
    void Send(uint8_t data);

private:

    uint8_t address;

};