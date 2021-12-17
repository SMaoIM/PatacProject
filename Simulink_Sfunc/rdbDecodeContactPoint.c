/*
 * sfuntmpl_basic.c: Basic 'C' template for a level 2 S-function.
 *
 *  -------------------------------------------------------------------------
 *  | See matlabroot/simulink/src/sfuntmpl_doc.c for a more detailed template |
 *  -------------------------------------------------------------------------
 *
 * Copyright 1990-2001 The MathWorks, Inc.
 * $Revision: 1.26 $
 */


/*
 * You must specify the S_FUNCTION_NAME as the name of your S-function
 * (i.e. replace sfuntmpl_basic with the name of your S-function).
 */

#define S_FUNCTION_NAME rdbDecodeContactPoint
#define S_FUNCTION_LEVEL 2

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
//#define DUMMY_COMPILE
#ifdef DUMMY_COMPILE
#include "slDummyDefs.h"
#else
#include "simstruc.h"
#endif

#include <stdio.h>
#include <string.h>
#include "viRDBIcd.h"

/*
* activate the following lines for dSPACE compilation environment
*/
/*
#ifndef MATLAB_MEX_FILE
#include <brtenv.h>
#endif
*/
  
/* Error handling
 * --------------
 *
 * You should use the following technique to report errors encountered within
 * an S-function:
 *
 *       ssSetErrorStatus(S,"Error encountered due to ...");
 *       return;
 *
 * Note that the 2nd argument to ssSetErrorStatus must be persistent memory.
 * It cannot be a local variable. For example the following will cause
 * unpredictable errors:
 *
 *      mdlOutputs()
 *      {
 *         char msg[256];         {ILLEGAL: to fix use "static char msg[256];"}
 *         sprintf(msg,"Error due to %s", string);
 *         ssSetErrorStatus(S,msg);
 *         return;
 *      }
 *
 * See matlabroot/simulink/src/sfuntmpl_doc.c for more details.
 */

/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */

#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)
  /* Function: mdlCheckParameters =============================================
   * Abstract:
   *    Validate our parameters to verify they are okay.
   */
  static void mdlCheckParameters(SimStruct *S) // S function callback routine
  {
  }

#endif /* MDL_CHECK_PARAMETERS */

static void mdlInitializeSizes(SimStruct *S)	//S function callback routine
{
    ssSetNumContStates(S, 0);		//Simstruct function setting the number of continuous states
    ssSetNumDiscStates(S, 0);		//Simstruct function setting the number of discrete states

    if (!ssSetNumInputPorts(S, 1)) 
        return; //Setting the number of input ports
    
    // configure input on first port    (1x RDB_CONTACT_POINT_t  data)
    ssSetInputPortWidth( S, 0, 14 );
    ssSetInputPortDataType( S, 0, SS_UINT32 );
    ssSetInputPortRequiredContiguous(S, 0, true);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    // configure output ports
    if ( !ssSetNumOutputPorts( S, 9 ) ) 
        return;
    
    ssSetOutputPortWidth(    S, 0, 1 );             // ID
    ssSetOutputPortDataType( S, 0, SS_UINT16 );

    ssSetOutputPortWidth(    S, 1, 1 );
    ssSetOutputPortDataType( S, 1, SS_UINT16 );      // flags
 
    ssSetOutputPortWidth(    S, 2, 3 );
    ssSetOutputPortDataType( S, 2, SS_DOUBLE );      // coord x,y,z
 
    ssSetOutputPortWidth(    S, 3, 3 );
    ssSetOutputPortDataType( S, 3, SS_SINGLE );     //coord h,p,r
 
    ssSetOutputPortWidth(    S, 4, 1 );
    ssSetOutputPortDataType( S, 4, SS_UINT8);        // coord flags
 
    ssSetOutputPortWidth(    S, 5, 1 );
    ssSetOutputPortDataType( S, 5, SS_UINT8);         // coord types
 
    ssSetOutputPortWidth(    S, 6, 1 );
    ssSetOutputPortDataType( S, 6, SS_UINT16 );        // coord system
 
    ssSetOutputPortWidth(    S, 7, 1);
    ssSetOutputPortDataType( S, 7, SS_SINGLE );         // friction
 
    ssSetOutputPortWidth(    S, 8, 1 );
    ssSetOutputPortDataType( S, 8, SS_INT32 );        // player ID
 
    
                   
    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);			//Concerned with work vectors
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    ssSetOptions(S, 0);
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, -1.0);
    ssSetOffsetTime(S, 0, 0.0);
}
   


