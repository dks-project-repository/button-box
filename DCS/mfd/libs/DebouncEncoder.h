namespace CustomInputs {

class Encoder {
private:
  int8_t c;
  int8_t val;
  uint8_t _clk;
  uint8_t _data;
  uint8_t _position = 0;
  uint8_t prevNextCode = 0;
  uint16_t store = 0;
  void init(uint8_t clk, uint8_t data) {
    _clk = clk;
    _data = data;
    pinMode(_clk, INPUT);
    pinMode(_clk, INPUT_PULLUP);
    pinMode(_data, INPUT);
    pinMode(_data, INPUT_PULLUP);
  }

  // A vald CW or  CCW move returns 1, invalid returns 0.
  int8_t read_rotary() {
    static int8_t rot_enc_table[] = {0, 1, 1, 0, 1, 0, 0, 1,
                                     1, 0, 0, 1, 0, 1, 1, 0};

    prevNextCode <<= 2;
    if (digitalRead(_data))
      prevNextCode |= 0x02;
    if (digitalRead(_clk))
      prevNextCode |= 0x01;
    prevNextCode &= 0x0f;

    // If valid then store as 16 bit data.
    if (rot_enc_table[prevNextCode]) {
      store <<= 4;
      store |= prevNextCode;
      // if (store==0xd42b) return 1;
      // if (store==0xe817) return -1;
      if ((store & 0xff) == 0x2b)
        return -1;
      if ((store & 0xff) == 0x17)
        return 1;
    }
    return 0;
  }
  void tick() {
    if (val = read_rotary()) {
      c += val;
      Serial.print(c);
      Serial.print(" ");

      if (prevNextCode == 0x0b) {
        Serial.print("eleven ");
        Serial.println(store, HEX);
      }

      if (prevNextCode == 0x07) {
        Serial.print("seven ");
        Serial.println(store, HEX);
      }
    }
  }

public:
  Encoder(uint8_t clk, uint8_t data) { init(clk, data); };
  void rotary_tick() { tick(); }
};

} // namespace CustomInputs