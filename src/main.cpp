#include "stm32f10x.h"
#include "core_cm3.h"
#include "stm32f1.h"

extern "C" {
void main();
}

void main() {

    using hwmodel::stm32f1::gpioARegs;
    using hwmodel::stm32f1::gpioERegs;
    using hwmodel::stm32f1::rccRegs;
    using namespace hwmodel::stm32f1::gpio;
    using namespace hwmodel::stm32f1::rcc;

    rccRegs->APB2ENR |= Apb2ClockRegion::GpioE;
    gpioERegs->CRL = createPinSetupLow<
            PinId::Px2,
            PinMode::Output2Mhz,
            PinConfig::GeneralPushPullOutput>();
    gpioERegs->ODR = PinId::Px2;
    gpioERegs->ODR = (PinId::Px2 | PinId::Px3);
    PinMask result = gpioERegs->IDR;
    gpioARegs->BSRR = toResetMask(PinId::Px0 | PinId::Px1) | toSetMask(PinId::Px2 | PinId::Px3);

    ///gpioARegs->ODR = PinId::Px0 | (PinId::Px1 | PinId::Px2);
    //    gpioARegs->ODR = PinId::Px0 | ~(PinId::Px1 | PinId::Px2);
    //
    //    constexpr SetResetMask foo = toResetMask(PinId::Px0 | PinId::Px2) | toSetMask(PinId::Px1 | PinId::Px3);
    //    gpioARegs->BSRR = foo;
    //    gpioARegs->BSRR = toResetMask(PinId::Px0 | PinId::Px2) | toSetMask(PinId::Px1 | PinId::Px3);
    //    gpioARegs->BSRR = SetResetId::ResetPx0;
    //    gpioARegs->BSRR = SetResetId::ResetPx0 | SetResetId::SetPx3;
    //
    //    rccRegs->AHBENR |= AhbClockRegion::Dma2;
    //    rccRegs->AHBENR |= AhbClockRegion::Dma1 | AhbClockRegion::Dma2;
    //    rccRegs->APB1ENR |= Apb1ClockRegion::Spi2 | Apb1ClockRegion::Spi3;
    //    rccRegs->APB1ENR.enableGates(Apb1ClockRegion::Spi2 | Apb1ClockRegion::Spi3);


    for (;;);
}
