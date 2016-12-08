/*******************************************************************************
* File Name: SWB.c  
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
#include "SWB.h"

static SWB_BACKUP_STRUCT  SWB_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: SWB_Sleep
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
*  \snippet SWB_SUT.c usage_SWB_Sleep_Wakeup
*******************************************************************************/
void SWB_Sleep(void)
{
    #if defined(SWB__PC)
        SWB_backup.pcState = SWB_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            SWB_backup.usbState = SWB_CR1_REG;
            SWB_USB_POWER_REG |= SWB_USBIO_ENTER_SLEEP;
            SWB_CR1_REG &= SWB_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SWB__SIO)
        SWB_backup.sioState = SWB_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        SWB_SIO_REG &= (uint32)(~SWB_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: SWB_Wakeup
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
*  Refer to SWB_Sleep() for an example usage.
*******************************************************************************/
void SWB_Wakeup(void)
{
    #if defined(SWB__PC)
        SWB_PC = SWB_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            SWB_USB_POWER_REG &= SWB_USBIO_EXIT_SLEEP_PH1;
            SWB_CR1_REG = SWB_backup.usbState;
            SWB_USB_POWER_REG &= SWB_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SWB__SIO)
        SWB_SIO_REG = SWB_backup.sioState;
    #endif
}


/* [] END OF FILE */
