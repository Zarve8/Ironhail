#pragma once
#include "SkillLibrary.generated.h"


UENUM(BlueprintType, Category = Modifier)
enum Mod {
	E_NoneMod UMETA(DisplayName = "None"),
	E_RapidFire UMETA(DisplayName = "RapidFire"),
	E_HighDamage UMETA(DisplayName = "HighDamage"),
	E_Pesto UMETA(DisplayName = "Pesto"),
	E_Frost UMETA(DisplayName = "Frost"),
	E_Burn UMETA(DisplayName = "Burn"),
	E_LongRange UMETA(DisplayName = "LongRange"),
	E_Lightning UMETA(DisplayName = "Lightning"),
};