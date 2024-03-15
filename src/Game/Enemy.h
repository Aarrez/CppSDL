#pragma once
#include "../Actor.h"

class Enemy : public Actor
{
public:
	static int NUM_ENEMIES;

	Enemy(Vector position);
	~Enemy() override;
	void update() override;
	void draw() override;

	void hit(int damage) override
	{
		health -= damage;
		if (health <= 0)
		{
			destroy();
		}
	}

	float speed = 50.f;

private:
	static constexpr int MAX_HEALTH = 100;
	int health = MAX_HEALTH;
};

class BigEnemy : public Actor
{
public:
    static int NUM_BIG_ENEMIES;

    BigEnemy(Vector position);
    ~BigEnemy() override;
    void update() override;
    void draw() override;

    void hit(int damage) override
    {
        health -= damage;
        if(health <= 0)
        {
            destroy();
        }
    }

    float speed = 25.0f;
private:
    static constexpr int MAX_HEALTH = 200;
    int health = MAX_HEALTH;
};

extern int NUM_ENEMIES;
