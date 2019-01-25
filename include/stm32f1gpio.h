#pragma once
#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace hwmodel {
namespace stm32f1 {
namespace gpio {

enum class PortId {
    GpioA, GpioB, GpioC, GpioD, GpioE, GpioF, GpioG
};

enum class PinId {
    Px0, Px1, Px2, Px3, Px4, Px5, Px6, Px7, Px8,
    Px9, Px10, Px11, Px12, Px13, Px14, Px15,
};

enum class SetResetId {
    SetPx0, SetPx1, SetPx2, SetPx3, SetPx4, SetPx5, SetPx6, SetPx7, SetPx8,
    SetPx9, SetPx10, SetPx11, SetPx12, SetPx13, SetPx14, SetPx15,
    ResetPx0, ResetPx1, ResetPx2, ResetPx3, ResetPx4, ResetPx5, ResetPx6, ResetPx7, ResetPx8,
    ResetPx9, ResetPx10, ResetPx11, ResetPx12, ResetPx13, ResetPx14, ResetPx15,
};

enum class PinMask {
    // PinMasks are created indirectly from PinId using logic operators
};

enum class PinConfig {
    Analog,
    FloatingInput,
    WeakInput,
    GeneralPushPullOutput,
    GeneralOpenDrainOutput,
    AltFuncPushPullOutput,
    AltFuncOpenDrainOutput
};

enum class PinConfigNumeric {
};

enum class PinMode {
    Input,
    Output10Mhz,
    Output2Mhz,
    Output50Mhz
};

enum class PinSetupLow {
    // via createPinSetupLow()
};

enum class PinSetupHigh {
    // via createPinSetupHigh()
};

template<PinConfig config>
constexpr PinConfigNumeric makeNumeric() {
    switch (config) {
        case PinConfig::Analog:
        case PinConfig::GeneralPushPullOutput:
            return static_cast<PinConfigNumeric> (0b00);
        case PinConfig::FloatingInput:
        case PinConfig::GeneralOpenDrainOutput:
            return static_cast<PinConfigNumeric> (0b01);
        case PinConfig::WeakInput:
        case PinConfig::AltFuncPushPullOutput:
            return static_cast<PinConfigNumeric> (0b10);
        case PinConfig::AltFuncOpenDrainOutput:
            return static_cast<PinConfigNumeric> (0b11);
    }
}

template<PinConfig config>
constexpr bool isOutput() {
    switch (config) {
        case PinConfig::Analog:
        case PinConfig::WeakInput:
        case PinConfig::FloatingInput:
            return false;
        case PinConfig::GeneralPushPullOutput:
        case PinConfig::GeneralOpenDrainOutput:
        case PinConfig::AltFuncPushPullOutput:
        case PinConfig::AltFuncOpenDrainOutput:
            return true;
    }
}

template<PinMode mode>
constexpr bool isOutput() {
    switch (mode) {
        case PinMode::Input:
            return false;
        case PinMode::Output10Mhz:
        case PinMode::Output2Mhz:
        case PinMode::Output50Mhz:
            return true;
    }
}

template<PinId pid, PinMode mode, PinConfig config>
constexpr PinSetupLow createPinSetupLow() {
    static_assert(static_cast<size_t> (pid) <= 7, "selected PinId is not part of the lower pin config register");
    static_assert(isOutput<mode>() == isOutput<config>(), "selected PinMode and PinConfig combination is illegal");
    return static_cast<PinSetupLow> (
            ((static_cast<uint32_t> (makeNumeric<config>()) << 2) |
            static_cast<uint32_t> (mode)) << (static_cast<size_t> (pid) * 4)
            );
}

template<PinId pid, PinMode mode, PinConfig config>
constexpr PinSetupHigh createPinSetupHigh() {
    static_assert(static_cast<size_t> (pid) > 7, "selected PinId is not part of the higher pin config register");
    static_assert(isOutput<mode>() == isOutput<config>(), "selected PinMode and PinConfig combination is illegal");
    return static_cast<PinSetupHigh> (
            ((static_cast<uint32_t> (makeNumeric<config>()) << 2) |
            static_cast<uint32_t> (mode)) << ((static_cast<size_t> (pid) - 8) * 4)
            );
}

constexpr PinSetupLow operator|(PinSetupLow lhs, PinSetupLow rhs) {
    return static_cast<PinSetupLow> (
            static_cast<uint32_t> (lhs) |
            static_cast<uint32_t> (rhs));
}

constexpr PinSetupHigh operator|(PinSetupHigh lhs, PinSetupHigh rhs) {
    return static_cast<PinSetupHigh> (
            static_cast<uint32_t> (lhs) |
            static_cast<uint32_t> (rhs));
}

constexpr PinMask operator|(PinMask lhs, PinMask rhs) {
    return static_cast<PinMask> (
            static_cast<uint16_t> (lhs) |
            static_cast<uint16_t> (rhs));
}

constexpr PinMask operator|(PinMask lhs, PinId rhs) {
    return static_cast<PinMask> (
            static_cast<size_t> (lhs) | (1 << static_cast<size_t> (rhs))
            );
}

constexpr PinMask operator|(PinId lhs, PinMask rhs) {
    return static_cast<PinMask> (
            (1 << static_cast<size_t> (lhs)) | static_cast<size_t> (rhs)
            );
}

constexpr PinMask operator|(PinId lhs, PinId rhs) {
    return static_cast<PinMask> (
            (1 << static_cast<size_t> (lhs)) | (1 << static_cast<size_t> (rhs))
            );
}

constexpr PinMask operator&(PinMask lhs, PinMask rhs) {
    return static_cast<PinMask> (
            static_cast<uint16_t> (lhs) &
            static_cast<uint16_t> (rhs));
}

constexpr PinMask operator&(PinMask lhs, PinId rhs) {
    return static_cast<PinMask> (
            static_cast<size_t> (lhs) & (1 << static_cast<size_t> (rhs))
            );
}

constexpr PinMask operator&(PinId lhs, PinMask rhs) {
    return static_cast<PinMask> (
            (1 << static_cast<size_t> (lhs)) & static_cast<size_t> (rhs)
            );
}

constexpr PinMask operator&(PinId lhs, PinId rhs) {
    return static_cast<PinMask> (
            (1 << static_cast<size_t> (lhs)) & (1 << static_cast<size_t> (rhs))
            );
}

constexpr PinMask operator~(PinMask pm) {
    return static_cast<PinMask> (~static_cast<uint16_t> (pm));
}

enum class SetResetMask {
    // SetResetPinMask are created indirectly from SetResetPinId using logic operators
};

constexpr SetResetMask operator|(SetResetMask lhs, SetResetMask rhs) {
    return static_cast<SetResetMask> (
            static_cast<uint16_t> (lhs) |
            static_cast<uint16_t> (rhs));
}

constexpr SetResetMask operator|(SetResetMask lhs, SetResetId rhs) {
    return static_cast<SetResetMask> (
            static_cast<size_t> (lhs) | (1 << static_cast<size_t> (rhs))
            );
}

constexpr SetResetMask operator|(SetResetId lhs, SetResetMask rhs) {
    return static_cast<SetResetMask> (
            (1 << static_cast<size_t> (lhs)) | static_cast<size_t> (rhs)
            );
}

constexpr SetResetMask operator|(SetResetId lhs, SetResetId rhs) {
    return static_cast<SetResetMask> (
            (1 << static_cast<size_t> (lhs)) | (1 << static_cast<size_t> (rhs))
            );
}

constexpr SetResetMask operator&(SetResetMask lhs, SetResetMask rhs) {
    return static_cast<SetResetMask> (
            static_cast<uint16_t> (lhs) &
            static_cast<uint16_t> (rhs));
}

constexpr SetResetMask operator&(SetResetMask lhs, SetResetId rhs) {
    return static_cast<SetResetMask> (
            static_cast<size_t> (lhs) & (1 << static_cast<size_t> (rhs))
            );
}

constexpr SetResetMask operator&(SetResetId lhs, SetResetMask rhs) {
    return static_cast<SetResetMask> (
            (1 << static_cast<size_t> (lhs)) & static_cast<size_t> (rhs)
            );
}

constexpr SetResetMask operator&(SetResetId lhs, SetResetId rhs) {
    return static_cast<SetResetMask> (
            (1 << static_cast<size_t> (lhs)) & (1 << static_cast<size_t> (rhs))
            );
}

constexpr SetResetMask toSetMask(PinMask pm) {
    return static_cast<SetResetMask> (pm);
}

constexpr SetResetMask toResetMask(PinMask pm) {
    return static_cast<SetResetMask> (static_cast<uint32_t> (pm) << 16);
}

class InputDataReg {
public:

