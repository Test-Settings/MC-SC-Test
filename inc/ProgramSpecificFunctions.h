/**
 ********************************************************************************
 * Project:             See MotionCode.c
 ********************************************************************************
 * Template-Version:    002.03.0
 ********************************************************************************
 * Description:
 * In these module MotionCode specific functions can be defined.
 ********************************************************************************
 */

#ifndef INC_PROGRAMSPECIFICFUNCTIONS_H_
#define INC_PROGRAMSPECIFICFUNCTIONS_H_

/**---------------- Includes --------------------------------------------------*/
#include <stdbool.h>                                                            // Include datatype bool
#include <stdint.h>                                                             // Include fixed width integer types

/**---------------- Public defines --------------------------------------------*/

/**---------------- Public typedefs -------------------------------------------*/

/**---------------- Public enums ----------------------------------------------*/

/**---------------- Public macros ---------------------------------------------*/

/**---------------- Public structs --------------------------------------------*/

/**---------------- Public module variable & constants declarations -----------*/

/**---------------- Public module function declarations -----------------------*/
extern void programSpecificFunctions_doRelPos(int32_t targetPositionRelative, int32_t targetVelocity);

#endif /* INC_PROGRAMSPECIFICFUNCTIONS_H_ */
