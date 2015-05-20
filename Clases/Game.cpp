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
, monedasTotales(500)
, coeficienteDesintegracion(75)
, status(2) // 0 = Juego, 1 = Tienda, 2 = Menu Princ, 3 = Muerte, 4 = Pto Control
{   
    
    spritesObjetosAleatorios = new sf::Sprite*[windowHeight];
    for(int i = 0; i < windowHeight; i++){
        spritesObjetosAleatorios[i] = new sf::Sprite[windowWidth];
    }
   
    
    window = new sf::RenderWindow(sf::VideoMode(ancho, alto), "Melting Me", sf::Style::Default);
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(125);
    
    
    
    /*Inicializar variables*/
    guardado = new Guardado();
    menuPuntoControl = new MenuPuntoDeControl(ancho, alto);
    menuMuerte = new MenuMuerte(ancho, alto);
    menu  = new Menu(ancho, alto);
    tienda = new Tienda(ancho, alto, monedasTotales);
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
    if(!texturaRobot->loadFromFile("Resources/spritesheetTotal.png")){
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
    
    posInicial.x = 16*32;
    posInicial.y = 8*32;
    hud->crearHud(debugFont, cantidadBloques);
    hud->recibirPiezas(piezas);
    robot->Init(*texturaRobot, (posInicial.x), (posInicial.y), coeficienteDesintegracion);
    colision->init(robot, cantidadBloques, nombreBloques);
    
    guardado->guardarPartida(3,2,3,4,5,6);
    guardado->restaurarPartida();
    
    camara->creaCamara(posInicial.x,posInicial.y-64,ancho,alto, cantidadBloques);
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
    delete menu;
    delete menuMuerte;
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
        
        if(menuPuntoControl->enPuntoControl(cantidadBloques, robot->getPos().x)){
            status = 4;
            robot->Init(*texturaRobot, (posInicial.x), (posInicial.y), coeficienteDesintegracion);
            camara->setPos(sf::Vector2f (0,0), 1);
            tienda->setMonedas(monedasTotales);
            menuPuntoControl->setMonedas(monedasRecogidas);
        }
        if(status==0){
            muerto=robot->actualizaPiezas(elapsedTime);
            if(muerto){
                robot->Init(*texturaRobot, (posInicial.x), (posInicial.y), coeficienteDesintegracion);
                status = 3;
            }
        }
         if(status==3){
            robot->Init(*texturaRobot, (posInicial.x), (posInicial.y), coeficienteDesintegracion);

        }
        
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
                   // pause=true;
                    muerto = true;
                    robot->Init(*texturaRobot, (posInicial.x), (posInicial.y), coeficienteDesintegracion);
                    status = 3;
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
                    for(int j=0; j<2; j++){
                        std::cout<<"Pieza robot["<<i<<"]["<<j<<"]: "<<piezasRobot[i][j]->getTipo()<<"Vida : "<<piezasRobot[i][j]->getVida()<<" Muerta?: "<<piezasRobot[i][j]->getMuerta()<<std::endl;
                    }
                }
                std::cout<<std::endl;
                std::cout<<std::endl;
                
                //random
                srand (time(NULL));
                int r = rand() % 2;
                int r2;
                bool piezaInsertada=false;
                if(r ==0){
                    r2 = rand() % 5 +6;
                    //comprobar brazos
                    piezaInsertada=robot->insertarBrazo(r2);
                    if(piezaInsertada)
                    std::cout<<"He insertado brazo?: "<<piezaInsertada<<std::endl;
                }
                else{
                    r2 = rand() % 5 +1;
                    //comprobar piernas
                    piezaInsertada= robot->insertarPierna(r2);
                    if(piezaInsertada)
                    std::cout<<"He insertado pierna?: "<<piezaInsertada<<std::endl;
                }
                std::cout<<"Tipo a insertar: "<<r2<<std::endl;
                piezasRobot = robot->getPiezas();
                for(int i=0; i<4; i++){
                    for(int j=0; j<2; j++){
                        std::cout<<"Pieza robot["<<i<<"]["<<j<<"]: "<<piezasRobot[i][j]->getTipo()<<"Vida : "<<piezasRobot[i][j]->getVida()<<" Muerta?: "<<piezasRobot[i][j]->getMuerta()<<std::endl;
                    }
                }
                
                std::cout<<std::endl;
                std::cout<<std::endl;
                
                
                
                /*
                std::cout<<"Piezaaaaaaaaaaaaaaaaaaaaa"<<std::endl;
                //Crear pieza random
                int tipoPieza = -1;
                tipoPieza = nuevaPieza->iniciarPieza(-1);
                //Comprobar casillas robot
                
                
                

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
                */
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
           window->draw(fondo[i]);
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


        
        if(!muerto){
            window->setView(*camara->getView());
            robot->Draw(*window, interpolacion);
            pintarHud(); //Agrupado todo en una funcion auxiliar para reducir codigo
        }
        //window->draw(*debugText);
    }
    else if(status==1){
        window->setView(*camara->getView());
        tienda->draw(*window);
    }
    else if(status==2){
        camara->setPos(sf::Vector2f(0,0), 2);
        window->setView(*camara->getView());
        menu->draw(*window);
    }
    else if(status==3){
        camara->setPos(sf::Vector2f(0,0), 3);
        window->setView(*camara->getView());
        menuMuerte->draw(*window);
    }
    else if(status == 4){
        camara->setPos(sf::Vector2f(0,0), 3);
        window->setView(*camara->getView());
        menuPuntoControl->draw(*window);
        
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
                else if(status==1){
                    controlarRobot(sf::Keyboard::Right, false);
                    controlarTienda(event.key.code);
                }
                else if(status==2){
                    controlarRobot(sf::Keyboard::Right, false);
                    controlarMenus(event.key.code);
                }
                else if(status==3){
                    controlarRobot(sf::Keyboard::Right, false);
                    controlarMenuMuerte(event.key.code);
                }
                else if(status==4){
                    controlarRobot(sf::Keyboard::Right, false);
                    controlarPuntoControl(event.key.code); 
                }

                break;

            case sf::Event::KeyReleased:
                if(status==0)
                    controlarRobot(event.key.code, false);

                break;
        }
        
    }
}

