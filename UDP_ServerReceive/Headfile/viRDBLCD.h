/*******************************************************
  * @file
  * ICD of the Runtime Data Bus (RDB)
  *
  * Copyright ©2021 VIRES Simulationstechnologie GmbH and its licensors. All rights reserved.
  * @author VIRES
  ********************************************************/

  /*****************************************************/
#pragma pack (push, 4)

#ifndef _VIRES_RDB_ICD_H
#define _VIRES_RDB_ICD_H

/* includes for 64bit compatibility */
#ifdef MATLAB_MEX_FILE
#include <sys/types.h>
#include "viRDBTypes.h"
#else
#include <stdint.h>
#endif


#define RDB_DEFAULT_PORT   48190       
#define RDB_FEEDBACK_PORT  48191       
#define RDB_IMAGE_PORT     48192       
#define RDB_MAGIC_NO       35712       
#define RDB_VERSION       0x0125       
#define RDB_SIZE_OBJECT_NAME       32       
#define RDB_SIZE_SCP_NAME          64       
#define RDB_SIZE_FILENAME        1024       
#define RDB_SIZE_TRLIGHT_PHASES     8       
#define RDB_PKG_ID_START_OF_FRAME               1     
#define RDB_PKG_ID_END_OF_FRAME                 2     
#define RDB_PKG_ID_COORD_SYSTEM                 3     
#define RDB_PKG_ID_COORD                        4     
#define RDB_PKG_ID_ROAD_POS                     5     
#define RDB_PKG_ID_LANE_INFO                    6     
#define RDB_PKG_ID_ROADMARK                     7     
#define RDB_PKG_ID_OBJECT_CFG                   8     
#define RDB_PKG_ID_OBJECT_STATE                 9     
#define RDB_PKG_ID_VEHICLE_SYSTEMS             10     
#define RDB_PKG_ID_VEHICLE_SETUP               11     
#define RDB_PKG_ID_ENGINE                      12     
#define RDB_PKG_ID_DRIVETRAIN                  13     
#define RDB_PKG_ID_WHEEL                       14     
#define RDB_PKG_ID_PED_ANIMATION               15     
#define RDB_PKG_ID_SENSOR_STATE                16     
#define RDB_PKG_ID_SENSOR_OBJECT               17     
#define RDB_PKG_ID_CAMERA                      18     
#define RDB_PKG_ID_CONTACT_POINT               19     
#define RDB_PKG_ID_TRAFFIC_SIGN                20     
#define RDB_PKG_ID_ROAD_STATE                  21     
#define RDB_PKG_ID_IMAGE                       22     
#define RDB_PKG_ID_LIGHT_SOURCE                23     
#define RDB_PKG_ID_ENVIRONMENT                 24     
#define RDB_PKG_ID_TRIGGER                     25     
#define RDB_PKG_ID_DRIVER_CTRL                 26     
#define RDB_PKG_ID_TRAFFIC_LIGHT               27     
#define RDB_PKG_ID_SYNC                        28     
#define RDB_PKG_ID_DRIVER_PERCEPTION           29     
#define RDB_PKG_ID_LIGHT_MAP                   30     
#define RDB_PKG_ID_TONE_MAPPING                31     
#define RDB_PKG_ID_ROAD_QUERY                  32     
#define RDB_PKG_ID_SCP                         33     
#define RDB_PKG_ID_TRAJECTORY                  34     
#define RDB_PKG_ID_DYN_2_STEER                 35     
#define RDB_PKG_ID_STEER_2_DYN                 36     
#define RDB_PKG_ID_PROXY                       37     
#define RDB_PKG_ID_MOTION_SYSTEM               38     
#define RDB_PKG_ID_OCCLUSION_MATRIX            39     
#define RDB_PKG_ID_FREESPACE                   40     
#define RDB_PKG_ID_DYN_EL_SWITCH               41     
#define RDB_PKG_ID_DYN_EL_DOF                  42     
#define RDB_PKG_ID_IG_FRAME                    43     
#define RDB_PKG_ID_RAY                         44     
#define RDB_PKG_ID_RT_PERFORMANCE              45     
#define RDB_PKG_ID_SYMBOL_STATE                46     
#define RDB_PKG_ID_SYMBOL_TEXT_STATE           47     
#define RDB_PKG_ID_SYMBOL_POLYGON_STATE        48     
#define RDB_PKG_ID_RADAR_HIT_POINT             49     
#define RDB_PKG_ID_CUSTOM_SCORING           10000     
#define RDB_PKG_ID_CUSTOM_OBJECT_CTRL_TRACK 10001     
#define RDB_PKG_ID_CUSTOM_LIGHT_B           10002     
#define RDB_PKG_ID_CUSTOM_LIGHT_A           10003     
#define RDB_PKG_ID_CUSTOM_LIGHT_GROUP_B     10004     
#define RDB_PKG_ID_CUSTOM_LOOK_AHEAD        10005     
#define RDB_PKG_ID_CUSTOM_AUDI_FORUM        12000     
#define RDB_PKG_ID_CUSTOM_OPTIX_START       12100     
#define RDB_PKG_ID_OPTIX_BUFFER             12101     
#define RDB_PKG_ID_CUSTOM_OPTIX_END         12149     
#define RDB_PKG_ID_CUSTOM_USER_A_START      12150     
#define RDB_PKG_ID_CUSTOM_USER_A_END        12174     
#define RDB_PKG_ID_CUSTOM_USER_B_START      12175     
#define RDB_PKG_ID_CUSTOM_USER_B_END        12200     
#define RDB_OBJECT_CATEGORY_NONE           0    
#define RDB_OBJECT_CATEGORY_PLAYER         1    
#define RDB_OBJECT_CATEGORY_SENSOR         2    
#define RDB_OBJECT_CATEGORY_CAMERA         3    
#define RDB_OBJECT_CATEGORY_LIGHT_POINT    4    
#define RDB_OBJECT_CATEGORY_COMMON         5    
#define RDB_OBJECT_CATEGORY_OPENDRIVE      6    
#define RDB_OBJECT_TYPE_NONE                   0    
#define RDB_OBJECT_TYPE_PLAYER_NONE            0    
#define RDB_OBJECT_TYPE_PLAYER_CAR             1    
#define RDB_OBJECT_TYPE_PLAYER_TRUCK           2    
#define RDB_OBJECT_TYPE_PLAYER_VAN             3    
#define RDB_OBJECT_TYPE_PLAYER_BIKE            4    
#define RDB_OBJECT_TYPE_PLAYER_PEDESTRIAN      5    
#define RDB_OBJECT_TYPE_PLAYER_PED_GROUP       6    
#define RDB_OBJECT_TYPE_POLE                   7    
#define RDB_OBJECT_TYPE_TREE                   8    
#define RDB_OBJECT_TYPE_BARRIER                9    
#define RDB_OBJECT_TYPE_OPT1                  10    
#define RDB_OBJECT_TYPE_OPT2                  11    
#define RDB_OBJECT_TYPE_OPT3                  12    
#define RDB_OBJECT_TYPE_PLAYER_MOTORBIKE      13    
#define RDB_OBJECT_TYPE_PLAYER_BUS            14    
#define RDB_OBJECT_TYPE_STREET_LAMP           15    
#define RDB_OBJECT_TYPE_TRAFFIC_SIGN          16    
#define RDB_OBJECT_TYPE_HEADLIGHT             17    
#define RDB_OBJECT_TYPE_PLAYER_TRAILER        18    
#define RDB_OBJECT_TYPE_BUILDING              19    
#define RDB_OBJECT_TYPE_PARKING_SPACE         20    
#define RDB_OBJECT_TYPE_ROAD_WORKS            21    
#define RDB_OBJECT_TYPE_ROAD_MISC             22    
#define RDB_OBJECT_TYPE_TUNNEL                23    
#define RDB_OBJECT_TYPE_LEGACY                24    
#define RDB_OBJECT_TYPE_VEGETATION            25    
#define RDB_OBJECT_TYPE_MISC_MOTORWAY         26    
#define RDB_OBJECT_TYPE_MISC_TOWN             27    
#define RDB_OBJECT_TYPE_PATCH                 28    
#define RDB_OBJECT_TYPE_OTHER                 29    
#define RDB_OBJECT_PLAYER_SEMI_TRAILER        30    
#define RDB_OBJECT_PLAYER_RAILCAR             31    
#define RDB_OBJECT_PLAYER_RAILCAR_SEMI_HEAD   32    
#define RDB_OBJECT_PLAYER_RAILCAR_SEMI_BACK   33    
#define RDB_OBJECT_TYPE_VEH_LIGHT_FRONT_LEFT  34    
#define RDB_OBJECT_TYPE_VEH_LIGHT_FRONT_RIGHT 35    
#define RDB_OBJECT_TYPE_VEH_LIGHT_REAR_LEFT   36    
#define RDB_OBJECT_TYPE_VEH_LIGHT_REAR_RIGHT  37    
#define RDB_OBJECT_TYPE_VEH_CABIN             38    
#define RDB_LANE_BORDER_UNKNOWN          0      
#define RDB_LANE_BORDER_NONE             1      
#define RDB_LANE_BORDER_POLE             2      
#define RDB_LANE_BORDER_BARRIER          3      
#define RDB_LANE_BORDER_SOFT_SHOULDER    4      
#define RDB_LANE_BORDER_HARD_SHOULDER    5      
#define RDB_LANE_BORDER_CURB             6      
#define RDB_ROADMARK_TYPE_NONE           0      
#define RDB_ROADMARK_TYPE_SOLID          1      
#define RDB_ROADMARK_TYPE_BROKEN         2      
#define RDB_ROADMARK_TYPE_CURB           3      
#define RDB_ROADMARK_TYPE_GRASS          4      
#define RDB_ROADMARK_TYPE_BOTDOT         5      
#define RDB_ROADMARK_TYPE_OTHER          6      
#define RDB_ROADMARK_TYPE_SOLID_SOLID    7      
#define RDB_ROADMARK_TYPE_BROKEN_SOLID   8      
#define RDB_ROADMARK_TYPE_SOLID_BROKEN   9      
#define RDB_ROADMARK_TYPE_LANE_CENTER   10      
#define RDB_ROADMARK_COLOR_NONE          0      
#define RDB_ROADMARK_COLOR_WHITE         1      
#define RDB_ROADMARK_COLOR_RED           2      
#define RDB_ROADMARK_COLOR_YELLOW        3      
#define RDB_ROADMARK_COLOR_OTHER         4      
#define RDB_ROADMARK_COLOR_BLUE          5      
#define RDB_ROADMARK_COLOR_GREEN         6      
#define RDB_WHEEL_ID_FRONT_LEFT          0      
#define RDB_GEAR_BOX_TYPE_AUTOMATIC      0      
#define RDB_GEAR_BOX_TYPE_MANUAL         1      
#define RDB_GEAR_BOX_POS_AUTO             0     
#define RDB_GEAR_BOX_POS_P                1     
#define RDB_GEAR_BOX_POS_R                2     
#define RDB_GEAR_BOX_POS_N                3     
#define RDB_GEAR_BOX_POS_D                4     
#define RDB_GEAR_BOX_POS_1                5     
#define RDB_GEAR_BOX_POS_2                6     
#define RDB_GEAR_BOX_POS_3                7     
#define RDB_GEAR_BOX_POS_4                8     
#define RDB_GEAR_BOX_POS_5                9     
#define RDB_GEAR_BOX_POS_6               10     
#define RDB_GEAR_BOX_POS_7               11     
#define RDB_GEAR_BOX_POS_8               12     
#define RDB_GEAR_BOX_POS_9               13     
#define RDB_GEAR_BOX_POS_10              14     
#define RDB_GEAR_BOX_POS_11              15     
#define RDB_GEAR_BOX_POS_12              16     
#define RDB_GEAR_BOX_POS_13              17     
#define RDB_GEAR_BOX_POS_14              18     
#define RDB_GEAR_BOX_POS_15              19     
#define RDB_GEAR_BOX_POS_16              20     
#define RDB_GEAR_BOX_POS_R1              21     
#define RDB_GEAR_BOX_POS_R2              22     
#define RDB_GEAR_BOX_POS_R3              23     
#define RDB_GEAR_BOX_POS_M               24     
#define RDB_GEAR_BOX_POS_M_UP            25     
#define RDB_GEAR_BOX_POS_M_DOWN          26     
#define RDB_GEAR_BOX_POS_C               27     
#define RDB_GEAR_BOX_POS_MS              28     
#define RDB_GEAR_BOX_POS_CS              29     
#define RDB_GEAR_BOX_POS_PS              30     
#define RDB_GEAR_BOX_POS_RS              31     
#define RDB_GEAR_BOX_POS_NS              32     
#define RDB_GEAR_BOX_POS_DS              33     
#define RDB_DRIVETRAIN_TYPE_FRONT        0      
#define RDB_DRIVETRAIN_TYPE_REAR         1      
#define RDB_DRIVETRAIN_TYPE_AWD          2      
#define RDB_PIX_FORMAT_RGB              0  
#define RDB_PIX_FORMAT_RGB_16           1  
#define RDB_PIX_FORMAT_RGB_24           2  
#define RDB_PIX_FORMAT_RGBA             3  
#define RDB_PIX_FORMAT_RGBA_16          4  
#define RDB_PIX_FORMAT_RGBA_24          5  
#define RDB_PIX_FORMAT_BW_8             6  
#define RDB_PIX_FORMAT_BW_16            7  
#define RDB_PIX_FORMAT_BW_24            8  
#define RDB_PIX_FORMAT_DEPTH_8          9  
#define RDB_PIX_FORMAT_DEPTH_16        10  
#define RDB_PIX_FORMAT_DEPTH_24        11  
#define RDB_PIX_FORMAT_RGB_32_F        12  
#define RDB_PIX_FORMAT_RGBA_32_F       13  
#define RDB_PIX_FORMAT_LUM_32_F        14  
#define RDB_PIX_FORMAT_LUMA_32_F       15  
#define RDB_PIX_FORMAT_RGB_16_F        16  
#define RDB_PIX_FORMAT_RGBA_16_F       17  
#define RDB_PIX_FORMAT_LUM_16_F        18  
#define RDB_PIX_FORMAT_LUMA_16_F       19  
#define RDB_PIX_FORMAT_DEPTH_32        20  
#define RDB_PIX_FORMAT_BW_32           21  
#define RDB_PIX_FORMAT_RGB_32          22  
#define RDB_PIX_FORMAT_RGBA_32         23  
#define RDB_PIX_FORMAT_R3_G2_B2        24  
#define RDB_PIX_FORMAT_R3_G2_B2_A8     25  
#define RDB_PIX_FORMAT_R5_G6_B5        26  
#define RDB_PIX_FORMAT_R5_G6_B5_A16    27  
#define RDB_PIX_FORMAT_RED8            28  
#define RDB_PIX_FORMAT_RED16           29  
#define RDB_PIX_FORMAT_RED16F          30  
#define RDB_PIX_FORMAT_RED24           31  
#define RDB_PIX_FORMAT_RED32           32  
#define RDB_PIX_FORMAT_RED32F          33  
#define RDB_PIX_FORMAT_RG8             34  
#define RDB_PIX_FORMAT_RG16            35  
#define RDB_PIX_FORMAT_RG16F           36  
#define RDB_PIX_FORMAT_RG32            37  
#define RDB_PIX_FORMAT_RG32F           38  
#define RDB_PIX_FORMAT_RGB8            39  
#define RDB_PIX_FORMAT_RGBA8           40  
#define RDB_PIX_FORMAT_RGB8_A24        41  
#define RDB_PIX_FORMAT_RGB16           42  
#define RDB_PIX_FORMAT_RGB16F          43  
#define RDB_PIX_FORMAT_RGBA16          44  
#define RDB_PIX_FORMAT_RGBA16F         45  
#define RDB_PIX_FORMAT_RGB32           46  
#define RDB_PIX_FORMAT_RGB32F          47  
#define RDB_PIX_FORMAT_RGBA32          48  
#define RDB_PIX_FORMAT_RGBA32F         49  
#define RDB_PIX_FORMAT_DEPTH8          50  
#define RDB_PIX_FORMAT_DEPTH16         51  
#define RDB_PIX_FORMAT_DEPTH24         52  
#define RDB_PIX_FORMAT_DEPTH32         53  
#define RDB_PIX_FORMAT_RGBA4           54  
#define RDB_PIX_FORMAT_CUSTOM_01           151     
#define RDB_PIX_FORMAT_CUSTOM_02           152     
#define RDB_PIX_FORMAT_CUSTOM_03           153     
#define RDB_SENSOR_TYPE_NONE            0  
#define RDB_SENSOR_TYPE_RADAR           1  
#define RDB_SENSOR_TYPE_VIDEO           2  
#define RDB_TRLIGHT_PHASE_OFF           0   
#define RDB_TRLIGHT_PHASE_STOP          1   
#define RDB_TRLIGHT_PHASE_STOP_ATTN     2   
#define RDB_TRLIGHT_PHASE_GO            3   
#define RDB_TRLIGHT_PHASE_GO_EXCL       4   
#define RDB_TRLIGHT_PHASE_ATTN          5   
#define RDB_TRLIGHT_PHASE_BLINK         6   
#define RDB_TRLIGHT_PHASE_UNKNOWN       7   
#define RDB_COORD_TYPE_INERTIAL         0  
#define RDB_COORD_TYPE_RESERVED_1       1  
#define RDB_COORD_TYPE_PLAYER           2  
#define RDB_COORD_TYPE_SENSOR           3  
#define RDB_COORD_TYPE_USK              4  
#define RDB_COORD_TYPE_USER             5  
#define RDB_COORD_TYPE_WINDOW           6  
#define RDB_COORD_TYPE_TEXTURE          7  
#define RDB_COORD_TYPE_RELATIVE_START   8  
#define RDB_COORD_TYPE_GEO              9  
#define RDB_COORD_TYPE_TRACK           10  
#define RDB_ENV_CLOUD_STATE_OFF         0  
#define RDB_ENV_CLOUD_STATE_0_8         1  
#define RDB_ENV_CLOUD_STATE_4_8         2  
#define RDB_ENV_CLOUD_STATE_6_8         3  
#define RDB_ENV_CLOUD_STATE_8_8         4  
#define RDB_FUNCTION_TYPE_NONE          0  
#define RDB_FUNCTION_TYPE_TONE_MAPPING  1  
#define RDB_ROAD_TYPE_UNKNOWN          0  
#define RDB_ROAD_TYPE_RURAL            1  
#define RDB_ROAD_TYPE_MOTORWAY         2  
#define RDB_ROAD_TYPE_TOWN             3  
#define RDB_ROAD_TYPE_LOW_SPEED        4  
#define RDB_ROAD_TYPE_PEDESTRIAN       5  
#define RDB_DRIVER_SOURCE_UNKNOWN          0  
#define RDB_DRIVER_SOURCE_GHOSTDRIVER      1  
#define RDB_SHM_SIZE_TC              5242880  
#define RDB_FREESPACE_STATE_OBJECT_NONE      0  
#define RDB_FREESPACE_STATE_OBJECT_SAME_DIR  1  
#define RDB_FREESPACE_STATE_OBJECT_ONCOMING  2  
#define RDB_DYN_EL_SCOPE_UNKNOWN            0       
#define RDB_DYN_EL_SCOPE_STATIC_DB          1       
#define RDB_DYN_EL_SCOPE_DYN_OBJECT         2       
#define RDB_DYN_EL_SCOPE_ANY                3       
#define RDB_DYN_EL_SCOPE_FIRST              4       
#define RDB_DYN_EL_SCOPE_STATIC_DB_SIGNAL   5       
#define RDB_DYN_EL_SCOPE_STATIC_DB_SWITCH   6       
#define RDB_RAY_TYPE_UNKNOWN            0       
#define RDB_RAY_TYPE_EMIT               1       
#define RDB_RAY_TYPE_HIT                2       
#define RDB_UNIT_DEFAULT                0       
#define RDB_UNIT_M                      1       
#define RDB_UNIT_S                      2       
#define RDB_PKG_FLAG_NONE                        0x0000      
#define RDB_PKG_FLAG_EXTENDED                    0x0001      
#define RDB_PKG_FLAG_HIDDEN                      0x0002      
#define RDB_OBJECT_VIS_FLAG_ALL                      0xffff  
#define RDB_OBJECT_VIS_FLAG_NONE                     0x0000  
#define RDB_OBJECT_VIS_FLAG_GFX                      0x0001  
#define RDB_OBJECT_VIS_FLAG_TRAFFIC                  0x0002  
#define RDB_OBJECT_VIS_FLAG_RECORDER                 0x0004  
#define RDB_VEHICLE_LIGHT_OFF                    0x00000000  
#define RDB_VEHICLE_LIGHT_PARK                   0x00000001  
#define RDB_VEHICLE_LIGHT_LOW_BEAM               0x00000002  
#define RDB_VEHICLE_LIGHT_HIGH_BEAM              0x00000004  
#define RDB_VEHICLE_LIGHT_REAR_BRAKE             0x00000008  
#define RDB_VEHICLE_LIGHT_REAR_DRIVE             0x00000010  
#define RDB_VEHICLE_LIGHT_INDICATOR_L            0x00000020  
#define RDB_VEHICLE_LIGHT_INDICATOR_R            0x00000040  
#define RDB_VEHICLE_LIGHT_FLASH                  0x00000080  
#define RDB_VEHICLE_LIGHT_FRONT_FOG              0x00000100  
#define RDB_VEHICLE_LIGHT_REAR_FOG               0x00000200  
#define RDB_VEHICLE_LIGHT_VIRES1                 0x00000400  
#define RDB_VEHICLE_LIGHT_DRL                    0x00000800  
#define RDB_VEHICLE_LIGHT_DRL_LEFT_LOW           0x00001000  
#define RDB_VEHICLE_LIGHT_DRL_RIGHT_LOW          0x00002000  
#define RDB_VEHICLE_LIGHT_EMERGENCY              0x00004000  
#define RDB_VEHICLE_LIGHT_INDICATOR_LAMP_ON      0x00008000  
#define RDB_VEHICLE_LIGHT_FORCE                  0x00010000  
#define RDB_VEHICLE_ACC_FLAG_OFF             0x00  
#define RDB_VEHICLE_ACC_FLAG_DIST_1          0x01  
#define RDB_VEHICLE_ACC_FLAG_DIST_2          0x02  
#define RDB_VEHICLE_ACC_FLAG_DIST_3          0x03  
#define RDB_VEHICLE_ACC_FLAG_TARGET          0x04  
#define RDB_VEHICLE_ACC_FLAG_SPEED           0x08  
#define RDB_VEHICLE_DISPLAY_LIGHT_OFF        0x0000  
#define RDB_VEHICLE_DISPLAY_LIGHT_01         0x0001  
#define RDB_VEHICLE_DISPLAY_LIGHT_02         0x0002  
#define RDB_VEHICLE_DISPLAY_LIGHT_03         0x0004  
#define RDB_VEHICLE_DISPLAY_LIGHT_04         0x0008  
#define RDB_VEHICLE_DISPLAY_LIGHT_05         0x0010  
#define RDB_VEHICLE_DISPLAY_LIGHT_06         0x0020  
#define RDB_VEHICLE_DISPLAY_LIGHT_07         0x0040  
#define RDB_VEHICLE_DISPLAY_LIGHT_08         0x0080  
#define RDB_VEHICLE_DISPLAY_LIGHT_09         0x0100  
#define RDB_VEHICLE_DISPLAY_LIGHT_10         0x0200  
#define RDB_VEHICLE_DISPLAY_LIGHT_11         0x0400  
#define RDB_VEHICLE_DISPLAY_LIGHT_12         0x0800  
#define RDB_VEHICLE_DISPLAY_LIGHT_13         0x1000  
#define RDB_VEHICLE_DISPLAY_LIGHT_14         0x2000  
#define RDB_VEHICLE_DISPLAY_LIGHT_15         0x4000  
#define RDB_VEHICLE_DISPLAY_LIGHT_16         0x8000  
#define RDB_LANE_EXISTS_OWN                      0x01        
#define RDB_LANE_EXISTS_LEFT                     0x02        
#define RDB_LANE_EXISTS_RIGHT                    0x04        
#define RDB_LANE_STATUS_NONE                     0x0000      
#define RDB_LANE_STATUS_ROADWORKS                0x0001      
#define RDB_LANE_STATUS_EXIT                     0x0002      
#define RDB_LANE_STATUS_ENTRY                    0x0004      
#define RDB_LANE_STATUS_LINKED                   0x0008      
#define RDB_LANE_STATUS_WET                      0x0010      
#define RDB_LANE_STATUS_SNOW                     0x0020      
#define RDB_DRIVER_FLAG_NONE                     0x00000000  
#define RDB_DRIVER_FLAG_INDICATOR_L              0x00000001  
#define RDB_DRIVER_FLAG_INDICATOR_R              0x00000002  
#define RDB_DRIVER_FLAG_PARKING_BRAKE            0x00000004  
#define RDB_DRIVER_FLAG_LIGHT_LOW_BEAM           0x00000008  
#define RDB_DRIVER_FLAG_LIGHT_HIGH_BEAM          0x00000010  
#define RDB_DRIVER_FLAG_LIGHT_FOG_FRONT          0x00000020  
#define RDB_DRIVER_FLAG_LIGHT_FOG_REAR           0x00000040  
#define RDB_DRIVER_FLAG_LIGHT_EMERGENCY          0x00000080  
#define RDB_DRIVER_FLAG_LIGHT_PRIORITY           0x00000100  
#define RDB_DRIVER_FLAG_COLLISION                0x00000200  
/* INPUT: MFL and SZL bits */
#define RDB_MOCKUP_INPUT0_MFL_PLUS           0x00000001  
#define RDB_MOCKUP_INPUT0_MFL_MINUS          0x00000002  
#define RDB_MOCKUP_INPUT0_MFL_PHONE          0x00000004  
#define RDB_MOCKUP_INPUT0_MFL_VOICE          0x00000008  
#define RDB_MOCKUP_INPUT0_MFL_UP             0x00000010  
#define RDB_MOCKUP_INPUT0_MFL_DOWN           0x00000020  
#define RDB_MOCKUP_INPUT0_MFL_DIAMOND        0x00000040  
#define RDB_MOCKUP_INPUT0_MFL_STAR           0x00000080  
#define RDB_MOCKUP_INPUT0_TURN_UP            0x00000100  
#define RDB_MOCKUP_INPUT0_TURN_UP_2          0x00000200  
#define RDB_MOCKUP_INPUT0_TURN_DOWN          0x00000400  
#define RDB_MOCKUP_INPUT0_TURN_DOWN_2        0x00000800  
#define RDB_MOCKUP_INPUT0_TURN_FLASHER       0x00001000  
#define RDB_MOCKUP_INPUT0_TURN_HIGHBEAM      0x00002000  
#define RDB_MOCKUP_INPUT0_TURN_CHECK         0x00004000  
#define RDB_MOCKUP_INPUT0_TURN_BC            0x00008000  
#define RDB_MOCKUP_INPUT0_ACC_BACK           0x00010000  
#define RDB_MOCKUP_INPUT0_ACC_BACK_2         0x00020000  
#define RDB_MOCKUP_INPUT0_ACC_FWD            0x00040000  
#define RDB_MOCKUP_INPUT0_ACC_FWD_2          0x00080000  
#define RDB_MOCKUP_INPUT0_ACC_UP             0x00100000  
#define RDB_MOCKUP_INPUT0_ACC_DOWN           0x00200000  
#define RDB_MOCKUP_INPUT0_ACC_SET            0x00400000  
#define RDB_MOCKUP_INPUT0_HORN               0x00800000  
#define RDB_MOCKUP_INPUT0_WIPER_INTERVAL     0x03000000  
#define RDB_MOCKUP_INPUT0_WIPER_INTERVAL_1   0x01000000  
#define RDB_MOCKUP_INPUT0_WIPER_INTERVAL_2   0x02000000  
#define RDB_MOCKUP_INPUT0_WIPER_INTERVAL_3   0x03000000  
#define RDB_MOCKUP_INPUT0_WIPER_AUTO         0x04000000  
#define RDB_MOCKUP_INPUT0_WIPER_BACK         0x08000000  
#define RDB_MOCKUP_INPUT0_WIPER_UP           0x10000000  
#define RDB_MOCKUP_INPUT0_WIPER_UP_2         0x20000000  
#define RDB_MOCKUP_INPUT0_WIPER_DOWN         0x40000000  
/* INPUT: ZBE and GWS bits */
#define RDB_MOCKUP_INPUT1_ZBE_COUNTER      0x0000FFFF   
#define RDB_MOCKUP_INPUT1_ZBE_FWD          0x00010000   
#define RDB_MOCKUP_INPUT1_ZBE_BACK         0x00020000   
#define RDB_MOCKUP_INPUT1_ZBE_LEFT         0x00040000   
#define RDB_MOCKUP_INPUT1_ZBE_RIGHT        0x00080000   
#define RDB_MOCKUP_INPUT1_ZBE_PRESS        0x00100000   
#define RDB_MOCKUP_INPUT1_ZBE_MENU         0x00200000   
#define RDB_MOCKUP_INPUT1_GWS_P            0x00400000   
#define RDB_MOCKUP_INPUT1_GWS_LOCK         0x00800000   
#define RDB_MOCKUP_INPUT1_GWS_FWD          0x01000000   
#define RDB_MOCKUP_INPUT1_GWS_FWD_2        0x02000000   
#define RDB_MOCKUP_INPUT1_GWS_BACK         0x04000000   
#define RDB_MOCKUP_INPUT1_GWS_BACK_2       0x08000000   
#define RDB_MOCKUP_INPUT1_GWS_AUTO_N       0x10000000   
#define RDB_MOCKUP_INPUT1_GWS_MAN_N        0x20000000   
#define RDB_MOCKUP_INPUT1_GWS_MAN_PLUS     0x40000000   
#define RDB_MOCKUP_INPUT1_GWS_MAN_MINUS    0x80000000   
#define RDB_MOCKUP_INPUT2_LSZ_POTI              0x000000FF 
#define RDB_MOCKUP_INPUT2_LSZ_PARKING           0x00000100 
#define RDB_MOCKUP_INPUT2_LSZ_DRIVING           0x00000200 
#define RDB_MOCKUP_INPUT2_LSZ_AUTO              0x00000300 
#define RDB_MOCKUP_INPUT2_LSZ_FOG_FRONT         0x00000400 
#define RDB_MOCKUP_INPUT2_LSZ_FOG_REAR          0x00000800 
#define RDB_MOCKUP_INPUT2_DB_DTC                0x00001000 
#define RDB_MOCKUP_INPUT2_DB_PDC                0x00002000 
#define RDB_MOCKUP_INPUT2_DB_SEAT_HEAT_L        0x00004000 
#define RDB_MOCKUP_INPUT2_DB_SEAT_HEAT_R        0x00008000 
#define RDB_MOCKUP_INPUT2_DB_STARTER            0x00010000 
#define RDB_MOCKUP_INPUT2_DB_HAZARD_LIGHTS      0x00020000 
#define RDB_MOCKUP_INPUT2_DB_LOCK               0x00040000 
#define RDB_MOCKUP_INPUT2_DB_STEER_ADJUST_FWD   0x00100000 
#define RDB_MOCKUP_INPUT2_DB_STEER_ADJUST_BACK  0x00200000 
#define RDB_MOCKUP_INPUT2_DB_STEER_ADJUST_UP    0x00400000 
#define RDB_MOCKUP_INPUT2_DB_STEER_ADJUST_DOWN  0x00800000 
#define RDB_DRIVER_PERCEPTION_FLAG_NONE          0x00000000  
#define RDB_DRIVER_PERCEPTION_FLAG_TURN_L        0x00000001  
#define RDB_DRIVER_PERCEPTION_FLAG_TURN_R        0x00000002  
#define RDB_DRIVER_INPUT_VALIDITY_NONE            0x00000000 
#define RDB_DRIVER_INPUT_VALIDITY_STEERING_WHEEL  0x00000001 
#define RDB_DRIVER_INPUT_VALIDITY_STEERING_SPEED  0x00000002 
#define RDB_DRIVER_INPUT_VALIDITY_THROTTLE        0x00000004 
#define RDB_DRIVER_INPUT_VALIDITY_BRAKE           0x00000008 
#define RDB_DRIVER_INPUT_VALIDITY_CLUTCH          0x00000010 
#define RDB_DRIVER_INPUT_VALIDITY_TGT_ACCEL       0x00000020 
#define RDB_DRIVER_INPUT_VALIDITY_TGT_STEERING    0x00000040 
#define RDB_DRIVER_INPUT_VALIDITY_GEAR            0x00000080 
#define RDB_DRIVER_INPUT_VALIDITY_CURVATURE       0x00000100 
#define RDB_DRIVER_INPUT_VALIDITY_STEERING_TORQUE 0x00000200 
#define RDB_DRIVER_INPUT_VALIDITY_ENGINE_TORQUE   0x00000400 
#define RDB_DRIVER_INPUT_VALIDITY_TGT_SPEED       0x00000800 
#define RDB_DRIVER_INPUT_VALIDITY_INFO_ONLY       0x00001000 
#define RDB_DRIVER_INPUT_VALIDITY_ADD_ON          0x00002000 
#define RDB_DRIVER_INPUT_VALIDITY_FLAGS           0x00004000 
#define RDB_DRIVER_INPUT_VALIDITY_MOCKUP_INPUT0   0x00008000 
#define RDB_DRIVER_INPUT_VALIDITY_MOCKUP_INPUT1   0x00010000 
#define RDB_DRIVER_INPUT_VALIDITY_MOCKUP_INPUT2   0x00020000 
#define RDB_DRIVER_INPUT_VALIDITY_STEERING_TPOS   0x00040000 
#define RDB_DRIVER_INPUT_VALIDITY_MODIFIED        0x00080000 
#define RDB_SCORING_FLAG_NONE                     0x00000000  
#define RDB_SCORING_FLAG_COLLISION                0x00000001  
#define RDB_SCORING_FLAG_OFF_ROAD                 0x00000002  
#define RDB_COORD_FLAG_NONE                       0x00        
#define RDB_COORD_FLAG_POINT_VALID                0x01        
#define RDB_COORD_FLAG_ANGLES_VALID               0x02        
#define RDB_LIGHT_SOURCE_FLAG_NONE                0x0000      
#define RDB_LIGHT_SOURCE_FLAG_USE_FRUSTUM         0x0001      
#define RDB_LIGHT_SOURCE_FLAG_PERSISTENT          0x0002      
#define RDB_LIGHT_SOURCE_FLAG_STENCIL             0x0004      
#define RDB_SENSOR_OBJECT_FLAG_NONE               0x0000      
#define RDB_SENSOR_OBJECT_FLAG_CRITICALITY_LOW    0x0001      
#define RDB_SENSOR_OBJECT_FLAG_CRITICALITY_MEDIUM 0x0002      
#define RDB_SENSOR_OBJECT_FLAG_CRITICALITY_HIGH   0x0003      
#define RDB_SENSOR_OBJECT_FLAG_LANE_POS_VALID     0x0008      
#define RDB_ROAD_EVENT_NONE                       0x00000000  
#define RDB_ROAD_EVENT_POTHOLE                    0x00000001  
#define RDB_ENV_FLAG_NONE                         0x0000  
#define RDB_ENV_FLAG_PRECIPITATION_SNOW           0x0001  
#define RDB_ENV_FLAG_PRECIPITATION_HAIL           0x0002  
#define RDB_ENV_FLAG_ROAD_SURFACE_WET             0x0004  
#define RDB_ENV_FLAG_STREET_LAMPS                 0x0008  
#define RDB_SHM_ID_IMG_GENERATOR_OUT              0x0816a   
#define RDB_SHM_ID_IMG_GENERATOR_IN               0x0817a   
#define RDB_SHM_ID_CONTROL_GENERATOR_IN           0x0817b   
#define RDB_SHM_ID_CUSTOM_01                      0x0818a   
#define RDB_SHM_ID_TC_IN                          0x08200   
#define RDB_SHM_ID_TC_OUT                         0x08201   
#define RDB_SHM_ID_DYN_2_STEER                    0x08210   
#define RDB_SHM_ID_STEER_2_DYN                    0x08211   
#define RDB_SHM_BUFFER_FLAG_NONE                    0x00000000      
#define RDB_SHM_BUFFER_FLAG_LOCK                    0x00000001      
#define RDB_SHM_BUFFER_FLAG_TC                      0x00000002      
#define RDB_SHM_BUFFER_FLAG_IG                      0x00000004      
#define RDB_OBJECT_CFG_FLAG_NONE                  0x0000 
#define RDB_OBJECT_CFG_FLAG_CTRL_EXTERN           0x0001 
#define RDB_OBJECT_CFG_FLAG_MODEL_ID_VALID        0x0002 
#define RDB_OBJECT_CFG_FLAG_FOREIGNER             0x0004 
#define RDB_OBJECT_CFG_FLAG_AUTO_SCALE            0x0008 
#define RDB_OBJECT_CFG_FLAG_SET_SIZE              0x0010 
#define RDB_OBJECT_CFG_FLAG_CORRECT_ONLY          0x0020 
#define RDB_ROAD_POS_FLAG_NONE                    0x00 
#define RDB_ROAD_POS_FLAG_DIR_FWD                 0x01 
#define RDB_ROAD_POS_FLAG_DIR_REAR                0x02 
#define RDB_ROAD_POS_FLAG_OFFROAD                 0x04 
#define RDB_CONTACT_POINT_FLAG_NONE                0x0000      
#define RDB_CONTACT_POINT_FLAG_PLAYER_VALID        0x0001      
#define RDB_SYNC_CMD_RENDER_CONTINUOUS          0x00000080      
#define RDB_SYNC_CMD_RENDER_PAUSE               0x00000100      
#define RDB_SYNC_CMD_RENDER_SINGLE_FRAME        0x00000200      
#define RDB_SYNC_CMD_RENDER_TARGET_FRAME        0x00000400      
#define RDB_TRAJECTORY_FLAG_NONE                0x0000          
#define RDB_TRAJECTORY_FLAG_TIME_DOMAIN         0x0001          
#define RDB_TRAJECTORY_FLAG_USE_COLOR           0x0002          
#define RDB_DYN_2_STEER_STATE_NONE                  0x0000          
#define RDB_DYN_2_STEER_STATE_PAUSE                 0x0001          
#define RDB_DYN_2_STEER_STATE_RUN                   0x0002          
#define RDB_DYN_2_STEER_STATE_ERROR                 0x0004          
#define RDB_DYN_2_STEER_CMD_NONE                    0x0000          
#define RDB_DYN_2_STEER_CMD_RESET                   0x0001          
#define RDB_DYN_2_STEER_EFFECT_NONE                 0x00000000      
#define RDB_DYN_2_STEER_EFFECT_TIRE_MODEL           0x00000001      
#define RDB_DYN_2_STEER_EFFECT_VIBRATION_10HZ       0x00000002      
#define RDB_STEER_2_DYN_STATE_OFF                   0x00000000      
#define RDB_STEER_2_DYN_STATE_INIT                  0x00000001      
#define RDB_STEER_2_DYN_STATE_FAIL                  0x00000002      
#define RDB_STEER_2_DYN_STATE_RUN                   0x00000004      
#define RDB_STEER_2_DYN_STATE_OVER_LIMITS           0x00000008      
#define RDB_WHEEL_FLAG_NONE                         0x0000          
#define RDB_WHEEL_FLAG_ON_ROADMARK                  0x0001          
#define RDB_MOTION_SYSTEM_FLAG_NONE             0x0000          
#define RDB_MOTION_SYSTEM_FLAG_ACTIVE           0x0001          
#define RDB_MOTION_SYSTEM_FLAG_ERROR            0x0002          
#define RDB_CUSTOM_TRACK_CTRL_FLAG_VIS_SENSOR_A  0x0001  
#define RDB_CUSTOM_TRACK_CTRL_FLAG_VIS_SENSOR_B  0x0002  
#define RDB_CUSTOM_TRACK_CTRL_FLAG_VIS_GFX       0x0004  
#define RDB_CUSTOM_TRACK_CTRL_FLAG_VIS_SENSOR_C  0x0008  
#define RDB_CUSTOM_TRACK_CTRL_FLAG_VIS_SENSOR_D  0x0010  
#define RDB_CUSTOM_TRACK_CTRL_FLAG_NAME_BY_ID    0x0100  
#define RDB_CUSTOM_TRACK_CTRL_FLAG_PLAYER_ACTIVE 0x0200  
#define RDB_CUSTOM_TRACK_CTRL_FLAG_DIRECT_MODE   0x0400  
#define RDB_CUSTOM_TRACK_CTRL_VALIDITY_DEFAULT         0x00000000 
#define RDB_CUSTOM_TRACK_CTRL_VALIDITY_TGT_ACCEL       0x00000001 
#define RDB_CUSTOM_TRACK_CTRL_VALIDITY_STEERING_TPOS   0x00000002 
#define RDB_ROAD_QUERY_FLAG_NONE                       0x0000 
#define RDB_ROAD_QUERY_FLAG_RELATIVE_POS               0x0001 
#define RDB_SYMBOL_TEXT_TYPE_3D_TEXT     0 /* Text in the 3D world*/
#define RDB_SYMBOL_TEXT_TYPE_SCREEN_TEXT 1 /*Text in screen coordinates*/

