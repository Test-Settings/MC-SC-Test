/**
 ********************************************************************************
 * Project:             MotionCodeTemplate
 ********************************************************************************
 * Template-Version:    002.03.0
 * Author:              Name
 ********************************************************************************
 * Description:
 * Describe the MotionCode here.
 * Please be aware of the MotionCode software documentation.
********************************************************************************
 */

/**---------------- Includes --------------------------------------------------*/
#include <stdint.h>                                                             // Include fixed width integer types
#include <stdlib.h>                                                             // Include general utilities
#include <stdbool.h>                                                            // Include datatype bool
#include <MotionCode.h>                                                         // Include MotionCode specific header
#include <MotionCodeNotificationType.h>                                         // Include MotionCode specific header
#include <MotionParameter.h>                                                    // Include MotionCode specific header
#include <DriveLib.h>                                                           // Include MotionCode specific header
#include <DriveLibIF.h>                                                         // Include MotionCode specific header
#include <DriveParameters.h>                                                    // Include MotionCode specific header
#include <MotionCodeFunctionLib.h>                                              // Include MotionCodeFunctionLib.h header
#include <ProgramSpecificFunctions.h>                                           // Include ProgramSpecificFunctions.h header

/**---------------- Private defines -------------------------------------------*/

/**---------------- Private typedefs ------------------------------------------*/
typedef void (*stateMachine) (void);                                            // Type definition "stateMachine"

/**---------------- Private enums ---------------------------------------------*/

/**---------------- Private macros --------------------------------------------*/

/**---------------- Private structs -------------------------------------------*/

/**---------------- Private variables & constants -----------------------------*/
static stateMachine stateFunction;                                              // Generate stateFunction from type stateMachine
static bool_t firstTimeExecuted = false;                                        // Flag which is true when the MotionCode is executed the first time

/**---------------- Public module variable & constants definitions ------------*/

/**---------------- Private function declarations -----------------------------*/
void bootupRoutine(void);                                                       // Once executed after bootup
void stateControl(void);                                                        // Basis of state machine: Defines next state
void stateError(void);                                                          // Executed if error is existing
void stateNOP(void);                                                            // No Operation
void stateStop(void);                                                           // Executed if command C_Stop
void stateStartMoving(void);                                                    // Executed if command C_StartMoving

/**---------------- Private function definitions ------------------------------*/
/*
 *******************************************************************************
 * Description:
 * This function is called once after bootup. It is used for initialisation of
 * the not storable MotionParameters.
 *******************************************************************************
*/
void bootupRoutine(void)
{
    drive->restoreExtended(0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu); // restore all storable motion parameters
    setNotStorableDefaultValues();                                              // Set default values of not storable MotionParameter

    drive->writeUi8(DEVICE_Command, 1);                                         // .. Clear Error
}

/*
 *******************************************************************************
 * Description:
 * This function is called cyclic. It is the base of the running state machine.
 * --> It analyzes the active myCommand and DEVICE_ErrorCode.
 * --> If they change: Depending on them the next stateFunction is defined.
 *******************************************************************************
*/
void stateControl(void)
{
    motionParameter.myCommand = motionCodeFunctionLib_readDebouncedDigitalInputs(0xFF, *motionParameter.debounceTime);    // Read DigitalInputs into myCommand

    static uint32_t oldMyCommand = C_Undefined;                                 // Stored internal variable to detect changes of myCommand

    int16_t actualError = 0;                                                    // Local variable to read DEVICE_ErrorCode
    drive->readI16(DEVICE_ErrorCode, &actualError);                             // Read Error Register

    if(actualError != 0)                                                        // If an error is existing ..
    {
        oldMyCommand = C_Undefined;                                             // .. reset oldMyCommand
        stateFunction = &stateError;                                            // .. go to stateError
    }
    else if(motionParameter.myCommand != oldMyCommand)                          // If no error and myCommand did change => define next state
    {
        oldMyCommand = motionParameter.myCommand;                               // .. Overwrite old myCommand

        switch(motionParameter.myCommand)                                       // .. Define next stateFunction depending on myCommand
        {
            case C_Stop:                                                        // .. If command == C_Stop ..
                stateFunction = &stateStop;                                     // .. .. go to stateStop
                break;
            case C_StartMoving:                                                 // .. If command == C_StartMoving ..
                stateFunction = &stateStartMoving;                              // .. .. go to stateStartMoving
                break;
            default:                                                            // .. If command is undefined ..
                motionParameter.debugProgramState = D_StateUndefined;           // .. .. set StateUndefined for debugging
                stateFunction = &stateControl;                                  // .. .. do not call any state
                break;
        }
    }
}

