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

#ifndef FALLTERGEIST_STATE_SKILLDEX_H
#define FALLTERGEIST_STATE_SKILLDEX_H

// C++ standard includes

// Falltergeist includes
#include "../../Format/Enums.h"
#include "../../State/State.h"
#include "../../State/Menus/Menu.h"
#include "../../UI/ImageButton.h"
#include "../../UI/TextArea.h"
#include "../../UI/BigCounter.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

class Skilldex : public Menu
{
public:
    Skilldex();
    ~Skilldex() override;

    void init() override;

    void setPosition() override;

    void onKeyDown(Event::Keyboard* event) override;
    void onStateActivate(Event::State* event) override;

private:
    // The number of skills in the skilldex
    static const int _skillCount = 8;
    // Vertical offset modifier for UI elements
    static const int _vertMod = 36;

    Point _origin;
    
    SKILL skillByIndex(const int i) const;
    
    // Initalise a skilldex counter
    inline UI::BigCounter* initCounter(const int x, const int y) const
    { return new UI::BigCounter(x, y, 3); }

    void initSkillButtons (const int x, const int y);
    void initSkillCounters(const int x, const int y);

    void onCancelButtonClick();
    void onButtonClick(SKILL skill);
};

} // State
} // Falltergeist

#endif // FALLTERGEIST_STATE_SKILLDEX_H
