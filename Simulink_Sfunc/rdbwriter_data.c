/*
 * RDB writer routine for VIRES Virtual Test Drive
 */


/*
 * You must specify the S_FUNCTION_NAME as the name of your S-function
 * (i.e. replace sfuntmpl_basic with the name of your S-function).
 */

#define S_FUNCTION_NAME rdbwriter_data
#define S_FUNCTION_LEVEL 2

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
/* #define DUMMY_COMPILE */
#ifdef DUMMY_COMPILE
#include "slDummyDefs.h"
#else
#include "simstruc.h"
#endif

#include "viRDBIcd.h"
#include <stdio.h>
#include <string.h>

// special local definition for output message
typedef struct
{
    RDB_MSG_HDR_t           hdr;              
    RDB_MSG_ENTRY_HDR_t     entrySOF;    
    RDB_MSG_ENTRY_HDR_t     entrydrivercontrol;
    RDB_DRIVER_CTRL_t       drivercontrol;
    RDB_MSG_ENTRY_HDR_t     entryObjectState; 
    RDB_OBJECT_STATE_t      objectState[2];
	RDB_MSG_ENTRY_HDR_t     entryRoadMark; 
	RDB_ROADMARK_t 			roadMark;
	RDB_MSG_ENTRY_HDR_t     entryLaneInfo; 
	RDB_LANE_INFO_t 		laneInfo;
	RDB_MSG_ENTRY_HDR_t     entryRoadPos; 
	RDB_ROAD_POS_t 			roadPos;
	/*
    RDB_MSG_ENTRY_HDR_t     entryWheelState; 
    RDB_WHEEL_BASE_t        wheelState[4];
    RDB_MSG_ENTRY_HDR_t     entryEngine; 
    RDB_ENGINE_BASE_t       engine;
    RDB_MSG_ENTRY_HDR_t     entryDrivetrain; 
    RDB_DRIVETRAIN_BASE_t   drivetrain;
    */
    RDB_MSG_ENTRY_HDR_t     entryVehicleSystems; 
    RDB_VEHICLE_SYSTEMS_t   vehicleSystems;
    
    RDB_MSG_ENTRY_HDR_t     entryEOF;
} MY_RDB_MSG_t;