/*
 *******************************************************************************
 * Description:
 * This stateFunction is called if an error occurs (see DEVICE_ErrorCode).
 * --> Defines the actions to be done if an error occurs
 *******************************************************************************
*/
void stateError(void)
{
    motionParameter.debugProgramState = D_StateError;                           // Set StateError for debugging

    // TODO: Define actions to be done when Error occurs

    if(motionParameter.myCommand == C_ClearError)                               // If command == C_ClearError
    {
        drive->writeUi8(DEVICE_Command, 1);                                     // .. clear error
    }

    int16_t actualError = 0;                                                    // Local variable to read DEVICE_ErrorCode
    drive->readI16(DEVICE_ErrorCode, &actualError);                             // Read Error Register
    if(actualError == 0)                                                        // If error is cleared ..
    {
        motionParameter.myStatus = S_ErrorCleared;                              // .. set myStatus S_ErrorCleared
    }
    else
    {
        motionParameter.myStatus = S_Error;                                     // .. else set myStatus S_Error
    }
}

/*
 *******************************************************************************
 * Description:
 * This stateFunction can be used to set the MotionCode in 'no operation' mode.
 *******************************************************************************
*/
void stateNOP(void)
{
    motionParameter.debugProgramState = D_StateNOP;                             // Set StateNOP for debugging
    stateFunction = &stateControl;                                              // Do not call this state again
}

/*
 *******************************************************************************
 * Description:
 * This stateFunction is called if myCommand C_Stop is detected.
 * --> It stops the motor.
 *******************************************************************************
*/
void stateStop(void)
{
    motionParameter.debugProgramState = D_StateStop;                            // Set StateStop for debugging

    // TODO: Define actions to be done in this state
//    drive->writeUi8(DEVICE_Command, 3);                                         // CMD_Halt --> Stop Motor

    motionParameter.myStatus = S_Stopped;                                       // Set S_Stopped
}

/*
 *******************************************************************************
 * Description:
 * This stateFunction is called if myCommand C_StartMoving is detected.
 * --> It starts the motor.
 *******************************************************************************
*/
void stateStartMoving(void)
{
    motionParameter.debugProgramState = D_StateStartMoving;                     // Set StateStartMoving for debugging

    // TODO: Define actions to be done in this state
//    programSpecificFunctions_doRelPos(512, 2000);                               // Do relative positioning on 512 increments with 2000 rpm

    motionParameter.myStatus = S_Moving;                                        // Set S_Moving
}


/**---------------- Public module function definitions ------------------------*/
/*
 *******************************************************************************
 * Description:
 * This is the 'MotionCode main function' executed by the motor firmware.
 * --> It defines the really running MotionCode
 * --> DO NOT REMOVE OR RENAME
 *******************************************************************************
*/
void motionCode_main(void* pd)
{
    if(firstTimeExecuted == true)                                               // If MotionCode is executed the first time ..
    {
        while(true)                                                             // .. do not execute the MotionCode ..
        {
            motionCodeFunctionLib_checkMotionParameterStoreCmdExtended(motionParameter.motionParameterStoreCmd);    // .. .. just check motionParameterStoreCmd
        }
    }
    else                                                                        // Else (If MotionCode is not executed the first time) ..
    {
        bootupRoutine();                                                        // .. call bootup routine
        stateFunction = &stateControl;                                          // .. set stateControl as first state

        while(true)                                                             // .. while MotionCode is running ..
        {
            motionCodeFunctionLib_checkMotionParameterStoreCmdExtended(motionParameter.motionParameterStoreCmd);    // .. .. check motionParameterStoreCmd
            stateControl();                                                     // .. .. call state Control
            stateFunction();                                                    // .. .. call state machine
        }
    }
}

/*
 *******************************************************************************
 * Description:
 * This function is called during system startup and before main function.
 * --> See MotionCode documentation for details.
 * --> DO NOT REMOVE OR RENAME
 *******************************************************************************
*/
void motionCode_init(void)
{
    /* make motion parameter storable */
    motionParameter.debounceTime        = &drive->memory[0]->ui32;               // Assign memory-field 0 to debounceTime
}

/*
 *******************************************************************************
 * Description:
 * This function is called by the system on certain notification types. The
 * different notificationTypes are set by different events by the firmware.
 * --> See MotionCode documentation for details.
 * --> DO NOT REMOVE OR RENAME
 *******************************************************************************
*/
void motionCode_notification (motion_code_notification_type_t notificationType)
{
    switch(notificationType)                                                    // Determine witch notoficationType is true
    {
        case UPDATED_MOTION_CODE:                                               // UPDATED_MOTION_CODE is called when the MotionCode is executed the first time
            setStorableDefaultValues();                                         // .. set  default values of storable MotionParameters
            drive->storeExtended(0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu);    // .. store all storable MotionParameters
            firstTimeExecuted = true;                                           // .. set firstTimeExecuted
            break;
        default:
            break;
    }
}
