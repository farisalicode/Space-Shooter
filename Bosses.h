#include<SFML/Graphics.hpp>
#include<iostream>
#include<cstring>
#include "Bomb.h"
#ifndef BOSSES_H_
#define BOSSES_H_
using namespace sf;



class Bosses
{
 public:
	std::string name;
	Texture texture;
	Sprite sprite;
	float speed;
	int og_x;
	int og_y;
	float curr_x;
	float curr_y;
	int boss_health;
	bool alive;
	Bomb* bomb;
	int points;

	virtual void fun1() = 0;

	virtual void move()
	{
		  float delta_x=0;
		  delta_x = delta_x + 1.0;
		  delta_x=delta_x * this->speed;

		  if (this->anaomally(delta_x) == false)
		  sprite.move(Vector2f(delta_x,0));
		  else if (this->anaomally(delta_x) == true)
		  this->position(0,10);
		  return;
		return;
	}

	virtual void position(int cor_x,int cor_y)
	{
		this->sprite.setPosition(cor_x,cor_y);
		return;
	}

	virtual bool anaomally(float delta_x)
	{
		  this->curr_x = sprite.getPosition().x;
		  this->curr_y = sprite.getPosition().y;
		  bool checker = false;
		  if ( curr_x + delta_x + this->sprite.getGlobalBounds().width > 780)
		   {
		  	 sprite.setPosition(curr_x,0);
		  	 checker = true;
		   }
		  return checker;
	}

	 virtual void shooting()
	 {
		 if (this->bomb->anaomally() == false)
		 this->bomb->move();
		 else
		 this->bomb->position(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2.0 - 6,this->sprite.getPosition().y);
	     this->bomb->reset = false;
	     return;
	 }

	 virtual void refresh()
	 {
	     this->bomb->position(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2.0 - 6,this->sprite.getPosition().y);
	     this->bomb->reset = true;
	     return;
	 }

	 virtual void fire1()
	 {
	  return;
	 }

	 virtual void fire2()
	 {
	  return;
	 }

	 virtual void fire3()
	 {
	  return;
	 }

	virtual ~Bosses()
	{
		if(this->bomb != NULL)
		{
			delete this->bomb;
			this->bomb = NULL;
		}
	}
};

class Invaders: public Bosses
{
 public:
	virtual void fun1() override
	{
		std::cout << "Invaders" << std::endl;
		return;
	}
};

class Alpha: public Invaders
{
 public:
	Alpha(std::string png_path = "img/alpha.png",float speed = 0.20,bool alive = true)
	{
		this->name = "Alpha";
		this->texture.loadFromFile(png_path);
		this->sprite.setTexture(texture);
		this->speed = speed;
		this->og_x = 300;
		this->og_y = 10;
		this->sprite.setPosition(og_x,og_y);
		this->sprite.setScale(0.5,0.5);
		this->curr_x = this->og_x;
		this->curr_y = this->og_y;
		this->boss_health = 2;
		this->alive = alive;
		this->bomb = new Bomb("img/bomb.png",this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2.0 - 6,this->sprite.getPosition().y);
	    this->bomb->speed = 0.4;
	    this->points = 10;
	}

	virtual void fun1() override
	{
		std::cout << "Alpha" << std::endl;
		return;
	}

	virtual ~Alpha()
	{
		if(this->bomb != NULL)
		{
			delete this->bomb;
			this->bomb = NULL;
		}
	}
};

class Beta: public Invaders
{
 public:
	Beta(std::string png_path = "img/beta.png",float speed = 0.25,bool alive = true)
	{
		this->name = "Beta";
		this->texture.loadFromFile(png_path);
		this->sprite.setTexture(texture);
		this->speed = speed;
		this->og_x = 300;
		this->og_y = 10;
		this->sprite.setPosition(og_x,og_y);
		this->sprite.setScale(0.5,0.5);
		this->curr_x = this->og_x;
		this->curr_y = this->og_y;
		this->boss_health = 3;
		this->alive = alive;
		this->bomb = new Bomb("img/bomb.png",this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2.0 - 6,this->sprite.getPosition().y);
	    this->bomb->speed = 0.50;
	    this->points = 20;
	}

	virtual void fun1() override
	{
		std::cout << "Beta" << std::endl;
		return;
	}

	virtual ~Beta()
	{
		if(this->bomb != NULL)
		{
			delete this->bomb;
			this->bomb = NULL;
		}
	}
};

