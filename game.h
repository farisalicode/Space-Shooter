#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include "player.h"
#include "Bosses.h"
#include "Bomb.h"
#include "Add_On.h"
#include "Extras.h"
#ifndef GAME_H_
#define GAME_H_
using namespace sf;
using namespace std;




class Game
{
public:
bool pause;
float level;
bool game_over;
Sprite background;
Texture bg_texture;
Sprite side_bar;
Texture sb_texture;
int num_inv;
Player* p;
Bosses* b1;
bool is_shooting;
bool is_bombing;
int invader_control;
float enemy_speed;
int player_health;
int player_score;
int types_counter;
float dragon_time;
float monster_time;
Clock dragon_clock;
Clock monster_clock;
float lives_time;
float danger_time;
Clock lives_clock;
Clock danger_clock;
bool is_firing;
bool is_lightning;
Add_On* ao1 = new Lives;
Add_On* ao2 = new Danger;
float fire_time;
float lightning_time;
Clock fire_clock;
Clock lightning_clock;
int bonus_marks;
string player_name;
Music music;
Font font;
SoundBuffer sound_buffer1;
SoundBuffer sound_buffer2;
SoundBuffer sound_buffer3;
SoundBuffer sound_buffer4;
SoundBuffer sound_buffer5;
Sound laser;
Sound roar;
Sound thunder;
Sound win;
Sound lose;
Asteroid asteroids[3];
UFO ufo[3];
int fire_cycle;
bool you_won;


Game()
{
 this->lightning_time = 0.0;
 this->fire_time = 0.0;
 this->danger_time = 0.0;
 this->lives_time = 0.0;
 this->bonus_marks = 0;
 this->pause = false;
 this->level = 1;
 this->game_over = false;
 this->p=new Player("img/player_ship.png");
 this->bg_texture.loadFromFile("img/background_1.jpg");
 this->background.setTexture(this->bg_texture);
 this->background.setScale(2.25, 1.35);
 this->sb_texture.loadFromFile("img/side_bar.png");
 this->side_bar.setTexture(this->sb_texture);
 this->side_bar.setScale(1.2,1.2);
 this->side_bar.setPosition(784,0);
 this->is_shooting = false;
 this->is_bombing = false;
 this->invader_control = 0;
 this->enemy_speed = 0.15;
 this->player_health = 15;
 this->num_inv = 4;
 this->b1 = new Alpha[num_inv];
 for (int i = 0;i < this->num_inv;i++)
 {
  this->b1[i].sprite.setPosition((180 * i + 40),10);
  this->b1[i].speed = 0.2 * level;
 }
 this->player_score = 0;
 this->types_counter = 0;
 this->dragon_time = 0;
 this->monster_time = 0;
 this->is_firing = true;
 this->is_lightning = true;
 this->lightning_time = 0.0;
 this->fire_time = 0.0;
 this->danger_time = 0.0;
 this->lives_time = 0.0;
 this->bonus_marks = 0;
 this->music.openFromFile("music.ogg");
 this->font.loadFromFile("TNR.ttf");
 this->sound_buffer1.loadFromFile("laser.ogg");
 this->sound_buffer2.loadFromFile("roar.ogg");
 this->sound_buffer3.loadFromFile("thunder.ogg");
 this->sound_buffer4.loadFromFile("win.ogg");
 this->sound_buffer5.loadFromFile("lose.ogg");
 this->laser.setBuffer(sound_buffer1);
 this->roar.setBuffer(sound_buffer2);
 this->thunder.setBuffer(sound_buffer3);
 this->win.setBuffer(sound_buffer4);
 this->lose.setBuffer(sound_buffer5);
 for(int i = 0;i < 3;i++)
 {
  this->asteroids[i].position();
  this->ufo[i].position();
 }
 this->fire_cycle = 0;
 this->you_won = false;
}

void danger_coming(bool& danger_spawned)
{
	if (this->danger_time > 10)
	{
	 danger_spawned = true;
	 this->danger_time = 0.0;
	}
	if (danger_spawned == true)
	{
     this->ao2->move();
     if (this->ao2->anaomally() == true)
	 {
      this->player_score += 30;
	  this->ao2->position();
	  danger_spawned = false;
	 }
     if (this->collision_detector(this->p->sprite,this->ao2->sprite) == true)
     {
      this->player_health -= 1;
      this->ao2->position();
      danger_spawned = false;
     }
	}
	return;
}

void lives_coming(bool& lives_spawned)
{
	if (this->lives_time > 15)
	{
	 lives_spawned = true;
	 this->lives_time = 0.0;
	}
	if (lives_spawned == true)
	{
     this->ao1->move();
     if (this->ao1->anaomally() == true)
	 {
	  this->ao1->position();
	  lives_spawned = false;
	 }
     if (this->collision_detector(this->p->sprite,this->ao1->sprite) == true)
     {
      this->player_health += 1;
      this->ao1->position();
      lives_spawned = false;
     }
	}
	return;
}

void firing_system()
{
	for (int i = 0;i < this->num_inv;i++)
	{
	 if (this->is_firing == false)
	 this->b1[i].bomb->sprite.setPosition(-20000,-20000);
	 else if (this->is_firing == true)
	 {
	  if(this->fire_cycle == 1)
	  this->b1[i].fire1();
	  if(this->fire_cycle == 2)
	  this->b1[i].fire2();
	  if(this->fire_cycle == 3)
	  this->b1[i].fire3();
	 }
	}
	return;
	/*float old_x= this->b1[i].sprite.getPosition().x;
		  this->b1[i].sprite.setPosition(this->p->sprite.getPosition().x - 40,10);
		  if(this->b1[i].sprite.getPosition().x + this->b1[i].sprite.getGlobalBounds().width > 780 || this->b1[i].sprite.getPosition().x < 0)
		  {
		   this->b1[i].sprite.setPosition(old_x,10);
		  }
		  this->b1[i].refresh();*/
}

void lightning_system()
{
	for (int i = 0;i < this->num_inv;i++)
	{
	 if (this->is_lightning == false)
	 this->b1[i].bomb->sprite.setPosition(-20000,-20000);
	 else if (this->is_lightning == true)
	 this->b1[i].refresh();
	}
	return;
}

void monster_system()
{
	for(int i = 0;i < this->num_inv;i++)
	{
	 this->b1[i].move();
	}
    float t = this->monster_clock.getElapsedTime().asSeconds();
    this->monster_clock.restart();
    this->monster_time += t;
    if (this->monster_time >= 2)
    {
     this->monster_time = 0.0;
    }
    if (this->monster_time < 1)
    {
     this->is_lightning = true;
    }
    else if(this->monster_time >= 1)
    {
     this->is_lightning = false;
     this->music.pause();
     this->thunder.setVolume(100);
     this->thunder.play();
     this->music.play();
    }
    this->lightning_system();
    return;
}

void dragon_system()
{
    float t = this->dragon_clock.getElapsedTime().asSeconds();
    this->dragon_clock.restart();
    this->dragon_time += t;
    if (this->dragon_time >= 2)
    {
     this->dragon_time = 0.0;
     this->fire_cycle++;
    }
    if (this->dragon_time < 1)
    {
     this->is_firing = true;
    }
    else if(this->dragon_time >= 1)
    {
     this->is_firing = false;
     this->music.pause();
     this->roar.setVolume(100);
     this->roar.play();
     this->music.play();
    }
    if(this->fire_cycle > 3)
    this->fire_cycle = 1;
    this->firing_system();
    return;
}

void drawing_monster(RenderWindow& window)
{
	if (this->b1 != NULL)
	{
     for (int i = 0;i < this->num_inv;i++)
	 {
	  if (this->b1[i].alive == true)
	  window.draw(this->b1[i].sprite);
	 }
	}
	if (this->b1 != NULL && this->b1[0].bomb != NULL)
	{
	 for (int i = 0;i < this->num_inv;i++)
	 {
	  if (this->b1[i].alive == true)
	  window.draw(this->b1[i].bomb->sprite);
	 }
	}
	return;
}

void drawing_dragon(RenderWindow& window)
{
	if (this->b1 != NULL)
	{
     for (int i = 0;i < this->num_inv;i++)
	 {
	  if (this->b1[i].alive == true)
	  window.draw(this->b1[i].sprite);
	 }
	}
	if (this->b1 != NULL && this->b1[0].bomb != NULL)
	{
	 for (int i = 0;i < this->num_inv;i++)
	 {
	  if (this->b1[i].alive == true)
	  window.draw(this->b1[i].bomb->sprite);
	 }
	}
	return;
}

void write_to_file()
{
    int counter = 0;
    int oldscore0;
    int oldscore1;
    int oldscore2;
    string olddata0;
    string olddata1;
    string olddata2;
    int newscore;
    string newdata;
    string text;
    string score1 = to_string(this->player_score);
    newdata = newdata + this->player_name + ": ";
    newdata = newdata + to_string(this->player_score);
    newdata = newdata + '\n';
    ofstream Thefile;
    Thefile.open("scores.txt",ios::app);
    Thefile << newdata;
    Thefile.close();
    ifstream Afile("highscores.txt");
    while (getline(Afile, text))
    {
     text = text + '\n';
     if (counter == 0)
     olddata0 = text;
     if (counter == 1)
     olddata1 = text;
     if (counter == 2)
     olddata2 = text;
     signed int size = text.length();
     int marker = 0;

     for(signed int i = 0;i < size;i++)
     {
      if(text[i] == ':')
      {
       marker = i + 2;
      }
     }
     string score2;
     for(signed int i = marker;i < size;i++)
     {
      score2 = score2 + text[i];
     }
     if (counter == 0)
     oldscore0 = stoi(score2);
     if (counter == 1)
     oldscore1 = stoi(score2);
     if (counter == 2)
     oldscore2 = stoi(score2);
     newscore = stoi(score1);
     ++counter;
    }
    ofstream temp("temp.txt",ios::out);
    if (newscore > oldscore0)
    {
     temp << newdata;
     temp << olddata0;
     temp << olddata1;
    }
    else if (newscore > oldscore1)
    {
     temp << olddata0;
     temp << newdata;
     temp << olddata1;
    }
    else if (newscore > oldscore2)
    {
     temp << olddata0;
     temp << olddata1;
     temp << newdata;
    }
    else
    {
     temp << olddata0;
     temp << olddata1;
     temp << olddata2;
    }

    temp.close();
	Afile.close();
	remove("highscores.txt");
	rename("temp.txt","highscores.txt");
	return;
}

bool invaders_still_there()
{
	bool flag = true;
	for (int i = 0;i < this->num_inv;i++)
	{
	 if (this->b1[i].alive == false)
	 {
	  flag = false;
	 }
	 else if (this->b1[i].alive == true)
	 {
	  flag = true;
	  break;
	 }
	}
	return flag;
}

void shooting_mechanism()
{
	if (this->is_shooting == true)
	{
		this->p->shooting();
	}
	else if (this->is_shooting == false && this->p->C->anaomally() == false && this->p->C->reset == false)
	{
		this->p->C->move();
		if(this->p->C->anaomally() == true)
		{
			this->p->refresh();
		}
	}
	else
	{
		this->p->refresh();
	}
	return;
}

void bombing_mechanism()
{
   for(int i = 0;i < this->num_inv;i++)
   {
	if (this->b1[i].alive == true)
	{
	 if (this->is_bombing == true)
	 {
	  this->b1[i].shooting();
	 }
	 else if (this->is_bombing == false && this->b1[i].bomb->anaomally() == false && this->b1[i].bomb->reset == false)
	 {
	  this->b1[i].bomb->move();
	  if(this->b1[i].bomb->anaomally() == true)
	  {
	   this->b1[i].refresh();
	  }
	 }
	 else
	 {
	  this->b1[i].refresh();
	 }
	}
   }
	return;
}

void invaders_system()
{
	int n = (rand()%4);
	if (n == 2)
	{
		this->is_bombing = true;
	}
	else
	{
		this->is_bombing = false;
	}
	for(int i = 0;i < this->num_inv;i++)
	{
	 if (this->b1[i].alive == true)
	 {
	  this->b1[i].move();
	 }
	}
	this->bombing_mechanism();
	return;
}

bool collision_detector(const Sprite& obj1,const Sprite& obj2)
{
	bool flag1 = false;
	bool flag2 = false;
	if (obj1.getPosition().x + obj1.getGlobalBounds().width >= obj2.getPosition().x && obj2.getPosition().x + obj2.getGlobalBounds().width >= obj1.getPosition().x)
	{
	 flag1 = true;
	}
	if (obj1.getPosition().y + obj1.getGlobalBounds().height >= obj2.getPosition().y && obj2.getPosition().y + obj2.getGlobalBounds().height >= obj1.getPosition().y)
	{
	 flag2 = true;
	}
	return (flag1 && flag2);
}

void drawing_invaders(RenderWindow& window)
{
	if (this->b1 != NULL && this->b1[0].bomb != NULL)
	{
	 for (int i = 0;i < this->num_inv;i++)
	 {
	  if (this->b1[i].alive == true)
	  window.draw(this->b1[i].bomb->sprite);
	 }
	}
	if (this->b1 != NULL)
	{
	 for (int i = 0;i < this->num_inv;i++)
	 {
	  if (this->b1[i].alive == true)
	  window.draw(this->b1[i].sprite);
	 }
	}
	return;
}

void drawing_player(RenderWindow& window)
{
	if (this->p != NULL && this->p->C != NULL)
	{
	 window.draw(this->p->C->sprite);
	}
	if (this->p != NULL)
	{
	 window.draw(p->sprite);
	}
	return;
}

void drawing_game_on(RenderWindow& window,Font& font,float& timer)
{
	 window.draw(background);
	 window.draw(this->side_bar);

	 Text text;
	 text.setFont(this->font);
	 string words;
	 words = "Timer: ";
	 words = words + std::to_string(timer);
	 words = words + '\n';
	 text.setString(words);
	 text.setCharacterSize(20);
	 text.setFillColor(sf::Color::White);
	 text.setStyle(sf::Text::Bold);
	 text.setPosition(800,10);
	 window.draw(text);

	 words = "Levels: ";
	 words = words + std::to_string(this->level);
	 words = words + '\n';
	 text.setString(words);
	 text.setCharacterSize(20);
	 text.setFillColor(sf::Color::White);
	 text.setStyle(sf::Text::Bold);
	 text.setPosition(800,50);
	 window.draw(text);

	 words = "Player Lives: ";
	 words = words + std::to_string(this->player_health);
	 words = words + '\n';
	 text.setString(words);
	 text.setCharacterSize(20);
	 text.setFillColor(sf::Color::White);
	 text.setStyle(sf::Text::Bold);
	 text.setPosition(800,90);
	 window.draw(text);

	 words = "Player Score: ";
	 words = words + std::to_string(this->player_score);
	 words = words + '\n';
	 text.setString(words);
	 text.setCharacterSize(20);
	 text.setFillColor(sf::Color::White);
	 text.setStyle(sf::Text::Bold);
	 text.setPosition(800,130);
	 window.draw(text);


	 for (int i = 0;i < this->num_inv;i++)
	 {
	  if (this->player_health >= 0)
	  {
	   sf::Text text;
	   text.setFont(font);
	   std::string words;
	   words = this->b1[i].name;
	   if (this->num_inv > 1)
	   {
	    words = words + ' ';
	    words = words + std::to_string(i + 1);
	   }
	   words = words + " Lives: ";
	   words = words + std::to_string(this->b1[i].boss_health);
	   words = words + '\n';
	   text.setString(words);
	   text.setCharacterSize(20);
	   text.setFillColor(sf::Color::White);
	   text.setStyle(sf::Text::Bold);
	   text.setPosition(800,40 * i + 170);
	   window.draw(text);
	  }
	 }
	 return;
}

void drawing_game_off(RenderWindow& window)
{
	window.draw(background);
	return;
}

void player_collisions1()
{
	for (int i = 0;i < this->num_inv;i++)
	{
	 if (this->b1[i].alive == true)
	  {
	   if (this->collision_detector(this->p->sprite,this->b1[i].sprite) == true)
	   {
		this->player_health -= 1;
	    this->b1[i].boss_health = 0;
	   }
	  }
	 }

	for (int i = 0;i < this->num_inv;i++)
	{
	 if (this->b1[i].alive == true)
	 {
	  if (this->collision_detector(this->p->sprite,this->b1[i].bomb->sprite) == true)
	  {
	   --this->player_health;
	   this->b1[i].bomb->sprite.setPosition(20,2270);
	  }
	 }
	}
	return;
}

void player_collisions2()
{
	for (int i = 0;i < this->num_inv;i++)
	{
	 if (this->b1[i].alive == true)
	  {
	   if (this->collision_detector(this->p->sprite,this->b1[i].sprite) == true)
	   {
	    this->game_over = true;
	   }
	  }
	 }

	for (int i = 0;i < this->num_inv;i++)
	{
	 if (this->b1[i].alive == true)
	 {
	  if (this->collision_detector(this->p->sprite,this->b1[i].bomb->sprite) == false && this->is_firing == true && this->bonus_marks == 0)
	  {
	   this->player_score += 50;
	   this->bonus_marks++;
	  }
	  if (this->is_firing == false)
	  {
	   this->bonus_marks = 0;
	  }
	  if (this->collision_detector(this->p->sprite,this->b1[i].bomb->sprite) == true)
	  {
	   this->fire_time += 1;
	  }
	  else
	  {
	   this->fire_time = 0;
	  }
	  if(this->fire_time == 1)
	  {
	   this->player_health -= 1;
	  }
	 }
	}
	return;
}

void player_collisions3()
{
	for (int i = 0;i < this->num_inv;i++)
	{
	 if (this->b1[i].alive == true)
	  {
	   if (this->collision_detector(this->p->sprite,this->b1[i].sprite) == true)
	   {
	    this->game_over = true;
	   }
	  }
	 }

	for (int i = 0;i < this->num_inv;i++)
	{
	 if (this->b1[i].alive == true)
	 {
	  if (this->collision_detector(this->p->sprite,this->b1[i].bomb->sprite) == false && this->is_lightning == true && this->bonus_marks == 0)
	  {
	   this->player_score += 40;
	   this->bonus_marks++;
	  }
	  if (this->is_lightning == false)
	  {
	   this->bonus_marks = 0;
	  }
	  if (this->collision_detector(this->p->sprite,this->b1[i].bomb->sprite) == true)
	  {
	   this->lightning_time += 1;
	  }
	  else
	  {
	   this->lightning_time = 0;
	  }
	  if(this->lightning_time == 1)
	  {
	   this->player_health -= 1;
	  }
	 }
	}
	return;
}

void invader_collisions()
{
	for (int i = 0;i < this->num_inv;i++)
	{
	 if(this->b1[i].alive == true)
	  if (this->collision_detector(this->p->C->sprite,this->b1[i].sprite) == true)
	  {
	   --this->b1[i].boss_health;
	   this->p->C->sprite.setPosition(20,-2270);
	  }
	}

	for (int i = 0;i < this->num_inv;i++)
	{
	 if (this->b1[i].alive == true)
	 {
	  if (this->b1[i].boss_health <= 0)
	  {
	   this->b1[i].alive = false;
	   this->player_score += this->b1[i].points * level;
	  }
	 }
	}
	return;
}

void dragon_collisions()
{
	for (int i = 0;i < this->num_inv;i++)
	{
	 if(this->b1[i].alive == true)
	  if (this->collision_detector(this->p->C->sprite,this->b1[i].sprite) == true)
	  {
	   --this->b1[i].boss_health;
	   this->player_score = this->player_score + 1;
	   this->p->C->sprite.setPosition(20,-2270);
	  }
	}

	for (int i = 0;i < this->num_inv;i++)
	{
	 if (this->b1[i].alive == true)
	 {
	  if (this->b1[i].boss_health <= 0)
	  {
	   this->b1[i].alive = false;
	   this->player_score += this->b1[i].points * level;
	  }
	 }
	}
	return;
}

void monster_collisions()
{
	for (int i = 0;i < this->num_inv;i++)
	{
	 if(this->b1[i].alive == true)
	  if (this->collision_detector(this->p->C->sprite,this->b1[i].sprite) == true)
	  {
	   --this->b1[i].boss_health;
	   this->player_score = this->player_score + 1;
	   this->p->C->sprite.setPosition(20,-2270);
	  }
	}

	for (int i = 0;i < this->num_inv;i++)
	{
	 if (this->b1[i].alive == true)
	 {
	  if (this->b1[i].boss_health <= 0)
	  {
	   this->b1[i].alive = false;
	   this->player_score += this->b1[i].points * this->level;
	   this->you_won = true;
	  }
	 }
	}
	return;
}

void start_game()
{
    srand(time(0));
    cout << "Please enter your good name." << endl;
    getline(cin,this->player_name);
    string title = "Faris Ali, 22I-0804, Section C";
    RenderWindow window(VideoMode(1040,780), title);

    int bipo = 0;
    this->music.setVolume(100);
    this->music.setLoop(true);
    this->music.play();

    Clock clock;
    float timer=0;
    int clamp = 1;
    bool alpha_spawned = true;
    bool beta_spawned = false;
    bool gamma_spawned = false;
    bool dragon_spawned = false;
    bool monster_spawned = false;
    bool lives_spawned = false;
    bool danger_spawned = false;


    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();

        if (this->pause == false && this->game_over == false && this->you_won == false)
        {
         timer += time;
         this->danger_time += time;
         this->lives_time += time;
        }

        if (timer < 10)
        {
         this->level = 1;
        }
        else if (timer >= 10 && timer < 20)
		{
         this->level = 2;
		}
        else if (timer >= 20)
		{
         this->level = 3;
		}

        if(this->invaders_still_there() == false)
        {
         this->types_counter = this->types_counter + 1;
        }

        for (int i = 0;i < this->num_inv;i++)
        {
         if(this->b1[i].alive == true)
         {
          if (this->types_counter == 0)
          this->b1[i].speed = 0.20 * level;
          if (this->types_counter == 1)
          this->b1[i].speed = 0.25 * level;
          if (this->types_counter == 2)
          this->b1[i].speed = 0.30 * level;
          if (this->types_counter == 4)
          this->b1[i].speed = 0.40 * level;
         }
        }

        if (this->types_counter == 3 && clamp <= 2)
        {
         this->types_counter = 0;
         alpha_spawned = false;
         beta_spawned = false;
         gamma_spawned = false;
         clamp = clamp  + 1;
        }

        if((this->types_counter == 0) && alpha_spawned == false)
        {
         alpha_spawned = true;
         delete[] this->b1;
         this->b1 = NULL;
         this->b1 = new Alpha[this->num_inv];
         for (int i = 0;i < this->num_inv;i++)
         {
          this->b1[i].alive = true;
          this->b1[i].sprite.setPosition((180 * i + 40),10);
          this->b1[i].speed = 0.20 * level;
         }
        }

        if((this->types_counter == 1) && beta_spawned == false)
        {
         beta_spawned = true;
         delete[] this->b1;
         this->b1 = NULL;
         this->b1 = new Beta[this->num_inv];
         for (int i = 0;i < this->num_inv;i++)
         {
          this->b1[i].alive = true;
          this->b1[i].sprite.setPosition((180 * i + 40),10);
          this->b1[i].speed = 0.25 * level;
         }
        }

        if((this->types_counter == 2) && gamma_spawned == false)
        {
         gamma_spawned = true;
         delete[] this->b1;
         this->b1 = NULL;
         this->b1 = new Gamma[this->num_inv];
         for (int i = 0;i < this->num_inv;i++)
         {
          this->b1[i].alive = true;
          this->b1[i].sprite.setPosition((180 * i + 40),10);
          this->b1[i].speed = 0.30 * level;
         }
        }

        if(this->types_counter == 3 && dragon_spawned == false)
        {
         this->num_inv = 1;
         dragon_spawned = true;
         delete[] this->b1;
         this->b1 = NULL;
         this->b1 = new Dragon[this->num_inv];
         for (int i = 0;i < this->num_inv;i++)
         {
          this->b1[i].alive = true;
          this->b1[i].sprite.setPosition(290,100);
          this->b1[i].speed = (this->enemy_speed + 0.3);
         }
        }

        if(this->types_counter == 4 && monster_spawned == false)
        {
         dragon_spawned = false;
         this->num_inv = 1;
         monster_spawned = true;
         delete[] this->b1;
         this->b1 = NULL;
         this->b1 = new Monster[this->num_inv];
         for (int i = 0;i < this->num_inv;i++)
         {
          this->b1[i].alive = true;
          this->b1[i].sprite.setPosition(((rand() % 380) + 20),10);
          this->b1[i].speed = (this->level * 0.40);
         }
        }

 	Event e;
        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed)
                window.close();
            if (e.Event::KeyPressed && e.Event::key.code == Keyboard::Escape)
            	window.close();
        }



    if (Keyboard::isKeyPressed(Keyboard::P))
    {
        this->pause = true;
    }

    if (Keyboard::isKeyPressed(Keyboard::R) && this->game_over == false)
    {
       this-> pause = false;
    }

    if (game_over == true || you_won == true)
    {
     bipo++;
    }
    if (this->pause == false && this->game_over == false && this->you_won == false)
    {
    if (Keyboard::isKeyPressed(Keyboard::Left))
            p->move("l");

	if (Keyboard::isKeyPressed(Keyboard::Right))
            p->move("r");

	if (Keyboard::isKeyPressed(Keyboard::Up))
            p->move("u");

	if (Keyboard::isKeyPressed(Keyboard::Down))
            p->move("d");
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		this->music.pause();

		this->laser.setVolume(100);
		this->laser.play();
		this->is_shooting = true;

		this->music.play();
	}
	else
	{
		this->is_shooting = false;
	}

	this->danger_coming(danger_spawned);
	this->lives_coming(lives_spawned);
	this->shooting_mechanism();
	if (dragon_spawned != true && monster_spawned != true)
	{
	 this->player_collisions1();
	 this->invaders_system();
     this->invader_collisions();
    }
	if (monster_spawned == true)
	{
	 this->player_collisions3();
	 this->monster_system();
     this->monster_collisions();
    }
	if (dragon_spawned == true)
	{
	 this->player_collisions2();
	 this->dragon_system();
     this->dragon_collisions();
    }

   }

    //is_shooting = false;

    if (this->player_health <= 0)
    {
     this->game_over = true;
    }

    if (this->game_over == true)
    {
    	this->pause = true;
        this->bg_texture.loadFromFile("img/game_over.png");
    	this->background.setTexture(bg_texture);
    	this->background.setScale(2.25, 1.35);
    }
    if (this->you_won == true)
    {
     this->pause = true;
     this->bg_texture.loadFromFile("img/you_won.jpg");
     this->background.setTexture(bg_texture);
     this->background.setScale(1.4, 1.35);
    }

	window.clear(Color::Black);
	if (game_over == false)
	{
	 this->drawing_game_on(window,font,timer);
	 for(int i = 0;i < 3;i++)
	 {
	  this->asteroids[i].move();
	  this->ufo[i].move();
	  if (this->asteroids[i].anaomally() == true)
	  {
	   this->asteroids[i].position();
	  }
	  if (this->ufo[i].anaomally() == true)
	  {
	   this->ufo[i].position();
	  }
	 }
	 for(int i = 0;i < 3;i++)
	 {
	  window.draw(this->asteroids[i].sprite);
	  window.draw(this->ufo[i].sprite);
	 }
	 window.draw(this->ao2->sprite);
	 window.draw(this->ao1->sprite);
	 this->drawing_player(window);
	 if (dragon_spawned != true && monster_spawned != true)
	 {
	  this->drawing_invaders(window);
	 }
	 if (monster_spawned == true)
	 {
	  this->drawing_monster(window);
	 }
	 if (dragon_spawned == true)
	 {
	  this->drawing_dragon(window);
	 }
	}
	if(this->game_over == true)
	{
	 this->drawing_game_off(window);
	 if (bipo == 20)
	 {
	  this->music.pause();
	  this->lose.setVolume(100);
	  this->lose.play();
      this->music.play();
	 }
	}
	if(this->you_won == true)
	{
	 this->drawing_game_off(window);
	 if (bipo == 20)
	 {
	  this->music.pause();
	  this->win.setVolume(100);
	  this->win.play();
      this->music.play();
	 }
	}
    window.display();
    }

    this->write_to_file();

}

~Game()
{
	if (this->p != NULL)
	{
		delete this->p;
		this->p = NULL;
	}
	if (this->b1 != NULL)
	{
		delete[] this->b1;
		this->b1 = NULL;
	}
	if (this->ao1 != NULL)
	{
		delete this->ao1;
		this->ao1 = NULL;
	}
	if (this->ao2 != NULL)
	{
		delete this->ao2;
		this->ao2 = NULL;
	}
}
};
#endif
