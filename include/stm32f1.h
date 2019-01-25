#pragma once
#include "hwmodel.h"
#include "stm32f1gpio.h"
#include "stm32f1rcc.h"


namespace hwmodel {
namespace stm32f1 {

enum class DevId {
    Tim1, Tim8, //< advanced control timers
    Tim2, Tim3, Tim4, Tim5, // general purpose timers (group A)
    Tim9, Tim10, Tim11, Tim12, Tim13, Tim14, // general purpose timers (group B)
    Tim6, Tim7, // basic timers
    //Tim15, Tim16, Tim17 // not mentioned in reference manual, but in ST header
    Rtc, Wwdg, Iwdg,
    Spi1, Spi2, Spi3,
    Usart1, Usart2, Usart3, Uart4, Uart5,
    I2c1, I2c2,
    Can1, Can2,
    Bkp,
    Pwr,
    Dac,
    Cec,
    Afio, Exti,
    GpioA, GpioB, GpioC, GpioD, GpioE, GpioF, GpioG,
    Adc1, Adc2, Adc3,
    Sdio,
    Dma1, Dma2,
    Rcc,
    Crc,
    Flash,
    Eth,
    Fsmc,
    Dbgmcu,
    UsbFs,
    UsbOtg
};

constexpr intptr_t PeriphBase = 0x40000000;
constexpr intptr_t Apb2PeriphBase = PeriphBase + 0x10000;
constexpr intptr_t AhbPeriphBase = PeriphBase + 0x20000;

constexpr intptr_t GpioABase = Apb2PeriphBase + 0x0800;
constexpr intptr_t GpioBBase = Apb2PeriphBase + 0x0C00;
constexpr intptr_t GpioCBase = Apb2PeriphBase + 0x1000;
constexpr intptr_t GpioDBase = Apb2PeriphBase + 0x1400;
constexpr intptr_t GpioEBase = Apb2PeriphBase + 0x1800;

constexpr intptr_t RccBase = AhbPeriphBase + 0x1000;

constexpr Dev_ptr<gpio::GpioRegs> gpioARegs(GpioABase);
constexpr Dev_ptr<gpio::GpioRegs> gpioBRegs(GpioBBase);
constexpr Dev_ptr<gpio::GpioRegs> gpioCRegs(GpioCBase);
constexpr Dev_ptr<gpio::GpioRegs> gpioDRegs(GpioDBase);
constexpr Dev_ptr<gpio::GpioRegs> gpioERegs(GpioEBase);

constexpr Dev_ptr<rcc::RccRegs> rccRegs(RccBase);


}
}
