/*******************************************************************************
* File Name: SWB.h  
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

#if !defined(CY_PINS_SWB_ALIASES_H) /* Pins SWB_ALIASES_H */
#define CY_PINS_SWB_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SWB_0			(SWB__0__PC)
#define SWB_0_PS		(SWB__0__PS)
#define SWB_0_PC		(SWB__0__PC)
#define SWB_0_DR		(SWB__0__DR)
#define SWB_0_SHIFT	(SWB__0__SHIFT)
#define SWB_0_INTR	((uint16)((uint16)0x0003u << (SWB__0__SHIFT*2u)))

#define SWB_INTR_ALL	 ((uint16)(SWB_0_INTR))


#endif /* End Pins SWB_ALIASES_H */


/* [] END OF FILE */
