/*******************************************************************************
* File Name: SWID.h  
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

#if !defined(CY_PINS_SWID_ALIASES_H) /* Pins SWID_ALIASES_H */
#define CY_PINS_SWID_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SWID_0			(SWID__0__PC)
#define SWID_0_PS		(SWID__0__PS)
#define SWID_0_PC		(SWID__0__PC)
#define SWID_0_DR		(SWID__0__DR)
#define SWID_0_SHIFT	(SWID__0__SHIFT)
#define SWID_0_INTR	((uint16)((uint16)0x0003u << (SWID__0__SHIFT*2u)))

#define SWID_INTR_ALL	 ((uint16)(SWID_0_INTR))


#endif /* End Pins SWID_ALIASES_H */


/* [] END OF FILE */
