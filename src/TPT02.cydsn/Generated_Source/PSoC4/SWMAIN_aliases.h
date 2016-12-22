/*******************************************************************************
* File Name: SWMAIN.h  
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

#if !defined(CY_PINS_SWMAIN_ALIASES_H) /* Pins SWMAIN_ALIASES_H */
#define CY_PINS_SWMAIN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SWMAIN_0			(SWMAIN__0__PC)
#define SWMAIN_0_PS		(SWMAIN__0__PS)
#define SWMAIN_0_PC		(SWMAIN__0__PC)
#define SWMAIN_0_DR		(SWMAIN__0__DR)
#define SWMAIN_0_SHIFT	(SWMAIN__0__SHIFT)
#define SWMAIN_0_INTR	((uint16)((uint16)0x0003u << (SWMAIN__0__SHIFT*2u)))

#define SWMAIN_INTR_ALL	 ((uint16)(SWMAIN_0_INTR))


#endif /* End Pins SWMAIN_ALIASES_H */


/* [] END OF FILE */