    operator PinMask() {
        return static_cast<PinMask> (rawReg);
    }

private:
    volatile uint32_t rawReg;
};

class OutputDataReg {
public:

    OutputDataReg& operator=(PinId pid) {
        rawReg = (1 << static_cast<size_t> (pid));
        return *this;
    }

    OutputDataReg& operator=(PinMask pm) {
        rawReg = static_cast<uint32_t> (pm);
        return *this;
    }

private:
    volatile uint32_t rawReg;
};

class SetResetMaskReg {
public:

    SetResetMaskReg& operator=(gpio::SetResetId pid) {
        rawReg = (1 << static_cast<size_t> (pid));
        return *this;
    }

    SetResetMaskReg& operator=(gpio::SetResetMask pm) {
        rawReg = static_cast<uint32_t> (pm);
        return *this;
    }

private:
    volatile uint32_t rawReg;
};

class PortConfigLowReg {
public:

    PortConfigLowReg& operator=(PinSetupLow setup) {
        rawReg = static_cast<uint32_t> (setup);
        return *this;
    }

private:
    volatile uint32_t rawReg;
};

class PortConfigHighReg {
public:

    PortConfigHighReg& operator=(PinSetupHigh setup) {
        rawReg = static_cast<uint32_t> (setup);
        return *this;
    }

private:
    volatile uint32_t rawReg;
};

struct GpioRegs {
    PortConfigLowReg CRL;
    PortConfigHighReg CRH;
    InputDataReg IDR;
    OutputDataReg ODR;
    SetResetMaskReg BSRR;
    volatile uint32_t BRR; //TODO
    volatile uint32_t LCKR; //TODO
};

static_assert(std::is_pod<GpioRegs>::value, "please issue a bug report!");

namespace detail {

template<PortId port, PinId pin>
constexpr uint8_t idConstructor() {
    static_assert(static_cast<size_t> (port) < 16, "port id out of range");
    static_assert(static_cast<size_t> (pin) < 16, "pin out of range");
    return ((static_cast<uint8_t> (port) << 4) | static_cast<uint8_t> (pin));
}

}

//template<PortId port_>
//struct GpioPort {
//    static constexpr PortId id = port_;
//    static constexpr Dev_ptr<Foo> regs;
//};

template<PortId port_, PinId pin_>
struct Gpio {
    static constexpr PortId port = port_;
    static constexpr PinId pin = pin_;
    static constexpr uint8_t id = detail::idConstructor<port_, pin_>();
};

}
}
}
