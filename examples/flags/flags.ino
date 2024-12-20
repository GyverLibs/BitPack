#include <Arduino.h>
#include <BitFlags.h>

#define MY_FLAG_0 bit(0)
#define KEK_FLAG bit(1)
#define SOME_F bit(2)

enum class Flags {
    f1 = bit(0),
    f2 = bit(1),
    f3 = bit(2),
};

void setup() {
    Serial.begin(115200);
    {
        BitFlags8 f;
        f.set(Flags::f1);
        f.set(Flags::f2);

        Serial.println(f.read(Flags::f1));
        Serial.println(f.read(Flags::f2));
        Serial.println(f.read(Flags::f3));
    }
    {
        BitFlags8 flags;
        flags.set(KEK_FLAG | SOME_F);                    // установить два флага
        Serial.println(flags.read(KEK_FLAG | SOME_F));   // стоит один из флагов
        Serial.println(flags.isSet(KEK_FLAG | SOME_F));  // стоят все флаги

        // операция compare берёт маску по первому аргументу и сравнивает со вторым
        // фактически смысл такой: определение ситуации, когда из указанных флагов подняты только определённые
        // здесь - из флагов KEK_FLAG и SOME_F поднят только SOME_F (KEK_FLAG опущен)
        Serial.println(flags.compare(KEK_FLAG | SOME_F, SOME_F));
    }
}

void loop() {
}