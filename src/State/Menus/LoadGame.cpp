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
#include "../../State/Menus/LoadGame.h"

// C++ standard includes
#include <sstream>

// Falltergeist includes
#include "../../Event/Event.h"
#include "../../Event/Mouse.h"
#include "../../Event/State.h"
#include "../../functions.h"
#include "../../Game/Game.h"
#include "../../Graphics/Point.h"
#include "../../Graphics/Renderer.h"
#include "../../Input/Mouse.h"
#include "../../ResourceManager.h"
#include "../../State/State.h"
#include "../../UI/Image.h"
#include "../../UI/ImageButton.h"
#include "../../UI/ImageList.h"
#include "../../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

// ctor
LoadGame::LoadGame() : Menu() 
{
    _fromMainMenu = !Game::getInstance()->locationState();
}
// dtor
LoadGame::~LoadGame() {}

void LoadGame::init()
{
    if (isInitalised()) return;
    setFullscreen(true);
    // Background
    addUI("background", createBackground("art/intrface/lsgame.frm"));
    setFont("font3.aaf", { 0x90, 0x78, 0x24, 0xff });
    // Buttons
    const Point lblOffset = Point(19, -1);
    const auto ha = TextArea::HorizontalAlign::LEFT;
    // Arrow buttons
    const auto arrows = createUpDownArrows(Point(35, 58));
    addUI("button_up", arrows[0]);
    addUI("button_down", arrows[1]);
    // Done button
    Point pos(391, 349);
    std::string text = _t(MSG_OPTIONS, 300);
    createLabelledButton(pos, lblOffset, text, ha, std::bind(&LoadGame::popState, this));
    // Cancel button
    pos.setX(495);
    text = _t(MSG_OPTIONS, 121);
    createLabelledButton(pos, lblOffset, text, ha, std::bind(&LoadGame::doCancel, this));
    // Load Game title label
    pos = Point(48, 27);
    text = _t(MSG_LOAD_SAVE, 110);
    addUI(createLabel(pos, text));
}

void LoadGame::doCancel()
{
    if (_fromMainMenu)
    {
        fadeOutFor(std::bind(&LoadGame::popState, this), 255, 255, 255);
    }
    else 
    {
        popState();
    }
}

void LoadGame::onStateActivate(Event::State* event)
{
    // Fade in if loaded from main menu
    if (_fromMainMenu) fadeIn(0, 0, 0);
    Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
}

void LoadGame::onStateDeactivate(Event::State* event)
{
    Game::getInstance()->mouse()->popState();
}

void LoadGame::onKeyDown(Event::Keyboard* event)
{
    switch (event->keyCode())
    {
        case SDLK_ESCAPE:
            doCancel();
            break;
    }
}

} // State
} // Falltergeist
