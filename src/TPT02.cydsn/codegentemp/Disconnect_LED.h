/*******************************************************************************
* File Name: Disconnect_LED.h  
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

#if !defined(CY_PINS_Disconnect_LED_H) /* Pins Disconnect_LED_H */
#define CY_PINS_Disconnect_LED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Disconnect_LED_aliases.h"


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
} Disconnect_LED_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Disconnect_LED_Read(void);
void    Disconnect_LED_Write(uint8 value);
uint8   Disconnect_LED_ReadDataReg(void);
#if defined(Disconnect_LED__PC) || (CY_PSOC4_4200L) 
    void    Disconnect_LED_SetDriveMode(uint8 mode);
#endif
void    Disconnect_LED_SetInterruptMode(uint16 position, uint16 mode);
uint8   Disconnect_LED_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Disconnect_LED_Sleep(void); 
void Disconnect_LED_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Disconnect_LED__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Disconnect_LED_DRIVE_MODE_BITS        (3)
    #define Disconnect_LED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Disconnect_LED_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Disconnect_LED_SetDriveMode() function.
         *  @{
         */
        #define Disconnect_LED_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Disconnect_LED_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Disconnect_LED_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Disconnect_LED_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Disconnect_LED_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Disconnect_LED_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Disconnect_LED_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Disconnect_LED_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Disconnect_LED_MASK               Disconnect_LED__MASK
#define Disconnect_LED_SHIFT              Disconnect_LED__SHIFT
#define Disconnect_LED_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Disconnect_LED_SetInterruptMode() function.
     *  @{
     */
        #define Disconnect_LED_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Disconnect_LED_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Disconnect_LED_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Disconnect_LED_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Disconnect_LED__SIO)
    #define Disconnect_LED_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Disconnect_LED__PC) && (CY_PSOC4_4200L)
    #define Disconnect_LED_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Disconnect_LED_USBIO_DISABLE              ((uint32)(~Disconnect_LED_USBIO_ENABLE))
    #define Disconnect_LED_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Disconnect_LED_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Disconnect_LED_USBIO_ENTER_SLEEP          ((uint32)((1u << Disconnect_LED_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Disconnect_LED_USBIO_SUSPEND_DEL_SHIFT)))
    #define Disconnect_LED_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Disconnect_LED_USBIO_SUSPEND_SHIFT)))
    #define Disconnect_LED_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Disconnect_LED_USBIO_SUSPEND_DEL_SHIFT)))
    #define Disconnect_LED_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Disconnect_LED__PC)
    /* Port Configuration */
    #define Disconnect_LED_PC                 (* (reg32 *) Disconnect_LED__PC)
#endif
/* Pin State */
#define Disconnect_LED_PS                     (* (reg32 *) Disconnect_LED__PS)
/* Data Register */
#define Disconnect_LED_DR                     (* (reg32 *) Disconnect_LED__DR)
/* Input Buffer Disable Override */
#define Disconnect_LED_INP_DIS                (* (reg32 *) Disconnect_LED__PC2)

/* Interrupt configuration Registers */
#define Disconnect_LED_INTCFG                 (* (reg32 *) Disconnect_LED__INTCFG)
#define Disconnect_LED_INTSTAT                (* (reg32 *) Disconnect_LED__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Disconnect_LED_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Disconnect_LED__SIO)
    #define Disconnect_LED_SIO_REG            (* (reg32 *) Disconnect_LED__SIO)
#endif /* (Disconnect_LED__SIO_CFG) */

/* USBIO registers */
#if !defined(Disconnect_LED__PC) && (CY_PSOC4_4200L)
    #define Disconnect_LED_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Disconnect_LED_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Disconnect_LED_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Disconnect_LED_DRIVE_MODE_SHIFT       (0x00u)
#define Disconnect_LED_DRIVE_MODE_MASK        (0x07u << Disconnect_LED_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Disconnect_LED_H */


/* [] END OF FILE */
