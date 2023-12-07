/**
 ********************************************************************************
 * Project:             See MotionCode.c
 ********************************************************************************
 * Template-Version:    002.03.0
 ********************************************************************************
 * Description:
 * In this file are the names of the MotionParameters defined. In addition are
 * names to the possible values of the MotionCode Debug variables defined.
 * Please be aware of the MotionCode software documentation.
********************************************************************************
 */

#ifndef INC_MOTIONPARAMETER_H_
#define INC_MOTIONPARAMETER_H_

/**---------------- Includes --------------------------------------------------*/
#include <stdint.h>                                                             // Include fixed width integer types
#include <stdbool.h>                                                            // Include datatype bool

/**---------------- Public defines --------------------------------------------*/

/**---------------- Public typedefs -------------------------------------------*/
typedef struct motion_parameter motion_parameter_t;                             // Typedef "motion_parameter_t" with structure of "motion_parameter"

/**---------------- Public enums ----------------------------------------------*/
/*
 *******************************************************************************
 * Description:
 * Assign tags to values of myCommand
 *******************************************************************************
*/
enum tags_for_myCommand
{
    C_ClearError            = 15,                                               // Command C_ClearError --> IN0=1 IN1=1 IN2=1 IN3=1 (IN4=0)
    C_Stop                  = 0,                                                // Command C_Stop       --> IN0=0 IN1=0 IN2=0 IN3=0 (IN4=0)
    C_StartMoving           = 1,                                                // Command C_StartMoving--> IN0=1 IN1=0 IN2=0 IN3=0 (IN4=0)
    C_Undefined             = 0xFF,                                             // Mandatory! Define value which cannot happen (for init of variable "oldMyCommand" in stateControl)
};

/*
 *******************************************************************************
 * Description:
 * Assign names to values of myStatus
 *******************************************************************************
*/
enum tags_for_myStatus
{
    S_Undefined             = 0,
    S_Error                 = 1,
    S_ErrorCleared          = 2,
    S_Stopped               = 10,
    S_Moving                = 20,
};

/*
 *******************************************************************************
 * Description:
 * Assign names to values of debugProgramState Debug variable
 *******************************************************************************
*/
enum tags_for_debugProgramState
{
    D_StateUndefined        = 0,
    D_StateError            = 1,
    D_StateNOP              = 10,
    D_StateStop             = 20,
    D_StateStartMoving      = 30,
};

/**---------------- Public macros ---------------------------------------------*/

/**---------------- Public structs --------------------------------------------*/
/*
 *******************************************************************************
 * Description:
 * This structure is used by MotionCode and Firmware to declare
 * MotionParameters.
 * --> Declare MotionParameters here
 *******************************************************************************
*/
struct motion_parameter
{
    /* storable motion parameter */
    uint32_t* debounceTime;                         // MOTIONCODE_PARAMETER_UI32_04 5102.04h rws

    /* not storable motion parameter */
    uint32_t myCommand;                             // MOTIONCODE_PARAMETER_UI32_01 5102.01h rw
    uint32_t myStatus;                              // MOTIONCODE_PARAMETER_UI32_02 5102.02h r
    uint32_t debugProgramState;                     // MOTIONCODE_PARAMETER_UI32_03 5102.03h r
    int32_t debug1;                                 // MOTIONCODE_PARAMETER_I32_40  5101.28h rw
    int32_t debug2;                                 // MOTIONCODE_PARAMETER_I32_41  5101.29h rw
    int32_t debug3;                                 // MOTIONCODE_PARAMETER_I32_42  5101.2Ah rw
    int32_t debug4;                                 // MOTIONCODE_PARAMETER_I32_43  5101.2Bh rw
    int32_t debug5;                                 // MOTIONCODE_PARAMETER_I32_44  5101.2Ch rw
    int32_t debug6;                                 // MOTIONCODE_PARAMETER_I32_45  5101.2Dh rw
    int32_t debug7;                                 // MOTIONCODE_PARAMETER_I32_46  5101.2Eh rw
    int32_t debug8;                                 // MOTIONCODE_PARAMETER_I32_47  5101.2Fh rw
    int32_t debug9;                                 // MOTIONCODE_PARAMETER_I32_48  5101.30h rw
    int32_t motionParameterStoreCmd;                // MOTIONCODE_PARAMETER_I32_50  5101.32h rw
};

/**---------------- Public module variable & constants declarations -----------*/
extern motion_parameter_t motionParameter;                                      // Declare object "motionParameter" with datatype "motion_parameter_t" using the structure "motion_parameter"

/**---------------- Public module function declarations -----------------------*/
extern void setStorableDefaultValues(void);
extern void setNotStorableDefaultValues(void);

#endif /* INC_MOTIONPARAMETER_H_ */
