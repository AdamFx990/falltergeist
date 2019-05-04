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
#include "../../State/Menus/NewGame.h"

// C++ standard includes
#include <sstream>
#include <memory>

// Falltergeist includes
#include "../../Event/State.h"
#include "../../functions.h"
#include "../../Format/Bio/File.h"
#include "../../Game/DudeObject.h"
#include "../../Game/Game.h"
#include "../../Graphics/Renderer.h"
#include "../../Helpers/StateLocationHelper.h"
#include "../../Helpers/EnumHelper.h"
#include "../../ResourceManager.h"
#include "../../State/Location.h"
#include "../../State/PlayerCreate.h"
#include "../../UI/Image.h"
#include "../../UI/ImageButton.h"
#include "../../UI/ImageList.h"
#include "../../UI/TextArea.h"


// Third party includes

namespace Falltergeist
{
using Helpers::StateLocationHelper;

namespace State
{
// ctor
NewGame::NewGame() : Menu() {}
// dtor
NewGame::~NewGame() {}

void NewGame::init()
{
    if (isInitalised()) return;
    setModal(true);
    addUI("background", createBackground("art/intrface/pickchar.frm"));
    // Red circle buttons
    const auto sprite = UI::ImageButton::Type::SMALL_RED_CIRCLE;
    addUI(createButton(Point( 81, 322), sprite, std::bind(&NewGame::doBegin,  this)));
    addUI(createButton(Point(436, 319), sprite, std::bind(&NewGame::doEdit,   this)));
    addUI(createButton(Point( 81, 424), sprite, std::bind(&NewGame::doCreate, this)));
    addUI(createButton(Point(461, 424), sprite, std::bind(&NewGame::doBack,   this)));
    // Left & right arrow buttons
    addUI(createButton(Point(292, 320), UI::ImageButton::Type::LEFT_ARROW , std::bind(&NewGame::doPrev, this)));
    addUI(createButton(Point(318, 320), UI::ImageButton::Type::RIGHT_ARROW, std::bind(&NewGame::doNext, this)));

    addUI("images", new UI::ImageList({ "art/intrface/combat.frm",
                                        "art/intrface/stealth.frm",
                                        "art/intrface/diplomat.frm" }, 27, 23));

    addUI("name", new UI::TextArea(300, 40));
    // Right alligned SPECIAL text area
    addUI("special_left", new UI::TextArea(0, 70));
    getTextArea("special_left")->setWidth(362);
    getTextArea("special_left")->setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);
    // Left alligned SPECIAL text area
    addUI("special_right", new UI::TextArea(367, 70));
    // Character bio
    addUI("bio", new UI::TextArea(437, 40));
    // Stats, skills & traits.
    addUI("stats", new UI::TextArea(294, 150));
    getTextArea("stats")->setWidth(85);
    getTextArea("stats")->setHorizontalAlign(UI::TextArea::HorizontalAlign::RIGHT);
    addUI("stats_values", new UI::TextArea(383, 150));
}

void NewGame::think()
{
    State::think();
}

void NewGame::doBegin()
{
    Game::getInstance()->setPlayer(std::move(_characters.at(_selectedCharacter)));
    _characters.clear();

    StateLocationHelper stateLocationHelper;
    Game::getInstance()->setState(stateLocationHelper.getInitialLocationState());
}

void NewGame::doEdit()
{
    Game::getInstance()->setPlayer(std::move(_characters.at(_selectedCharacter)));
    _characters.clear();
    Game::getInstance()->pushState(new PlayerCreate());
}

void NewGame::doCreate()
{
    auto none = std::make_unique<Game::DudeObject>();
    none->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/blank.gcd"));
    Game::getInstance()->setPlayer(std::move(none));
    Game::getInstance()->pushState(new PlayerCreate());
}

void NewGame::doBack()
{
    fadeDoneHandler().clear();
    fadeDoneHandler().add(std::bind(&NewGame::onBackFadeDone, this));
    Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
}

void NewGame::doNext()
{
    if (_selectedCharacter < 2)
    {
        _selectedCharacter++;
    }
    else
    {
        _selectedCharacter = 0;
    }
    _changeCharacter();
}

void NewGame::doPrev()
{
    if (_selectedCharacter > 0)
    {
        _selectedCharacter--;
    }
    else
    {
        _selectedCharacter = 2;
    }
    _changeCharacter();
}

void NewGame::onBackFadeDone()
{
    fadeDoneHandler().clear();
    Game::getInstance()->popState();
}


void NewGame::_changeCharacter()
{
    using namespace Helpers;
    auto& dude = _characters.at(_selectedCharacter);

    std::string special_left  = "";
    std::string special_right = "";
    for (int i = 0; i < 7; i++)
    {
        const int stat = dude->stat(EnumHelper::intToStat(i));
        special_left += _t(MSG_STATS, 100 + i)  // Stat name
                     + (stat < 10 ? " 0" : " ") // Whether to perfix a '0'
                     + std::to_string(stat) + "\n";
        special_right += _t(MSG_STATS, stat + 300) + "\n"; // e.g. GREAT
    }
    getTextArea("special_left" )->setText(special_left );
    getTextArea("special_right")->setText(special_right);

    getTextArea("bio")->setText(dude->biography());
    getTextArea("name")->setText(dude->name());
    getImageList("images")->setCurrentImage(_selectedCharacter);

    std::string stats = _t(MSG_MISC,   16) + "\n"  // Hit Points
                      + _t(MSG_STATS, 109) + "\n"  // Armour Class
                      + _t(MSG_MISC,   15) + "\n"  // Action Points
                      + _t(MSG_STATS, 111) + "\n"; // Melee Damage

    std::string stats_values = std::to_string(dude->hitPointsMax()) + "/"
                             + std::to_string(dude->hitPointsMax()) + "\n"
                             + std::to_string(dude->armorClass())   + "\n"
                             + std::to_string(dude->actionPoints()) + "\n"
                             + std::to_string(dude->meleeDamage())  + "\n";

    for (int i = EnumHelper::skillToInt(SKILL::SMALL_GUNS); i <= EnumHelper::skillToInt(SKILL::OUTDOORSMAN); i++)
    {
        if (dude->skillTagged(EnumHelper::intToSkill(i)))
        {
            stats += "\n" + _t(MSG_SKILLS, 100 + i);
            stats_values += "\n" + std::to_string(dude->skillValue(EnumHelper::intToSkill(i))) + "%";
        }
    }
    for (int i = EnumHelper::traitToInt(TRAIT::FAST_METABOLISM); i <= EnumHelper::traitToInt(TRAIT::GIFTED); i++)
    {
        if (dude->traitTagged(EnumHelper::intToTrait(i)))
        {
            stats += "\n" + _t(MSG_TRAITS, 100 + i);
        }
    }
    getTextArea("stats")->setText(stats);
    getTextArea("stats_values")->setText(stats_values);
}

void NewGame::onKeyDown(Event::Keyboard* event)
{
    switch (event->keyCode())
    {
        case SDLK_ESCAPE:
        case SDLK_b:
            doBack();
            break;
        case SDLK_t:
            doBegin();
            break;
        case SDLK_c:
            doCreate();
            break;
        case SDLK_m:
            doEdit();
            break;
        case SDLK_LEFT:
            doPrev();
            break;
        case SDLK_RIGHT:
            doNext();
            break;
    }
}

void NewGame::onStateActivate(Event::State* event)
{
    auto combat = std::make_unique<Game::DudeObject>();
    combat->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/combat.gcd"));
    combat->setBiography(ResourceManager::getInstance()->bioFileType("premade/combat.bio")->text());
    _characters.emplace_back(std::move(combat));

    auto stealth = std::make_unique<Game::DudeObject>();
    stealth->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/stealth.gcd"));
    stealth->setBiography(ResourceManager::getInstance()->bioFileType("premade/stealth.bio")->text());
    _characters.emplace_back(std::move(stealth));

    auto diplomat = std::make_unique<Game::DudeObject>();
    diplomat->loadFromGCDFile(ResourceManager::getInstance()->gcdFileType("premade/diplomat.gcd"));
    diplomat->setBiography(ResourceManager::getInstance()->bioFileType("premade/diplomat.bio")->text());
    _characters.emplace_back(std::move(diplomat));

    _changeCharacter();

    Game::getInstance()->renderer()->fadeIn(0,0,0,1000);
}

} // State
} // Falltergeist
