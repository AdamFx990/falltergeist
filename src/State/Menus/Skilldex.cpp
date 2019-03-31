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
#include "../../State/Menus/Skilldex.h"

// C++ standard includes

// Falltergeist includes
#include "../../functions.h"
#include "../../Game/DudeObject.h"
#include "../../Game/Game.h"
#include "../../Graphics/Point.h"
#include "../../Graphics/Renderer.h"
#include "../../Input/Mouse.h"
#include "../../Logger.h"
#include "../../ResourceManager.h"
#include "../../State/ExitConfirm.h"
#include "../../State/Location.h"
#include "../../State/SettingsMenu.h"
#include "../../UI/Image.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

using namespace UI;

// ctor
Skilldex::Skilldex() : Menu() {}
// dtor
Skilldex::~Skilldex() {}

// Initalise the skilldex UI
void Skilldex::init()
{
    if(isInitalised()) return;
    setFullscreen(false);
    // Initalise background
    const Point rendSize = Game::getInstance()->renderer()->size();
    Image* background = new Image("art/intrface/skldxbox.frm");    
    // calculate the origin of the background
    const int x = (rendSize.x() + 640 - 2 * background->size().width()) / 2;
    const int y = (rendSize.y() - 480 + 6);
    background->setPosition({x, y});
    addUI(background);

    // Initalise skills UI
    initSkillButtons(x + 14, y + 44);
    initSkillCounters(x + 111, y + 48);
    
    // Initalise the title label
    std::string text = _t(MSG_TYPE::MSG_SKILLDEX, 100); // "Skilldex"
    Point pos = Point(x + 56, y + 14);
    TextArea* title = createLabel(pos, text);
    title->setWidth(76);
    addUI(title);

    // Initalise the cancel button
    text = _t(MSG_TYPE::MSG_SKILLDEX, 101); // "Cancel"
    const auto ha = TextArea::HorizontalAlign::LEFT;
    const auto event = std::bind(&Skilldex::onCancelButtonClick, this);
    createLabelledButton(Point(x + 48, y + 338), Point(22, -1), text, ha, event);
}

void Skilldex::onKeyDown(Event::Keyboard* event)
{
    if (event->keyCode() == SDLK_ESCAPE) onCancelButtonClick();
}

void Skilldex::onStateActivate(Event::State* event)
{
    Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
}


// Returns a skill based on where it appears in the skilldex
SKILL Skilldex::skillByIndex(const int i) const
{
    switch (i)
    {
        case 0: return SKILL::SNEAK;
        case 1: return SKILL::LOCKPICK;
        case 2: return SKILL::STEAL;
        case 3: return SKILL::TRAPS;
        case 4: return SKILL::FIRST_AID;
        case 5: return SKILL::DOCTOR;
        case 6: return SKILL::SCIENCE;
        case 7: return SKILL::REPAIR;
    }
    return SKILL::NONE;
}


// Initalises all skills' buttons and their labels
void Skilldex::initSkillButtons(const int x, const int y)
{
    const Point lblOffset(3, 8);
    const ImageButton::Type btnType = ImageButton::Type::SKILLDEX;
    for (int i = 0; i < _skillCount; i++)
    {
        const Point pos = Point(x, y + (_vertMod * i));
        const std::string text = _t(MSG_TYPE::MSG_SKILLDEX, 102 + i);
        const auto event = std::bind(&Skilldex::onButtonClick, this, skillByIndex(i));

        createLabelledButton(pos, lblOffset, text, btnType, event);
    }
}

// Initalises all the skilldex counters
void Skilldex::initSkillCounters(const int x, const int y)
{
    for (int i = 0; i < _skillCount; i++)
    {
        auto counter = initCounter(x, y + (_vertMod * i));
        counter->setNumber(Game::getInstance()->
            player()->skillValue(skillByIndex(i)));
        addUI(counter);
    }
}

// Activates the skill that's been clicked
void Skilldex::onButtonClick(SKILL skill)
{
    Game::getInstance()->locationState()->setSkillInUse(skill);
    auto mouse = Game::getInstance()->mouse();
    mouse->popState();
    mouse->setState(Input::Mouse::Cursor::USE);
    Game::getInstance()->popState();
}

// Closes the skilldex and reverts the cursor to its previous state
void Skilldex::onCancelButtonClick()
{
    popMouseState();
    popState();
}

} // State
} // Falltergeist
