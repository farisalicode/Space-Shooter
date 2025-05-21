#include<SFML/Graphics.hpp>
#include<iostream>
#include<cstring>
#ifndef BOMB_H_
#define BOMB_H_
using namespace sf;



class Bomb
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

	Bomb(std::string png_path = "img/bomb.png",float x = 0,float y = 0)
	{
	 this->texture.loadFromFile(png_path);
	 this->sprite.setTexture(texture);
	 this->speed = 0.25;
	 this->og_x = x;
	 this->og_y = y;
	 this->sprite.setPosition(og_x,og_y);
	 this->sprite.setScale(1,1);
	 this->curr_x = 0.0;
	 this->curr_y = 0.0;
	 this->reset = true;
	}

	void position(float x_cor,float y_cor)
	{
		this->sprite.setPosition(x_cor, y_cor);
		return;
	}

	void move()
	{
	  float delta_y=0;
	  delta_y = delta_y + 1.0;
	  delta_y=delta_y * this->speed;
	  sprite.move(0, delta_y);
	  return;
	 }

	 bool anaomally()
	 {
	  this->curr_x = sprite.getPosition().x;
	  this->curr_y = sprite.getPosition().y;
	  bool checker = false;
	  if ( curr_y + this->sprite.getGlobalBounds().height> 740)
	  {
	   checker = true;
	  }
	  return checker;
	 }


};
#endif
