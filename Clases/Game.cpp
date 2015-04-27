/* 
 * File:   Game.cpp
 * Author: aletormat
 * 
 * Created on 15 de abril de 2015, 9:46
 */

#include "Game.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f/20.f);
const int ancho = 960, alto = 640; 
sf::Clock saltoTime = sf::Clock();

Game::Game() :
 posIniSalto(-1)
, mIzq(false)
, mDcha(false)
, caiendo(false)
, primeraVez(true)
, windowHeight(20)
, windowWidth(30)
{
    sprites = new sf::Sprite*[windowHeight];
    for(int i = 0; i < windowHeight; i++){
        sprites[i] = new sf::Sprite[windowWidth];
    }
    /*Inicializar variables*/
    
    robot = new Robot();
    mapa = new Mapa();
    colision = new ColisionSuelo();
    
    texturaRobot = new sf::Texture();
    
    debugFont = new sf::Font();
    debugText = new sf::Text();
    
   
    window = new sf::RenderWindow(sf::VideoMode(ancho, alto), "Titulo", sf::Style::Close);
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(125);
    
    
    if(!debugFont->loadFromFile("Resources/OpenSans.ttf")){
        std::cout<<"Error al cargar la fuente"<<std::endl;
    }   
    //Cargamos la textura del robot
    if(!texturaRobot->loadFromFile("Resources/robotFake.png")){
        std::cout<<"Error al cargar la textura"<<std::endl;
    }
    
    
    //mapa->PruebasTinyxml();
    sprites = mapa->crearMapa();
    //mapa->createColisiones();
        
    //AQUI
    robot->Init(*texturaRobot, (16*32), (8*32));
    colision->recibirRobot(robot);
    
    debugText->setFont(*debugFont);
    debugText->setPosition(5.f, 5.f);
    debugText->setCharacterSize(13);
    debugText->setColor(sf::Color::Black);
    debugText->setString("Interp");

}

Game::~Game(){
    std::cout<<"Liberar memoria"<<std::endl;
    delete robot;
    delete texturaRobot;
    delete debugFont;
    delete debugText;
    delete window;
}

void Game::run() {
    
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero; 
    
    while (window->isOpen()){
        
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
    bool hayColision = false;
    bool hayColisionDcha = false;
    float vel_x = 0.f, vel_y=0.f;
    
    sf::Vector2f velocidad;
    
    hayColision = colision->comprobarColision();
    hayColisionDcha = colision->comprobarColisionDcha();

    if(!primeraVez){
        if(mIzq)
            vel_x = -300.f;
        if(mDcha && !hayColisionDcha){
            vel_x = 300.f;
        }
        if(caiendo){
           // std::cout<<robot.getPos().y<<std::endl;
            //vel_y = robot->salta(posIniSalto, saltoTime, elapsedTime);    
            
            if(hayColision && robot->getVel().y > 0)
                caiendo = false;
            else
                vel_y = robot->caer(saltoTime.getElapsedTime(),elapsedTime);
        }     
    }
        if(!hayColision){
            caiendo=true;
            //caer
        }  
 
    
    velocidad = sf::Vector2f(vel_x, vel_y);
    robot->Update(velocidad, elapsedTime);
    primeraVez = false;

}


void Game::render(float interpolacion){
    //std::cout<<"Render"<<std::endl;
    window->clear(sf::Color::White);
    
    //Dibujamos desde player
   for (int i = 0; i < windowHeight; i++) {
        for(int j = 0; j < windowWidth; j++){
            //std::cout<<"i: "<<i<<" j: "<<j<<std::endl;
            window->draw(sprites[i][j]);
        }
    }
    robot->Draw(*window, interpolacion);
    window->draw(*debugText);
    
    
    
    window->display();
}

/** Eventos **/

void Game::processEvents(){
    sf::Event event;
    while(window->pollEvent(event)){
        switch (event.type){
            case sf::Event::Closed:
                window->close();
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
    
    if(key == sf::Keyboard::Left) 
        mIzq = presionada;
    else if (key==sf::Keyboard::Right) 
        mDcha = presionada;
    else if (key==sf::Keyboard::Up){
        if(!caiendo){
            caiendo = true;
            posIniSalto=robot->getLastPos().y;
            saltoTime.restart();
            robot->saltar();
        }
    }
    else if (key==sf::Keyboard::R){
        robot->mueveA(16*32,8*32);
    }
    else if (key==sf::Keyboard::Escape){
        window->close();
    }
    
}