void Game::controlarTienda(sf::Keyboard::Key key){
    switch(key){
        case sf::Keyboard::Up:
            tienda->MoveUp();
            break;
        case sf::Keyboard::Down:
            tienda->MoveDown();
            break;
        case sf::Keyboard::Escape:
            status=2;
            break;
        
        case sf::Keyboard::Return:
            
            switch(tienda->GetPressedItem()){
                case 0:
                    status=2;
                   
                    
                break;
                case 1:
                     
                     if(monedasTotales >= 100){
                         if(robot->insertarPierna(4)){
                             monedasTotales -= 100;
                            tienda->setMonedas(monedasTotales);
                            std::cout<<"Has comprado Pierna reforzada"<<std::endl;
                         }
                         else{
                             std::cout<<"No tienes espacio para la pieza"<<std::endl;
                         }
                         
                     }
                    else{
                        std::cout<<"No puedes comprar Pierna reforzada"<<std::endl;
                    }
                    
                    
                break;
                case 2:
                    
                    if(monedasTotales >= 300){
                         if(robot->insertarPierna(5)){
                            monedasTotales -= 300;
                            tienda->setMonedas(monedasTotales);
                            std::cout<<"Has comprado Pierna boing"<<std::endl;
                         }
                         
                     }
                    else{
                        std::cout<<"No puedes comprar Pierna boing"<<std::endl;
                    }
                    
                    
                break;
                case 3:
                    
                    if(monedasTotales >= 500){
                         if(robot->insertarBrazo(9)){
                            monedasTotales -= 500;
                            tienda->setMonedas(monedasTotales);
                            std::cout<<"Has comprado Brazo de midas"<<std::endl; 
                         }
                         
                    }
                    else{
                        std::cout<<"No puedes comprar Brazo de midas"<<std::endl;
                    }
                   
                break;
                case 4:
                     
                     if(monedasTotales >= 200){
                         if(robot->insertarBrazo(8)){
                            monedasTotales -= 200;
                            tienda->setMonedas(monedasTotales);
                            std::cout<<"Has comprado Brazo-pierna"<<std::endl;
                         }
                         
                     }
                    else{
                        std::cout<<"No puedes comprar Brazo-pierna"<<std::endl;
                    }
                    
                    
                break;
                case 5:
                    
                    if(monedasTotales >= 600){
                         if(robot->insertarBrazo(7)){
                            monedasTotales -= 600;
                            tienda->setMonedas(monedasTotales);
                            std::cout<<"Has comprado Brazo de Chuck Norris"<<std::endl;
                         }
                         
                     }
                    else{
                        std::cout<<"No puedes comprar Brazo de Chuck Norris"<<std::endl;
                    }
                    break;
            }
            break;
            
    }
}

