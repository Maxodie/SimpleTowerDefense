#pragma once
#include"TurretType.h"

struct TurretData {//defaults values for BASIC_TURRET
	float damageAmount = 7.f;
	float range = 2.f;

	float freezeAmount = 0.f;//percentage (0-1)
	float fireRate = 1.f;
	float cost = 300.f;

	float sellPrice = 150.f;

	TurretType type = TurretType::BASIC_TURRET;
};