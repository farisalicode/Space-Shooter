#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include "player.h"
#include "Bosses.h"
#include "Bomb.h"
#ifndef START_MENU_H_
#define START_MENU_H_
const char title[] = "Start Menu";
using namespace sf;
using namespace std;


class start_menu
{
public:
 Sprite background;
 Texture bg_texture;
 Font font;
 char choice;
 start_menu()
 {
  this->bg_texture.loadFromFile("img/background_2.png");
  this->background.setTexture(bg_texture);
  this->background.setScale(2.25, 2.85);
  font.loadFromFile("TNR.ttf");
  choice = ' ';
 }
 void option_one(RenderWindow& window)
 {
  Text text;
  text.setFont(font);
  string words;
  words = "Space Shenanigans";
  text.setString(words);
  text.setCharacterSize(66);
  text.setFillColor(sf::Color::Yellow);
  text.setStyle(sf::Text::Italic);
  text.setPosition(130,4);
  window.draw(text);


  words = "Press Enter to play a new game.";
  text.setString(words);
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::Yellow);
  text.setStyle(sf::Text::Bold);
  text.setPosition(20,260);
  window.draw(text);
  return;
 }
 void option_two(RenderWindow& window)
 {
  Text text;
  text.setFont(font);
  string words;
  words = "Press Space to play saved game.";
  text.setString(words);
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::Yellow);
  text.setStyle(sf::Text::Bold);
  text.setPosition(20,340);
  window.draw(text);
  return;
 }
 void option_three(RenderWindow& window)
  {
   Text text;
   text.setFont(font);
   string words;
   words = "Press H to view high scores.";
   text.setString(words);
   text.setCharacterSize(24);
   text.setFillColor(sf::Color::Yellow);
   text.setStyle(sf::Text::Bold);
   text.setPosition(20,420);
   window.draw(text);
   return;
  }
 void option_four(RenderWindow& window)
  {
   Text text;
   text.setFont(font);
   string words;
   words = "Press I to view instructions.";
   text.setString(words);
   text.setCharacterSize(24);
   text.setFillColor(sf::Color::Yellow);
   text.setStyle(sf::Text::Bold);
   text.setPosition(20,500);
   window.draw(text);
   return;
  }
 void option_five(RenderWindow& window)
   {
    Text text;
    text.setFont(font);
    string words;
    words = "Press R to view system requirements.";
    text.setString(words);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Yellow);
    text.setStyle(sf::Text::Bold);
    text.setPosition(20,580);
    window.draw(text);
    return;
   }

 void high_one(RenderWindow& window,string words)
  {
   Text text;
   text.setFont(font);
   text.setString("High Scores");
   text.setCharacterSize(48);
   text.setFillColor(sf::Color::Yellow);
   text.setStyle(sf::Text::Bold);
   text.setPosition(260,4);
   window.draw(text);

   Texture texture;
   Sprite sprite;
   texture.loadFromFile("img/gold.png");
   sprite.setTexture(texture);
   sprite.setPosition(40,140);
   sprite.setScale(0.42,0.24);
   text.setString(words);
   text.setCharacterSize(24);
   text.setFillColor(sf::Color::Yellow);
   text.setStyle(sf::Text::Bold);
   text.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width + 20,140);
   window.draw(sprite);
   window.draw(text);
   return;
  }
 void high_two(RenderWindow& window,string words)
  {
   Text text;
   text.setFont(font);
   Texture texture;
   Sprite sprite;
   texture.loadFromFile("img/silver.png");
   sprite.setTexture(texture);
   sprite.setPosition(40,280);
   sprite.setScale(0.195,0.11);
   text.setString(words);
   text.setCharacterSize(24);
   text.setFillColor(sf::Color::Yellow);
   text.setStyle(sf::Text::Bold);
   text.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width + 20,280);
   window.draw(sprite);
   window.draw(text);
   return;
  }
 void high_three(RenderWindow& window,string words)
  {
   Text text;
   text.setFont(font);
   Texture texture;
   Sprite sprite;
   texture.loadFromFile("img/bronze.png");
   sprite.setTexture(texture);
   sprite.setPosition(10,420);
   sprite.setScale(0.26,0.20);
   text.setString(words);
   text.setCharacterSize(24);
   text.setFillColor(sf::Color::Yellow);
   text.setStyle(sf::Text::Bold);
   text.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width - 10,420);
   window.draw(sprite);
   window.draw(text);
   return;
  }

 void instructors(RenderWindow& window)
   {
    Text text;
    text.setFont(font);
    text.setString("Instructions");
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::Yellow);
    text.setStyle(sf::Text::Bold);
    text.setPosition(260,4);
    window.draw(text);

    string words = "Use Up arrow to move up.\n";
    words = words + "Use Down arrow to move down.\n";
    words = words + "Use Right arrow to move right.\n";
    words = words + "Use Left arrow to move left.\n";
    words = words + "Use Space to shoot.\n";
    words = words + "Beat each invader wave thrice to fight final two bosses, dragon and monster.\n";
    words = words + "The dragon will breath fire at you in three seprate directions.\n";
    words = words + "The monster will chase you around and unleash lightning bolts on you.\n";
    words = words + "Beat both these bosses to win the game.\n";
    words = words + "Earn as points as possible to earn a position on the leader board.\n\n\n\n\n\n\n\n";
    words = words + "Good Luck!\n";
    text.setString(words);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Yellow);
    text.setStyle(sf::Text::Bold);
    text.setPosition(10,140);
    window.draw(text);
    return;
   }

 void special_touch(RenderWindow& window)
    {
     Text text;
     text.setFont(font);
     text.setString("System Requirements");
     text.setCharacterSize(48);
     text.setFillColor(sf::Color::Yellow);
     text.setStyle(sf::Text::Bold);
     text.setPosition(170,4);
     window.draw(text);

     string words = "\"Object-oriented programming is an exceptionally bad idea\nwhich could only have originated in California.\"\n";
     text.setString(words);
     text.setCharacterSize(30);
     text.setFillColor(sf::Color::Yellow);
     text.setStyle(sf::Text::Bold);
     text.setPosition(10,180);
     window.draw(text);

     words = "Edsger W. Dijkstra\n";
     text.setString(words);
     text.setCharacterSize(20);
     text.setFillColor(sf::Color::Yellow);
     text.setStyle(sf::Text::Italic);
     text.setPosition(10,270);
     window.draw(text);

     words = "(I personally do not endorse this statement)\n";
     text.setString(words);
     text.setCharacterSize(20);
     text.setFillColor(sf::Color::Yellow);
     text.setStyle(sf::Text::Bold);
     text.setPosition(10,320);
     window.draw(text);

     words = "1.4GHz CPU\n";
     words = words + "4GB RAM\n";
     words = words + "1GB GPU\n";
     words = words + "8MB Storage\n";
     words = words + "Windows 10 or greater\n";
     words = words + "Eclipse For C++\n";
     words = words + "SFML Library Package\n";
     text.setString(words);
     text.setCharacterSize(20);
     text.setFillColor(sf::Color::Yellow);
     text.setStyle(sf::Text::Bold);
     text.setPosition(10,450);
     window.draw(text);
     return;
    }

 void main_menu()
 {
    srand(time(0));
    RenderWindow window(VideoMode(780, 780), "Main Menu");
    Clock clock;
    float timer=0;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
 	Event e;
        while (window.pollEvent(e))
        {
         if (e.type == Event::Closed)
         window.close();

         if (e.Event::KeyPressed && e.Event::key.code == Keyboard::Escape)
         window.close();
        }

	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
	 this->choice = 'E';
	 window.close();
	}


	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
	 this->choice = 'S';
	 window.close();
	}

	if (Keyboard::isKeyPressed(Keyboard::H))
	{
	 this->choice = 'H';
	 window.close();
	}

	if (Keyboard::isKeyPressed(Keyboard::I))
	{
	 this->choice = 'I';
	 window.close();
	}

	if (Keyboard::isKeyPressed(Keyboard::R))
	{
	 this->choice = 'R';
	 window.close();
	}


	window.clear(Color::Black);
	window.draw(background);
	this->option_one(window);
	this->option_two(window);
	this->option_three(window);
	this->option_four(window);
	this->option_five(window);
	window.display();
   }
   return;
 }

 void instructions_menu()
 {
    srand(time(0));
    RenderWindow window(VideoMode(780, 780), "Instructions");
    Clock clock;
    float timer=0;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
 	Event e;
        while (window.pollEvent(e))
        {
         if (e.type == Event::Closed)
         window.close();

         if (e.Event::KeyPressed && e.Event::key.code == Keyboard::Escape)
         window.close();
        }

	window.clear(Color::Black);
	window.draw(background);
	this->instructors(window);
	window.display();
   }
   return;
 }

 void requirements_menu()
  {
     srand(time(0));
     RenderWindow window(VideoMode(780, 780), "Requirements");
     Clock clock;
     float timer=0;
     while (window.isOpen())
     {
         float time = clock.getElapsedTime().asSeconds();
         clock.restart();
         timer += time;
  	Event e;
         while (window.pollEvent(e))
         {
          if (e.type == Event::Closed)
          window.close();

          if (e.Event::KeyPressed && e.Event::key.code == Keyboard::Escape)
          window.close();
         }

 	window.clear(Color::Black);
 	window.draw(background);
 	this->special_touch(window);
 	window.display();
    }
    return;
  }

 void scores_menu()
  {
     srand(time(0));
     RenderWindow window(VideoMode(780, 780), "High Scores");
     Clock clock;
     float timer=0;
     while (window.isOpen())
     {
         float time = clock.getElapsedTime().asSeconds();
         clock.restart();
         timer += time;
  	Event e;
         while (window.pollEvent(e))
         {
          if (e.type == Event::Closed)
          window.close();

          if (e.Event::KeyPressed && e.Event::key.code == Keyboard::Escape)
          window.close();
         }

 	window.clear(Color::Black);
 	window.draw(background);
    string text;
    ifstream file("highscores.txt");
    int counter = 0;
    while (getline(file, text))
    {
     if(counter == 0)
	 {
      this->high_one(window,text);
	 }
     if(counter == 1)
	 {
      this->high_two(window,text);
	 }
	 if(counter == 2)
	 {
	  this->high_three(window,text);
	 }
	 ++counter;
    }
    file.close();
 	window.display();
    }
    return;
  }
};

#endif