#define RDB_SYMBOL_CULL_FACE_NONE  0 /*Draw both front- and back-facing polygons.*/
#define RDB_SYMBOL_CULL_FACE_BACK  1 /*Cull all back-facing polygons -> draw only front-facing polygons. This is the default.*/
#define RDB_SYMBOL_CULL_FACE_FRONT 2 /*Cull all front-facing polygons -> draw only back-facing polygons. */

#define RDB_SYMBOL_TEXT_SIZE_ABSOLUTE        0 /* Text size is given in meters */
#define RDB_SYMBOL_TEXT_SIZE_SCREEN_RELATIVE 1 /* Text size is given relative to screen size. One is screen size */

#define RDB_SYMBOL_TEXT_ALIGN_LEFT_TOP            0 /* The anchor point is left and to the top of the text*/
#define RDB_SYMBOL_TEXT_ALIGN_LEFT_CENTER         1
#define RDB_SYMBOL_TEXT_ALIGN_LEFT_BOTTOM         2
#define RDB_SYMBOL_TEXT_ALIGN_CENTER_TOP          3
#define RDB_SYMBOL_TEXT_ALIGN_CENTER_CENTER       4
#define RDB_SYMBOL_TEXT_ALIGN_CENTER_BOTTOM       5
#define RDB_SYMBOL_TEXT_ALIGN_RIGHT_TOP           6
#define RDB_SYMBOL_TEXT_ALIGN_RIGHT_CENTER        7
#define RDB_SYMBOL_TEXT_ALIGN_RIGHT_BOTTOM        8
#define RDB_SYMBOL_TEXT_ALIGN_LEFT_BASE_LINE      9 /* Text starts at anchor point. The baseline of the first line of the text also runs through the anchor point.*/
#define RDB_SYMBOL_TEXT_ALIGN_CENTER_BASE_LINE   10
#define RDB_SYMBOL_TEXT_ALIGN_RIGHT_BASE_LINE    11
#define RDB_SYMBOL_TEXT_ALIGN_LEFT_BOTTOM_BASE_LINE 12 /* Like TEXT_ALIGN_LEFT_BASE_LINE, except the base line of the last  line of text is taken as a reference.*/
#define RDB_SYMBOL_TEXT_ALIGN_CENTER_BOTTOM_BASE_LINE 13
#define RDB_SYMBOL_TEXT_ALIGN_RIGHT_BOTTOM_BASE_LINE 14

