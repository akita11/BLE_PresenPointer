/*******************************************************************************
* File Name: SWO.h  
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

#if !defined(CY_PINS_SWO_ALIASES_H) /* Pins SWO_ALIASES_H */
#define CY_PINS_SWO_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SWO_0			(SWO__0__PC)
#define SWO_0_PS		(SWO__0__PS)
#define SWO_0_PC		(SWO__0__PC)
#define SWO_0_DR		(SWO__0__DR)
#define SWO_0_SHIFT	(SWO__0__SHIFT)
#define SWO_0_INTR	((uint16)((uint16)0x0003u << (SWO__0__SHIFT*2u)))

#define SWO_INTR_ALL	 ((uint16)(SWO_0_INTR))


#endif /* End Pins SWO_ALIASES_H */


/* [] END OF FILE */
