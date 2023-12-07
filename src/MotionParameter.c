/**
 ********************************************************************************
 * Project:             See MotionCode.c
 ********************************************************************************
 * Template-Version:    002.03.0
 ********************************************************************************
 * Description:
 * In this file are the names of the MotionParameters defined. In addition are
 * names to the possible values of the MotionCode Debug variables defined.
 * Please be aware of the MotionCode software documentation
********************************************************************************
 */

/**---------------- Includes --------------------------------------------------*/
#include <MotionParameter.h>                                                    // Include MotionCode specific Header
#include <DriveParameters.h>                                                    // Include MotionCode specific Header
#include <DriveLib.h>                                                           // Include MotionCode specific Header
#include <DriveLibIF.h>                                                         // Include MotionCode specific Header
#include <ComObjectIF.h>                                                        // Include MotionCode specific Header
#include <MotionCodeOd.h>                                                       // Include MotionCode specific Header
#include <MotionParameterNames.h>                                               // Include MotionCode specific Header

/**---------------- Private defines -------------------------------------------*/

/**---------------- Private typedefs ------------------------------------------*/

/**---------------- Private enums ---------------------------------------------*/

/**---------------- Private macros --------------------------------------------*/

/**---------------- Private structs -------------------------------------------*/

/**---------------- Private variables & constants -----------------------------*/

/**---------------- Public module variable & constants definitions ------------*/
motion_parameter_t motionParameter;                                             // Define variable "motionParameter" of type "motion_parameter_t"

/**---------------- Private function declarations -----------------------------*/

/**---------------- Private function definitions ------------------------------*/

/**---------------- Public module function definitions ------------------------*/
/*
 *******************************************************************************
 * Description:
 * Function called when MotionCode is executed the first time.
 * --> Set default values of storable motionParameters here
 *******************************************************************************
*/
void setStorableDefaultValues(void)
{
    *motionParameter.debounceTime = 10;                                         // Set debounceTime default value [ms]
}

/*
 *******************************************************************************
 * Description:
 * Function called on every bootup
 * --> Set default values of not storable motionParameters here
 *******************************************************************************
*/
void setNotStorableDefaultValues(void)
{
    motionParameter.myCommand = C_Undefined;                                    // Set myCommand default value
    motionParameter.debugProgramState = D_StateUndefined;                       // Set debugProgramState default value
    motionParameter.myStatus = S_Undefined;                                     // Set myStatus default value
    motionParameter.motionParameterStoreCmd = 0;                                // Set MotionParameterStoreCMD default value
    motionParameter.debug1 = 0;                                                 // Set debug1 default value
    motionParameter.debug2 = 0;                                                 // Set debug2 default value
    motionParameter.debug3 = 0;                                                 // Set debug3 default value
    motionParameter.debug4 = 0;                                                 // Set debug4 default value
    motionParameter.debug5 = 0;                                                 // Set debug5 default value
    motionParameter.debug6 = 0;                                                 // Set debug6 default value
    motionParameter.debug7 = 0;                                                 // Set debug7 default value
    motionParameter.debug8 = 0;                                                 // Set debug8 default value
    motionParameter.debug9 = 0;                                                 // Set debug9 default value
}

