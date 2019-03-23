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
Skilldex::Skilldex() : Menu()
{
    // Get skill names from fallout data files
    for(int i = 0; i < _skillCount; i++)
    {
        _skillText[i] =  _t(MSG_SKILLDEX, i + 102);
    }
}
// dtor
Skilldex::~Skilldex() {}

// Returns a skill based on where it appears in the skilldex
SKILL Skilldex::skillByIndex(int i) const
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
    // Offset applied to the labels' origin
    const Point labelOffset(3, 8);
    // The texture the buttons will use
    const ImageButton::Type btnType = ImageButton::Type::SKILLDEX;

    for (int i = 0; i < _skillCount; i++)
    {
        createLabelledButton(Point(x, y + (_vertMod * i)),
            labelOffset, _skillText[i], btnType, std::bind(
                &Skilldex::onSkillButtonClick, this, skillByIndex(i)));
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

// Initalise the skilldex UI
void Skilldex::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(false);
    // Initalise the skilldex background and position.
    setPosition();

    // Initalise skills UI
    initSkillButtons(_origin.x() + 14, _origin.y() + 44);
    initSkillCounters(_origin.x() + 111, _origin.y() + 48);
    // Initalise the title label (MSG_SKILLDEX, 100)
    TextArea* title = createCentredLabel(
        Point(_origin.x() + 56, _origin.y() + 14), "Skilldex");
    title->setWidth(76);
    addUI(title);
    // Initalise the cancel button
    addUI(createButton(Point(_origin.x() + 48, _origin.y() + 338), ImageButton
        ::Type::SMALL_RED_CIRCLE, std::bind(&Skilldex::onCancelButtonClick, this)));
    // Label the cancel button (MSG_SKILLDEX, 101)
    addUI(createLabel(Point(_origin.x() + 70, _origin.y() + 337), "Cancel",
        TextArea::VerticalAlign::CENTER, TextArea::HorizontalAlign::LEFT));
}

// Calculate the origin on the skilldex and add the background image
void Skilldex::setPosition()
{
    // Initalise background
    auto rendSize   = Game::getInstance()->renderer()->size();
    auto background = createBackground("art/intrface/skldxbox.frm");    
    // calculate the origin of the background
    const int x = (rendSize.width() + 640 - 2 * background->size().width()) / 2;
    const int y = (rendSize.height() - 480 + 6);
    background->setPosition({x, y});
    // set origin to the calculated background position
    _origin = background->position();

    addUI(background);
}

void Skilldex::onCancelButtonClick()
{
    Game::getInstance()->mouse()->popState();
    Game::getInstance()->popState();
}

void Skilldex::onKeyDown(Event::Keyboard* event)
{
    if (event->keyCode() == SDLK_ESCAPE) onCancelButtonClick();
}

void Skilldex::onStateActivate(Event::State* event)
{
    Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
}

void Skilldex::onSkillButtonClick(SKILL skill)
{
    Game::getInstance()->locationState()->setSkillInUse(skill);
    auto mouse = Game::getInstance()->mouse();
    mouse->popState();
    mouse->setState(Input::Mouse::Cursor::USE);
    Game::getInstance()->popState();
}

} // State
} // Falltergeist
