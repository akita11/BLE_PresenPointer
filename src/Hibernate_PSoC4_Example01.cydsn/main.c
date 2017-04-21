/*******************************************************************************
* File: main.c
*
* Version: 2.0
*
* Description:
*  This is the source code for the Power Management API example, which is
*  part of the cy_boot component. This project demonstrates the Hibernate low
*  power mode for PSoC 4 devices.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/
#include <project.h>
#include <cyPm.h>

#define LIGHT_OFF                       (1u)
#define LIGHT_ON                        (0u)

/* Interrupt prototypes */
CY_ISR_PROTO(GPIOIsrHandler);

/* Puts variable in memory section which is retained in low power modes */
CY_NOINIT uint32 hibernateCnt;


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  The main function performs the following functions:
*   1. Enable global interrupts
*   2. Turns LED on to indicate the active mode.
*   3. Makes a delay of 1000 ms is made for LED visibility.
*   4. Blinks LED for 1000 ms for each even value of the hibernate counter.
*   5. Turns off LED to indicate the hibernate mode.
*   6. Switches to the hibernate Mode.
*   7. Wakes up from the hibernate mode with the SW button.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
int main()
{
    /* Set initial state (off) for LED */
    LED_Mode_Write(LIGHT_OFF);

    /* Set up GPIO interrupt and enable it */
    isr_GPIO_StartEx(GPIOIsrHandler);

    /* Enable global interrupts */
    CyGlobalIntEnable;

    /* Indicate enter active mode */
    LED_Mode_Write(LIGHT_ON);

    /* Delay for LED visibility */
    CyDelay(1000u);

    /* Blink LED for 1000 ms for each even value of hibernateCnt */
    if (0u == (hibernateCnt % 2u))
    {
        LED_Status_Write(LIGHT_ON);

        /* Delay for LED visibility */
        CyDelay(1000u);

        LED_Status_Write(LIGHT_OFF);
    }

    /* Increase hibernate counter */
    hibernateCnt++;

    /* Indicate enter hibernate mode */
    LED_Mode_Write(LIGHT_OFF);

    /* Enter hibernate mode */
    CySysPmHibernate();

    /* Sleep and wait for interrupt. Wakeup from hibernate is performed
     * through reset state, causing a normal boot procedure to occur.
     */

    for(;;)
    {
    }
}


/*******************************************************************************
* Function Name: GPIOIsrHandler
********************************************************************************
* Summary:
*  The interrupt handler for GPIO interrupts.
*  Clears a pending Interrupt.
*  Clears a pin Interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(GPIOIsrHandler)
{
    /* Clear pending Interrupt */
    isr_GPIO_ClearPending();

    /* Clear pin Interrupt */
    Pin_Sw_ClearInterrupt();
}

/* [] END OF FILE */
