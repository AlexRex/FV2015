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
, muerto(false)
, pause(false)
, windowHeight(20)
, windowWidth(30)
, cantidadBloques(2)
, posiblesBloques(1)
, monedasRecogidas(0)
, status(1)
{   
    
    spritesObjetosAleatorios = new sf::Sprite*[windowHeight];
    for(int i = 0; i < windowHeight; i++){
        spritesObjetosAleatorios[i] = new sf::Sprite[windowWidth];
    }
   
    
    window = new sf::RenderWindow(sf::VideoMode(ancho, alto), "Melting Me", sf::Style::Default);
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(125);
    
    
    
    /*Inicializar variables*/
    
    tienda = new Tienda(ancho, alto);
    robot = new Robot();
    mapa = new Mapa();
    colision = new Colisiones();
    camara = new Camara();
    camaraMenu = new Camara();
    hud = new Hud();
    tiempoPartida = new sf::Clock();
    nuevaPieza = new Pieza();
    
    texturaRobot = new sf::Texture();
    
    piezas = new sf::Sprite[5];
    
    
    debugFont = new sf::Font();
    debugText = new sf::Text();
    
   
    
    
    
    if(!debugFont->loadFromFile("Resources/OpenSans.ttf")){
        std::cout<<"Error al cargar la fuente"<<std::endl;
    }   
    //Cargamos la textura del robot
    if(!texturaRobot->loadFromFile("Resources/spriteSheetTotal.png")){
        std::cout<<"Error al cargar la textura"<<std::endl;
    }
    
    spriteFondo = new sf::Sprite();
    
    if(!texturaFondo.loadFromFile("Resources/fondoG.png")){
        std::cerr << "Error cargando las texturas";
        exit(0);
    }
    
    
    spriteFondo->setTexture(texturaFondo);
    spriteFondo->setOrigin(0, 0);
    
    fondo = new sf::Sprite[cantidadBloques];
    for(int i=0; i<cantidadBloques; i++){
        spriteFondo->setPosition(i*ancho, 0); 
        fondo[i] = *spriteFondo;
    }

    this->construirMapas();
    //spritesMonedas = mapa->sitiosMonedas();
    //spritesObjetosAleatorios = mapa->objetosAleatorios();
    piezas = mapa->crearEsquema();
    
    barrasVida = new sf::RectangleShape[4];

    //AQUI
    sf::Vector2i posInicial;
    posInicial.x = 16*32;
    posInicial.y = 8*32;
    hud->crearHud(debugFont);
    hud->recibirPiezas(piezas);
    robot->Init(*texturaRobot, (posInicial.x), (posInicial.y));
    colision->init(robot, cantidadBloques, nombreBloques);
    
    camara->creaCamara(posInicial.x,posInicial.y-64,ancho,alto);
    camaraMenu->creaCamaraMenu(posInicial.x, posInicial.y-64, ancho, alto);
    robot->recibirCamara(camara);
    robot->recibirHud(hud);

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
    delete spriteFondo;
    delete fondo;
    delete camara;
    delete camaraMenu;
    delete window;
    delete tienda;
}

bool Game::run() {
    
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero; 
    
    while (window->isOpen()){
        
        if(!pause){
            sf::Time elapsedTime = clock.restart();
            timeSinceLastUpdate += elapsedTime;
        }
        //Procesamos los eventos
        processEvents();
        
        if(!pause){
            while(timeSinceLastUpdate > timePerFrame){
                timeSinceLastUpdate -= timePerFrame;

                //Update

                update(timePerFrame);
            }

            interpolacion = (float)std::min(1.f, timeSinceLastUpdate.asSeconds() / timePerFrame.asSeconds());

            //Render
            render(interpolacion);
        }
        if(muerto){
            return true;
        }
        

    }
    
    
    return true;

}

/**Update y Render**/