#define RDB_SYMBOL_AXIS_ALIGN_SCREEN                    0
#define RDB_SYMBOL_AXIS_ALIGN_XY_PLANE                  1
#define RDB_SYMBOL_AXIS_ALIGN_REVERSED_XY_PLANE         2
#define RDB_SYMBOL_AXIS_ALIGN_XZ_PLANE                  3
#define RDB_SYMBOL_AXIS_ALIGN_REVERSED_XZ_PLANE         4
#define RDB_SYMBOL_AXIS_ALIGN_YZ_PLANE                  5
#define RDB_SYMBOL_AXIS_ALIGN_REVERSED_YZ_PLANE         6
#define RDB_SYMBOL_AXIS_ALIGN_USER_DEFINED_ROTATION     7

#define RDB_SYMBOL_DIR_ABSOLUTE              0 /* Direction of the drawing coordinate system matches the global coordinate system.*/
#define RDB_SYMBOL_DIR_RELTOOBJECT           1 /* Direction of the drawing coordinate system is the same as the direction of the object.*/
#define RDB_SYMBOL_DIR_BILLBOARD_SPHERICAL   2 /* The direction of the drawing coordinate system points towards the camera.*/
#define RDB_SYMBOL_DIR_BILLBOARD_CYLINDRICAL 3 /* The direction of the drawing coordinate system points towards the camera, except the Z dir points upwards, as in the global coordinate system.*/

