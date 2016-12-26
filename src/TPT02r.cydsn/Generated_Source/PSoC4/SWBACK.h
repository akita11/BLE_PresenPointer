/*******************************************************************************
* File Name: SWBACK.h  
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

#if !defined(CY_PINS_SWBACK_H) /* Pins SWBACK_H */
#define CY_PINS_SWBACK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SWBACK_aliases.h"


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
} SWBACK_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SWBACK_Read(void);
void    SWBACK_Write(uint8 value);
uint8   SWBACK_ReadDataReg(void);
#if defined(SWBACK__PC) || (CY_PSOC4_4200L) 
    void    SWBACK_SetDriveMode(uint8 mode);
#endif
void    SWBACK_SetInterruptMode(uint16 position, uint16 mode);
uint8   SWBACK_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SWBACK_Sleep(void); 
void SWBACK_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SWBACK__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SWBACK_DRIVE_MODE_BITS        (3)
    #define SWBACK_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SWBACK_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SWBACK_SetDriveMode() function.
         *  @{
         */
        #define SWBACK_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SWBACK_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SWBACK_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SWBACK_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SWBACK_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SWBACK_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SWBACK_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SWBACK_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SWBACK_MASK               SWBACK__MASK
#define SWBACK_SHIFT              SWBACK__SHIFT
#define SWBACK_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SWBACK_SetInterruptMode() function.
     *  @{
     */
        #define SWBACK_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SWBACK_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SWBACK_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SWBACK_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SWBACK__SIO)
    #define SWBACK_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SWBACK__PC) && (CY_PSOC4_4200L)
    #define SWBACK_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SWBACK_USBIO_DISABLE              ((uint32)(~SWBACK_USBIO_ENABLE))
    #define SWBACK_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SWBACK_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SWBACK_USBIO_ENTER_SLEEP          ((uint32)((1u << SWBACK_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SWBACK_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWBACK_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SWBACK_USBIO_SUSPEND_SHIFT)))
    #define SWBACK_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SWBACK_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWBACK_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SWBACK__PC)
    /* Port Configuration */
    #define SWBACK_PC                 (* (reg32 *) SWBACK__PC)
#endif
/* Pin State */
#define SWBACK_PS                     (* (reg32 *) SWBACK__PS)
/* Data Register */
#define SWBACK_DR                     (* (reg32 *) SWBACK__DR)
/* Input Buffer Disable Override */
#define SWBACK_INP_DIS                (* (reg32 *) SWBACK__PC2)

/* Interrupt configuration Registers */
#define SWBACK_INTCFG                 (* (reg32 *) SWBACK__INTCFG)
#define SWBACK_INTSTAT                (* (reg32 *) SWBACK__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SWBACK_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SWBACK__SIO)
    #define SWBACK_SIO_REG            (* (reg32 *) SWBACK__SIO)
#endif /* (SWBACK__SIO_CFG) */

/* USBIO registers */
#if !defined(SWBACK__PC) && (CY_PSOC4_4200L)
    #define SWBACK_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SWBACK_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SWBACK_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SWBACK_DRIVE_MODE_SHIFT       (0x00u)
#define SWBACK_DRIVE_MODE_MASK        (0x07u << SWBACK_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SWBACK_H */


/* [] END OF FILE */
