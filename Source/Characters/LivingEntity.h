#ifndef LIVING_H
#define LIVING_H

#include "../Base/Entity.h"
#include "../Base/config.h"
/*
Objects in the game that can be moved.
*/
class LivingEntity : public Entity
{
protected:
	/// <summary>
	/// Health points of the entity 
	/// </summary>
	int health;
	
	/// <summary>
	/// HP count (health points)
	/// </summary>
	int maxHealth;
	
	/// <summary>
	/// Amount of money the entity has or will yield when killed.
	/// </summary>
	int money;
	
	/// <summary>
	/// Amount of experience the entity has or will yield when killed.
	/// </summary>
	int experience;
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="startHealth"></param>
	/// <param name="startMoney"></param>
	/// <param name="startExp"></param>
	LivingEntity(int startHealth, int startMoney, int startExp);
	
	/// <summary>
	/// Applies damage to the character, making it lose HP according to its resistance.
	/// </summary>
	/// <param name="dmg"></param>
	void damage(int dmg);

	/// <summary>
	/// Changes the entity's health to the desired amount.
	/// </summary>
	/// <param name="h"></param>
	void setHealth(int h);
	
	/// <summary>
	/// True if the player is alive (more than 0 HP)
	/// </summary>
	/// <returns></returns>
	virtual bool isAlive() const;
	
	/// <summary>
	/// Instantly kills the entity (pure virtual).
	/// </summary>
	virtual void kill() = 0;
	
	/// <summary>
	/// Draws the entity's healthbar.
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX"></param>
	/// <param name="offsetY"></param>
	virtual void drawHealthBar(RenderContext& renderer, int offsetX, int offsetY)const;
};

#endif
