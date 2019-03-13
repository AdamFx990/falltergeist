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
    // Cache of calculated verticle offset values for UI elements.
    int _vertUiOffsets[_skillCount];
    Point _viewCentre;
    UI::Image* _background = new Image("art/intrface/skldxbox.frm");

    SKILL getSkillByIndex(int i) const;
    void initButtons();
    void initCounters();
    void initLabels();
};
}
}
#endif // FALLTERGEIST_STATE_SKILLDEX_H
