/*
 * You must specify the S_FUNCTION_NAME as the name of your S-function
 * (i.e. replace sfuntmpl_basic with the name of your S-function).
 */

#define S_FUNCTION_NAME rdbDecodeRoadMark
#define S_FUNCTION_LEVEL 2

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
// #define DUMMY_COMPILE
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
    
    // configure input on first port    (1x RDB_ROADMARK_t data)
    ssSetInputPortWidth( S, 0, 19 );
    ssSetInputPortDataType( S, 0, SS_UINT32 );
    ssSetInputPortRequiredContiguous(S, 0, true);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    // configure output ports
    if ( !ssSetNumOutputPorts( S, 12 ) ) 
        return;
    
    ssSetOutputPortWidth(    S, 0, 1 );            // playerID
    ssSetOutputPortDataType( S, 0, SS_UINT32 );

    ssSetOutputPortWidth(    S, 1, 1 );
    ssSetOutputPortDataType( S, 1, SS_INT8 );    // markId
 
    ssSetOutputPortWidth(    S, 2, 1 );
    ssSetOutputPortDataType( S, 2, SS_INT8 );      // laneId
 
    ssSetOutputPortWidth(    S, 3, 2 );
    ssSetOutputPortDataType( S, 3, SS_DOUBLE );     // curvHor,curvHordot
 
    ssSetOutputPortWidth(    S, 4, 2 );
    ssSetOutputPortDataType( S, 4, SS_SINGLE );    //  startDx,peiviewDx
 
    ssSetOutputPortWidth(    S, 5, 2);
    ssSetOutputPortDataType( S, 5, SS_SINGLE );    // mark width, hight
 
    ssSetOutputPortWidth(    S, 6, 2 );
    ssSetOutputPortDataType( S, 6, SS_SINGLE );    // mark lateralDist, yawRel
 
    ssSetOutputPortWidth(    S, 7, 2 );
    ssSetOutputPortDataType( S, 7, SS_DOUBLE );    // curvVert, curvVertDot
 
    ssSetOutputPortWidth(    S, 8, 1 );
    ssSetOutputPortDataType( S, 8, SS_UINT8 );    // mark type
 
    ssSetOutputPortWidth(    S, 9, 1 );
    ssSetOutputPortDataType( S, 9, SS_UINT8 );    // mark color
                   
    ssSetOutputPortWidth(    S, 10, 2 );
    ssSetOutputPortDataType( S, 10, SS_UINT8 );    // mark prev/next ID

    ssSetOutputPortWidth(    S, 11, 1 );
    ssSetOutputPortDataType( S, 11, SS_UINT32 );    //roadID
    
                   
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
    RDB_ROADMARK_t* inData           = (RDB_ROADMARK_t*) ssGetInputPortSignal( S, 0 );
    unsigned int*  outDataId         = (unsigned int*)  ssGetOutputPortSignal( S, 0 );
    char*          outDataMarkId     = (char*)          ssGetOutputPortSignal( S, 1 );
    char*          outDataLaneId     = (char*)          ssGetOutputPortSignal( S, 2 );
    double*        outDataCurvHor    = (double*)        ssGetOutputPortSignal( S, 3 );
    float*         outDataStaPrewDx  = (float*)         ssGetOutputPortSignal( S, 4 );
    float*         outDataRoadWidHgt = (float*)         ssGetOutputPortSignal( S, 5 );
    float*         outDataMarkOffset = (float*)         ssGetOutputPortSignal( S, 6 );
    double*        outDataCurvVert   = (double*)        ssGetOutputPortSignal( S, 7 );
    unsigned char* outDataType       = (unsigned char*) ssGetOutputPortSignal( S, 8 );
    unsigned char* outDataColor      = (unsigned char*) ssGetOutputPortSignal( S, 9 );
    char*          outDataPrevNextID = (char*)          ssGetOutputPortSignal( S, 10 );
    unsigned int*  outDataRoadId     = (unsigned int*)  ssGetOutputPortSignal( S, 11 );
    
    if ( !inData )
        return;

    // let's map the data
    *outDataId         = inData->playerId;  
    *outDataMarkId     = inData->id;    
    *outDataLaneId     = inData->laneId;    
    memcpy(outDataCurvHor, &(inData->curvHor), 2 * sizeof(double));
    memcpy(outDataStaPrewDx, &(inData->startDx), 2 * sizeof(float));
    memcpy(outDataRoadWidHgt, &(inData->width), 2 * sizeof(float));
    memcpy(outDataMarkOffset, &(inData->lateralDist), 2 * sizeof(float));
    memcpy(outDataCurvVert, &(inData->curvVert), 2 * sizeof(double));
    *outDataType       = inData->type;
    *outDataColor      = inData->color;
    memcpy(outDataPrevNextID, &(inData->prevId), 2 * sizeof(int8_t));
    *outDataRoadId     = inData->roadId;
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
}

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
