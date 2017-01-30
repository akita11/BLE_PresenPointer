/***************************************************************************//**
* \file UART_DEB_PM.c
* \version 3.20
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UART_DEB.h"
#include "UART_DEB_PVT.h"

#if(UART_DEB_SCB_MODE_I2C_INC)
    #include "UART_DEB_I2C_PVT.h"
#endif /* (UART_DEB_SCB_MODE_I2C_INC) */

#if(UART_DEB_SCB_MODE_EZI2C_INC)
    #include "UART_DEB_EZI2C_PVT.h"
#endif /* (UART_DEB_SCB_MODE_EZI2C_INC) */

#if(UART_DEB_SCB_MODE_SPI_INC || UART_DEB_SCB_MODE_UART_INC)
    #include "UART_DEB_SPI_UART_PVT.h"
#endif /* (UART_DEB_SCB_MODE_SPI_INC || UART_DEB_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(UART_DEB_SCB_MODE_UNCONFIG_CONST_CFG || \
   (UART_DEB_SCB_MODE_I2C_CONST_CFG   && (!UART_DEB_I2C_WAKE_ENABLE_CONST))   || \
   (UART_DEB_SCB_MODE_EZI2C_CONST_CFG && (!UART_DEB_EZI2C_WAKE_ENABLE_CONST)) || \
   (UART_DEB_SCB_MODE_SPI_CONST_CFG   && (!UART_DEB_SPI_WAKE_ENABLE_CONST))   || \
   (UART_DEB_SCB_MODE_UART_CONST_CFG  && (!UART_DEB_UART_WAKE_ENABLE_CONST)))

    UART_DEB_BACKUP_STRUCT UART_DEB_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: UART_DEB_Sleep
****************************************************************************//**
*
*  Prepares the UART_DEB component to enter Deep Sleep.
*  The �gEnable wakeup from Deep Sleep Mode�h selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the UART_DEB_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void UART_DEB_Sleep(void)
{
#if(UART_DEB_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_DEB_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_DEB_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_DEB_I2CSaveConfig();
        }
        else if(UART_DEB_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_DEB_EzI2CSaveConfig();
        }
    #if(!UART_DEB_CY_SCBIP_V1)
        else if(UART_DEB_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_DEB_SpiSaveConfig();
        }
        else if(UART_DEB_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_DEB_UartSaveConfig();
        }
    #endif /* (!UART_DEB_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        UART_DEB_backup.enableState = (uint8) UART_DEB_GET_CTRL_ENABLED;

        if(0u != UART_DEB_backup.enableState)
        {
            UART_DEB_Stop();
        }
    }

#else

    #if (UART_DEB_SCB_MODE_I2C_CONST_CFG && UART_DEB_I2C_WAKE_ENABLE_CONST)
        UART_DEB_I2CSaveConfig();

    #elif (UART_DEB_SCB_MODE_EZI2C_CONST_CFG && UART_DEB_EZI2C_WAKE_ENABLE_CONST)
        UART_DEB_EzI2CSaveConfig();

    #elif (UART_DEB_SCB_MODE_SPI_CONST_CFG && UART_DEB_SPI_WAKE_ENABLE_CONST)
        UART_DEB_SpiSaveConfig();

    #elif (UART_DEB_SCB_MODE_UART_CONST_CFG && UART_DEB_UART_WAKE_ENABLE_CONST)
        UART_DEB_UartSaveConfig();

    #else

        UART_DEB_backup.enableState = (uint8) UART_DEB_GET_CTRL_ENABLED;

        if(0u != UART_DEB_backup.enableState)
        {
            UART_DEB_Stop();
        }

    #endif /* defined (UART_DEB_SCB_MODE_I2C_CONST_CFG) && (UART_DEB_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_DEB_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UART_DEB_Wakeup
****************************************************************************//**
*
*  Prepares the UART_DEB component for Active mode operation after 
*  Deep Sleep.
*  The �gEnable wakeup from Deep Sleep Mode�h selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the UART_DEB_Wakeup() function without first calling the 
*   UART_DEB_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void UART_DEB_Wakeup(void)
{
#if(UART_DEB_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UART_DEB_SCB_WAKE_ENABLE_CHECK)
    {
        if(UART_DEB_SCB_MODE_I2C_RUNTM_CFG)
        {
            UART_DEB_I2CRestoreConfig();
        }
        else if(UART_DEB_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UART_DEB_EzI2CRestoreConfig();
        }
    #if(!UART_DEB_CY_SCBIP_V1)
        else if(UART_DEB_SCB_MODE_SPI_RUNTM_CFG)
        {
            UART_DEB_SpiRestoreConfig();
        }
        else if(UART_DEB_SCB_MODE_UART_RUNTM_CFG)
        {
            UART_DEB_UartRestoreConfig();
        }
    #endif /* (!UART_DEB_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != UART_DEB_backup.enableState)
        {
            UART_DEB_Enable();
        }
    }

#else

    #if (UART_DEB_SCB_MODE_I2C_CONST_CFG  && UART_DEB_I2C_WAKE_ENABLE_CONST)
        UART_DEB_I2CRestoreConfig();

    #elif (UART_DEB_SCB_MODE_EZI2C_CONST_CFG && UART_DEB_EZI2C_WAKE_ENABLE_CONST)
        UART_DEB_EzI2CRestoreConfig();

    #elif (UART_DEB_SCB_MODE_SPI_CONST_CFG && UART_DEB_SPI_WAKE_ENABLE_CONST)
        UART_DEB_SpiRestoreConfig();

    #elif (UART_DEB_SCB_MODE_UART_CONST_CFG && UART_DEB_UART_WAKE_ENABLE_CONST)
        UART_DEB_UartRestoreConfig();

    #else

        if(0u != UART_DEB_backup.enableState)
        {
            UART_DEB_Enable();
        }

    #endif /* (UART_DEB_I2C_WAKE_ENABLE_CONST) */

#endif /* (UART_DEB_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
