#include "MyGame.hpp"
#include <sstream>
#include <string>

MyGame::MyGame(int scrwidth, int scrheight, std::string title, int style)
    : Game(scrwidth,scrheight,title,style) {

    Pelota aux(this,10,100);
    balls = std::vector<Pelota> (1);
    balls[0] = aux;
    timer=0.0;
    time_to_next_ball=0.4;
	fps = 0;
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	fpsText.setFont(font);
	fpsText.setCharacterSize(30);
	fpsText.setPosition(50.0,50.0);
	std::stringstream text2;
	text2 << fps;
	std::string str = text2.str();
	fpsText.setString(str);
	window.setVerticalSyncEnabled(false);
}

MyGame::~MyGame() {}

void MyGame::update(float deltaTime){
    for (unsigned i = 0; i < balls.size(); ++i) balls[i].update(deltaTime);
	fps = fps*0.999 + (1 / deltaTime)*0.001;
	std::stringstream text2;
	text2 << fps;
	std::string str = text2.str();
	fpsText.setString(str);
	//balls colision
	for (int i = 0; i < balls.size(); i++)
	{
		for (int j = i + 1; j < balls.size(); j++)
		{
			if (balls[i].hit(balls[j]))
			{
				balls[i].avoid(balls[j]);
			}
		}
	}
}

void MyGame::draw(){
    for (unsigned i = 0; i < balls.size(); ++i) balls[i].draw();
	window.draw(fpsText);
}

void MyGame::processEvents(float deltaTime){
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) window.close();
            if (event.key.code == sf::Keyboard::Space and timer>=time_to_next_ball){
                timer=0.0;
                Pelota nBall(this,100,100);
                balls.push_back(nBall);
            }
            break;
        case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left){
				for (unsigned i = 0; i < balls.size(); ++i){
					balls[i].boost(500.0, event.mouseButton.x, event.mouseButton.y);
				}
			}
            
			if (event.mouseButton.button == sf::Mouse::Right){
				for (unsigned i = 0; i < balls.size(); ++i){
					if (balls[i].rekt(event.mouseButton.x, event.mouseButton.y)){
						for (unsigned j = i; j < balls.size()-1; ++j){
							balls[i] = balls[i + 1];
						}
						balls.pop_back();
					}
				}
			}
            break;
            // Add more events to handle them
        default:
            break;
        }
    }
    timer+=deltaTime;

	
}

sf::RenderWindow *MyGame::getWindow() {
    return &window;
}

std::vector<Pelota> MyGame::getBalls(){
	return this->balls;
}