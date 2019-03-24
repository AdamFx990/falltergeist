/*
 * Copyright 2012-2018 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

// Related headers
#include "../../State/Menus/MainMenu.h"

// C++ standard includes
#include <sstream>
#include <functional>

// Falltergeist includes
#include "../../Audio/Mixer.h"
#include "../../Event/State.h"
#include "../../functions.h"
#include "../../Game/Game.h"
#include "../../Graphics/Renderer.h"
#include "../../Graphics/Point.h"
#include "../../Input/Mouse.h"
#include "../../Logger.h"
#include "../../ResourceManager.h"
#include "../../State/Credits.h"
#include "../../State/LoadGame.h"
#include "../../State/Movie.h"
#include "../../State/NewGame.h"
#include "../../State/SettingsMenu.h"
#include "../../UI/Animation.h"
#include "../../UI/Image.h"
#include "../../UI/ImageButton.h"
#include "../../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

// ctor
MainMenu::MainMenu() : Menu() {}
// dtor
MainMenu::~MainMenu()
{
    Game::getInstance()->mixer()->stopMusic();
}

void MainMenu::init()
{
    using namespace UI;

    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(true);

    setPosition();
    addUI("background", createBackground("art/intrface/mainmenu.frm"));
    setFont("font4.aaf", { 0xb8, 0x9c, 0x28, 0xff });
    // Constants for UI elements
    const int vertMod = 41;
    const int lblWidth = 150;
    const Point origin(30, 19);
    const Point lblOffset(20, 1);
    const ImageButton::Type btnType = ImageButton::Type::MENU_RED_CIRCLE;
    const char* text[] = { 
        "INTRO",
        "NEW GAME",
        "LOAD GAME",
        "SETTINGS",
        "CREDITS",
        "EXIT"
    };
    // Initalise Menu buttons and text
    for (int i = 0; i < _entryCount; i++)
    {
        const Point pos = Point(origin.x(), origin.y() + vertMod * i);
        const auto event = std::bind(&MainMenu::onButtonClick, this, i);
        createLabelledButton(pos, lblOffset, lblWidth, text[i], btnType, event);
    }
}

void MainMenu::onStateActivate(Event::State* event)
{
    Game::getInstance()->mouse()->setState(Input::Mouse::Cursor::BIG_ARROW);
    Game::getInstance()->mixer()->playACMMusic("07desert.acm",true);
    Game::getInstance()->renderer()->fadeIn(0,0,0,1000);
}

// Triggers an event for the button that is clicked
void MainMenu::onButtonClick(const int i)
{
    switch (i)
    {
        case 0:
            doIntro();
            break;
        case 1:
            doNewGame();
            break;
        case 2:
            doLoadGame();
            break;
        case 3:
            doSettings();
            break;
        case 4:
            doCredits();
            break;
        case 5:
            doExit();
            break;
    }
}

// Triggers an event for the key that is pressed
void MainMenu::onKeyDown(Event::Keyboard* event)
{
    switch (event->keyCode())
    {
        case SDLK_i: // I
            doIntro();
            break;  
        case SDLK_n: // N
            doNewGame();
            break;
        case SDLK_l: // L
            doLoadGame();
            break;
        case SDLK_o: // O
            doSettings();
            break;
        case SDLK_c: // C
            doCredits();
            break;
        case SDLK_e: // E
        case SDLK_ESCAPE:
            doExit();
            break;
    }
}

void MainMenu::doExit()
{
    fadeDoneHandler().clear();
    fadeDoneHandler().add([this](Event::Event* event){ this->onExitStart(dynamic_cast<Event::State*>(event)); });
    Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
}

void MainMenu::doNewGame()
{
    fadeDoneHandler().clear();
    fadeDoneHandler().add([this](Event::Event* event){ this->onNewGameStart(dynamic_cast<Event::State*>(event)); });
    Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
}

void MainMenu::doLoadGame()
{
    fadeDoneHandler().clear();
    fadeDoneHandler().add([this](Event::Event* event){ this->onLoadGameStart(dynamic_cast<Event::State*>(event)); });
    Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
}

void MainMenu::doSettings()
{
    Game::getInstance()->pushState(new SettingsMenu());
}

void MainMenu::doIntro()
{
    fadeDoneHandler().clear();
    fadeDoneHandler().add([this](Event::Event* event){ this->onIntroStart(dynamic_cast<Event::State*>(event)); });
    Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
}

void MainMenu::doCredits()
{
    fadeDoneHandler().clear();
    fadeDoneHandler().add([this](Event::Event* event){ this->onCreditsStart(dynamic_cast<Event::State*>(event)); });
    Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
}


void MainMenu::onExitStart(Event::State* event)
{
    fadeDoneHandler().clear();
    Game::getInstance()->mixer()->stopMusic();
    Game::getInstance()->quit();
}

void MainMenu::onNewGameStart(Event::State* event)
{
    fadeDoneHandler().clear();
    Game::getInstance()->pushState(new NewGame());
}

void MainMenu::onLoadGameStart(Event::State* event)
{
    fadeDoneHandler().clear();
    Game::getInstance()->pushState(new LoadGame());
}

void MainMenu::onIntroStart(Event::State* event)
{
    fadeDoneHandler().clear();
    Game::getInstance()->pushState(new Movie(17));
    Game::getInstance()->pushState(new Movie(1));
}

void MainMenu::onCreditsStart(Event::State* event)
{
    fadeDoneHandler().clear();
    Game::getInstance()->pushState(new Credits());
}

} // State
} // Falltergeist
