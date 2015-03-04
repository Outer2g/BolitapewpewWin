#ifndef PELOTA_HPP
#define PELOTA_HPP
#include "utils.hpp"

class MyGame;
class Pelota
{
private:
    MyGame* g;
    sf::CircleShape ball;
    sf::Vector2f speed;
    sf::FloatRect boundRect;
	bool CheckCol(int x,int y);
public:
    Pelota();
    Pelota(MyGame* game,int radio,float velo);
    void update(float deltaTime);
    void draw();
    void boost(float Boost,int x, int y);
	bool rekt(int x,int y);
	bool hit(Pelota& ball2);
	void avoid(Pelota& ball2);
};

#endif // PELOTA_HPP
