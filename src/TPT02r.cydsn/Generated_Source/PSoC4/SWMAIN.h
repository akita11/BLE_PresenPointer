/*******************************************************************************
* File Name: SWMAIN.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SWMAIN_H) /* Pins SWMAIN_H */
#define CY_PINS_SWMAIN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SWMAIN_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} SWMAIN_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SWMAIN_Read(void);
void    SWMAIN_Write(uint8 value);
uint8   SWMAIN_ReadDataReg(void);
#if defined(SWMAIN__PC) || (CY_PSOC4_4200L) 
    void    SWMAIN_SetDriveMode(uint8 mode);
#endif
void    SWMAIN_SetInterruptMode(uint16 position, uint16 mode);
uint8   SWMAIN_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SWMAIN_Sleep(void); 
void SWMAIN_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SWMAIN__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SWMAIN_DRIVE_MODE_BITS        (3)
    #define SWMAIN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SWMAIN_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SWMAIN_SetDriveMode() function.
         *  @{
         */
        #define SWMAIN_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SWMAIN_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SWMAIN_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SWMAIN_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SWMAIN_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SWMAIN_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SWMAIN_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SWMAIN_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SWMAIN_MASK               SWMAIN__MASK
#define SWMAIN_SHIFT              SWMAIN__SHIFT
#define SWMAIN_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SWMAIN_SetInterruptMode() function.
     *  @{
     */
        #define SWMAIN_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SWMAIN_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SWMAIN_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SWMAIN_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SWMAIN__SIO)
    #define SWMAIN_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SWMAIN__PC) && (CY_PSOC4_4200L)
    #define SWMAIN_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SWMAIN_USBIO_DISABLE              ((uint32)(~SWMAIN_USBIO_ENABLE))
    #define SWMAIN_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SWMAIN_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SWMAIN_USBIO_ENTER_SLEEP          ((uint32)((1u << SWMAIN_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SWMAIN_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWMAIN_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SWMAIN_USBIO_SUSPEND_SHIFT)))
    #define SWMAIN_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SWMAIN_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWMAIN_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SWMAIN__PC)
    /* Port Configuration */
    #define SWMAIN_PC                 (* (reg32 *) SWMAIN__PC)
#endif
/* Pin State */
#define SWMAIN_PS                     (* (reg32 *) SWMAIN__PS)
/* Data Register */
#define SWMAIN_DR                     (* (reg32 *) SWMAIN__DR)
/* Input Buffer Disable Override */
#define SWMAIN_INP_DIS                (* (reg32 *) SWMAIN__PC2)

/* Interrupt configuration Registers */
#define SWMAIN_INTCFG                 (* (reg32 *) SWMAIN__INTCFG)
#define SWMAIN_INTSTAT                (* (reg32 *) SWMAIN__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SWMAIN_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SWMAIN__SIO)
    #define SWMAIN_SIO_REG            (* (reg32 *) SWMAIN__SIO)
#endif /* (SWMAIN__SIO_CFG) */

/* USBIO registers */
#if !defined(SWMAIN__PC) && (CY_PSOC4_4200L)
    #define SWMAIN_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SWMAIN_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SWMAIN_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SWMAIN_DRIVE_MODE_SHIFT       (0x00u)
#define SWMAIN_DRIVE_MODE_MASK        (0x07u << SWMAIN_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SWMAIN_H */


/* [] END OF FILE */
