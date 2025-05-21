#include<SFML/Graphics.hpp>
#include<iostream>
#include<cstring>
#include "Cartridge.h"
#ifndef PLAYER_H_
#define PLAYER_H_
using namespace sf;


class A
{
protected:
	int x;
	int y;
public:
	virtual void fun() = 0;
	virtual ~A()
	{

	}
};

class B: public A
{
public:
	void fun() override
	{
		this->x = 8;
		std::cout << x << std::endl;
	}
};

class Player
{

 public:
 Texture texture;
 Sprite sprite;
 float speed = 0.7;
 float og_x;
 float og_y;
 float curr_x;
 float curr_y;
 Cartridge* C;

Player(std::string png_path = "img/player_ship.png")
{
 this->texture.loadFromFile(png_path);
 this->sprite.setTexture(texture);
 this->og_x = 340;
 this->og_y = 620;
 this->sprite.setPosition(og_x,og_y);
 this->sprite.setScale(0.75,0.75);
 this->curr_x = 0.0;
 this->curr_y = 0.0;
 C = new Cartridge("img/cartridge.png",this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2.0 - 6 ,this->sprite.getPosition().y - 26);
}

 void shooting()
 {
	 if (this->C->anaomally() == false)
	 this->C->move();
	 else
	 this->C->position(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2.0 - 6,this->sprite.getPosition().y);
     this->C->reset = false;
     return;
 }

 void refresh()
 {
     this->C->position(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width/2.0 - 6,this->sprite.getPosition().y);
     this->C->reset = true;
     return;
 }

 void move(std::string s)
{

 float delta_x=0;
 float delta_y=0;


 if(s=="l")
	 delta_x = -1;
 else if(s=="r")
	 delta_x = +1;

 if(s=="u")
	 delta_y = -1;
 else if(s=="d")
	 delta_y = +1;

 delta_x*=speed;
 delta_y*=speed;

 if (anaomally(delta_x,delta_y) == false)
 sprite.move(delta_x, delta_y);

 return;
 }

 bool anaomally(float& delta_x,float& delta_y)
 {
	  this->curr_x = sprite.getPosition().x;
	  this->curr_y = sprite.getPosition().y;
	  bool checker = false;
	  if (curr_x + delta_x < 0.2)
	  {
	 	 sprite.setPosition(780 - sprite.getGlobalBounds().width,curr_y);
	 	 checker = true;
	  }

	  else if ( curr_x + this->sprite.getGlobalBounds().width + delta_x > 780)
	  {
	 	 sprite.setPosition(0,curr_y);
	 	 checker = true;
	  }

	  if (curr_y + delta_y < 0.2)
	  {
	  	sprite.setPosition(curr_x,720-this->sprite.getGlobalBounds().height);
	  	checker = true;
	  }

	  else if ( curr_y + delta_y + this->sprite.getGlobalBounds().height> 720)
	  {
	  	sprite.setPosition(curr_x,0.2);
	  	checker = true;
	  }
	  return checker;
 }

 ~Player()
 {
	 if (this->C != NULL)
	 {
		 delete C;
		 C = NULL;
	 }
 }
};
#endif