#define RDB_SYMBOL_POLYGON_TYPE_TRIANGLES      0 /*points define a series of triangles; order suitable as an input in GL mode GL_TRIANGLES*/
#define RDB_SYMBOL_POLYGON_TYPE_TRIANGLE_STRIP 1 /*points define a triangle strip; order suitable as an input in GL mode GL_TRIANGLE_STRIP*/
#define RDB_SYMBOL_POLYGON_TYPE_QUADS          2 /*define a series of quads; order suitable as an input in GL mode GL_QUADS*/
#define RDB_SYMBOL_POLYGON_TYPE_QUAD_STRIP     3 /*points define a quadstrip; order suitable as an input in GL mode GL_QUAD_STRIP*/
#define RDB_SYMBOL_POLYGON_TYPE_LINES          4 /*define a series of lines; order suitable as an input in GL mode GL_LINES*/
#define RDB_SYMBOL_POLYGON_TYPE_LINE_STRIP     5 /*points define a linestrip; order suitable as an input in GL mode GL_LINE_STRIP*/
#define RDB_SYMBOL_POLYGON_TYPE_POINTS         6 /*A list of points*/

#define RDB_SYMBOL_COLORMODE_FLAT             0 /*one color for the entire polygon*/
#define RDB_SYMBOL_COLORMODE_SHADED           1 /*one color per vertex*/
#define RDB_SYMBOL_COLORMODE_TEXTURED         2 /*textured polygon, texture coordinates given for each vertex*/
#define RDB_SYMBOL_COLORMODE_TEXTURED_SHADED  3 /*texture and color for each vertex, combined using GL_MODULATE*/

