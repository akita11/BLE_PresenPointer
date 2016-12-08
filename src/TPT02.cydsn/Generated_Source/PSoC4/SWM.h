/*******************************************************************************
* File Name: SWM.h  
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

#if !defined(CY_PINS_SWM_H) /* Pins SWM_H */
#define CY_PINS_SWM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SWM_aliases.h"


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
} SWM_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SWM_Read(void);
void    SWM_Write(uint8 value);
uint8   SWM_ReadDataReg(void);
#if defined(SWM__PC) || (CY_PSOC4_4200L) 
    void    SWM_SetDriveMode(uint8 mode);
#endif
void    SWM_SetInterruptMode(uint16 position, uint16 mode);
uint8   SWM_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SWM_Sleep(void); 
void SWM_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SWM__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SWM_DRIVE_MODE_BITS        (3)
    #define SWM_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SWM_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SWM_SetDriveMode() function.
         *  @{
         */
        #define SWM_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SWM_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SWM_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SWM_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SWM_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SWM_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SWM_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SWM_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SWM_MASK               SWM__MASK
#define SWM_SHIFT              SWM__SHIFT
#define SWM_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SWM_SetInterruptMode() function.
     *  @{
     */
        #define SWM_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SWM_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SWM_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SWM_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SWM__SIO)
    #define SWM_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SWM__PC) && (CY_PSOC4_4200L)
    #define SWM_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SWM_USBIO_DISABLE              ((uint32)(~SWM_USBIO_ENABLE))
    #define SWM_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SWM_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SWM_USBIO_ENTER_SLEEP          ((uint32)((1u << SWM_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SWM_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWM_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SWM_USBIO_SUSPEND_SHIFT)))
    #define SWM_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SWM_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWM_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SWM__PC)
    /* Port Configuration */
    #define SWM_PC                 (* (reg32 *) SWM__PC)
#endif
/* Pin State */
#define SWM_PS                     (* (reg32 *) SWM__PS)
/* Data Register */
#define SWM_DR                     (* (reg32 *) SWM__DR)
/* Input Buffer Disable Override */
#define SWM_INP_DIS                (* (reg32 *) SWM__PC2)

/* Interrupt configuration Registers */
#define SWM_INTCFG                 (* (reg32 *) SWM__INTCFG)
#define SWM_INTSTAT                (* (reg32 *) SWM__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SWM_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SWM__SIO)
    #define SWM_SIO_REG            (* (reg32 *) SWM__SIO)
#endif /* (SWM__SIO_CFG) */

/* USBIO registers */
#if !defined(SWM__PC) && (CY_PSOC4_4200L)
    #define SWM_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SWM_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SWM_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SWM_DRIVE_MODE_SHIFT       (0x00u)
#define SWM_DRIVE_MODE_MASK        (0x07u << SWM_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SWM_H */


/* [] END OF FILE */