/*
 ****************************** GET PARAMETER **********************************
 * Description:
 * GET PARAMETER Function --> Make motionParameter readable
 * This function is called in firmware but defined by MotionCode
 * --> Interface between MotionCode and firmware
 * --> DO NOT REMOVE!
 *******************************************************************************
 * Input values:
 * void* const this --> Only used by firmware
 * com_object_if_variable_t* value --> Only used by firmware
 *******************************************************************************
 * Return values:
 * com_object_if_error_t result --> Only used by firmware
 *******************************************************************************
*/
com_object_if_error_t motionCode_odGetParameter(void* const this, com_object_if_variable_t* value)
{
    com_object_if_error_t result = ERROR_NONE;                                  // DO NOT REMOVE - Initialization of motionCode_odGetParameter()

    switch(PARAMETER)
    {
        /* int32_t */
        case MOTIONCODE_PARAMETER_I32_40:                                       // Assign MOTIONCODE_PARAMETER_I32_40 ..
            value->i32 = (motionParameter.debug1);                              // .. to motionParameter debug1
            break;
        case MOTIONCODE_PARAMETER_I32_41:                                       // Assign MOTIONCODE_PARAMETER_I32_41 ..
            value->i32 = (motionParameter.debug2);                              // .. to motionParameter debug2
            break;
        case MOTIONCODE_PARAMETER_I32_42:                                       // Assign MOTIONCODE_PARAMETER_I32_42 ..
            value->i32 = (motionParameter.debug3);                              // .. to motionParameter debug3
            break;
        case MOTIONCODE_PARAMETER_I32_43:                                       // Assign MOTIONCODE_PARAMETER_I32_43 ..
            value->i32 = (motionParameter.debug4);                              // .. to motionParameter debug4
            break;
        case MOTIONCODE_PARAMETER_I32_44:                                       // Assign MOTIONCODE_PARAMETER_I32_44 ..
            value->i32 = (motionParameter.debug5);                              // .. to motionParameter debug5
            break;
        case MOTIONCODE_PARAMETER_I32_45:                                       // Assign MOTIONCODE_PARAMETER_I32_45 ..
            value->i32 = (motionParameter.debug6);                              // .. to motionParameter debug6
            break;
        case MOTIONCODE_PARAMETER_I32_46:                                       // Assign MOTIONCODE_PARAMETER_I32_46 ..
            value->i32 = (motionParameter.debug7);                              // .. to motionParameter debug7
            break;
        case MOTIONCODE_PARAMETER_I32_47:                                       // Assign MOTIONCODE_PARAMETER_I32_47 ..
            value->i32 = (motionParameter.debug8);                              // .. to motionParameter debug8
            break;
        case MOTIONCODE_PARAMETER_I32_48:                                       // Assign MOTIONCODE_PARAMETER_I32_48 ..
            value->i32 = (motionParameter.debug9);                              // .. to motionParameter debug9
            break;

        case MOTIONCODE_PARAMETER_I32_50:                                       // Assign MOTIONCODE_PARAMETER_I32_50 ..
            value->i32 = (motionParameter.motionParameterStoreCmd);             // .. to motionParameter motionParameterStoreCmd
            break;

        /* uint32_t */
        case MOTIONCODE_PARAMETER_UI32_01:                                      // Assign MOTIONCODE_PARAMETER_UI32_01 ..
            value->ui32 = (motionParameter.myCommand);                          // .. to motionParameter myCommand
            break;
        case MOTIONCODE_PARAMETER_UI32_02:                                      // Assign MOTIONCODE_PARAMETER_UI32_02 ..
            value->ui32 = (motionParameter.myStatus);                           // .. to motionParameter myStatus
            break;
        case MOTIONCODE_PARAMETER_UI32_03:                                      // Assign MOTIONCODE_PARAMETER_UI32_03 ..
            value->ui32 = (motionParameter.debugProgramState);                  // .. to motionParameter debugProgramState
            break;
        case MOTIONCODE_PARAMETER_UI32_04:                                      // Assign MOTIONCODE_PARAMETER_UI32_04 ..
            value->ui32 = *(motionParameter.debounceTime);                      // .. to storable motionParameter debounceTime
            break;
        /* int16_t */

        /* uint16_t */

        /* int8_t */

        /* uint8_t */

        /* default DO NOT CHANGE */
        default:
            result = ERROR_OBJECT_NOT_EXIST;                                    // DO NOT REMOVE - Result if PARAMETER is undefined
            break;
    }
    return result;                                                              // DO NOT REMOVE - Return result to firmware
}