typedef struct
{
	double x;
	double y;
	double z;
	uint8_t  flags;
	uint8_t  type;
	uint16_t system;
} RDB_POINT_t;

typedef struct
{
	double   x;
	double   y;
	double   z;
	float    h;
	float    p;
	float    r;
	uint8_t  flags;
	uint8_t  type;
	uint16_t system;
} RDB_COORD_t;

typedef struct
{
	uint16_t     id;
	uint16_t     spare;
	RDB_COORD_t  pos;
} RDB_COORD_SYSTEM_t;

typedef struct
{
	uint32_t         playerId;
	uint16_t         roadId;
	int8_t           laneId;
	uint8_t          flags;
	float            roadS;
	float            roadT;
	float            laneOffset;
	float            hdgRel;
	float            pitchRel;
	float            rollRel;
	uint8_t          roadType;
	uint8_t          spare1;
	uint16_t         spare2;
	float            pathS;
} RDB_ROAD_POS_t;

typedef struct
{
	uint32_t    playerId;
	int8_t      id;
	int8_t      prevId;
	int8_t      nextId;
	int8_t      laneId;
	float       lateralDist;
	float       yawRel;
	double      curvHor;
	double      curvHorDot;
	float       startDx;
	float       previewDx;
	float       width;
	float       height;
	double      curvVert;
	double      curvVertDot;
	uint8_t     type;
	uint8_t     color;
	uint16_t    noDataPoints;
	uint32_t    roadId;
	uint32_t    spare1;
} RDB_ROADMARK_t;

