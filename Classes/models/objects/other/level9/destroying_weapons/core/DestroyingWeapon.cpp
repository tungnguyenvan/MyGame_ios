#include "DestroyingWeapon.h"

DestroyingWeapon::DestroyingWeapon(const std::string& name) : CoreModel(name)
{
	// There is no physics body in the destroyer objects, so we do this //
	mCorePhysicsBody = nullptr;

	// Constructor //
}

void DestroyingWeapon::Init()
{
	// Initialization //
}

void DestroyingWeapon::Update()
{
	// Update //
}