void Game::update(sf::Time elapsedTime){
    
    
    //Actualizamos fisica de los pj
    //std::cout<<"Update"<<std::endl;
        bool hayColision = false;
        bool hayColisionDcha = false;
        bool hayColisionMoneda =false;
        bool hayColisionPieza = false;
        float vel_x = 0.f, vel_y=0.f;
        
        sf::Vector2f velocidad;

        hayColision = colision->comprobarColision();
        hayColisionDcha = colision->comprobarColisionDcha();
        hayColisionMoneda = colision->comprobarMoneda(spritesMonedas);
        //std::cout<<"En game"<<std::endl;
        hayColisionPieza = colision->comprobarPieza();

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
                if(robot->getPos().y>555){
                    pause=true;
                    muerto = true;
                }
                //caer
            }
            //Coge moneda        
            if(hayColisionMoneda){
                monedasRecogidas++;
                std::cout<<"Monedas: "<<monedasRecogidas<<std::endl;

            }
            if(hayColisionPieza){
                std::cout<<"Piezaaaaaaaaaaaaaaaaaaaaa"<<std::endl;
                //Crear pieza random
                int tipoPieza = -1;
                tipoPieza = nuevaPieza->iniciarPieza(-1);
                //Comprobar casillas robot
                
                
                
                /* Imprimir array piezas robot*/
                Pieza*** piezasRobot = new Pieza**[4];
                piezasRobot = new Pieza**[4];
                for(int i = 0; i < 4; i++){
                    piezasRobot[i] = new Pieza*[2];
                    for(int j = 0; j < 2; j++){
                        piezasRobot[i][j] = new Pieza();
                    }
                }
                piezasRobot = robot->getPiezas();
                for(int i=0; i<4; i++){
                    //for(int j=0; j<2; j++){
                        std::cout<<"Pieza robot["<<i<<"]["<<0<<"]: "<<piezasRobot[i][0]->getTipo()<<std::endl;
                    //}
                }
                std::cout<<std::endl;
                std::cout<<std::endl;
                robot->insertarPieza(nuevaPieza);
                std::cout<<"Tipo pieza nueva: "<<tipoPieza<<std::endl;
                piezasRobot = robot->getPiezas();
                std::cout<<std::endl;
                for(int i=0; i<4; i++){
                    //for(int j=0; j<2; j++){
                        std::cout<<"Pieza robot["<<i<<"]["<<0<<"]: "<<piezasRobot[i][0]->getTipo()<<std::endl;
                    //}
                }
            }


        velocidad = sf::Vector2f(vel_x, vel_y);
        //velCam = sf::Vector2f(vel_xCam, vel_yCam);
        if(status == 0){
            robot->Update(velocidad, elapsedTime);
            primeraVez = false;
        }
        //Actualizamos Hud
        hud->recibirDatos(tiempoPartida);
        

       

}


void Game::render(float interpolacion){
    //std::cout<<"Render"<<std::endl;
    window->clear(sf::Color::White);
    //window->draw(*spriteFondo);
    //Dibujamos desde player
    if(status==0){
        for(int i = 0; i<cantidadBloques; i++){
           //window->draw(fondo[i]);
        }
        for (int i = 0; i < windowHeight; i++) {
            for(int j = 0; j < windowWidth; j++){
                //std::cout<<"i: "<<i<<" j: "<<j<<std::endl;
                //window->draw(spritesFondo[i][j]);
                for(int a = 0; a<cantidadBloques; a++){
                   //window->draw(spritesMonedas[a][i][j]);
                   window->draw(spritesBloques[a][i][j]);
                }
                for(int a = 0; a<cantidadBloques; a++){
                    window->draw(spritesMonedas[a][i][j]);
                }
                for(int a = 0; a<cantidadBloques; a++){
                    window->draw(spritesPiezas[a][i][j]);

                }
                //window->draw(spritesObjetosAleatorios[i][j]);
                //window->draw(spritesMonedas[i][j]);
            }
        }


        if(muerto){
            window->clear(sf::Color::White);
            window->setView(*camaraMenu->getMenuView());
        }
        else{
            window->setView(*camara->getView());
            robot->Draw(*window, interpolacion);
            pintarHud(); //Agrupado todo en una funcion auxiliar para reducir codigo
        }
        //window->draw(*debugText);
    }
    else{
        tienda->draw(*window);
    }
    
    
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
                if(status==0){
                    controlarRobot(event.key.code, true);
                    controlarJuego(event.key.code);
                }
                else{
                    controlarMenus(event.key.code);
                }

                break;

            case sf::Event::KeyReleased:
                if(status==0)
                    controlarRobot(event.key.code, false);

                break;
        }
        
    }
}


