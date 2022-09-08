#ifndef MfdModule_h
#define MfdModule_h

enum Mode : uint8_t
{
    Base = 0,
    Left = 1,
    Right = 2,
    Bottom = 3
};

enum State : bool
{
    Pressed = true,
    Released = false,
};

typedef struct JoyButtonMessage
{
    uint8_t mode;
    uint8_t button;
    uint8_t value;
};

#endif