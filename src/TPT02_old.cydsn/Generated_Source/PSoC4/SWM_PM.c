/*******************************************************************************
* File Name: SWM.c  
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
#include "SWM.h"

static SWM_BACKUP_STRUCT  SWM_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: SWM_Sleep
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
*  \snippet SWM_SUT.c usage_SWM_Sleep_Wakeup
*******************************************************************************/
void SWM_Sleep(void)
{
    #if defined(SWM__PC)
        SWM_backup.pcState = SWM_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            SWM_backup.usbState = SWM_CR1_REG;
            SWM_USB_POWER_REG |= SWM_USBIO_ENTER_SLEEP;
            SWM_CR1_REG &= SWM_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SWM__SIO)
        SWM_backup.sioState = SWM_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        SWM_SIO_REG &= (uint32)(~SWM_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: SWM_Wakeup
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
*  Refer to SWM_Sleep() for an example usage.
*******************************************************************************/
void SWM_Wakeup(void)
{
    #if defined(SWM__PC)
        SWM_PC = SWM_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            SWM_USB_POWER_REG &= SWM_USBIO_EXIT_SLEEP_PH1;
            SWM_CR1_REG = SWM_backup.usbState;
            SWM_USB_POWER_REG &= SWM_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SWM__SIO)
        SWM_SIO_REG = SWM_backup.sioState;
    #endif
}


/* [] END OF FILE */
