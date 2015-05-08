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
, cantidadBloques(4)
, posiblesBloques(4)
{
    
    
    
    
    spritesMonedas = new sf::Sprite*[windowHeight];
    for(int i = 0; i < windowHeight; i++){
        spritesMonedas[i] = new sf::Sprite[windowWidth];
    }
    
    spritesObjetosAleatorios = new sf::Sprite*[windowHeight];
    for(int i = 0; i < windowHeight; i++){
        spritesObjetosAleatorios[i] = new sf::Sprite[windowWidth];
    }
    /*Inicializar variables*/
    
    robot = new Robot();
    mapa = new Mapa();
    colision = new ColisionSuelo();
    camara = new Camara();
    
    texturaRobot = new sf::Texture();
    
    piezas = new sf::Sprite[5];
    
    
    debugFont = new sf::Font();
    debugText = new sf::Text();
    
    this->construirMapas();
   
    window = new sf::RenderWindow(sf::VideoMode(ancho, alto), "Melting Me", sf::Style::Default);
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(125);
    
    
    if(!debugFont->loadFromFile("Resources/OpenSans.ttf")){
        std::cout<<"Error al cargar la fuente"<<std::endl;
    }   
    //Cargamos la textura del robot
    if(!texturaRobot->loadFromFile("Resources/spriteSheetTotal.png")){
        std::cout<<"Error al cargar la textura"<<std::endl;
    }
    
   
    
        
    
    //spritesMapa = mapa->crearMapa();
    spritesMonedas = mapa->sitiosMonedas();
    spritesObjetosAleatorios = mapa->objetosAleatorios();
    piezas = mapa->crearEsquema();
    
    
    
    vida1 = new sf::RectangleShape(sf::Vector2f(60, 10));
    vida2 = new sf::RectangleShape(sf::Vector2f(60, 10));
    vida3 = new sf::RectangleShape(sf::Vector2f(60, 10));
    vida4 = new sf::RectangleShape(sf::Vector2f(60, 10));
    
    vida1->setFillColor(sf::Color(150, 50, 250));
    vida1->setPosition(40,90);
    
    vida2->setFillColor(sf::Color(150, 50, 250));
    vida2->setPosition(165,90);
    
    vida3->setFillColor(sf::Color(150, 50, 250));
    vida3->setPosition(40,120);
    
    vida4->setFillColor(sf::Color(150, 50, 250));
    vida4->setPosition(165,120);
    
    
    //AQUI
    sf::Vector2i posInicial;
    posInicial.x = 16*32;
    posInicial.y = 8*32;
    robot->Init(*texturaRobot, (posInicial.x), (posInicial.y));
    colision->recibirRobot(robot);
    
    camara->creaCamara(posInicial.x,posInicial.y-64,960,640);
    robot->recibirCamara(camara);

    debugText->setFont(*debugFont);
    debugText->setPosition(400.f, 5.f);
    debugText->setCharacterSize(13);
    debugText->setColor(sf::Color::Black);
    debugText->setString("Arriba: Saltar\nDerecha: Andar Decha\nIzq: Andar Izq\nR: Volver a la pos inicial\nEsc: Salir");

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
    //velCam = sf::Vector2f(vel_xCam, vel_yCam);
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
            for(int a = 0; a<cantidadBloques; a++){
               window->draw(spritesBloques[a][i][j]);
            }
            //window->draw(spritesObjetosAleatorios[i][j]);
            //window->draw(spritesMonedas[i][j]);
        }
    }
    
    for (int i = 0; i < 5; i++){
        window->draw(piezas[i]);
    }
    window->draw(*vida1);
    window->draw(*vida2);
    window->draw(*vida3);
    window->draw(*vida4);
    
    window->setView(*camara->getView());
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


sf::Sprite*** Game::construirMapas(){
    /*PRUEBA GEN MAPA*/
    nombresBloques = new char*[cantidadBloques];
    for(int i=0; i < cantidadBloques; i++){
        nombresBloques[i] = new char[13];
    }
    nombresBloques = mapa->generarMapa(cantidadBloques, posiblesBloques); //Cantidad de mapas en el nivel (2) / Bloques distintos que pueden salir (10)
    
    for(int i=0; i<cantidadBloques; i++){
        std::cout<<"Nombre: "<<nombresBloques[i]<<std::endl;
    }
    
    spritesBloques = new sf::Sprite**[cantidadBloques];
    
    for(int a = 0; a<cantidadBloques; a++){
        spritesBloques[a] = new sf::Sprite*[windowHeight]; //Reservamos memoria para el mapa
        for(int i = 0; i < windowHeight; i++){
            spritesBloques[a][i] = new sf::Sprite[windowWidth];
        }
    }
    for(int i = 0; i < cantidadBloques; i++){
        spritesBloques[i] = mapa->crearMapa(i, nombresBloques[i]);
    }
       
    return spritesBloques;
}