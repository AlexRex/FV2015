/* 
 * File:   Game.cpp
 * Author: aletormat
 * 
 * Created on 15 de abril de 2015, 9:46
 */

#include "Game.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f/15.f);
const int ancho = 1024, alto = 560; 


Game::Game()
: window(sf::VideoMode(ancho, alto), "Interpol", sf::Style::Close)
, debugText()
, debugFont()
, robot()
, mIzq(false)
, mDcha(false)
{
    window.setVerticalSyncEnabled(true);
   // window.setFramerateLimit(125);

    
    if(!debugFont.loadFromFile("Resources/OpenSans.ttf")){
        std::cout<<"Error al cargar la fuente";
    }
    
    robot.Init(200.f, 250.f);
    
    debugText.setFont(debugFont);
    debugText.setPosition(5.f, 5.f);
    debugText.setCharacterSize(13);
    debugText.setColor(sf::Color::Black);
    debugText.setString("Interp");

}

void Game::run() {
    
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero; 
    
    while (window.isOpen()){
        
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        //Procesamos los eventos
        processEvents();
        
        while(timeSinceLastUpdate > timePerFrame){
            timeSinceLastUpdate -= timePerFrame;
            
            //Update
            update(timePerFrame);
        }
        
        interpolacion = (float)std::min(1.f, timeSinceLastUpdate.asSeconds() / timePerFrame.asSeconds());
        
        //Render
        render(interpolacion);
    }
}

/**Update y Render**/

void Game::update(sf::Time elapsedTime){
    //Actualizamos fisica de los pj
    //std::cout<<"Update"<<std::endl;
    
    float vel_x = 0.f, vel_y=0.f;
    
    sf::Vector2f velocidad;
    
    if(mIzq)
        vel_x = -300.f;
    if(mDcha)
        vel_x = 300.f;
    
    velocidad = sf::Vector2f(vel_x, vel_y);
    
    robot.Update(velocidad, elapsedTime);
}

void Game::render(float interpolacion){
    //std::cout<<"Render"<<std::endl;
    window.clear(sf::Color::White);
    
    //Dibujamos desde player
    
    robot.Draw(window, interpolacion);
    
    window.draw(debugText);
    window.display();
}

/** Eventos **/

void Game::processEvents(){
    sf::Event event;
    while(window.pollEvent(event)){
        switch (event.type){
            case sf::Event::Closed:
                window.close();
                break;
            
            case sf::Event::KeyPressed:
                controlarRobot(event.key.code, true);
                break;
                
            case sf::Event::KeyReleased:
                controlarRobot(event.key.code, false);
                break;
        }
    }
}


void Game::controlarRobot(sf::Keyboard::Key key, bool presionada){
    if(key == sf::Keyboard::Left) mIzq = presionada;
    else if (key==sf::Keyboard::Right) mDcha = presionada;
}