typedef struct
{
	uint16_t    roadId;
	int8_t      id;
	uint8_t     neighborMask;
	int8_t      leftLaneId;
	int8_t      rightLaneId;
	uint8_t     borderType;
	uint8_t     material;
	uint16_t    status;
	uint16_t    type;
	float       width;
	double      curvVert;
	double      curvVertDot;
	double      curvHor;
	double      curvHorDot;
	uint32_t    playerId;
	uint32_t    spare1;
} RDB_LANE_INFO_t;

typedef struct
{
	uint32_t id;
	uint8_t  category;
	uint8_t  type;
	int16_t  modelId;
	char     name[RDB_SIZE_OBJECT_NAME];
	char     modelName[RDB_SIZE_OBJECT_NAME];
	char     fileName[RDB_SIZE_FILENAME];
	uint16_t flags;
	uint16_t spare0;
	uint32_t spare1;
} RDB_OBJECT_CFG_t;

typedef struct
{
	float dimX;
	float dimY;
	float dimZ;
	float offX;
	float offY;
	float offZ;
} RDB_GEOMETRY_t;

typedef struct
{
	uint32_t            id;
	uint8_t             category;
	uint8_t             type;
	uint16_t            visMask;
	char                name[RDB_SIZE_OBJECT_NAME];
	RDB_GEOMETRY_t      geo;
	RDB_COORD_t         pos;
	uint32_t            parent;
	uint16_t            cfgFlags;
	int16_t             cfgModelId;
} RDB_OBJECT_STATE_BASE_t;

typedef struct
{
	RDB_COORD_t         speed;
	RDB_COORD_t         accel;
	float               traveledDist;
	uint32_t            spare[3];
} RDB_OBJECT_STATE_EXT_t;

typedef struct
{
	RDB_OBJECT_STATE_BASE_t base;
	RDB_OBJECT_STATE_EXT_t  ext;
} RDB_OBJECT_STATE_t;

typedef struct
{
	uint32_t playerId;
	float    rps;
	float    load;
	uint32_t spare1[2];
} RDB_ENGINE_BASE_t;

typedef struct
{
	float    rpsStart;
	float    torque;
	float    torqueInner;
	float    torqueMax;
	float    torqueFriction;
	float    fuelCurrent;
	float    fuelAverage;
	float    oilTemperature;
	float    temperature;
} RDB_ENGINE_EXT_t;

typedef struct
{
	RDB_ENGINE_BASE_t base;
	RDB_ENGINE_EXT_t  ext;
} RDB_ENGINE_t;

typedef struct
{
	uint32_t playerId;
	uint8_t  gearBoxType;
	uint8_t  driveTrainType;
	uint8_t  gear;
	uint8_t  spare0;
	uint32_t spare1[2];
} RDB_DRIVETRAIN_BASE_t;

typedef struct
{
	float    torqueGearBoxIn;
	float    torqueCenterDiffOut;
	float    torqueShaft;
	uint32_t spare1[2];
} RDB_DRIVETRAIN_EXT_t;

typedef struct
{
	RDB_DRIVETRAIN_BASE_t base;
	RDB_DRIVETRAIN_EXT_t  ext;
} RDB_DRIVETRAIN_t;

