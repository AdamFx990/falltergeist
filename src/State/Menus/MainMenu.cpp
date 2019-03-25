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
    const auto btnType = ImageButton::Type::MENU_RED_CIRCLE;
    const char* text[] = { 
        "INTRO",
        "NEW GAME",
        "LOAD GAME",
        "OPTIONS",
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
    Game::getInstance()->mixer()->playACMMusic("07desert.acm", true);
    Game::getInstance()->renderer()->fadeIn(0, 0, 0, 1000);
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
            pushState(new NewGame());
            break;
        case 2:
            pushState(new LoadGame());
            break;
        case 3:
            pushState(new SettingsMenu());
            break;
        case 4:
            pushState(new Credits());
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
            pushState(new NewGame());
            break;
        case SDLK_l: // L
            pushState(new LoadGame());
            break;
        case SDLK_o: // O
            Game::getInstance()->pushState(new SettingsMenu());
            break;
        case SDLK_c: // C
            pushState(new Credits());
            break;
        case SDLK_e: // E
        case SDLK_ESCAPE:
            doExit();
            break;
    }
}

void MainMenu::onIntro()
{
    fadeDoneHandler().clear();
    Game::getInstance()->pushState(new Movie(17));
    Game::getInstance()->pushState(new Movie(1));
}

void MainMenu::onExit()
{
    fadeDoneHandler().clear();
    Game::getInstance()->mixer()->stopMusic();
    Game::getInstance()->quit();
}

} // State
} // Falltergeist
