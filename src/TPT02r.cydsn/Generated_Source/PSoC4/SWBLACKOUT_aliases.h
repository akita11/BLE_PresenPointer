/*******************************************************************************
* File Name: SWBLACKOUT.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SWBLACKOUT_ALIASES_H) /* Pins SWBLACKOUT_ALIASES_H */
#define CY_PINS_SWBLACKOUT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SWBLACKOUT_0			(SWBLACKOUT__0__PC)
#define SWBLACKOUT_0_PS		(SWBLACKOUT__0__PS)
#define SWBLACKOUT_0_PC		(SWBLACKOUT__0__PC)
#define SWBLACKOUT_0_DR		(SWBLACKOUT__0__DR)
#define SWBLACKOUT_0_SHIFT	(SWBLACKOUT__0__SHIFT)
#define SWBLACKOUT_0_INTR	((uint16)((uint16)0x0003u << (SWBLACKOUT__0__SHIFT*2u)))

#define SWBLACKOUT_INTR_ALL	 ((uint16)(SWBLACKOUT_0_INTR))


#endif /* End Pins SWBLACKOUT_ALIASES_H */


/* [] END OF FILE */