static unsigned int sTotalMsgSize             = sizeof( MY_RDB_MSG_t );
static unsigned int sNetworkStreamNoElements  = sizeof( MY_RDB_MSG_t )/ 4; // msg size, measured in [unsigned int]
static unsigned int sNetworkStreamElementSize = sizeof( unsigned int );    // bytes per network element

 
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

    if (!ssSetNumInputPorts(S, 7)) 
        return; //Setting the number of input ports
    
    // configure input on first port ( active / inactive )
    ssSetInputPortWidth( S, 0, 1 );
    ssSetInputPortDataType( S, 0, SS_UINT32 );
    ssSetInputPortRequiredContiguous(S, 0, true);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    // configure input on second port ( simulation time )
    ssSetInputPortWidth( S, 1, 1 );
    ssSetInputPortDataType( S, 1, SS_DOUBLE );
    ssSetInputPortRequiredContiguous(S, 1, true);
    ssSetInputPortDirectFeedThrough(S, 1, 1);

    // configure input on third port ( simulation frame )
    ssSetInputPortWidth( S, 2, 1 );
    ssSetInputPortDataType( S, 2, SS_UINT32 );
    ssSetInputPortRequiredContiguous(S, 2, true);
    ssSetInputPortDirectFeedThrough(S, 2, 1);

    // configure input on fourth port ( own ID )
    ssSetInputPortWidth( S, 3, 1 );
    ssSetInputPortDataType( S, 3, SS_UINT32 );
    ssSetInputPortRequiredContiguous(S, 3, true);
    ssSetInputPortDirectFeedThrough(S, 3, 1);

    // configure input on fifth port ( own steeingwheel, steeringspeed, throttlepedal,brakepedal )
    ssSetInputPortWidth( S, 4, 4 );
    ssSetInputPortDataType( S, 4, SS_DOUBLE );
    ssSetInputPortRequiredContiguous(S, 4, true);
    ssSetInputPortDirectFeedThrough(S, 4, 1);

    // configure input on sixth port ( own acceltgt, steeringtgt, speedtgt )
    ssSetInputPortWidth( S, 5, 3 );
    ssSetInputPortDataType( S, 5, SS_DOUBLE );
    ssSetInputPortRequiredContiguous(S, 5, true);
    ssSetInputPortDirectFeedThrough(S, 5, 1);

    // configure input on seventh port ( light flag )
    ssSetInputPortWidth( S, 6, 1 );
    ssSetInputPortDataType( S, 6, SS_UINT32 );
    ssSetInputPortRequiredContiguous(S, 6, true);
    ssSetInputPortDirectFeedThrough(S, 6, 1);
    
    /*
    // configure input on fifth port ( own X, Y, Z, H, P, R )
    ssSetInputPortWidth( S, 4, 6 );
    ssSetInputPortDataType( S, 4, SS_DOUBLE );
    ssSetInputPortRequiredContiguous(S, 4, true);
    ssSetInputPortDirectFeedThrough(S, 4, 1);

    // configure input on sixth port ( own Xdot, Ydot, Zdot, Hdot, Pdot, Rdot )
    ssSetInputPortWidth( S, 5, 6 );
    ssSetInputPortDataType( S, 5, SS_DOUBLE );
    ssSetInputPortRequiredContiguous(S, 5, true);
    ssSetInputPortDirectFeedThrough(S, 5, 1);

    // configure input on seventh port ( sync flag )
    ssSetInputPortWidth( S, 6, 1 );
    ssSetInputPortDataType( S, 6, SS_UINT32 );
    ssSetInputPortRequiredContiguous(S, 6, true);
    ssSetInputPortDirectFeedThrough(S, 6, 1);

    // configure input on 8th port ( wheel front left: radiusStatic, springCompression, rotAngle, slip, steeringAngle )
    ssSetInputPortWidth( S, 7, 5 );
    ssSetInputPortDataType( S, 7, SS_DOUBLE );
    ssSetInputPortRequiredContiguous(S, 7, true);
    ssSetInputPortDirectFeedThrough(S, 7, 1);
    
    // configure input on 9th port ( wheel front right: radiusStatic, springCompression, rotAngle, slip, steeringAngle )
    ssSetInputPortWidth( S, 8, 5 );
    ssSetInputPortDataType( S, 8, SS_DOUBLE );
    ssSetInputPortRequiredContiguous(S, 8, true);
    ssSetInputPortDirectFeedThrough(S, 8, 1);
    
    // configure input on 10th port ( wheel rear left: radiusStatic, springCompression, rotAngle, slip, steeringAngle )
    ssSetInputPortWidth( S, 9, 5 );
    ssSetInputPortDataType( S, 9, SS_DOUBLE );
    ssSetInputPortRequiredContiguous(S, 9, true);
    ssSetInputPortDirectFeedThrough(S, 9, 1);
    
    // configure input on 11th port ( wheel rear right: radiusStatic, springCompression, rotAngle, slip, steeringAngle )
    ssSetInputPortWidth( S, 10, 5 );
    ssSetInputPortDataType( S, 10, SS_DOUBLE );
    ssSetInputPortRequiredContiguous(S, 10, true);
    ssSetInputPortDirectFeedThrough(S, 10, 1);

    // configure input on 12th port ( engine information: load [0.0..1.0], speed [1/s] )
    ssSetInputPortWidth( S, 11, 2 );
    ssSetInputPortDataType( S, 11, SS_DOUBLE );
    ssSetInputPortRequiredContiguous(S, 11, true);
    ssSetInputPortDirectFeedThrough(S, 11, 1);

    // configure input on 13th port ( drivetrain information: gearbox type, drivetrain type, gear )
    ssSetInputPortWidth( S, 12, 3 );
    ssSetInputPortDataType( S, 12, SS_UINT32 );
    ssSetInputPortRequiredContiguous(S, 12, true);
    ssSetInputPortDirectFeedThrough(S, 12, 1);

    // configure input on 14th port ( vehicle system information: light mask, steering wheel torque )
    ssSetInputPortWidth( S, 13, 2 );
    ssSetInputPortDataType( S, 13, SS_DOUBLE );
    ssSetInputPortRequiredContiguous(S, 13, true);
    ssSetInputPortDirectFeedThrough(S, 13, 1);
    */


    // configure output ports
    if ( !ssSetNumOutputPorts( S, 3 ) ) 
        return;
    
    // port 0 is the debugging information vector with 200 * 4 bytes
    ssSetOutputPortWidth(    S, 0, 200 );
    ssSetOutputPortDataType( S, 0, SS_UINT32 );
    
    // data package which is to be sent via RDB
    // port 1 holds the number of valid bytes in port 2 (0 if no message is available)
    // port 2 holds a complete RDB message (with sTotalMsgSize bytes, i.e. sNetworkStreamNoElements * 4 bytes)
    ssSetOutputPortWidth(    S, 1, 1 );
    ssSetOutputPortDataType( S, 1, SS_UINT32 );
    ssSetOutputPortWidth(    S, 2, sNetworkStreamNoElements );
    ssSetOutputPortDataType( S, 2, SS_UINT32 );
    
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
    static unsigned int sLastSimFrame = 0;
    static double       sLastSimTime  = 0.0;
    static unsigned int sLastActive   = 0;
    
    /* input data */
    unsigned int *pInActive      = (unsigned int*)ssGetInputPortSignal( S, 0 );
    double       *pInSimTime     = (double*)ssGetInputPortSignal( S, 1 );
    unsigned int *pInSimFrame    = (unsigned int*)ssGetInputPortSignal( S, 2 );
    unsigned int *pInOwnId       = (unsigned int*)ssGetInputPortSignal( S, 3 );
    double       *pInDriverCtrl  = (double*)ssGetInputPortSignal( S, 4 );
    double       *pInVehState    = (double*)ssGetInputPortSignal( S, 5 );
    unsigned int *pInLightSt     = (unsigned int*)ssGetInputPortSignal( S, 6 );

    /*
    double       *pInOwnPos      = (double*)ssGetInputPortSignal( S, 4 );
    double       *pInOwnSpeed    = (double*)ssGetInputPortSignal( S, 5 );
    unsigned int *pInSync        = (unsigned int*)ssGetInputPortSignal( S, 6 );
    double       *pInWheelFL     = (double*)ssGetInputPortSignal( S, 7 );
    double       *pInWheelFR     = (double*)ssGetInputPortSignal( S, 8 );
    double       *pInWheelRL     = (double*)ssGetInputPortSignal( S, 9 );
    double       *pInWheelRR     = (double*)ssGetInputPortSignal( S, 10 );
    double       *pInEngine      = (double*)ssGetInputPortSignal( S, 11 );
    unsigned int *pInDrivetrain  = (unsigned int*)ssGetInputPortSignal( S, 12 );
    double       *pInVehSys      = (double*)ssGetInputPortSignal( S, 13 );
    */

    /* output data */
    unsigned int *pOutDebugData  = ssGetOutputPortSignal(S,0);
    unsigned int *pOutMsgSize    = ssGetOutputPortSignal(S,1);
    unsigned int *pOutMsg        = ssGetOutputPortSignal(S,2);
    char         *pOutData       = ( char* )pOutMsg;
    
    MY_RDB_MSG_t* rdbMsg = ( MY_RDB_MSG_t* )pOutMsg;

    // initialize and reset the output
    *pOutMsgSize = 0;
    
    memset( pOutMsg, 0, sTotalMsgSize );
    
    // is valid input available
    if ( ( *pInActive == 0 ) || ( *pInSimTime == sLastSimTime ) || ( *pInSimFrame == sLastSimFrame ) )
        return;
        
    // in first frame, request contact points
    if ( !sLastActive )
    {
        sLastActive = 1;
    }
        
    // register time and frame of last simulation call    
    sLastSimFrame = *pInSimFrame;
    sLastSimTime  = *pInSimTime;
    
    // now fill the message
    
    // first the header
    rdbMsg->hdr.magicNo    = RDB_MAGIC_NO;
    rdbMsg->hdr.version    = RDB_VERSION;
    rdbMsg->hdr.headerSize = sizeof( RDB_MSG_HDR_t );
    rdbMsg->hdr.dataSize   = 8 * sizeof( RDB_MSG_ENTRY_HDR_t ) + sizeof( RDB_DRIVER_CTRL_t )+2*sizeof(RDB_OBJECT_STATE_t) +sizeof(RDB_ROADMARK_t)+sizeof(RDB_LANE_INFO_t)+sizeof(RDB_ROAD_POS_t)+sizeof(RDB_VEHICLE_SYSTEMS_t);
    rdbMsg->hdr.frameNo    = *pInSimFrame;
    rdbMsg->hdr.simTime    = *pInSimTime;

    // second: start-of-frame
    rdbMsg->entrySOF.headerSize  = sizeof( RDB_MSG_ENTRY_HDR_t );
    rdbMsg->entrySOF.dataSize    = 0;
    rdbMsg->entrySOF.elementSize = 0;
    rdbMsg->entrySOF.pkgId       = RDB_PKG_ID_START_OF_FRAME;
    rdbMsg->entrySOF.flags       = 0;
    
    // third: driver control 
    rdbMsg->entrydrivercontrol.headerSize  = sizeof( RDB_MSG_ENTRY_HDR_t );
    rdbMsg->entrydrivercontrol.dataSize    = sizeof( RDB_DRIVER_CTRL_t );
    rdbMsg->entrydrivercontrol.elementSize = rdbMsg->entrydrivercontrol.dataSize;   // one element only
    rdbMsg->entrydrivercontrol.pkgId       = RDB_PKG_ID_DRIVER_CTRL;
    rdbMsg->entrydrivercontrol.flags       = RDB_PKG_FLAG_EXTENDED;//TBD

    rdbMsg->drivercontrol.playerId = *pInOwnId;
    rdbMsg->drivercontrol.steeringWheel = pInDriverCtrl[0];
    rdbMsg->drivercontrol.steeringSpeed = pInDriverCtrl[1];
    rdbMsg->drivercontrol.throttlePedal = pInDriverCtrl[2];
    rdbMsg->drivercontrol.brakePedal = pInDriverCtrl[3];
    rdbMsg->drivercontrol.clutchPedal = 0;
    rdbMsg->drivercontrol.accelTgt = pInVehState[0];
    rdbMsg->drivercontrol.steeringTgt = pInVehState[1];
    rdbMsg->drivercontrol.curvatureTgt = 0;
    rdbMsg->drivercontrol.steeringTorque = 0;
    rdbMsg->drivercontrol.engineTorqueTgt = 0;
    rdbMsg->drivercontrol.speedTgt = pInVehState[2];
    rdbMsg->drivercontrol.gear = 4;
    rdbMsg->drivercontrol.sourceId = 0;
    rdbMsg->drivercontrol.spare0[0] = 0;
    rdbMsg->drivercontrol.spare0[1] = 0;
    rdbMsg->drivercontrol.validityFlags = 0x48E2;
    rdbMsg->drivercontrol.flags = *pInLightSt;
    rdbMsg->drivercontrol.mockupInput0 = 0;
    rdbMsg->drivercontrol.mockupInput1 = 0;
    rdbMsg->drivercontrol.mockupInput2 = 0;
    rdbMsg->drivercontrol.spare = 0;


  
    // third: the object state
    rdbMsg->entryObjectState.headerSize  = sizeof( RDB_MSG_ENTRY_HDR_t );
    rdbMsg->entryObjectState.dataSize    = sizeof( RDB_OBJECT_STATE_t );
    rdbMsg->entryObjectState.elementSize = 2 * rdbMsg->entryObjectState.dataSize;   // one element only
    rdbMsg->entryObjectState.pkgId       = RDB_PKG_ID_OBJECT_STATE;
    rdbMsg->entryObjectState.flags       = RDB_PKG_FLAG_EXTENDED;
    
    rdbMsg->objectState[0].base.id         = *pInOwnId;
    rdbMsg->objectState[0].base.category   = RDB_OBJECT_CATEGORY_PLAYER;
    rdbMsg->objectState[0].base.type       = RDB_OBJECT_TYPE_PLAYER_CAR;
    rdbMsg->objectState[0].base.visMask    = RDB_OBJECT_VIS_FLAG_TRAFFIC;
    
    rdbMsg->objectState[1].base.id         = 2;
    rdbMsg->objectState[1].base.category   = RDB_OBJECT_CATEGORY_PLAYER;
    rdbMsg->objectState[1].base.type       = RDB_OBJECT_TYPE_PLAYER_CAR;
    rdbMsg->objectState[1].base.visMask    = RDB_OBJECT_VIS_FLAG_TRAFFIC;
    
