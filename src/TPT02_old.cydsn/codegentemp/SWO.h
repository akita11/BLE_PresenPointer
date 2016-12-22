/*******************************************************************************
* File Name: SWO.h  
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

#if !defined(CY_PINS_SWO_H) /* Pins SWO_H */
#define CY_PINS_SWO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SWO_aliases.h"


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
} SWO_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SWO_Read(void);
void    SWO_Write(uint8 value);
uint8   SWO_ReadDataReg(void);
#if defined(SWO__PC) || (CY_PSOC4_4200L) 
    void    SWO_SetDriveMode(uint8 mode);
#endif
void    SWO_SetInterruptMode(uint16 position, uint16 mode);
uint8   SWO_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SWO_Sleep(void); 
void SWO_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SWO__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SWO_DRIVE_MODE_BITS        (3)
    #define SWO_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SWO_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SWO_SetDriveMode() function.
         *  @{
         */
        #define SWO_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SWO_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SWO_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SWO_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SWO_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SWO_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SWO_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SWO_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SWO_MASK               SWO__MASK
#define SWO_SHIFT              SWO__SHIFT
#define SWO_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SWO_SetInterruptMode() function.
     *  @{
     */
        #define SWO_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SWO_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SWO_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SWO_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SWO__SIO)
    #define SWO_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SWO__PC) && (CY_PSOC4_4200L)
    #define SWO_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SWO_USBIO_DISABLE              ((uint32)(~SWO_USBIO_ENABLE))
    #define SWO_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SWO_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SWO_USBIO_ENTER_SLEEP          ((uint32)((1u << SWO_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SWO_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWO_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SWO_USBIO_SUSPEND_SHIFT)))
    #define SWO_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SWO_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWO_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SWO__PC)
    /* Port Configuration */
    #define SWO_PC                 (* (reg32 *) SWO__PC)
#endif
/* Pin State */
#define SWO_PS                     (* (reg32 *) SWO__PS)
/* Data Register */
#define SWO_DR                     (* (reg32 *) SWO__DR)
/* Input Buffer Disable Override */
#define SWO_INP_DIS                (* (reg32 *) SWO__PC2)

/* Interrupt configuration Registers */
#define SWO_INTCFG                 (* (reg32 *) SWO__INTCFG)
#define SWO_INTSTAT                (* (reg32 *) SWO__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SWO_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SWO__SIO)
    #define SWO_SIO_REG            (* (reg32 *) SWO__SIO)
#endif /* (SWO__SIO_CFG) */

/* USBIO registers */
#if !defined(SWO__PC) && (CY_PSOC4_4200L)
    #define SWO_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SWO_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SWO_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SWO_DRIVE_MODE_SHIFT       (0x00u)
#define SWO_DRIVE_MODE_MASK        (0x07u << SWO_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SWO_H */


/* [] END OF FILE */
