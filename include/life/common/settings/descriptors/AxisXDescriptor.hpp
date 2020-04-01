#ifndef AXISXDESCRIPTOR_HPP
#define AXISXDESCRIPTOR_HPP

#include <life/common/settings/descriptors/SettingDescriptor.hpp>


DV_LIFE_OPEN_NAMESPACE

DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_STEP_PER_MM, SettingsGroup::AXIS_X, "StepPerMm", "Step per mm", 1000)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_MIN_POS_MM, SettingsGroup::AXIS_X, "MinPosMm", "Min position [mm]", 0)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_MAX_POS_MM, SettingsGroup::AXIS_X, "MaxPosMm", "Max position [mm]", 1500)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_SAFETY_POS_MM, SettingsGroup::AXIS_X, "SafetyPositionMm", "Safety position [mm]", 1500)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_BASE_OFFSET_MM, SettingsGroup::AXIS_X, "BaseOffsetMm", "Base offset [mm]", -40)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_MANUAL_SPEED_MMS, SettingsGroup::AXIS_X, "ManualSpeedMms", "Manual speed [mm/s]", 20)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_MANUAL_ACC_MMS2, SettingsGroup::AXIS_X, "ManualAccMms2", "Manual acceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_MANUAL_DEC_MMS2, SettingsGroup::AXIS_X, "ManualDecMms2", "Manual deceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_OPERATIVE_SPEED_MMS, SettingsGroup::AXIS_X, "OperativeSpeedMms", "Operative speed [mm/s]", 20)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_OPERATIVE_ACC_MMS2, SettingsGroup::AXIS_X, "OperativeAccMms2", "Operative acceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_OPERATIVE_DEC_MMS2, SettingsGroup::AXIS_X, "OperativeDecMms2", "Operative deceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_HOMING_SPEED_MMS, SettingsGroup::AXIS_X, "HomingSpeedMms", "Homing speed [mm/s]", 20)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_HOMING_ACC_MMS2, SettingsGroup::AXIS_X, "HomingAccMms2", "Homing acceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_HOMING_DEC_MMS2, SettingsGroup::AXIS_X, "HomingDecMms2", "Homing deceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_STEP_SPEED_MMS, SettingsGroup::AXIS_X, "StepModeSpeedMms", "Step mode speed [mm/s]", 20)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_STEP_ACC_MMS2, SettingsGroup::AXIS_X, "StepModeAccMms2", "Step Mode acceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_STEP_DEC_MMS2, SettingsGroup::AXIS_X, "StepModeDecMms2", "Step Mode deceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_FEEDBACK, SettingsGroup::AXIS_X, "Feedback", "Feedback", AxisXFeedback::LINEAR_ENCODER)

//DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_FEEDBACK, SettingsGroup::AXIS_X, "Feedback",  AxisXFeedback::LINEAR_ENCODER)
//DECL_MACHINE_PARAMETER_NOOPT(AXIS_X_MOTOR_KIND, SettingsGroup::AXIS_X, "MotorKind", MotorXKind::LINEAR)


static constexpr SettingDescriptor AXIS_X_DESCR({
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
    AXIS_X_FEEDBACK
});

DV_LIFE_CLOSE_NAMESPACE

#endif // AXISXDESCRIPTOR_HPP
