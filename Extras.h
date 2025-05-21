#include<SFML/Graphics.hpp>
#include<iostream>
#include<cstring>
#include<cstdlib>
#ifndef EXTRAS_H_
#define EXTRAS_H_
using namespace sf;



class Extras
{
public:
	Texture texture;
	Sprite sprite;
	float speed;
	int og_x;
	int og_y;
	float curr_x;
	float curr_y;
	bool reset;

	virtual void fun1() = 0;

	virtual void position()
	{
		this->sprite.setPosition(-380,((rand() % 520) + 30));
		return;
	}

	virtual void move()
	{
	  float delta_x=0;
	  delta_x = delta_x + 1.0;
	  delta_x = delta_x * this->speed;
	  sprite.move(delta_x,0);
	  return;
	 }

	 virtual bool anaomally()
	 {
	  this->curr_x = sprite.getPosition().x;
	  bool checker = false;
	  if ( curr_x + this->sprite.getGlobalBounds().width > 780)
	  {
	   checker = true;
	  }
	  return checker;
	 }

	 virtual ~Extras(){}
};

class UFO: public Extras
{
public:
	UFO(std::string png_path = "img/UFO.png",float x = 0,float y = -40)
	{
	 this->texture.loadFromFile(png_path);
	 this->sprite.setTexture(texture);
	 this->speed = 0.55;
	 this->og_x = x;
	 this->og_y = y;
	 this->sprite.setPosition(((rand() % 750) + 5),og_y);
	 this->sprite.setScale(0.6,0.6);
	 this->curr_x = 0.0;
	 this->curr_y = 0.0;
	 this->reset = true;
	}

	virtual void fun1() override
	{
		std::cout << "Lives" << std::endl;
		return;
	}
	virtual ~UFO(){}
};

class Asteroid: public Extras
{
public:
	Asteroid(std::string png_path = "img/Asteroid.png",float x = 0,float y = -40)
	{
	 this->texture.loadFromFile(png_path);
	 this->sprite.setTexture(texture);
	 this->speed = 0.55;
	 this->og_x = x;
	 this->og_y = y;
	 this->sprite.setPosition(((rand() % 750) + 5),og_y);
	 this->sprite.setScale(0.6,0.6);
	 this->curr_x = 0.0;
	 this->curr_y = 0.0;
	 this->reset = true;
	}

	virtual void fun1() override
	{
		std::cout << "Danger" << std::endl;
		return;
	}
	virtual ~Asteroid(){}
};

#endif
