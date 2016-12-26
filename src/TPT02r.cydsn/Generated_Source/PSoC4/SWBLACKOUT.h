/*******************************************************************************
* File Name: SWBLACKOUT.h  
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

#if !defined(CY_PINS_SWBLACKOUT_H) /* Pins SWBLACKOUT_H */
#define CY_PINS_SWBLACKOUT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SWBLACKOUT_aliases.h"


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
} SWBLACKOUT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SWBLACKOUT_Read(void);
void    SWBLACKOUT_Write(uint8 value);
uint8   SWBLACKOUT_ReadDataReg(void);
#if defined(SWBLACKOUT__PC) || (CY_PSOC4_4200L) 
    void    SWBLACKOUT_SetDriveMode(uint8 mode);
#endif
void    SWBLACKOUT_SetInterruptMode(uint16 position, uint16 mode);
uint8   SWBLACKOUT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SWBLACKOUT_Sleep(void); 
void SWBLACKOUT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SWBLACKOUT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SWBLACKOUT_DRIVE_MODE_BITS        (3)
    #define SWBLACKOUT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SWBLACKOUT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SWBLACKOUT_SetDriveMode() function.
         *  @{
         */
        #define SWBLACKOUT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SWBLACKOUT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SWBLACKOUT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SWBLACKOUT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SWBLACKOUT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SWBLACKOUT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SWBLACKOUT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SWBLACKOUT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SWBLACKOUT_MASK               SWBLACKOUT__MASK
#define SWBLACKOUT_SHIFT              SWBLACKOUT__SHIFT
#define SWBLACKOUT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SWBLACKOUT_SetInterruptMode() function.
     *  @{
     */
        #define SWBLACKOUT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SWBLACKOUT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SWBLACKOUT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SWBLACKOUT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SWBLACKOUT__SIO)
    #define SWBLACKOUT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SWBLACKOUT__PC) && (CY_PSOC4_4200L)
    #define SWBLACKOUT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SWBLACKOUT_USBIO_DISABLE              ((uint32)(~SWBLACKOUT_USBIO_ENABLE))
    #define SWBLACKOUT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SWBLACKOUT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SWBLACKOUT_USBIO_ENTER_SLEEP          ((uint32)((1u << SWBLACKOUT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SWBLACKOUT_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWBLACKOUT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SWBLACKOUT_USBIO_SUSPEND_SHIFT)))
    #define SWBLACKOUT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SWBLACKOUT_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWBLACKOUT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SWBLACKOUT__PC)
    /* Port Configuration */
    #define SWBLACKOUT_PC                 (* (reg32 *) SWBLACKOUT__PC)
#endif
/* Pin State */
#define SWBLACKOUT_PS                     (* (reg32 *) SWBLACKOUT__PS)
/* Data Register */
#define SWBLACKOUT_DR                     (* (reg32 *) SWBLACKOUT__DR)
/* Input Buffer Disable Override */
#define SWBLACKOUT_INP_DIS                (* (reg32 *) SWBLACKOUT__PC2)

/* Interrupt configuration Registers */
#define SWBLACKOUT_INTCFG                 (* (reg32 *) SWBLACKOUT__INTCFG)
#define SWBLACKOUT_INTSTAT                (* (reg32 *) SWBLACKOUT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SWBLACKOUT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SWBLACKOUT__SIO)
    #define SWBLACKOUT_SIO_REG            (* (reg32 *) SWBLACKOUT__SIO)
#endif /* (SWBLACKOUT__SIO_CFG) */

/* USBIO registers */
#if !defined(SWBLACKOUT__PC) && (CY_PSOC4_4200L)
    #define SWBLACKOUT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SWBLACKOUT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SWBLACKOUT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SWBLACKOUT_DRIVE_MODE_SHIFT       (0x00u)
#define SWBLACKOUT_DRIVE_MODE_MASK        (0x07u << SWBLACKOUT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SWBLACKOUT_H */


/* [] END OF FILE */