void Game::controlarMenus(sf::Keyboard::Key key){
    switch(key){
        case sf::Keyboard::Up:
            tienda->MoveUp();
            break;
        case sf::Keyboard::Down:
            tienda->MoveDown();
            break;
        case sf::Keyboard::Return:
            switch(tienda->GetPressedItem()){
                case 0:
                    std::cout<<"jugar"<<std::endl;
                    status = 0;
                break;
                case 1:
                    std::cout<<"opciones"<<std::endl;
                break;
                case 2:
                    std::cout<<"Salir"<<std::endl;
                    window->close();
                break;
            }
            break;
            
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
}

void Game::controlarJuego(sf::Keyboard::Key key){
    if (key==sf::Keyboard::Escape){
        window->close();
    }
    else if (key==sf::Keyboard::P){
        pause = !pause;
    }
    else if (key==sf::Keyboard::R){
        robot->mueveA(16*32,8*32);
    }
}


sf::Sprite*** Game::construirMapas(){
    /*PRUEBA GEN MAPA*/
    nombreBloques = new char*[cantidadBloques];
    for(int i=0; i < cantidadBloques; i++){
        nombreBloques[i] = new char[13];
    }
    nombreBloques = mapa->generarMapa(cantidadBloques, posiblesBloques); //Cantidad de mapas en el nivel (2) / Bloques distintos que pueden salir (10)
    
    for(int i=0; i<cantidadBloques; i++){
        std::cout<<"Nombre: "<<nombreBloques[i]<<std::endl;
    }
    
    spritesBloques = new sf::Sprite**[cantidadBloques];
    spritesMonedas = new sf::Sprite**[cantidadBloques];
    spritesPiezas =  new sf::Sprite**[cantidadBloques];
    
    for(int a = 0; a<cantidadBloques; a++){
        spritesMonedas[a] = new sf::Sprite*[windowHeight];
        spritesPiezas[a]  = new sf::Sprite*[windowHeight];
        spritesBloques[a] = new sf::Sprite*[windowHeight]; //Reservamos memoria para el mapa
        for(int i = 0; i < windowHeight; i++){
            spritesBloques[a][i] = new sf::Sprite[windowWidth];
            spritesMonedas[a][i] = new sf::Sprite[windowWidth];
            spritesPiezas[a][i]  = new sf::Sprite[windowWidth];
        }
    }
    std::cout<<"he"<<std::endl;
    for(int i = 0; i < cantidadBloques; i++){
        spritesBloques[i] = mapa->crearMapa(i, nombreBloques[i]);
        spritesMonedas[i] = mapa->sitiosMonedas(i, nombreBloques[i]);
        spritesPiezas[i]  = mapa->sitiosPiezas(i, nombreBloques[i]);
    }
       
    return spritesBloques;
}

sf::Sprite*** Game::construirFondos(){
    
    spritesFondos = new sf::Sprite**[cantidadBloques];
    
    for(int a = 0; a<cantidadBloques; a++){
        spritesFondos[a] = new sf::Sprite*[windowHeight]; //Reservamos memoria para el mapa
        for(int i = 0; i < windowHeight; i++){
            spritesFondos[a][i] = new sf::Sprite[windowWidth];
        }
    }
    for(int i = 0; i < cantidadBloques; i++){
        spritesFondos[i] = mapa->crearFondo(i);
    }
       
    return spritesFondos;
}

void Game::pintarHud(){
    sf::Text textoHud;
    textoHud = *hud->getTiempo();
    window->draw(textoHud);
        
    for (int i = 0; i < 5; i++){
        if(i<4){
            barrasVida[i]=*hud->getVida(i); //Actualizamos la posicion de las barras
            window->draw(barrasVida[i]);//Pintamos barras
        }
        piezas[i] = hud->getPieza(i); //Actualizamos la posicion de los sprites del esquema
        window->draw(piezas[i]); //Pintamos sprite del esquema
    }
}