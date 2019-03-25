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

#ifndef FALLTERGEIST_STATE_MAINMENU_H
#define FALLTERGEIST_STATE_MAINMENU_H

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../../State/Menus/Menu.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

class MainMenu : public Menu
{
public:
    MainMenu();
    ~MainMenu() override;

protected:
    void init() override;

    void onStateActivate(Event::State* event) override;
    void onKeyDown(Event::Keyboard* event) override;

private:
    // The total number of menu items
    const int _entryCount = 6;

    void onButtonClick(const int i);

    void onExitButtonClick(Event::Mouse* event);
    void onNewGameButtonClick(Event::Mouse* event);
    void onSettingsButtonClick(Event::Mouse* event);

    inline void doIntro()
    { fadeOutFor(std::bind(&MainMenu::onIntro, this)); };
    inline void doExit()
    { fadeOutFor(std::bind(&MainMenu::onExit, this)); };

    void onIntro();
    void onExit();
};

} // State
} // Falltergeist

#endif // FALLTERGEIST_STATE_MAINMENU_H