typedef struct
{
	uint32_t playerId;
	uint8_t  id;
	uint8_t  flags;
	uint8_t  spare0[2];
	float    radiusStatic;
	float    springCompression;
	float    rotAngle;
	float    slip;
	float    steeringAngle;
	uint32_t spare1[4];
} RDB_WHEEL_BASE_t;

typedef struct
{
	float    vAngular;
	float    forceZ;
	float    forceLat;
	float    forceLong;
	float    forceTireWheelXYZ[3];
	float    radiusDynamic;
	float    brakePressure;
	float    torqueDriveShaft;
	float    damperSpeed;
	uint32_t spare2[4];
} RDB_WHEEL_EXT_t;

typedef struct
{
	RDB_WHEEL_BASE_t base;
	RDB_WHEEL_EXT_t  ext;
} RDB_WHEEL_t;

typedef struct
{
	uint32_t playerId;
	uint32_t lightMask;
	float    steering;
	float    steeringWheelTorque;
	uint8_t  accMask;
	uint8_t  accSpeed;
	uint8_t  batteryState;
	int8_t   batteryRate;
	uint16_t displayLightMask;
	uint16_t fuelGauge;
	uint32_t spare[5];
} RDB_VEHICLE_SYSTEMS_t;

typedef struct
{
	uint32_t playerId;
	float    mass;
	float    wheelBase;
	int32_t  spare[4];
} RDB_VEHICLE_SETUP_t;

typedef struct
{
	uint32_t id;
	uint16_t width;
	uint16_t height;
	uint8_t  pixelSize;
	uint8_t  pixelFormat;
	uint16_t cameraId;
	uint32_t imgSize;
	uint8_t  color[4];
	uint32_t spare1[3];
} RDB_IMAGE_t;

typedef struct
{
	uint16_t lightElementId;
	uint16_t width;
	uint16_t height;
	uint16_t spare0;
	uint32_t dataSize;
	uint32_t spare1[3];
} RDB_CUSTOM_LIGHT_B_t;

typedef struct
{
	uint16_t lightElementId;
	uint16_t groupId;
	float    intensity;
	float    hOffset;
	float    pOffset;
	uint32_t spare[4];
} RDB_CUSTOM_LIGHT_GROUP_B_t;


typedef struct
{
	uint32_t id;
	uint8_t  type;
	uint8_t  dimension;
	uint16_t spare;
	uint32_t dataSize;
	uint32_t spare1[4];
} RDB_FUNCTION_t;

typedef struct
{
	uint32_t    id;
	uint8_t     type;
	uint8_t     hostCategory;
	uint16_t    spare0;
	uint32_t    hostId;
	char        name[RDB_SIZE_OBJECT_NAME];
	float       fovHV[2];
	float       clipNF[2];
	RDB_COORD_t pos;
	RDB_COORD_t originCoordSys;
	float       fovOffHV[2];
	int32_t     spare[2];
} RDB_SENSOR_STATE_t;

typedef struct
{
	uint8_t     category;
	uint8_t     type;
	uint16_t    flags;
	uint32_t    id;
	uint32_t    sensorId;
	double      dist;
	RDB_COORD_t sensorPos;
	int8_t      occlusion;
	int8_t      deltaLanePos;
	uint8_t     spare0[2];
	uint32_t    spare[3];
} RDB_SENSOR_OBJECT_t;

typedef struct
{
	uint16_t    id;
	uint16_t    width;
	uint16_t    height;
	uint16_t    spare0;
	float       clipNear;
	float       clipFar;
	float       focalX;
	float       focalY;
	float       principalX;
	float       principalY;
	RDB_COORD_t pos;
	uint32_t    spare1[4];
} RDB_CAMERA_t;

typedef struct
{
	uint16_t     id;
	int8_t       templateId;
	uint8_t      state;
	int32_t      playerId;
	RDB_COORD_t  pos;
	uint16_t     flags;
	uint16_t     spare0;
	int32_t      spare1[2];
} RDB_LIGHT_SOURCE_BASE_t;

typedef struct
{
	float        nearFar[2];
	float        frustumLRBT[4];
	float        intensity[3];
	float        atten[3];
	int32_t      spare1[3];
} RDB_LIGHT_SOURCE_EXT_t;

typedef struct
{
	RDB_LIGHT_SOURCE_BASE_t base;
	RDB_LIGHT_SOURCE_EXT_t  ext;
} RDB_LIGHT_SOURCE_t;

typedef struct
{
	uint16_t     id;
	uint16_t     flags;
	RDB_COORD_t  roadDataIn;
	float        friction;
	int32_t      playerId;
	int32_t      spare1;
} RDB_CONTACT_POINT_t;

typedef struct
{
	uint32_t     id;
	uint32_t     playerId;
	float        roadDist;
	RDB_COORD_t  pos;
	int32_t      type;
	int32_t      subType;
	float        value;
	uint32_t     state;
	int8_t       readability;
	int8_t       occlusion;
	uint16_t     spare0;
	uint32_t     addOnId;
	int8_t       minLane;
	int8_t       maxLane;
	uint16_t     spare;
} RDB_TRAFFIC_SIGN_t;

typedef struct
{
	uint32_t     playerId;
	int8_t       wheelId;
	uint8_t      spare0;
	uint16_t     spare1;
	uint32_t     roadId;
	float        defaultSpeed;
	float        waterLevel;
	uint32_t     eventMask;
	float        distToJunc;
	int32_t      spare2[11];
} RDB_ROAD_STATE_t;

typedef struct
{
	float          visibility;
	uint32_t       timeOfDay;
	float          brightness;
	uint8_t        precipitation;
	uint8_t        cloudState;
	uint16_t       flags;
	float          temperature;
	uint8_t        day;
	uint8_t        month;
	uint16_t       year;
	int16_t        timeZoneMinutesWest;
	uint16_t       spare2;
	float          frictionScale;
	uint32_t       spare1[4];
} RDB_ENVIRONMENT_t;

typedef struct
{
	uint32_t          playerId;
	RDB_COORD_t       pos;
	uint32_t          spare[4];
	uint32_t          noCoords;
	uint32_t          dataSize;
} RDB_PED_ANIMATION_t;

typedef struct
{
	uint32_t playerId;
	float    pathS;
	float    roadS;
	float    fuelCurrent;
	float    fuelAverage;
	uint32_t stateFlags;
	float    slip;
	uint32_t spare[4];
} RDB_CUSTOM_SCORING_t;

typedef struct
{
	float    deltaT;
	uint32_t frameNo;
	uint16_t features;
	int16_t  spare0;
} RDB_TRIGGER_t;

typedef struct
{
	float    deltaT;
	uint32_t frameNo;
	uint32_t spare[2];
} RDB_IG_FRAME_t;

typedef struct
{
	uint32_t playerId;
	float    steeringWheel;
	float    steeringSpeed;
	float    throttlePedal;
	float    brakePedal;
	float    clutchPedal;
	float    accelTgt;
	float    steeringTgt;              /* TODO: maybe this should become the turn rate */
	double   curvatureTgt;
	float    steeringTorque;
	float    engineTorqueTgt;
	float    speedTgt;
	uint8_t  gear;
	uint8_t  sourceId;
	uint8_t  spare0[2];
	uint32_t validityFlags;
	uint32_t flags;
	uint32_t mockupInput0;
	uint32_t mockupInput1;
	uint32_t mockupInput2;
	uint32_t spare;
} RDB_DRIVER_CTRL_t;

typedef struct
{
	uint32_t playerId;
	float    speedFromRules;
	float    distToSpeed;
	float    spare0[4];
	uint32_t flags;
	uint32_t spare[4];
} RDB_DRIVER_PERCEPTION_t;

typedef struct
{
	int32_t                   id;
	float                     state;
	uint32_t                  stateMask;
} RDB_TRAFFIC_LIGHT_BASE_t;

typedef struct
{
	float   duration;
	uint8_t type;
	uint8_t spare[3];
} RDB_TRAFFIC_LIGHT_PHASE_t;

typedef struct
{
	int32_t                   ctrlId;
	float                     cycleTime;
	uint16_t                  noPhases;
	uint32_t                  dataSize;
} RDB_TRAFFIC_LIGHT_EXT_t;

typedef struct
{
	RDB_TRAFFIC_LIGHT_BASE_t base;
	RDB_TRAFFIC_LIGHT_EXT_t  ext;
} RDB_TRAFFIC_LIGHT_t;

typedef struct
{
	uint32_t mask;
	uint32_t cmdMask;
	double   systemTime;
} RDB_SYNC_t;

typedef struct
{
	uint16_t id;
	uint16_t flags;
	uint16_t spare[2];
	double   x;
	double   y;
} RDB_ROAD_QUERY_t;

typedef struct
{
	uint16_t  version;
	uint16_t  spare;
	char      sender[RDB_SIZE_SCP_NAME];
	char      receiver[RDB_SIZE_SCP_NAME];
	uint32_t  dataSize;
} RDB_SCP_t;

