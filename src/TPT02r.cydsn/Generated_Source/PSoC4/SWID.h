/*******************************************************************************
* File Name: SWID.h  
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

#if !defined(CY_PINS_SWID_H) /* Pins SWID_H */
#define CY_PINS_SWID_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SWID_aliases.h"


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
} SWID_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SWID_Read(void);
void    SWID_Write(uint8 value);
uint8   SWID_ReadDataReg(void);
#if defined(SWID__PC) || (CY_PSOC4_4200L) 
    void    SWID_SetDriveMode(uint8 mode);
#endif
void    SWID_SetInterruptMode(uint16 position, uint16 mode);
uint8   SWID_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SWID_Sleep(void); 
void SWID_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SWID__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SWID_DRIVE_MODE_BITS        (3)
    #define SWID_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SWID_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SWID_SetDriveMode() function.
         *  @{
         */
        #define SWID_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SWID_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SWID_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SWID_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SWID_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SWID_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SWID_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SWID_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SWID_MASK               SWID__MASK
#define SWID_SHIFT              SWID__SHIFT
#define SWID_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SWID_SetInterruptMode() function.
     *  @{
     */
        #define SWID_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SWID_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SWID_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SWID_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SWID__SIO)
    #define SWID_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SWID__PC) && (CY_PSOC4_4200L)
    #define SWID_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SWID_USBIO_DISABLE              ((uint32)(~SWID_USBIO_ENABLE))
    #define SWID_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SWID_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SWID_USBIO_ENTER_SLEEP          ((uint32)((1u << SWID_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SWID_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWID_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SWID_USBIO_SUSPEND_SHIFT)))
    #define SWID_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SWID_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWID_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SWID__PC)
    /* Port Configuration */
    #define SWID_PC                 (* (reg32 *) SWID__PC)
#endif
/* Pin State */
#define SWID_PS                     (* (reg32 *) SWID__PS)
/* Data Register */
#define SWID_DR                     (* (reg32 *) SWID__DR)
/* Input Buffer Disable Override */
#define SWID_INP_DIS                (* (reg32 *) SWID__PC2)

/* Interrupt configuration Registers */
#define SWID_INTCFG                 (* (reg32 *) SWID__INTCFG)
#define SWID_INTSTAT                (* (reg32 *) SWID__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SWID_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SWID__SIO)
    #define SWID_SIO_REG            (* (reg32 *) SWID__SIO)
#endif /* (SWID__SIO_CFG) */

/* USBIO registers */
#if !defined(SWID__PC) && (CY_PSOC4_4200L)
    #define SWID_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SWID_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SWID_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SWID_DRIVE_MODE_SHIFT       (0x00u)
#define SWID_DRIVE_MODE_MASK        (0x07u << SWID_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SWID_H */


/* [] END OF FILE */