/*
 ****************************** SET PARAMETER **********************************
 * Description:
 * SET PARAMETER Function --> Make motionParameter writable
 * This function is called in firmware but defined by MotionCode
 * --> Interface between MotionCode and firmware
 * --> DO NOT REMOVE!
 *******************************************************************************
 * Input values:
 * void* const this --> Only used by firmware
 * com_object_if_variable_t value --> Only used by firmware
 *******************************************************************************
 * Return values:
 * com_object_if_error_t result --> Only used by firmware
 *******************************************************************************
*/
com_object_if_error_t motionCode_odSetParameter(void* const this, com_object_if_variable_t value)
{
    com_object_if_error_t result = ERROR_NONE;                                  // DO NOT REMOVE - Initialization of motionCode_odSetParameter()
    drive_lib_if_error_t writeError;                                            // DO NOT REMOVE - Initialization of motionCode_odSetParameter()

    switch(PARAMETER)
    {
        /* int32_t */
        case MOTIONCODE_PARAMETER_I32_40:                                       // Assign MOTIONCODE_PARAMETER_I32_40 ..
            (motionParameter.debug1) = value.i32;                               // .. to motionParameter debug1
            break;
        case MOTIONCODE_PARAMETER_I32_41:                                       // Assign MOTIONCODE_PARAMETER_I32_41 ..
            (motionParameter.debug2) = value.i32;                               // .. to motionParameter debug2
            break;
        case MOTIONCODE_PARAMETER_I32_42:                                       // Assign MOTIONCODE_PARAMETER_I32_42 ..
            (motionParameter.debug3) = value.i32;                               // .. to motionParameter debug3
            break;
        case MOTIONCODE_PARAMETER_I32_43:                                       // Assign MOTIONCODE_PARAMETER_I32_43 ..
            (motionParameter.debug4) = value.i32;                               // .. to motionParameter debug4
            break;
        case MOTIONCODE_PARAMETER_I32_44:                                       // Assign MOTIONCODE_PARAMETER_I32_44 ..
            (motionParameter.debug5) = value.i32;                               // .. to motionParameter debug5
            break;
        case MOTIONCODE_PARAMETER_I32_45:                                       // Assign MOTIONCODE_PARAMETER_I32_45 ..
            (motionParameter.debug6) = value.i32;                               // .. to motionParameter debug6
            break;
        case MOTIONCODE_PARAMETER_I32_46:                                       // Assign MOTIONCODE_PARAMETER_I32_46 ..
            (motionParameter.debug7) = value.i32;                               // .. to motionParameter debug7
            break;
        case MOTIONCODE_PARAMETER_I32_47:                                       // Assign MOTIONCODE_PARAMETER_I32_47 ..
            (motionParameter.debug8) = value.i32;                               // .. to motionParameter debug8
            break;
        case MOTIONCODE_PARAMETER_I32_48:                                       // Assign MOTIONCODE_PARAMETER_I32_48 ..
            (motionParameter.debug9) = value.i32;                               // .. to motionParameter debug9
            break;

        case MOTIONCODE_PARAMETER_I32_50:                                       // Assign MOTIONCODE_PARAMETER_I32_50 ..
            (motionParameter.motionParameterStoreCmd) = value.i32;              // .. to motionParameter motionParameterStoreCmd
            break;

        /* uint32_t */
        case MOTIONCODE_PARAMETER_UI32_01:                                      // Assign MOTIONCODE_PARAMETER_UI32_01 ..
            (motionParameter.myCommand) = value.ui32;                           // .. to motionParameter myCommand
            break;
        case MOTIONCODE_PARAMETER_UI32_04:                                      // Assign MOTIONCODE_PARAMETER_UI32_04 ..
            *(motionParameter.debounceTime) = value.ui32;                       // .. to storable motionParameter debounceTime
            break;

        /* int16_t */

        /* uint16_t */

        /* int8_t */

        /* uint8_t */

        /* default DO NOT CHANGE */
        default:
            result = ERROR_OBJECT_NOT_EXIST;                                    // DO NOT REMOVE - Result if PARAMETER is undefined
            break;
    }
    return result;                                                              // DO NOT REMOVE - Return result to firmware
}
