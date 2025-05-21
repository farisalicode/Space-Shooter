#include<SFML/Graphics.hpp>
#include<iostream>
#include<cstring>
#include<cstdlib>
#ifndef ADD_ON_H_
#define ADD_ON_H_
using namespace sf;


class Add_On
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
		this->sprite.setPosition(((rand() % 750) + 5), -200);
		return;
	}

	virtual void move()
	{
	  float delta_y=0;
	  delta_y = delta_y + 1.0;
	  delta_y=delta_y * this->speed;
	  sprite.move(0, delta_y);
	  return;
	 }

	 virtual bool anaomally()
	 {
	  this->curr_y = sprite.getPosition().y;
	  bool checker = false;
	  if ( curr_y + this->sprite.getGlobalBounds().height > 740)
	  {
	   checker = true;
	  }
	  return checker;
	 }

	 virtual ~Add_On(){}
};

class Lives: public Add_On
{
public:
	Lives(std::string png_path = "img/Lives.png",float x = 0,float y = -120)
	{
	 this->texture.loadFromFile(png_path);
	 this->sprite.setTexture(texture);
	 this->speed = 0.55;
	 this->og_x = x;
	 this->og_y = y;
	 this->sprite.setPosition(((rand() % 750) + 5),og_y);
	 this->sprite.setScale(1.3,1.3);
	 this->curr_x = 0.0;
	 this->curr_y = 0.0;
	 this->reset = true;
	}

	virtual void fun1() override
	{
		std::cout << "Lives" << std::endl;
		return;
	}

	virtual ~Lives(){}
};

class Danger: public Add_On
{
public:
	Danger(std::string png_path = "img/Danger.png",float x = 0,float y = -120)
	{
	 this->texture.loadFromFile(png_path);
	 this->sprite.setTexture(texture);
	 this->speed = 0.55;
	 this->og_x = x;
	 this->og_y = y;
	 this->sprite.setPosition(((rand() % 750) + 5),og_y);
	 this->sprite.setScale(1.3,1.3);
	 this->curr_x = 0.0;
	 this->curr_y = 0.0;
	 this->reset = true;
	}

	virtual void fun1() override
	{
		std::cout << "Danger" << std::endl;
		return;
	}
	virtual ~Danger(){}
};
#endif
