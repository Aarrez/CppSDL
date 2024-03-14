#pragma once
#include "../Actor.h"

class HealthPickUp : public Actor
{
public:
	explicit HealthPickUp(Vector position);
};

class AmmoPickUp : public Actor
{
public: AmmoPickUp(Vector position);
};
