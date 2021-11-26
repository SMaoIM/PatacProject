#pragma once
#include <stdint.h>

typedef struct
{
	uint32_t playerId; //< unique player ID to which the controls apply @unit _
	float steeringWheel; //< steering wheel angle @unit rad
	/*
	float steeringSpeed; //< steering speed @unit rad/s
	float throttlePedal; //< throttle pedal position @unit [0.0..1.0]
	float brakePedal; //< brake pedal position @unit [0.0..1.0]
	float clutchPedal; //< clutch pedal position @unit [0.0..1.0]
	float accelTgt; //< desired acceleration @unit m/s2
	float steeringTgt; //< desired steering angle at wheels @unit rad
	double curvatureTgt; //< desired resulting curvature of the lateral motion @unit 1/m
	float steeringTorque; //< torque at steering wheel @unit Nm
	float engineTorqueTgt; //< target engine torque @unit Nm
	float speedTgt; //< target speed @unit m/s
	uint8_t gear; //< desired gear box position @unit @link RDB_GEAR_BOX_POS @endlink
	uint8_t sourceId; //< unique number of the source providing this input @unit @link RDB_DRIVER_SOURCE @endlink
	uint8_t spare0[2]; //< some spares for future use @unit _
	*/
	uint32_t validityFlags; //< flags which of the above inputs are valid @unit @link RDB_DRIVER_INPUT_VALIDITY @endlink
	/*
	uint32_t flags; //< input flags (indicator etc.) @unit @link RDB_DRIVER_FLAG @endlink
	uint32_t mockupInput0; //< flags resulting from mockup buttons, part 1 @unit @link RDB_MOCKUP_INPUT0 @endlink
	uint32_t mockupInput1; //< flags resulting from mockup buttons, part 2 @unit @link RDB_MOCKUP_INPUT1 @endlink
	uint32_t mockupInput2; //< flags resulting from mockup buttons, part 3 @unit @link RDB_MOCKUP_INPUT2 @endlink
	uint32_t spare; //< some spare for future use @unit _
	*/
} RDB_DRIVER_CTRL_t;