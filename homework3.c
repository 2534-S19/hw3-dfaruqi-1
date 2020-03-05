#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "homework3.h"
#include "myGPIO.h"
#include "myTimer.h"

int main(void)
{
    // Count variables to control the LEDs.
    unsigned int count0 = 0;
    unsigned int count1 = 0;

    // TODO: Declare the variables that main uses to interact with your state machine.
    unsigned char buttonhistory = 0;

    // Stops the Watchdog timer.
    initBoard();
    // Initialize the GPIO.
    // YOU MUST WRITE THIS FUNCTION IN myGPIO.c
    initGPIO();
    // Initialize Timer0 to provide a one second count interval for updating LED2.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER32_0_BASE, TIMER0_PRESCALER, TIMER0_COUNT);
    // Initialize Timer1 to provide a one millisecond count interval for updating the button history.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER32_1_BASE, TIMER1_PRESCALER, TIMER1_COUNT);

    while(1)
    {
        // Update the color of LED2 using count0 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
         changeLaunchpadLED2(count0);
        // Update the color of the Boosterpack LED using count1 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeBoosterpackLED(count1);

        // TODO: If Timer0 has expired, increment count0.
        // YOU MUST WRITE timer0expired IN myTimer.c
        unsigned int timer0Value = Timer32_getValue(TIMER0);
        if(timer0Expired()){
            count0++;
            Timer32_setCount(TIMER0, TIMER0_COUNT);
            Timer32_startTimer(TIMER32_0_BASE, true);
        }

        // TODO: If Timer1 has expired, update the button history from the pushbutton value.
        // YOU MUST WRITE timer1expired IN myTimer.c
        unsigned int timer1Value = Timer32_getValue(TIMER1);
        if(timer1Expired()){
            buttonhistory = buttonhistory << 1;
            if(checkStatus_BoosterpackS1()){
                buttonhistory |= (1 << 0);
            }
            else{
                buttonhistory &= ~(1 << 0);
            }
        }

        // TODO: Call the button state machine function to check for a completed, debounced button press.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        if(fsmBoosterpackButtonS1(buttonhistory)){
            count1++;
        }


        // TODO: If a completed, debounced button press has occurred, increment count1.



    }
}

void initBoard()
{
    WDT_A_hold(WDT_A_BASE);
}

// TODO: Map the value of a count variable to a color for LED2.
// Since count is an unsigned integer, you can mask the value in some way.
void changeLaunchpadLED2(unsigned int count)
{
    //red, green, yellow, blue, magenta, cyan, white, off
    if(count % 8 == 1){
        turnOn_LaunchpadLED2Red();
        turnOff_LaunchpadLED2Green();
        turnOff_LaunchpadLED2Blue();
    }
    else if(count % 8 == 2){
        turnOn_LaunchpadLED2Green();
        turnOff_LaunchpadLED2Blue();
        turnOff_LaunchpadLED2Red();
    }
    else if(count % 8 == 3){
        turnOn_LaunchpadLED2Green();
        turnOn_LaunchpadLED2Red();
        turnOff_LaunchpadLED2Blue();
    }
    else if(count % 8 == 4){
        turnOn_LaunchpadLED2Blue();
        turnOff_LaunchpadLED2Red();
        turnOff_LaunchpadLED2Green();
    }
    else if(count % 8 == 5){
        turnOn_LaunchpadLED2Red();
        turnOn_LaunchpadLED2Blue();
        turnOff_LaunchpadLED2Green();
    }
    else if(count % 8 == 6){
        turnOn_LaunchpadLED2Green();
        turnOn_LaunchpadLED2Blue();
        turnOff_LaunchpadLED2Red();
    }
    else if(count % 8 == 7){
        turnOn_LaunchpadLED2Red();
        turnOn_LaunchpadLED2Green();
        turnOn_LaunchpadLED2Blue();
    }
    else{
        turnOff_LaunchpadLED2Red();
        turnOff_LaunchpadLED2Green();
        turnOff_LaunchpadLED2Blue();
    }
}

// TODO: Maybe the value of a count variable to a color for the Boosterpack LED
// This is essentially a copy of the previous function, using a different LED
void changeBoosterpackLED(unsigned int count)
{
    //red, green, yellow, blue, magenta, cyan, white, off
    if(count % 8 == 1){
        turnOn_BoosterpackLEDRed();
        turnOff_BoosterpackLEDGreen();
        turnOff_BoosterpackLEDBlue();
    }
    else if(count % 8 == 2){
        turnOn_BoosterpackLEDGreen();
        turnOff_BoosterpackLEDBlue();
        turnOff_BoosterpackLEDRed();
    }
    else if(count % 8 == 3){
        turnOn_BoosterpackLEDGreen();
        turnOn_BoosterpackLEDRed();
        turnOff_BoosterpackLEDBlue();
    }
    else if(count % 8 == 4){
        turnOn_BoosterpackLEDBlue();
        turnOff_BoosterpackLEDRed();
        turnOff_BoosterpackLEDGreen();
    }
    else if(count % 8 == 5){
        turnOn_BoosterpackLEDRed();
        turnOn_BoosterpackLEDBlue();
        turnOff_BoosterpackLEDGreen();
    }
    else if(count % 8 == 6){
        turnOn_BoosterpackLEDGreen();
        turnOn_BoosterpackLEDBlue();
        turnOff_BoosterpackLEDRed();
    }
    else if(count % 8 == 7){
        turnOn_BoosterpackLEDRed();
        turnOn_BoosterpackLEDGreen();
        turnOn_BoosterpackLEDBlue();
    }
    else{
        turnOff_BoosterpackLEDRed();
        turnOff_BoosterpackLEDGreen();
        turnOff_BoosterpackLEDBlue();
    }
}

// TODO: Create a button state machine.
// The button state machine should return true or false to indicate a completed, debounced button press.
bool fsmBoosterpackButtonS1(unsigned char buttonhistory)
{
    bool pressed = false;

    if(buttonhistory == 0b10000000){
        pressed = true;
    }

    return pressed;
}
