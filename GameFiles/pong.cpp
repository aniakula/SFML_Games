#include<SFML/Graphics.hpp>
#include<sstream>

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");
    window.setFramerateLimit(60);

    sf::Font font;
    if(!font.loadFromFile("Arial.ttf"))
        return -1;
    

    //paddles:
    sf::RectangleShape leftP(sf::Vector2f(10.f, 100.f));
    leftP.setPosition(50, 250);
    leftP.setFillColor(sf::Color::Red);

    sf::RectangleShape rightP(sf::Vector2f(10.f, 100.f));
    rightP.setPosition(740, 250);
    rightP.setFillColor(sf::Color::Blue);

    float paddleSpeed = 5.f;
    sf::Vector2f ballSpeed(-4.f, -4.f);

    //ball:
    sf::CircleShape ball(10);
    ball.setPosition(395, 295);

    int LScore = 0;
    int RScore = 0;

    sf::Text leftScore;
    sf::Text rightScore;
    leftScore.setFont(font);
    rightScore.setFont(font);
    leftScore.setCharacterSize(30);
    rightScore.setCharacterSize(30);
    leftScore.setPosition(300, 20);
    rightScore.setPosition(450, 20);
    leftScore.setFillColor(sf::Color::White);
    rightScore.setFillColor(sf::Color::White);



    while(window.isOpen()){
        sf::Event e;
        while(window.pollEvent(e)){
            if(e.type == sf::Event::Closed)
            window.close();
        }

        //paddle movement:
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftP.getPosition().y > 0)
            leftP.move(0, -paddleSpeed);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftP.getPosition().y + leftP.getSize().y  <  window.getSize().y)
            leftP.move(0, paddleSpeed);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightP.getPosition().y > 0)
            rightP.move(0, -paddleSpeed);
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightP.getPosition().y + rightP.getSize().y < window.getSize().y)
            rightP.move(0, paddleSpeed);

        //ball collisons:
        ball.move(ballSpeed);

        if(ball.getPosition().y <= 0 || ball.getPosition().y + ball.getRadius() * 2 >= window.getSize().y)
          ballSpeed.y = -ballSpeed.y;
        

        if(ball.getGlobalBounds().intersects(leftP.getGlobalBounds())){
            ballSpeed.x < 0.0 ? ballSpeed.x = -ballSpeed.x + 0.5 : ballSpeed.x = -ballSpeed.x - 0.5;
            ballSpeed.y < 0.0 ? ballSpeed.y = ballSpeed.y - 0.5 : ballSpeed.y = ballSpeed.y + 0.5;
        }

        if(ball.getGlobalBounds().intersects(rightP.getGlobalBounds())){
            ballSpeed.x < 0.0 ? ballSpeed.x = -ballSpeed.x + 0.5 : ballSpeed.x = -ballSpeed.x - 0.5;
            ballSpeed.y < 0.0 ? ballSpeed.y = ballSpeed.y - 0.5 : ballSpeed.y = ballSpeed.y + 0.5;
        }

        if(ball.getPosition().x <= 0 || ball.getPosition().x + ball.getRadius() * 2 >= window.getSize().x){
            ball.getPosition().x <= 0 ? RScore++ : LScore++;
            ball.setPosition(395, 295);
            ballSpeed = sf::Vector2f(-4.f, -4.f);
        }

        std::stringstream ss;
        ss << LScore;
        leftScore.setString(ss.str());
        ss.str("");
        ss << RScore;
        rightScore.setString(ss.str());
        
        if(LScore == 2 || RScore == 2){
            sf::Text win;
            win.setFont(font);
            win.setCharacterSize(50);
            (RScore == 2) ? win.setFillColor(sf::Color::Blue) : win.setFillColor(sf::Color::Red);
            win.setPosition(200, 200);
            (RScore == 2) ? win.setString("Player 2 Wins!") : win.setString("Player 1 Wins!");
            window.clear(sf::Color::Black);
            window.draw(win);
            window.display();

            sf::sleep(sf::seconds(3));
            window.close();
        }
       
        window.clear(sf::Color::Black);

        window.draw(leftP);
        window.draw(rightP);
        window.draw(ball);
        window.draw(leftScore);
        window.draw(rightScore);

        window.display();
    }

    return 0; 
}