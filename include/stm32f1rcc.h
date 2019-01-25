#pragma once

namespace hwmodel {
namespace stm32f1 {
namespace rcc {

enum class AhbClockRegion {
    Dma1 = 0,
    Dma2 = 1,
    Sram = 2,
    Flitf = 4,
    Crc = 6,
    Fsmc = 8,
    Sdio = 10,
    UsbOtg = 12,
    EthMac = 14,
    EthMacTx = 15,
    EthMacRx = 16
};

enum class Apb1ClockRegion {
    Tim2 = 0,
    Tim3,
    Tim4,
    Tim5,
    Tim6,
    Tim7,
    Tim12,
    Tim13,
    Tim14,
    Wwdg = 11,
    Spi2 = 14,
    Spi3 = 15,
    Usart2 = 17,
    Usart3 = 18,
    Usart4 = 19,
    Usart5 = 20,
    I2c1 = 21,
    I2c2 = 22,
    Usb = 23,
    Can = 25,
    Bkp = 27,
    Pwr = 28,
    Dac = 29
};

enum class Apb2ClockRegion {
    Afio = 0,
    GpioA = 2,
    GpioB = 3,
    GpioC = 4,
    GpioD = 5,
    GpioE = 6,
    Adc1 = 9,
    Adc2 = 10,
    Tim1 = 11,
    Spi1 = 12,
    Usart1 = 14
};

enum class AhbClockRegionMask {
    // AhbClockRegionMask is created indirectly from AhbClockRegion using logic operators
};

enum class Apb1ClockRegionMask {
    // Apb1ClockRegionMask is created indirectly from Apb1ClockRegion using logic operators
};

enum class Apb2ClockRegionMask {
    // Apb2ClockRegionMask is created indirectly from Apb2ClockRegion using logic operators
};

constexpr AhbClockRegionMask operator|(AhbClockRegionMask lhs, AhbClockRegionMask rhs) {
    return static_cast<AhbClockRegionMask> (
            static_cast<uint32_t> (lhs) |
            static_cast<uint32_t> (rhs));
}

constexpr AhbClockRegionMask operator|(AhbClockRegionMask lhs, AhbClockRegion rhs) {
    return static_cast<AhbClockRegionMask> (
            static_cast<size_t> (lhs) | (1 << static_cast<size_t> (rhs))
            );
}

constexpr AhbClockRegionMask operator|(AhbClockRegion lhs, AhbClockRegionMask rhs) {
    return static_cast<AhbClockRegionMask> (
            (1 << static_cast<size_t> (lhs)) | static_cast<size_t> (rhs)
            );
}

constexpr AhbClockRegionMask operator|(AhbClockRegion lhs, AhbClockRegion rhs) {
    return static_cast<AhbClockRegionMask> (
            (1 << static_cast<size_t> (lhs)) | (1 << static_cast<size_t> (rhs))
            );
}

constexpr Apb1ClockRegionMask operator|(Apb1ClockRegionMask lhs, Apb1ClockRegionMask rhs) {
    return static_cast<Apb1ClockRegionMask> (
            static_cast<uint32_t> (lhs) |
            static_cast<uint32_t> (rhs));
}

constexpr Apb1ClockRegionMask operator|(Apb1ClockRegionMask lhs, Apb1ClockRegion rhs) {
    return static_cast<Apb1ClockRegionMask> (
            static_cast<size_t> (lhs) | (1 << static_cast<size_t> (rhs))
            );
}

constexpr Apb1ClockRegionMask operator|(Apb1ClockRegion lhs, Apb1ClockRegionMask rhs) {
    return static_cast<Apb1ClockRegionMask> (
            (1 << static_cast<size_t> (lhs)) | static_cast<size_t> (rhs)
            );
}

constexpr Apb1ClockRegionMask operator|(Apb1ClockRegion lhs, Apb1ClockRegion rhs) {
    return static_cast<Apb1ClockRegionMask> (
            (1 << static_cast<size_t> (lhs)) | (1 << static_cast<size_t> (rhs))
            );
}

constexpr Apb2ClockRegionMask operator|(Apb2ClockRegionMask lhs, Apb2ClockRegionMask rhs) {
    return static_cast<Apb2ClockRegionMask> (
            static_cast<uint32_t> (lhs) |
            static_cast<uint32_t> (rhs));
}

constexpr Apb2ClockRegionMask operator|(Apb2ClockRegionMask lhs, Apb2ClockRegion rhs) {
    return static_cast<Apb2ClockRegionMask> (
            static_cast<size_t> (lhs) | (1 << static_cast<size_t> (rhs))
            );
}

constexpr Apb2ClockRegionMask operator|(Apb2ClockRegion lhs, Apb2ClockRegionMask rhs) {
    return static_cast<Apb2ClockRegionMask> (
            (1 << static_cast<size_t> (lhs)) | static_cast<size_t> (rhs)
            );
}

constexpr Apb2ClockRegionMask operator|(Apb2ClockRegion lhs, Apb2ClockRegion rhs) {
    return static_cast<Apb2ClockRegionMask> (
            (1 << static_cast<size_t> (lhs)) | (1 << static_cast<size_t> (rhs))
            );
}

class AhbEnableReg {
public:

    AhbEnableReg& operator|=(AhbClockRegion region) {
        rawReg |= (1 << static_cast<size_t> (region));
        return *this;
    }

    AhbEnableReg& operator|=(AhbClockRegionMask regionMask) {
        rawReg |= static_cast<uint32_t> (regionMask);
        return *this;
    }

private:
    volatile uint32_t rawReg;
};

class Apb1EnableReg {
public:

    Apb1EnableReg& operator|=(Apb1ClockRegion region) {
        rawReg |= (1 << static_cast<size_t> (region));
        return *this;
    }

    Apb1EnableReg& operator|=(Apb1ClockRegionMask regionMask) {
        rawReg |= static_cast<uint32_t> (regionMask);
        return *this;
    }

    Apb1EnableReg& enableGates(Apb1ClockRegion region) {
        rawReg |= (1 << static_cast<size_t> (region));
        return *this;
    }

    Apb1EnableReg& enableGates(Apb1ClockRegionMask regionMask) {
        rawReg |= static_cast<uint32_t> (regionMask);
        return *this;
    }

private:
    volatile uint32_t rawReg;
};

class Apb2EnableReg {
public:

    Apb2EnableReg& operator|=(Apb2ClockRegion region) {
        rawReg |= (1 << static_cast<size_t> (region));
        return *this;
    }

    Apb2EnableReg& operator|=(Apb2ClockRegionMask regionMask) {
        rawReg |= static_cast<uint32_t> (regionMask);
        return *this;
    }

    Apb2EnableReg& enableGates(Apb2ClockRegion region) {
        rawReg |= (1 << static_cast<size_t> (region));
        return *this;
    }

    Apb2EnableReg& enableGates(Apb2ClockRegionMask regionMask) {
        rawReg |= static_cast<uint32_t> (regionMask);
        return *this;
    }

private:
    volatile uint32_t rawReg;
};

struct RccRegs {
    uint32_t CR;
    uint32_t CFGR;
    uint32_t CIR;
    uint32_t APB2RSTR;
    uint32_t APB1RSTR;
    AhbEnableReg AHBENR;
    Apb2EnableReg APB2ENR;
    Apb1EnableReg APB1ENR;
    uint32_t BDCR;
    uint32_t CSR;
    uint32_t RESERVED0;
    uint32_t CFGR2;
};

static_assert(std::is_pod<RccRegs>::value, "please issue a bug report!");

}
}
}
