#pragma once
#include "TimerSystem.h"
#include "../Actor.h"

struct Gun
{
	int ammo {10};
	int bullets = 1;
	float bullet_speed {0.1};
	bool can_shoot {true};
};

class Player : public Actor
{
public:
	Player(Vector position);

	void update() override;
	void draw() override;

	void hit(int damage) override
	{
		if (is_invincible())
			return;

		last_hit_time = engCurrentTime();

		health -= damage;
		if (health <= 0)
		{
			destroy();
		}
	}

	float speed = 300.f;

private:
	static constexpr float INVINCIBILITY_TIME = 2.f;
	static constexpr int MAX_HEALTH = 3;
	static constexpr int MAX_PISTOL_AMMO = 20;
	static constexpr float BULLET_INTERNAL_PISTOL = 3.0f;
	static constexpr int MAX_SHOTGUN_AMMO = 5;
	static constexpr float BULLET_INTERNAL_SHOTGUN = 2.0f;
	bool is_invincible()
	{
		return engTimePassedSince(last_hit_time) < INVINCIBILITY_TIME;
	}

	int health = MAX_HEALTH;
	float last_hit_time = -INVINCIBILITY_TIME;
	Gun shotgun, pistol;
	Timer_System timer;
	const float cross_hair_length = 500.0f;
};
