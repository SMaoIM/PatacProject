#include "viRDBIcd.h"
#include <stdio.h>

typedef struct
{
    RDB_MSG_HDR_t           hdr;              
    RDB_MSG_ENTRY_HDR_t     entrySOF;    
    //RDB_MSG_ENTRY_HDR_t     entrydrivercontrol;
    //RDB_DRIVER_CTRL_t       drivercontrol;
    RDB_MSG_ENTRY_HDR_t     entryObjectState; 
    RDB_OBJECT_STATE_t      objectState;
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
    RDB_MSG_ENTRY_HDR_t     entryVehicleSystems; 
    RDB_VEHICLE_SYSTEMS_t   vehicleSystems;
    */
    RDB_MSG_ENTRY_HDR_t     entryEOF;
} MY_RDB_MSG_t;

void main()
{
    int a,b,c,d,e;
    a=sizeof(MY_RDB_MSG_t);
    b=sizeof(RDB_MSG_HDR_t);
    c=sizeof(RDB_MSG_ENTRY_HDR_t);
    d=sizeof(RDB_OBJECT_STATE_t);
    e=sizeof(RDB_ROADMARK_t);
    printf("%d\t%d\t%d\t%d\t%d\n",a,b,c,d,e);
    while(1);
}