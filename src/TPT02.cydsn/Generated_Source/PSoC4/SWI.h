/*******************************************************************************
* File Name: SWI.h  
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

#if !defined(CY_PINS_SWI_H) /* Pins SWI_H */
#define CY_PINS_SWI_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SWI_aliases.h"


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
} SWI_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SWI_Read(void);
void    SWI_Write(uint8 value);
uint8   SWI_ReadDataReg(void);
#if defined(SWI__PC) || (CY_PSOC4_4200L) 
    void    SWI_SetDriveMode(uint8 mode);
#endif
void    SWI_SetInterruptMode(uint16 position, uint16 mode);
uint8   SWI_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SWI_Sleep(void); 
void SWI_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SWI__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SWI_DRIVE_MODE_BITS        (3)
    #define SWI_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SWI_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SWI_SetDriveMode() function.
         *  @{
         */
        #define SWI_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SWI_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SWI_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SWI_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SWI_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SWI_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SWI_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SWI_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SWI_MASK               SWI__MASK
#define SWI_SHIFT              SWI__SHIFT
#define SWI_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SWI_SetInterruptMode() function.
     *  @{
     */
        #define SWI_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SWI_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SWI_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SWI_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SWI__SIO)
    #define SWI_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SWI__PC) && (CY_PSOC4_4200L)
    #define SWI_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SWI_USBIO_DISABLE              ((uint32)(~SWI_USBIO_ENABLE))
    #define SWI_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SWI_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SWI_USBIO_ENTER_SLEEP          ((uint32)((1u << SWI_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SWI_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWI_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SWI_USBIO_SUSPEND_SHIFT)))
    #define SWI_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SWI_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWI_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SWI__PC)
    /* Port Configuration */
    #define SWI_PC                 (* (reg32 *) SWI__PC)
#endif
/* Pin State */
#define SWI_PS                     (* (reg32 *) SWI__PS)
/* Data Register */
#define SWI_DR                     (* (reg32 *) SWI__DR)
/* Input Buffer Disable Override */
#define SWI_INP_DIS                (* (reg32 *) SWI__PC2)

/* Interrupt configuration Registers */
#define SWI_INTCFG                 (* (reg32 *) SWI__INTCFG)
#define SWI_INTSTAT                (* (reg32 *) SWI__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SWI_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SWI__SIO)
    #define SWI_SIO_REG            (* (reg32 *) SWI__SIO)
#endif /* (SWI__SIO_CFG) */

/* USBIO registers */
#if !defined(SWI__PC) && (CY_PSOC4_4200L)
    #define SWI_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SWI_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SWI_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SWI_DRIVE_MODE_SHIFT       (0x00u)
#define SWI_DRIVE_MODE_MASK        (0x07u << SWI_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SWI_H */


/* [] END OF FILE */
