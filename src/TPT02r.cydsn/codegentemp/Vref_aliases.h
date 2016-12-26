/*******************************************************************************
* File Name: Vref.h  
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

#if !defined(CY_PINS_Vref_ALIASES_H) /* Pins Vref_ALIASES_H */
#define CY_PINS_Vref_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Vref_0			(Vref__0__PC)
#define Vref_0_PS		(Vref__0__PS)
#define Vref_0_PC		(Vref__0__PC)
#define Vref_0_DR		(Vref__0__DR)
#define Vref_0_SHIFT	(Vref__0__SHIFT)
#define Vref_0_INTR	((uint16)((uint16)0x0003u << (Vref__0__SHIFT*2u)))

#define Vref_INTR_ALL	 ((uint16)(Vref_0_INTR))


#endif /* End Pins Vref_ALIASES_H */


/* [] END OF FILE */
