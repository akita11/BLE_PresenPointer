/*******************************************************************************
* File Name: SWB.h  
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

#if !defined(CY_PINS_SWB_H) /* Pins SWB_H */
#define CY_PINS_SWB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SWB_aliases.h"


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
} SWB_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SWB_Read(void);
void    SWB_Write(uint8 value);
uint8   SWB_ReadDataReg(void);
#if defined(SWB__PC) || (CY_PSOC4_4200L) 
    void    SWB_SetDriveMode(uint8 mode);
#endif
void    SWB_SetInterruptMode(uint16 position, uint16 mode);
uint8   SWB_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SWB_Sleep(void); 
void SWB_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SWB__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SWB_DRIVE_MODE_BITS        (3)
    #define SWB_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SWB_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SWB_SetDriveMode() function.
         *  @{
         */
        #define SWB_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SWB_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SWB_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SWB_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SWB_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SWB_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SWB_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SWB_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SWB_MASK               SWB__MASK
#define SWB_SHIFT              SWB__SHIFT
#define SWB_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SWB_SetInterruptMode() function.
     *  @{
     */
        #define SWB_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SWB_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SWB_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SWB_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SWB__SIO)
    #define SWB_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SWB__PC) && (CY_PSOC4_4200L)
    #define SWB_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SWB_USBIO_DISABLE              ((uint32)(~SWB_USBIO_ENABLE))
    #define SWB_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SWB_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SWB_USBIO_ENTER_SLEEP          ((uint32)((1u << SWB_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SWB_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWB_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SWB_USBIO_SUSPEND_SHIFT)))
    #define SWB_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SWB_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWB_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SWB__PC)
    /* Port Configuration */
    #define SWB_PC                 (* (reg32 *) SWB__PC)
#endif
/* Pin State */
#define SWB_PS                     (* (reg32 *) SWB__PS)
/* Data Register */
#define SWB_DR                     (* (reg32 *) SWB__DR)
/* Input Buffer Disable Override */
#define SWB_INP_DIS                (* (reg32 *) SWB__PC2)

/* Interrupt configuration Registers */
#define SWB_INTCFG                 (* (reg32 *) SWB__INTCFG)
#define SWB_INTSTAT                (* (reg32 *) SWB__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SWB_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SWB__SIO)
    #define SWB_SIO_REG            (* (reg32 *) SWB__SIO)
#endif /* (SWB__SIO_CFG) */

/* USBIO registers */
#if !defined(SWB__PC) && (CY_PSOC4_4200L)
    #define SWB_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SWB_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SWB_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SWB_DRIVE_MODE_SHIFT       (0x00u)
#define SWB_DRIVE_MODE_MASK        (0x07u << SWB_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SWB_H */


/* [] END OF FILE */