class Gamma: public Invaders
{
 public:
	Gamma(std::string png_path = "img/gamma.png",float speed = 0.30,bool alive = true)
	{
		this->name = "Gamma";
		this->texture.loadFromFile(png_path);
		this->sprite.setTexture(texture);
		this->speed = speed;
		this->og_x = 300;
		this->og_y = 10;
		this->sprite.setPosition(og_x,og_y);
		this->sprite.setScale(0.5,0.5);
		this->curr_x = this->og_x;
		this->curr_y = this->og_y;
		this->boss_health = 4;
		this->alive = alive;
		this->bomb = new Bomb("img/bomb.png",this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2.0 - 6,this->sprite.getPosition().y);
	    this->bomb->speed = 0.65;
	    this->points = 30;
	}

	virtual void fun1() override
	{
		std::cout << "Gamma" << std::endl;
		return;
	}


	virtual ~Gamma()
	{
		if(this->bomb != NULL)
		{
			delete this->bomb;
			this->bomb = NULL;
		}
	}
};

class Dragon: public Bosses
{
 public:
	std::string s1 = "a";
	Bomb*f1 = new Bomb("img/fire_ball1.png",40,20);
	Bomb*f2 = new Bomb("img/fire_ball2.png",40,20);
	Bomb*f3 = new Bomb("img/fire_ball3.png",40,20);
	Dragon(std::string png_path = "img/dragon.png",float speed = 0.7,bool alive = true)
	{
		this->name = "Dragon";
		this->texture.loadFromFile(png_path);
		this->sprite.setTexture(texture);
		this->speed = speed;
		this->og_x = 300;
		this->og_y = 10;
		this->sprite.setPosition(og_x,og_y);
		this->sprite.setScale(1,1);
		this->curr_x = this->og_x;
		this->curr_y = this->og_y;
		this->boss_health = 15;
		this->alive = alive;
		this->f1->sprite.scale(0.13,0.3);
		this->f2->sprite.scale(0.26,0.5);
		this->f3->sprite.scale(0.26,0.5);
		this->bomb = f1;
        this->points = 100;
	}

	virtual void fun1() override
	{
		std::cout << "Dragon" << std::endl;
		return;
	}

	virtual void refresh()
	{
	    this->bomb->position(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2.0 - 20,this->sprite.getPosition().y + 155);
	    return;
	}

	virtual void fire1() override
	{
     this->bomb = f1;
	 this->bomb->position(355,340);
	 return;
	}

	virtual void fire2() override
	{
	 this->bomb = f2;
	 this->bomb->position(140,300);
	 return;
	}

	virtual void fire3() override
	{
	 this->bomb = f3;
	 this->bomb->position(390,280);
	 return;
	}

	virtual ~Dragon()
	{
		if(this->f1 != NULL)
		{
			delete this->f1;
			this->f1 = NULL;
		}
		if(this->f2 != NULL)
		{
			delete this->f2;
			this->f2 = NULL;
		}
		if(this->f3 != NULL)
		{
			delete this->f3;
			this->f3 = NULL;
		}
	}
};

class Monster: public Bosses
{
 public:
	bool greater_780;
	Monster(std::string png_path = "img/monster.png",float speed = 0.7,bool alive = true)
	{
		this->name = "Monster";
		this->texture.loadFromFile(png_path);
		this->sprite.setTexture(texture);
		this->speed = speed;
		this->og_x = 300;
		this->og_y = 10;
		this->sprite.setPosition(og_x,og_y);
		this->sprite.setScale(0.5,0.5);
		this->curr_x = this->og_x;
		this->curr_y = this->og_y;
		this->boss_health = 15;
		this->alive = alive;
		this->bomb = new Bomb("img/lightning_bolt.png",this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2.0 - 6,this->sprite.getPosition().y);
		this->bomb->sprite.scale(0.7,1.95);
		this->greater_780 = false;
		this->points = 100;
	}

	virtual void fun1() override
	{
		std::cout << "Monster" << std::endl;
		return;
	}

	virtual void move()
	{
		  float delta_x = 1;
		  if (this->sprite.getPosition().x + this->sprite.getGlobalBounds().width > 780)
		  this->greater_780 = true;
		  if (this->sprite.getPosition().x < 0)
		  this->greater_780 = false;
		  if (this->greater_780 == true)
		  delta_x = -delta_x * this->speed;
		  else if (this->greater_780 == false)
		  delta_x = +delta_x * this->speed;
		  this->sprite.move(delta_x,0);
		  return;
		return;
	}


	 virtual void refresh()
	 {
	     this->bomb->position(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2.0 - 110,this->sprite.getPosition().y + 85);
	     return;
	 }

	 virtual ~Monster()
	 {
	  if(this->bomb != NULL)
	  {
	   delete this->bomb;
	   this->bomb = NULL;
	  }
	 }
};






#endif
