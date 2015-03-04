#include "Resources.hpp"
#include "MyGame.hpp"

int main() {
    Resources::load();
	MyGame mygame(800, 600 // Size of the window <width,height>
            ,"MyGame" // Title of the window
            ,sf::Style::Default); // Style of the window
    mygame.run();
    return 0;
}