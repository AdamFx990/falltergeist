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
#include "../UI/BigCounter.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace State
{
using namespace UI;

Skilldex::Skilldex() : State()
{
    // original coordinates = 455x6
    Graphics::Size rendSize = Game::getInstance()->renderer()->size();
    // background size = 185x368
    _viewCentre.setX((rendSize.width() + 640 - 2 * _background->size().width()) / 2);
    _viewCentre.setY(rendSize.height() - 480 + 6);
}

Skilldex::~Skilldex() {}

// Returns a skill based on where it appears in the skilldex
SKILL Skilldex::getSkillByIndex(int i) const
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

// Initalise Skilldex buttons and add them to the UI
void Skilldex::initButtons()
{
    // set x & y co-ords to use as a starting point
    const int x = _viewCentre.x + 14; const int y = _viewCentre.y + 44;
    // Initalise skill buttons
    for (int i = 0; i < _skillCount; i++)
    {
        auto button = new ImageButton(
             ImageButton::Type::SKILLDEX_BUTTON, x, y + _vertUiOffsets[i]);
        button->mouseClickHandler().add(
            std::bind(&Skilldex::onSkillButtonClick, this, getSkillByIndex(i)));
        addUI(button);
    }
    // Initalise cancel button
    auto cancelButton = new ImageButton(
         ImageButton::Type::SKILLDEX_BUTTON, _viewCentre.x + 48, _viewCentre.y + 338);
    cancelButton->mouseClickHandler().add(
         std::bind(&Skilldex::onCancelButtonClick, this));
    addUI(cancelButton);
}
// Initalise Skilldex counters and add them to the UI
void Skilldex::initCounters()
{
    // set x & y co-ords to use as a starting point
    const int x = _viewCentre.x + 111; const int y = _viewCentre.y + 48;
    const std::shared_ptr<Game::DudeObject> player = Game::getInstance()->player();
    // Initalise skill counters
    for (int i = 0; i < _skillCount; i++)
    {
        auto counter = new BigCounter(x, y + _vertUiOffsets[i], 3);
        counter->setNumber(player->skillValue(getSkillByIndex(i)));
        addUI(counter);
    }
}
// Initalise Skilldex labels and add them to the UI
void Skilldex::initLabels()
{
    const char* font = "font3.aff";
    const SDL_Color color = { 0xb8, 0x9c, 0x28, 0xff };
    // set x & y co-ords to use as a starting point
    const int x = _viewCentre.x + 17; const int y = _viewCentre.y + 52;
    // Initalise title (100) label
    auto label = new TextArea(_t(MSG_SKILLDEX, 100), _viewCentre.x + 56, _viewCentre.y + 14);
    label->setFont(font, color);
    label->setWidth(76);
    label->setHorizontalAlign(TextArea::HorizontalAlign::CENTER);
    addUI(label);
    // Initalise cancel (101) label
    label = new TextArea(_t(MSG_SKILLDEX, 101), _viewCentre.x + 70, _viewCentre.y + 337);
    label->setFont(font, color);
    addUI(label);
    // Initalise skill labels
    const int iMod = 102 + _skillCount;
    for (int i = 102; i < iMod; i++)
    {
        // TODO: Cache message text to reduce unecessary disk IO.
        label = new TextArea(_t(MSG_SKILLDEX, i), x, y + _vertUiOffsets[i]);
        label->setFont(font, color);
        label->setWidth(84);
        label->setHorizontalAlign(TextArea::HorizontalAlign::CENTER);
        addUI(label);
    }
}

void Skilldex::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(false);
    
    // Vertical offset modifier for skilldex UI items.
    const int offsetMod = 36;
    /* Calculate verticle offset modifier for UI elements ahead of time to *
     * avoid repeating the same calculation for labels, counters & buttons */
    for (int i = 0; i < _skillCount; i++)
    {
        _vertUiOffsets[i] = offsetMod * i;
    }
    
    // Initalise background
    _background->setPosition(_viewCentre);
    addUI(_background);
    // Initalise buttons
    initButtons();
    // Initalise counters
    initCounters();
    // Initalise labels
    initLabels();
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