void Game::controlarPuntoControl(sf::Keyboard::Key key){
    switch(key){
        case sf::Keyboard::Up:
            menuPuntoControl->MoveUp();
            break;
        case sf::Keyboard::Down:
            menuPuntoControl->MoveDown();
            break;
        case sf::Keyboard::Escape:
            status=2;
            break;
        case sf::Keyboard::Return:
            switch(menuPuntoControl->GetPressedItem()){
                case 0:
                    std::cout<<"jugar"<<std::endl;
                    status = 0;
                break;
                case 1:
                    std::cout<<"tienda"<<std::endl;
                    status = 1;
                break;
                case 2:
                    std::cout<<"Salir"<<std::endl;
                    window->close();
                break;
            }
            break;
            
    }
}

void Game::controlarMenuMuerte(sf::Keyboard::Key key){
    switch(key){
        case sf::Keyboard::Up:
            menuMuerte->MoveUp();
            break;
        case sf::Keyboard::Down:
            menuMuerte->MoveDown();
            break;
        case sf::Keyboard::Escape:
            status=2;
            break;
        case sf::Keyboard::Return:
            switch(menuMuerte->GetPressedItem()){
                case 0:
                    std::cout<<"jugar"<<std::endl;
                    status = 0;
                    muerto = false;
                break;
                case 1:
                    std::cout<<"tienda"<<std::endl;
                    status = 2;
                    muerto = false;
                break;
                case 2:
                    std::cout<<"Salir"<<std::endl;
                    window->close();
                break;
            }
            break;
            
    }
}

void Game::controlarMenus(sf::Keyboard::Key key){
    switch(key){
        case sf::Keyboard::Up:
            menu->MoveUp();
            break;
        case sf::Keyboard::Down:
            menu->MoveDown();
            break;
        case sf::Keyboard::Return:
            switch(menu->GetPressedItem()){
                case 0:
                    std::cout<<"jugar"<<std::endl;
                    status = 0;
                break;
                case 1:
                    std::cout<<"tienda"<<std::endl;
                    status = 1;
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
    
    /*for(int i=0; i<cantidadBloques; i++){
        std::cout<<"Nombre: "<<nombreBloques[i]<<std::endl;
    }*/
    
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
            //Actualizamos la posicion de las barras
            Hud* nuevo= robot->getHud();
            barrasVida[i]=*nuevo->getVida(i);
             
            window->draw(barrasVida[i]);//Pintamos barras
        }
        piezas[i] = hud->getPieza(i); //Actualizamos la posicion de los sprites del esquema
        window->draw(piezas[i]); //Pintamos sprite del esquema
    }
}