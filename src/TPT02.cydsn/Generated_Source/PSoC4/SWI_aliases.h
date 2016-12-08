/*******************************************************************************
* File Name: SWI.h  
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

#if !defined(CY_PINS_SWI_ALIASES_H) /* Pins SWI_ALIASES_H */
#define CY_PINS_SWI_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SWI_0			(SWI__0__PC)
#define SWI_0_PS		(SWI__0__PS)
#define SWI_0_PC		(SWI__0__PC)
#define SWI_0_DR		(SWI__0__DR)
#define SWI_0_SHIFT	(SWI__0__SHIFT)
#define SWI_0_INTR	((uint16)((uint16)0x0003u << (SWI__0__SHIFT*2u)))

#define SWI_INTR_ALL	 ((uint16)(SWI_0_INTR))


#endif /* End Pins SWI_ALIASES_H */


/* [] END OF FILE */
