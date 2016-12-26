/*******************************************************************************
* File Name: Advertising_LED.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Advertising_LED.h"

static Advertising_LED_BACKUP_STRUCT  Advertising_LED_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Advertising_LED_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Advertising_LED_SUT.c usage_Advertising_LED_Sleep_Wakeup
*******************************************************************************/
void Advertising_LED_Sleep(void)
{
    #if defined(Advertising_LED__PC)
        Advertising_LED_backup.pcState = Advertising_LED_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Advertising_LED_backup.usbState = Advertising_LED_CR1_REG;
            Advertising_LED_USB_POWER_REG |= Advertising_LED_USBIO_ENTER_SLEEP;
            Advertising_LED_CR1_REG &= Advertising_LED_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Advertising_LED__SIO)
        Advertising_LED_backup.sioState = Advertising_LED_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Advertising_LED_SIO_REG &= (uint32)(~Advertising_LED_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Advertising_LED_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Advertising_LED_Sleep() for an example usage.
*******************************************************************************/
void Advertising_LED_Wakeup(void)
{
    #if defined(Advertising_LED__PC)
        Advertising_LED_PC = Advertising_LED_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Advertising_LED_USB_POWER_REG &= Advertising_LED_USBIO_EXIT_SLEEP_PH1;
            Advertising_LED_CR1_REG = Advertising_LED_backup.usbState;
            Advertising_LED_USB_POWER_REG &= Advertising_LED_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Advertising_LED__SIO)
        Advertising_LED_SIO_REG = Advertising_LED_backup.sioState;
    #endif
}


/* [] END OF FILE */
