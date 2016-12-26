/*******************************************************************************
* File Name: Vref.h  
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

#if !defined(CY_PINS_Vref_H) /* Pins Vref_H */
#define CY_PINS_Vref_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Vref_aliases.h"


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
} Vref_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Vref_Read(void);
void    Vref_Write(uint8 value);
uint8   Vref_ReadDataReg(void);
#if defined(Vref__PC) || (CY_PSOC4_4200L) 
    void    Vref_SetDriveMode(uint8 mode);
#endif
void    Vref_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vref_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Vref_Sleep(void); 
void Vref_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Vref__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Vref_DRIVE_MODE_BITS        (3)
    #define Vref_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Vref_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Vref_SetDriveMode() function.
         *  @{
         */
        #define Vref_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Vref_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Vref_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Vref_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Vref_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Vref_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Vref_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Vref_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Vref_MASK               Vref__MASK
#define Vref_SHIFT              Vref__SHIFT
#define Vref_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vref_SetInterruptMode() function.
     *  @{
     */
        #define Vref_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Vref_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Vref_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Vref_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Vref__SIO)
    #define Vref_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Vref__PC) && (CY_PSOC4_4200L)
    #define Vref_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Vref_USBIO_DISABLE              ((uint32)(~Vref_USBIO_ENABLE))
    #define Vref_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Vref_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Vref_USBIO_ENTER_SLEEP          ((uint32)((1u << Vref_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Vref_USBIO_SUSPEND_DEL_SHIFT)))
    #define Vref_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Vref_USBIO_SUSPEND_SHIFT)))
    #define Vref_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Vref_USBIO_SUSPEND_DEL_SHIFT)))
    #define Vref_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Vref__PC)
    /* Port Configuration */
    #define Vref_PC                 (* (reg32 *) Vref__PC)
#endif
/* Pin State */
#define Vref_PS                     (* (reg32 *) Vref__PS)
/* Data Register */
#define Vref_DR                     (* (reg32 *) Vref__DR)
/* Input Buffer Disable Override */
#define Vref_INP_DIS                (* (reg32 *) Vref__PC2)

/* Interrupt configuration Registers */
#define Vref_INTCFG                 (* (reg32 *) Vref__INTCFG)
#define Vref_INTSTAT                (* (reg32 *) Vref__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Vref_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Vref__SIO)
    #define Vref_SIO_REG            (* (reg32 *) Vref__SIO)
#endif /* (Vref__SIO_CFG) */

/* USBIO registers */
#if !defined(Vref__PC) && (CY_PSOC4_4200L)
    #define Vref_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Vref_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Vref_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Vref_DRIVE_MODE_SHIFT       (0x00u)
#define Vref_DRIVE_MODE_MASK        (0x07u << Vref_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Vref_H */


/* [] END OF FILE */
