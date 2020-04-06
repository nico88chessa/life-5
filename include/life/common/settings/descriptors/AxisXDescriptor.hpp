#ifndef AXISXDESCRIPTOR_HPP
#define AXISXDESCRIPTOR_HPP

#include <life/common/settings/SettingDescriptor.hpp>


DV_LIFE_OPEN_NAMESPACE

DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_STEP_PER_MM, SettingsGroupType::AXIS_X, "StepPerMm", "Step per mm", 1000)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_MIN_POS_MM, SettingsGroupType::AXIS_X, "MinPosMm", "Min position [mm]", 0)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_MAX_POS_MM, SettingsGroupType::AXIS_X, "MaxPosMm", "Max position [mm]", 1500)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_SAFETY_POS_MM, SettingsGroupType::AXIS_X, "SafetyPositionMm", "Safety position [mm]", 1500)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_BASE_OFFSET_MM, SettingsGroupType::AXIS_X, "BaseOffsetMm", "Base offset [mm]", -40)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_MANUAL_SPEED_MMS, SettingsGroupType::AXIS_X, "ManualSpeedMms", "Manual speed [mm/s]", 20)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_MANUAL_ACC_MMS2, SettingsGroupType::AXIS_X, "ManualAccMms2", "Manual acceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_MANUAL_DEC_MMS2, SettingsGroupType::AXIS_X, "ManualDecMms2", "Manual deceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_OPERATIVE_SPEED_MMS, SettingsGroupType::AXIS_X, "OperativeSpeedMms", "Operative speed [mm/s]", 20)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_OPERATIVE_ACC_MMS2, SettingsGroupType::AXIS_X, "OperativeAccMms2", "Operative acceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_OPERATIVE_DEC_MMS2, SettingsGroupType::AXIS_X, "OperativeDecMms2", "Operative deceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_HOMING_SPEED_MMS, SettingsGroupType::AXIS_X, "HomingSpeedMms", "Homing speed [mm/s]", 20)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_HOMING_ACC_MMS2, SettingsGroupType::AXIS_X, "HomingAccMms2", "Homing acceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_HOMING_DEC_MMS2, SettingsGroupType::AXIS_X, "HomingDecMms2", "Homing deceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_STEP_SPEED_MMS, SettingsGroupType::AXIS_X, "StepModeSpeedMms", "Step mode speed [mm/s]", 20)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_STEP_ACC_MMS2, SettingsGroupType::AXIS_X, "StepModeAccMms2", "Step Mode acceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_STEP_DEC_MMS2, SettingsGroupType::AXIS_X, "StepModeDecMms2", "Step Mode deceleration [(mm/s)^2]", 100)

// solo per test
DECL_MACHINE_PARAMETER(AXIS_X_TEST, SettingsGroupType::AXIS_X, "Test", "Test", AxisXFeedback::LINEAR_ENCODER, ( Option::IS_IP_ADDRESS ) )
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_FEEDBACK, SettingsGroupType::AXIS_X, "Feedback", "Feedback", AxisXFeedback::LINEAR_ENCODER)


DECL_SETTINGS_DESCRIPTOR(AXIS_X_DESCR, SettingsGroupType::AXIS_X, true, (
    AXIS_X_STEP_PER_MM,
    AXIS_X_MIN_POS_MM,
    AXIS_X_MAX_POS_MM,
    AXIS_X_SAFETY_POS_MM,
    AXIS_X_BASE_OFFSET_MM,
    AXIS_X_MANUAL_SPEED_MMS,
    AXIS_X_MANUAL_ACC_MMS2,
    AXIS_X_MANUAL_DEC_MMS2,
    AXIS_X_OPERATIVE_SPEED_MMS,
    AXIS_X_OPERATIVE_ACC_MMS2,
    AXIS_X_OPERATIVE_DEC_MMS2,
    AXIS_X_HOMING_SPEED_MMS,
    AXIS_X_HOMING_ACC_MMS2,
    AXIS_X_HOMING_DEC_MMS2,
    AXIS_X_STEP_SPEED_MMS,
    AXIS_X_STEP_ACC_MMS2,
    AXIS_X_STEP_DEC_MMS2,
    AXIS_X_FEEDBACK)
)

DV_LIFE_CLOSE_NAMESPACE

#endif // AXISXDESCRIPTOR_HPP
