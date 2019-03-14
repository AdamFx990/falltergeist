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
#include "../Format/Enums.h"
#include "../State/State.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

class Skilldex : public State
{
public:
    Skilldex();
    ~Skilldex() override;

    void init() override;

    void onKeyDown(Event::Keyboard* event) override;
    void onStateActivate(Event::State* event) override;

    void onCancelButtonClick();
    void onSkillButtonClick(SKILL skill);

private:
    // The number of skills in the skilldex
    static const int _skillCount = 8;
    // Vertical offset modifier for UI elements
    static const int _vertMod = 36;
    
    SKILL skillByIndex(int i) const;
    
    // Initalise a skilldex counter
    inline BigCounter* initCounter(const int x, const int y) const
    { return new BigCounter(x, y); }

    TextArea* initLabel(const int x, const int y, const int msg, const bool centred = true) const;
    ImageButton* initSkillButton(const int x, const int y, const int skill);

    void initSkillButtons (const int x, const int y);
    void initSkillCounters(const int x, const int y);
};
}
}
#endif // FALLTERGEIST_STATE_SKILLDEX_H
