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
#include "../State/Skilldex.h"

// C++ standard includes

// Falltergeist includes
#include "../functions.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Point.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../State/ExitConfirm.h"
#include "../State/Location.h"
#include "../State/SettingsMenu.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
namespace State
{
using namespace UI;
// ctor
Skilldex::Skilldex() : State() {}
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

// Initalise a skilldex label
TextArea* Skilldex::initLabel(const int x, const int y, const int msg, const bool centred)
{
    const SDL_Color col = { 0xb8, 0x9c, 0x28, 0xff };
    const std::string font = "font3.aff";
    // TODO: Cache message text to reduce unecessary disk IO.
    auto label =  new TextArea(_t(MSG_SKILLDEX, msg), x, y);
    label->setFont(font, col);
    if (centred)
    {
        label->setHorizontalAlign(TextArea::HorizontalAlign::CENTER);
    }
    return label;
}

// Initalise a skilldex button
ImageButton* Skilldex::initSkillButton(const int x, const int y, const int skill)
{
    auto button = new ImageButton(
        ImageButton::Type::SKILLDEX_BUTTON, x, y
    );
    button->mouseClickHandler().add(std::bind(
        &Skilldex::onSkillButtonClick, this, skillByIndex(skill)
    ));
    return button;
}

// Initalises all skills' buttons and their labels
void Skilldex::initSkillButtons(const int x, const int y)
{
    // Offset the label's origin so it appears inside the button
    const int lx = x + 3; const int ly = y + 8;
    for (int i = 0; i < _skillCount; i++)
    {
        // Buttons
        auto button = initSkillButton(
            x, y + (_vertMod * i), i
        );
        addUI(button);
        // Labels
        auto label = initLabel(
            lx, (ly + (_vertMod * i)), (i + 102), true
        );
        label->setWidth(84);
        addUI(label);
    }
}

// Initalises all the skilldex counters
void Skilldex::initSkillCounters(const int x, const int y)
{
    for (int i = 0; i < _skillCount; i++)
    {
        auto counter = initCounter(x, y + (_vertMod * i));
        counter->setNumber(Game::getInstance()->
            player()->skillValue(skillByIndex(i))
        );
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
    // Initalise background
    auto rendSize = Game::getInstance()->renderer()->size();
    auto background = new Image("art/intrface/skldxbox.frm");
    // calculate the origin of the background
    const int x = (rendSize.width() + 640 - 2 * background->size().width()) / 2;
    const int y = (rendSize.height() - 480 + 6);
    background->setPosition({ x, y });
    addUI(background);
    // Initalise skills UI
    initSkillButtons((x + 14), (y + 44));
    initSkillCounters((x + 111), (y + 48));
    // Initalise the title
    auto title = initLabel(x + 56, y + 14, 100, true);
    title->setWidth(76);
    addUI(title);
    // Initalise the cancel button
    auto cancelButton = new ImageButton(
        ImageButton::Type::SMALL_RED_CIRCLE, (x + 48), (y + 338)
    );
    cancelButton->mouseClickHandler().add(
        std::bind(&Skilldex::onCancelButtonClick, this)
    );
    addUI(cancelButton);
    // Label the cancel button
    addUI(initLabel((x + 70), (y + 337), 101, false));
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

}
}