//     if ( *pInSync )
//         rdbMsg->objectState[0].base.visMask |= RDB_OBJECT_VIS_FLAG_RECORDER;
    
//     sprintf( rdbMsg->objectState[0].base.name, "%s", "ISAR_EGO" ) ;
    rdbMsg->objectState[0].base.geo.dimX   = 5.0;
    rdbMsg->objectState[0].base.geo.dimY   = 2.0;
    rdbMsg->objectState[0].base.geo.dimZ   = 1.6;
    rdbMsg->objectState[0].base.geo.offX   = 0.8;
    rdbMsg->objectState[0].base.geo.offY   = 0.0;
    rdbMsg->objectState[0].base.geo.offZ   = 0.4;
    rdbMsg->objectState[0].base.pos.x      = 1;
    rdbMsg->objectState[0].base.pos.y      = 2;
    rdbMsg->objectState[0].base.pos.z      = 3;
    rdbMsg->objectState[0].base.pos.h      = 4;
    rdbMsg->objectState[0].base.pos.p      = 5;
    rdbMsg->objectState[0].base.pos.r      = 6;
    rdbMsg->objectState[0].base.pos.flags  = RDB_COORD_FLAG_POINT_VALID | RDB_COORD_FLAG_ANGLES_VALID;
    rdbMsg->objectState[0].base.pos.type   = RDB_COORD_TYPE_RELATIVE_START;
    rdbMsg->objectState[0].base.pos.system = 0;
    
    rdbMsg->objectState[0].ext.speed.x      = 6.1;
    rdbMsg->objectState[0].ext.speed.y      = 5.2;
    rdbMsg->objectState[0].ext.speed.z      = 4.3;
    rdbMsg->objectState[0].ext.speed.h      = 3.4;
    rdbMsg->objectState[0].ext.speed.p      = 2.5;
    rdbMsg->objectState[0].ext.speed.r      = 1.6;
    rdbMsg->objectState[0].ext.speed.flags  = RDB_COORD_FLAG_POINT_VALID | RDB_COORD_FLAG_ANGLES_VALID;
    rdbMsg->objectState[0].ext.speed.type   = RDB_COORD_TYPE_RELATIVE_START;
    rdbMsg->objectState[0].ext.speed.system = 0;
    // fourth: the road mark 
    rdbMsg->entryRoadMark.headerSize  = sizeof( RDB_MSG_ENTRY_HDR_t );
    rdbMsg->entryRoadMark.dataSize    = sizeof( RDB_ROADMARK_t );  
    rdbMsg->entryRoadMark.elementSize = rdbMsg->entryRoadMark.dataSize;
    rdbMsg->entryRoadMark.pkgId       = RDB_PKG_ID_ROADMARK;
    rdbMsg->entryRoadMark.flags       = 0; 

    rdbMsg->roadMark.playerId = 77876;

    // fifth: the road mark 
    rdbMsg->entryLaneInfo.headerSize  = sizeof( RDB_MSG_ENTRY_HDR_t );
    rdbMsg->entryLaneInfo.dataSize    = sizeof( RDB_LANE_INFO_t );  
    rdbMsg->entryLaneInfo.elementSize = rdbMsg->entryLaneInfo.dataSize;
    rdbMsg->entryLaneInfo.pkgId       = RDB_PKG_ID_LANE_INFO;
    rdbMsg->entryLaneInfo.flags       = 0; 

    rdbMsg->laneInfo.playerId = 7862;

    // fifth: the road mark 
    rdbMsg->entryRoadPos.headerSize  = sizeof( RDB_MSG_ENTRY_HDR_t );
    rdbMsg->entryRoadPos.dataSize    = sizeof( RDB_ROAD_POS_t );  
    rdbMsg->entryRoadPos.elementSize = rdbMsg->entryRoadPos.dataSize;
    rdbMsg->entryRoadPos.pkgId       = RDB_PKG_ID_ROAD_POS;
    rdbMsg->entryRoadPos.flags       = 0; 

    rdbMsg->roadPos.playerId = 8678;

      /*
    // fourth: the wheel state
    rdbMsg->entryWheelState.headerSize  = sizeof( RDB_MSG_ENTRY_HDR_t );
    rdbMsg->entryWheelState.elementSize = sizeof( RDB_WHEEL_BASE_t );
    rdbMsg->entryWheelState.dataSize    = 4 * rdbMsg->entryWheelState.elementSize;   // four wheels
    rdbMsg->entryWheelState.pkgId       = RDB_PKG_ID_WHEEL;
    rdbMsg->entryWheelState.flags       = 0;
    
    rdbMsg->wheelState[0].playerId          = *pInOwnId;
    rdbMsg->wheelState[0].id                = RDB_WHEEL_ID_FRONT_LEFT;
    rdbMsg->wheelState[0].radiusStatic      = pInWheelFL[0];
    rdbMsg->wheelState[0].springCompression = pInWheelFL[1];
    rdbMsg->wheelState[0].rotAngle          = pInWheelFL[2];
    rdbMsg->wheelState[0].slip              = pInWheelFL[3];
    rdbMsg->wheelState[0].steeringAngle     = pInWheelFL[4];
    
    rdbMsg->wheelState[1].playerId          = *pInOwnId;
    rdbMsg->wheelState[1].id                = 1;
    rdbMsg->wheelState[1].radiusStatic      = pInWheelFR[0];
    rdbMsg->wheelState[1].springCompression = pInWheelFR[1];
    rdbMsg->wheelState[1].rotAngle          = pInWheelFR[2];
    rdbMsg->wheelState[1].slip              = pInWheelFR[3];
    rdbMsg->wheelState[1].steeringAngle     = pInWheelFR[4];
    
    rdbMsg->wheelState[2].playerId          = *pInOwnId;
    rdbMsg->wheelState[2].id                = 2;
    rdbMsg->wheelState[2].radiusStatic      = pInWheelRR[0];
    rdbMsg->wheelState[2].springCompression = pInWheelRR[1];
    rdbMsg->wheelState[2].rotAngle          = pInWheelRR[2];
    rdbMsg->wheelState[2].slip              = pInWheelRR[3];
    rdbMsg->wheelState[2].steeringAngle     = pInWheelRR[4];
    
    rdbMsg->wheelState[3].playerId          = *pInOwnId;
    rdbMsg->wheelState[3].id                = 3;
    rdbMsg->wheelState[3].radiusStatic      = pInWheelRL[0];
    rdbMsg->wheelState[3].springCompression = pInWheelRL[1];
    rdbMsg->wheelState[3].rotAngle          = pInWheelRL[2];
    rdbMsg->wheelState[3].slip              = pInWheelRL[3];
    rdbMsg->wheelState[3].steeringAngle     = pInWheelRL[4];
    
    // fifth: engine
    rdbMsg->entryEngine.headerSize  = sizeof( RDB_MSG_ENTRY_HDR_t );
    rdbMsg->entryEngine.elementSize = sizeof( RDB_ENGINE_BASE_t );
    rdbMsg->entryEngine.dataSize    = rdbMsg->entryEngine.elementSize;
    rdbMsg->entryEngine.pkgId       = RDB_PKG_ID_ENGINE;
    rdbMsg->entryEngine.flags       = 0;
    
    rdbMsg->engine.playerId = *pInOwnId;
    rdbMsg->engine.rps      = pInEngine[1];
    rdbMsg->engine.load     = pInEngine[0];
    
    // sixth: drivetrain
    rdbMsg->entryDrivetrain.headerSize  = sizeof( RDB_MSG_ENTRY_HDR_t );
    rdbMsg->entryDrivetrain.elementSize = sizeof( RDB_DRIVETRAIN_BASE_t );
    rdbMsg->entryDrivetrain.dataSize    = rdbMsg->entryDrivetrain.elementSize;
    rdbMsg->entryDrivetrain.pkgId       = RDB_PKG_ID_DRIVETRAIN;
    rdbMsg->entryDrivetrain.flags       = 0;
    
    rdbMsg->drivetrain.playerId       = *pInOwnId;
    rdbMsg->drivetrain.gearBoxType    = pInDrivetrain[0];
    rdbMsg->drivetrain.driveTrainType = pInDrivetrain[1];
    rdbMsg->drivetrain.gear           = pInDrivetrain[2];
    */ 
    
    // seventh: vehicle systems
    rdbMsg->entryVehicleSystems.headerSize  = sizeof( RDB_MSG_ENTRY_HDR_t );
    rdbMsg->entryVehicleSystems.elementSize = sizeof( RDB_VEHICLE_SYSTEMS_t );
    rdbMsg->entryVehicleSystems.dataSize    = rdbMsg->entryVehicleSystems.elementSize;
    rdbMsg->entryVehicleSystems.pkgId       = RDB_PKG_ID_VEHICLE_SYSTEMS;
    rdbMsg->entryVehicleSystems.flags       = 0;
    
    rdbMsg->vehicleSystems.playerId            = *pInOwnId;
    rdbMsg->vehicleSystems.steering            = 1.1;
    rdbMsg->vehicleSystems.lightMask           = 444;
    rdbMsg->vehicleSystems.steeringWheelTorque = 22;
       

    // eighth: end-of-frame
    rdbMsg->entryEOF.headerSize  = sizeof( RDB_MSG_ENTRY_HDR_t );
    rdbMsg->entryEOF.dataSize    = 0;
    rdbMsg->entryEOF.elementSize = 0;
    rdbMsg->entryEOF.pkgId       = RDB_PKG_ID_END_OF_FRAME;
    rdbMsg->entryEOF.flags       = 0;
    
    // finally set the output data size to a valid value
    *pOutMsgSize = sizeof( MY_RDB_MSG_t );
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
