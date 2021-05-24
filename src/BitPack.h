/*
    BitPack - библиотека для упаковки битовых флагов в байтовый массив (экономия места)
    Документация: 
    GitHub: https://github.com/GyverLibs/BitPack
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.0 - релиз
*/

#ifndef BitPack_h
#define BitPack_h

template <uint8_t AMOUNT>
class BitPack {
public:
    BitPack() {
        clearAll();
    }
    void set(uint8_t num) {
        bitSet(pack[(num) >> 3], (num) & 0b111);
    }
    void clear(uint8_t num) {
        bitClear(pack[(num) >> 3], (num) & 0b111);
    }
    void toggle(uint8_t num) {
        read(num) ? clear(num) : set(num);
    }
    void write(uint8_t num, bool state) {
        state ? set(num) : clear(num);
    }
    bool read(uint8_t num) {
        return bitRead(pack[(num) >> 3], (num) & 0b111);
    }
    void setAll() {
        memset(pack, 255, sizeof(pack));
    }
    void clearAll() {
        memset(pack, 0, sizeof(pack));
    }
    uint8_t operator[] (uint8_t num) const {
        return read(num);
    }
    uint8_t& operator [] (uint8_t num) {
        buf = (num) & 0b111;
        return pack[(num) >> 3];
    }
    BitPack& operator = (bool val) {
        val ? bitSet(*this, buf) : bitClear(*this, buf);
    }

private:
    uint8_t pack[(AMOUNT + 8 - 1) >> 3];
    uint8_t buf;
};
#endif
