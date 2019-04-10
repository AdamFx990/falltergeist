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
#include "../../State/Menus/GameMenu.h"

// C++ standard includes

// Falltergeist includes
#include "../../Audio/Mixer.h"
#include "../../functions.h"
#include "../../Game/Game.h"
#include "../../Graphics/Renderer.h"
#include "../../Input/Mouse.h"
#include "../../ResourceManager.h"
#include "../../State/Menus/ExitConfirm.h"
#include "../../State/Menus/LoadGame.h"
#include "../../State/Location.h"
#include "../../State/SaveGame.h"
#include "../../State/SettingsMenu.h"
#include "../../UI/Image.h"
#include "../../UI/ImageButton.h"
#include "../../UI/PlayerPanel.h"
#include "../../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace State
{
using namespace UI;

// ctor
GameMenu::GameMenu() : Menu() {}
// dtor
GameMenu::~GameMenu() {}

void GameMenu::init()
{
    if (isInitalised()) return;
    setFullscreen(false);

    // background
    const Point rendSize = Game::getInstance()->renderer()->size();
    const auto background = new Image("art/intrface/opbase.frm");
    const auto panelHeight = Game::getInstance()->locationState()->playerPanel()->size().height();
    const auto bgPos = (rendSize - background->size() - Point(0, panelHeight)) / 2;
    background->setPosition(bgPos);
    addUI(background);

    // Labelled buttons
    setFont("font3.aaf", {0xb8, 0x9c, 0x28, 0xff});

    const int x = bgPos.x();
    const int y = bgPos.y();
    const int lblWidth = 150;
    const int vertOffset = 37;
    const Point lblOffset = Point(-6, 8);
    const auto sprite = ImageButton::Type::OPTIONS;

    for (int i = 0; i < 5; i++)
    {
        const std::string text = _t(MSG_OPTIONS, i);
        const Point origin(x + 14, y + 18 + (vertOffset * i));
        const auto func = std::bind(&GameMenu::onClick, this, i);
        createLabelledButton(origin, lblOffset, lblWidth, text, sprite, func);
    }
}

void GameMenu::onStateActivate(Event::State* event)
{
    setMouseState(Input::Mouse::Cursor::BIG_ARROW);
}

void GameMenu::onStateDeactivate(Event::State* event)
{
    popMouseState();
}

void GameMenu::onKeyDown(Event::Keyboard* event)
{
    switch (event->keyCode())
    {
        case SDLK_ESCAPE:
        case SDLK_d:
            closeMenu();
            break;
        case SDLK_s:
            pushState(new SaveGame());
            break;
        case SDLK_l:
            pushState(new LoadGame());
            break;
        case SDLK_p:
            pushState(new SettingsMenu());
            break;
        case SDLK_e:
            pushState(new ExitConfirm());
            break;
    }
}

void GameMenu::onClick(const int i)
{
    switch (i)
    {
        case 0:
            pushState(new SaveGame());
            break;
        case 1:
            pushState(new LoadGame());
            break;
        case 2:
            pushState(new SettingsMenu());
            break;
        case 3:
            pushState(new ExitConfirm());
            break;
        case 4:
            closeMenu();
            break;
    }
}

} // State
} // Falltergeist
