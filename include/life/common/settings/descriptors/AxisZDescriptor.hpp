#ifndef AXISZDESCRIPTOR_HPP
#define AXISZDESCRIPTOR_HPP

#include <life/common/settings/descriptors/SettingDescriptor.hpp>


DV_LIFE_OPEN_NAMESPACE

DECL_MACHINE_PARAMETER_NOOPT(AXIS_Z_STEP_PER_MM, SettingsGroup::AXIS_Z, "StepPerMm", "Step per mm", 1000)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_Z_MIN_POS_MM, SettingsGroup::AXIS_Z, "MinPosMm", "Min position [mm]", 0)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_Z_MAX_POS_MM, SettingsGroup::AXIS_Z, "MaxPosMm", "Max position [mm]", 1500)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_Z_SAFETY_POS_MM, SettingsGroup::AXIS_Z, "SafetyPositionMm", "Safety position [mm]", 1500)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_Z_MANUAL_SPEED_MMS, SettingsGroup::AXIS_Z, "ManualSpeedMms", "Manual speed [mm/s]", 20)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_Z_MANUAL_ACC_MMS2, SettingsGroup::AXIS_Z, "ManualAccMms2", "Manual acceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_Z_MANUAL_DEC_MMS2, SettingsGroup::AXIS_Z, "ManualDecMms2", "Manual deceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_Z_OPERATIVE_SPEED_MMS, SettingsGroup::AXIS_Z, "OperativeSpeedMms", "Operative speed [mm/s]", 20)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_Z_OPERATIVE_ACC_MMS2, SettingsGroup::AXIS_Z, "OperativeAccMms2", "Operative acceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_Z_OPERATIVE_DEC_MMS2, SettingsGroup::AXIS_Z, "OperativeDecMms2", "Operative deceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_Z_HOMING_SPEED_MMS, SettingsGroup::AXIS_Z, "HomingSpeedMms", "Homing speed [mm/s]", 20)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_Z_HOMING_ACC_MMS2, SettingsGroup::AXIS_Z, "HomingAccMms2", "Homing acceleration [(mm/s)^2]", 100)
DECL_MACHINE_PARAMETER_NOOPT(AXIS_Z_HOMING_DEC_MMS2, SettingsGroup::AXIS_Z, "HomingDecMms2", "Homing deceleration [(mm/s)^2]", 100)


static constexpr SettingDescriptor AXIS_Z_DESCR({
    AXIS_Z_STEP_PER_MM,
    AXIS_Z_MIN_POS_MM,
    AXIS_Z_MAX_POS_MM,
    AXIS_Z_SAFETY_POS_MM,
    AXIS_Z_MANUAL_SPEED_MMS,
    AXIS_Z_MANUAL_ACC_MMS2,
    AXIS_Z_MANUAL_DEC_MMS2,
    AXIS_Z_OPERATIVE_SPEED_MMS,
    AXIS_Z_OPERATIVE_ACC_MMS2,
    AXIS_Z_OPERATIVE_DEC_MMS2,
    AXIS_Z_HOMING_SPEED_MMS,
    AXIS_Z_HOMING_ACC_MMS2,
    AXIS_Z_HOMING_DEC_MMS2
});

DV_LIFE_CLOSE_NAMESPACE

#endif // AXISZDESCRIPTOR_HPP