#define MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
  /* Function: mdlInitializeConditions ========================================
   * Abstract:
   *    In this function, you should initialize the continuous and discrete
   *    states for your S-function block.  The initial states are placed
   *    in the state vector, ssGetContStates(S) or ssGetRealDiscStates(S).
   *    You can also perform any other initialization activities that your
   *    S-function may require. Note, this routine will be called at the
   *    start of simulation and if it is present in an enabled subsystem
   *    configured to reset states, it will be call when the enabled subsystem
   *    restarts execution to reset the states.
   */
  static void mdlInitializeConditions(SimStruct *S)
  {

  }
#endif /* MDL_INITIALIZE_CONDITIONS */



#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START)
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
  }
#endif /*  MDL_START */



/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block. Generally outputs are placed in the output vector, ssGetY(S).
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    RDB_CONTACT_POINT_t  * inData    = (RDB_CONTACT_POINT_t  *) ssGetInputPortSignal( S, 0 );
    unsigned int*  outDataId         = (unsigned int*)    ssGetOutputPortSignal( S, 0 );
    unsigned int* outDataFlags       = (unsigned int*)   ssGetOutputPortSignal( S, 1 );
    double* outDataCoordXYZ          = (double*)   ssGetOutputPortSignal( S, 2 );
    float*  outDataCoordHPR          = (float*)   ssGetOutputPortSignal( S, 3 );
    unsigned char* outDataCoordFlags = (unsigned char*) ssGetOutputPortSignal( S, 4 );
    unsigned char* outDataCoordTypes = (unsigned char*)  ssGetOutputPortSignal( S, 5 );
    unsigned int*  outDataCoordSys   = (unsigned int*) ssGetOutputPortSignal( S, 6 );
    float*  outDataFric              = (float*)  ssGetOutputPortSignal( S, 7 );
    int*        outDataPlayerId  = (int *) ssGetOutputPortSignal( S, 8 );
    
    
    if ( !inData )
        return;
        
    // let's map the data
    *outDataId       = inData->id;
    *outDataFlags    = inData->flags;
    memcpy( outDataCoordXYZ, &(inData->roadDataIn.x), 3 * sizeof (double)) ;
    memcpy( outDataCoordHPR, &( inData->roadDataIn.h), 3 * sizeof( float ) );
    *outDataCoordFlags = inData->roadDataIn.flags;
    *outDataCoordTypes = inData->roadDataIn.type;
    *outDataCoordSys   = inData->roadDataIn.system;
    *outDataFric     = inData->friction;
    *outDataPlayerId = inData->playerId;
}
 


#define MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
  /* Function: mdlUpdate ======================================================
   * Abstract:
   *    This function is called once for every major integration time step.
   *    Discrete states are typically updated here, but this function is useful
   *    for performing any tasks that should only take place once per
   *    integration step.
   */
  static void mdlUpdate(SimStruct *S, int_T tid)
  {
  }
#endif /* MDL_UPDATE */



#define MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
  /* Function: mdlDerivatives =================================================
   * Abstract:
   *    In this function, you compute the S-function block's derivatives.
   *    The derivatives are placed in the derivative vector, ssGetdX(S).
   */
  static void mdlDerivatives(SimStruct *S)
  {
  }
#endif /* MDL_DERIVATIVES */



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
   /*
    * rdbMapperTerminate();
    */
}


/*======================================================*
 * See sfuntmpl_doc.c for the optional S-function methods *
 *======================================================*/

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
