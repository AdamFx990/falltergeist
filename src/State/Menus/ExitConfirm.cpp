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
#include "../../State/Menus/ExitConfirm.h"

// C++ standard includes

// Falltergeist includes
#include "../../functions.h"
#include "../../Game/Game.h"
#include "../../Graphics/Renderer.h"
#include "../../Input/Mouse.h"
#include "../../ResourceManager.h"
#include "../../State/Location.h"
#include "../../State/Menus/MainMenu.h"
#include "../../UI/Image.h"
#include "../../UI/ImageButton.h"
#include "../../UI/PlayerPanel.h"
#include "../../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace State
{
// ctor
ExitConfirm::ExitConfirm() : Menu() {}
// dtor
ExitConfirm::~ExitConfirm() {}

void ExitConfirm::init()
{
    if (isInitalised()) return;
    setFullscreen(false);

    auto background = new UI::Image("art/intrface/lgdialog.frm");
    auto panelHeight = Game::getInstance()->locationState()->playerPanel()->size().height();
    auto bgPos = (Game::getInstance()->renderer()->size() - background->size() - Point(0, panelHeight)) / 2;
    background->setPosition(bgPos);
    addUI(background);

    for (unsigned i = 0; i < 2; i++)
    {
        const unsigned xOffset = 122;
        Point origin = bgPos + Point(38 + (xOffset * i), 98);
        createDoneButton(origin, i);
    }

    // label: Are you sure you want to quit?
    auto quitLabel = new UI::TextArea(_t(MSG_MISC, 0), bgPos + Point(30, 52));
    quitLabel->setFont("font1.aaf", {0xb8,0x9c, 0x28, 0xff});
    quitLabel->setSize({244, 0});
    quitLabel->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);

    addUI(quitLabel);
}

void ExitConfirm::onKeyDown(Event::Keyboard* event)
{
    switch (event->keyCode())
    {
        case SDLK_ESCAPE:
        case SDLK_n:
            doNo();
            break;
        case SDLK_RETURN:
        case SDLK_y:
            doYes();
            break;
    }
}

void ExitConfirm::onStateActivate(Event::State* event)
{
    Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
}

void ExitConfirm::onStateDeactivate(Event::State* event)
{
    Game::getInstance()->mouse()->popState();
}

void ExitConfirm::createDoneButton(Point &origin, unsigned index)
{
    auto box = new UI::Image("art/intrface/donebox.frm");
    box->setPosition(origin);
    addUI(box);

    origin += Point(12, 4);
    auto func = std::bind(&ExitConfirm::onClick, this, index);
    const std::string text = _t(MSG_DIALOG_BOX, (101 + index));
    setFont("font3.aff", {0xb8, 0x9c, 0x28, 0xff});
    createLabelledButton(origin, Point(36, 3), text, UI::ImageButton::Type::SMALL_RED_CIRCLE, func);
}

void ExitConfirm::onClick(const unsigned i)
{
    switch (i)
    {
        case 0:
            doYes();
            break;
        case 1:
            doNo();
            break;
    }
}

void ExitConfirm::doYes()
{
    Game::getInstance()->setState(new MainMenu());
}

} // State
} // Falltergeist
