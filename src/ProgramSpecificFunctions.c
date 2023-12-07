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

/**---------------- Includes --------------------------------------------------*/
#include <MotionParameter.h>                                                    // Include MotionCode specific header
#include <DriveLib.h>                                                           // Include MotionCode specific header
#include <DriveLibIF.h>                                                         // Include MotionCode specific header
#include <DriveParameters.h>                                                    // Include MotionCode specific header
#include <MotionCodeFunctionLib.h>                                              // Include MotionCodeLib.h header
#include <ProgramSpecificFunctions.h>                                           // Include ProgramSpecificFunctions.h header
#include <stdlib.h>                                                             // Include general utilities

/**---------------- Private defines -------------------------------------------*/

/**---------------- Private typedefs ------------------------------------------*/

/**---------------- Private enums ---------------------------------------------*/

/**---------------- Private macros --------------------------------------------*/

/**---------------- Private structs -------------------------------------------*/

/**---------------- Private variables & constants -----------------------------*/

/**---------------- Public module variable & constants definitions ------------*/

/**---------------- Private function declarations -----------------------------*/

/**---------------- Private function definitions ------------------------------*/

/**---------------- Public module function definitions ------------------------*/
/*
 *******************************************************************************
 * Description:
 * Example function of the template. This function executes a relative
 * positioning with the given target velocity and target position.
 *******************************************************************************
 * Input values:
 * int32_t targetPositionRelative --> target position for relative positioning
 * int32_t targetVelocity --> target velocity for relative positioning
 *******************************************************************************
*/
void programSpecificFunctions_doRelPos(int32_t targetPositionRelative, int32_t targetVelocity)
{
    drive->writeUi8(DEVICE_ModeOfOperation, 7);                                 // Set position mode
    drive->writeI32(VEL_TargetValue, targetVelocity);                           // Set target Velocity
    drive->writeUi8(DEVICE_EnablePowerStage, 1);                                // Enable powerstage
    drive->writeI32(POS_PositioningRelative, targetPositionRelative);           // Set relative target position
}
