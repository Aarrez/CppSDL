#include "Player.h"

#include <SDL_log.h>
#include <random>

#include "Game.h"
#include "Enemy.h"
#include "Bullet.h"
#include "../Config.h"

Player::Player(Vector position)
	: Actor(position, Vector(32), COLOR_WHITE)
{
	collision_channel = Collision_Channel::Player;
	shotgun.ammo = MAX_SHOTGUN_AMMO;
	shotgun.bullets = 5;
	shotgun.bullet_speed = BULLET_INTERNAL_SHOTGUN;
	pistol.ammo = MAX_PISTOL_AMMO;
	pistol.bullet_speed = BULLET_INTERNAL_PISTOL;
}

void Player::update()
{
	timer.update();
	Vector input;

	if (engKeyDown(Key::W))
		input.y -= 1.f;
	if (engKeyDown(Key::S))
		input.y += 1.f;
	if (engKeyDown(Key::D))
		input.x += 1.f;
	if (engKeyDown(Key::A))
		input.x -= 1.f;

	input.normalize();
	position += input * speed * engDeltaTime();

	if (engKeyPressed(Key::E))
		speed += 50.f;
	if (engKeyPressed(Key::Q))
		speed -= 50.f;

	if (engMouseButtonDown(Mouse_Button::Left))
	{
		if(pistol.can_shoot && pistol.ammo > 0)
		{
			timer.add_timer(.1f,
				[this](){pistol.can_shoot = true;},false);

			Vector mouse_position = Vector(engMouseX(), engMouseY());
			mouse_position = game->get_camera().screen_to_world(mouse_position);

			Vector bullet_direction = mouse_position - position;
			bullet_direction.normalize();

			auto* bullet = game->spawn_actor<Bullet>(position);
			bullet->set_direction(bullet_direction);
			pistol.ammo--;
			pistol.can_shoot = false;
		}

	}

	if(engMouseButtonPressed(Mouse_Button::Right))
	{
		if(shotgun.can_shoot && shotgun.ammo > 0)
		{
			timer.add_timer(shotgun.bullet_speed,
				[this]{ shotgun.can_shoot = true; }, false);

			Vector mouse_position = Vector(engMouseX(), engMouseY());
			mouse_position = game->get_camera().screen_to_world(mouse_position);

			Vector bullet_direction = mouse_position - position;
			bullet_direction.normalize();


			for (int i = 0; i < shotgun.bullets; ++i)
			{
				std::random_device dev;
				std::mt19937 rng(dev());
				std::uniform_int_distribution<int> nomral_dist{-5 , 5};

				const auto random_int = nomral_dist(rng);
				const float num = std::roundf(static_cast<float>(random_int)) / 100;
				bullet_direction.x += num;
				bullet_direction.y += num;

				auto* bullet = game->spawn_actor<Bullet>(position);
				bullet->set_direction(bullet_direction);
				/*SDL_Log("Direction Normalized x: %f y: %f", bullet_direction.x, bullet_direction.y);*/
			}
			shotgun.ammo--;
			shotgun.can_shoot = false;
		}
	}

	if (health < MAX_HEALTH)
	{
		Actor* pickupActor =
			game->get_colliding_actor(this, Collision_Channel::HealthPickup);
		if (pickupActor)
		{
			pickupActor->destroy();
			health++;
		}
	}
	if(pistol.ammo < MAX_PISTOL_AMMO || shotgun.ammo < MAX_SHOTGUN_AMMO)
	{
		Actor* pickup_ammo =
			game->get_colliding_actor(this, Collision_Channel::AmmoPickup);
		if(pickup_ammo)
		{
			pickup_ammo->destroy();
			pistol.ammo = MAX_PISTOL_AMMO;
			shotgun.ammo = MAX_SHOTGUN_AMMO;
		}
	}

}

void Player::draw()
{
	Vector mouse_position = Vector(engMouseX(), engMouseY());
	mouse_position = game->get_camera().screen_to_world(mouse_position);


	Vector aim_direction = mouse_position - position;
	aim_direction.normalize();

	Vector crosshair_start =
		game->get_camera().world_to_screen(position + aim_direction * 45.f);
	Vector crosshair_end =
		game->get_camera().world_to_screen(position + aim_direction * cross_hair_length);

	engSetDrawColor(COLOR_RED);
	engDrawLine(
		crosshair_start.x, crosshair_start.y,
		crosshair_end.x, crosshair_end.y
	);


	// Draw health UI 
	for (int i = 0; i < MAX_HEALTH; ++i)
	{
		if (i < health)
			engSetDrawColor(COLOR_WHITE);
		else
			engSetDrawColor(0xFFFFFF55);

		engFillRect(10 + 40 * i, 10, 32, 32);
	}

	engDrawTextF(Config::WINDOW_WIDTH - 200 ,10,
		"Pistol Ammo: %i", pistol.ammo);
	engDrawTextF(Config::WINDOW_WIDTH - 220, 40,
		"Shotgun Ammo: %i", shotgun.ammo);

	// Flash player when invincible
	if (is_invincible())
	{
		if (int(engCurrentTime() * 15) % 2 == 0)
			color = 0xFFFFFF77;
		else
			color = COLOR_WHITE;
	}
	else
	{
		color = COLOR_WHITE;
	}

	Actor::draw();
}