typedef struct
{
	uint16_t  protocol;
	uint16_t  pkgId;
	uint32_t  spare[6];
	uint32_t  dataSize;
} RDB_PROXY_t;

typedef struct
{
	uint32_t  playerId;
	double    spacing;
	uint16_t  flags;
	uint16_t  noDataPoints;
	uint8_t   color[4];
	uint32_t  spare[3];
} RDB_TRAJECTORY_t;

typedef struct
{
	uint32_t            playerId;
	uint32_t            flags;
	RDB_COORD_t         pos;
	RDB_COORD_t         speed;
	uint8_t             subSystem;
	uint8_t             spare1[3];
	uint32_t            spare[5];
} RDB_MOTION_SYSTEM_t;

typedef struct
{
	uint32_t            id;
	RDB_COORD_t         pos;
	RDB_POINT_t         scale;
	uint32_t            playerId;
	uint8_t             zBuffer;
	uint8_t             cullFaceMode;
	uint8_t             dirMode;
	uint8_t             spare0;
	uint8_t             color[4];
	uint64_t            channelMaskLow;
	uint64_t            channelMaskHigh;
} RDB_SYMBOL_STATE_t;

typedef struct
{
	RDB_SYMBOL_STATE_t  general;
	int32_t             fontId;
	uint16_t            fontWidth;
	uint16_t            fontHeight;
	float               size;
	uint32_t            textSize;
	uint8_t             textSizeMode;
	uint8_t             textAlignment;
	uint8_t             type;
	uint8_t             axisAlignment;
	uint32_t            spare[3];
} RDB_SYMBOL_TEXT_STATE_t;

typedef struct {
	RDB_SYMBOL_STATE_t  general;
	int32_t             textureId;
	float               width;
	uint32_t            floatSize;
	uint8_t             type;
	uint8_t             colorMode;
	uint16_t            spare0;
	uint32_t            spare[3];
} RDB_SYMBOL_POLYGON_STATE_t;

typedef struct
{
	uint32_t playerId;
	uint16_t flags;
	uint8_t  posType;
	int8_t   dir;
	uint32_t roadId;
	double   initialRoadDeltaS;
	float    targetRoadT;
	float    speedTgtS;
	float    minAccelS;
	float    maxAccelS;
	float    accelTgt;
	uint32_t validityFlags;
	uint8_t  canTimeStamp;
	uint8_t  spare0[3];
	uint32_t spare[3];
} RDB_CUSTOM_OBJECT_CTRL_TRACK_t;

typedef struct
{
	uint32_t playerId;
	float    distance;
	float    angleLeft;
	float    angleRight;
	float    distanceLeft;
	float    distanceRight;
	uint8_t  stateLeft;
	uint8_t  stateRight;
	uint8_t  stateDistance;
	uint8_t  noVisibleObjects;
	uint32_t spare1[3];
} RDB_FREESPACE_t;

typedef struct
{
	uint32_t objectId;
	uint32_t elementId;
	uint8_t  scope;
	uint8_t  spare0[3];
	uint32_t state;
	uint32_t spare1[2];
} RDB_DYN_EL_SWITCH_t;

typedef struct
{
	uint32_t objectId;
	uint32_t elementId;
	uint8_t  scope;
	uint8_t  validity;
	uint8_t  nValues;
	uint8_t  spare0;
	uint32_t spare1[3];
} RDB_DYN_EL_DOF_t;

#ifndef MATLAB_MEX_FILE

typedef struct
{
} RDB_END_OF_FRAME_t;

typedef struct
{
} RDB_START_OF_FRAME_t;
#endif

typedef struct
{
	uint32_t  playerId;
	uint32_t  state;
	float     angle;
	float     rev;
	float     torque;
	uint32_t  spare[8];
} RDB_STEER_2_DYN_t;

typedef struct
{
	uint32_t  playerId;
	uint16_t  state;
	uint16_t  cmd;
	uint32_t  effects;
	float     torque;
	float     friction;
	float     damping;
	float     stiffness;
	float     velocity;
	float     angle;
	float     neutralPos;
	float     dampingMaxTorque;
	uint32_t  spare[6];
} RDB_DYN_2_STEER_t;

typedef struct
{
	uint32_t    id;
	uint32_t    emitterId;
	uint8_t     type;
	uint8_t     spare0;
	uint16_t    spare2;
	float       length;
	uint32_t    spare1[3];
	RDB_COORD_t ray;
} RDB_RAY_t;

typedef struct
{
	uint32_t    noOverruns;
	uint32_t    noUnderruns;
	uint32_t    noMeasurements;
	float       tolerance;
	float       nominalFrameTime;
	float       actualFrameTime;
	uint8_t     instanceId;
	uint8_t     frameLockCounter;
	int8_t      exponent;
	uint8_t     spare1;
	uint16_t    sgFrameTimes[4];
	uint32_t    spare2[3];
} RDB_RT_PERFORMANCE_t;

typedef struct
{
	uint32_t playerId;
	float    distance;
	uint8_t  distUnit;
	uint8_t  spare0[3];
	float    laneOffset;
	float    hdgRel;
	float    curvHor;
	float    curvHorDot;
	uint32_t spare[7];
} RDB_CUSTOM_LOOK_AHEAD_t;

typedef struct
{
	uint16_t  magicNo;
	uint16_t  version;
	uint32_t  headerSize;
	uint32_t  dataSize;
	uint32_t  frameNo;
	double    simTime;
} RDB_MSG_HDR_t;

typedef struct
{
	uint32_t  headerSize;
	uint32_t  dataSize;
	uint32_t  elementSize;
	uint16_t  pkgId;
	uint16_t  flags;
} RDB_MSG_ENTRY_HDR_t;


typedef union
{
	RDB_COORD_SYSTEM_t              coordSystem;
	RDB_COORD_t                     coord;
	RDB_ROAD_POS_t                  roadPos;
	RDB_LANE_INFO_t                 laneInfo;
	RDB_ROADMARK_t                  roadMark;
	RDB_OBJECT_CFG_t                objectCfg;
	RDB_OBJECT_STATE_t              objectState;
	RDB_VEHICLE_SYSTEMS_t           vehicleSystems;
	RDB_VEHICLE_SETUP_t             vehicleSetup;
	RDB_ENGINE_t                    engine;
	RDB_DRIVETRAIN_t                drivetrain;
	RDB_WHEEL_t                     wheel;
	RDB_PED_ANIMATION_t             pedAnimation;
	RDB_SENSOR_STATE_t              sensorState;
	RDB_SENSOR_OBJECT_t             sensorObject;
	RDB_CAMERA_t                    camera;
	RDB_CONTACT_POINT_t             contactPoint;
	RDB_TRAFFIC_SIGN_t              trafficSign;
	RDB_ROAD_STATE_t                roadState;
	RDB_IMAGE_t                     image;
	RDB_LIGHT_SOURCE_t              lightSrc;
	RDB_ENVIRONMENT_t               environment;
	RDB_TRIGGER_t                   trigger;
	RDB_DRIVER_CTRL_t               driverCtrl;
	RDB_TRAFFIC_LIGHT_t             trafficLight;
	RDB_SYNC_t                      sync;
	RDB_DRIVER_PERCEPTION_t         driverPerception;
	RDB_IMAGE_t                     lightMap;
	RDB_FUNCTION_t                  toneMapping;
	RDB_PROXY_t                     proxy;
	RDB_MOTION_SYSTEM_t             motionSystem;
	RDB_IG_FRAME_t                  igFrame;
	/* custom packages here, please */
	RDB_CUSTOM_SCORING_t            scoring;
} RDB_MSG_UNION_t;

typedef struct
{
	RDB_MSG_HDR_t       hdr;
	RDB_MSG_ENTRY_HDR_t entryHdr;
	RDB_MSG_UNION_t     u;
} RDB_MSG_t;

typedef struct
{
	uint32_t  thisSize;
	uint32_t  bufferSize;
	uint16_t  id;
	uint16_t  spare0;
	uint32_t  flags;
	uint32_t  offset;
	uint32_t  spare1[4];
} RDB_SHM_BUFFER_INFO_t;

typedef struct
{
	uint32_t  headerSize;
	uint32_t  dataSize;
	uint8_t   noBuffers;
} RDB_SHM_HDR_t;


typedef struct
{
	uint32_t    objectId;
	float       distance;
	float       radialVelocity;
	float       spare;
	float       azimuthAngle;
	float       elevationAngle;
	uint32_t    spare1[5];
} RDB_RADAR_HIT_POINT_t;

#endif        /* _VIRES_RDB_ICD_H */

/* end of pragma 4 */
#pragma pack(pop)
#pragma once
