#include "PickUp.h"

HealthPickUp::HealthPickUp(Vector position)
	: Actor(position, Vector(20), COLOR_GREEN)
{
	collision_channel = Collision_Channel::HealthPickup;
}

AmmoPickUp::AmmoPickUp(Vector position)
	: Actor(position, Vector(20), COLOR_LIGHT_GRAY)
{
	collision_channel = Collision_Channel::AmmoPickup;
}



