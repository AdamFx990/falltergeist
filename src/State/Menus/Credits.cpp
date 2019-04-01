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
#include "../../State/Menus/Credits.h"

// C++ standard includes
#include <sstream>

// Falltergeist includes
#include "../../CrossPlatform.h"
#include "../../Event/Keyboard.h"
#include "../../Event/Mouse.h"
#include "../../Event/State.h"
#include "../../Font.h"
#include "../../Format/Dat/MiscFile.h"
#include "../../Game/Game.h"
#include "../../Graphics/Renderer.h"
#include "../../Input/Mouse.h"
#include "../../ResourceManager.h"
#include "../../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace State
{
using namespace UI;

// ctor
Credits::Credits() : Menu() {}
// dtor
Credits::~Credits() {}

void Credits::init()
{
    if (isInitalised()) return;
    setFullscreen(true);

    setMouseState(Input::Mouse::Cursor::NONE);

    const int targetWidth = 640;
    const auto credits = ResourceManager::getInstance()->miscFileType("text/english/credits.txt");
    const auto renderer = Game::getInstance()->renderer();
    setPosition(Point((renderer->size().width() - targetWidth) / 2, renderer->size().height()));    
    
    std::stringstream ss;
    credits->stream().setPosition(0);
    ss << &credits->stream();
    std::string line;

    int y = 0;
    while (std::getline(ss, line))
    {
        if (line.find('\r') != std::string::npos)
        {
            line.erase(line.find('\r'));
        }
        switch(line[0])
        {
            case '#':
                line.erase(line.begin());
                setFont("font4.aaf", {0x8c, 0x8c, 0x84, 0xFF});
                break;
            case '@':
                line.erase(line.begin());
                setFont("font3.aaf", {0x70, 0x60, 0x50, 0xFF});
                y += 6; // vertical whitespace
                break;
            default:
                if(line.empty()) line = "    "; // horizontal whitespace
                setFont("font4.aaf", {0x90, 0x78, 0x24, 0xFF});
                break;
        }
        auto tx = createLabel(Point(0, y), line);
        tx->setSize({targetWidth, 0});
        tx->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
        addUI(tx);
        _lines.push_back(tx);
        y += tx->textSize().height() + currentFont()->verticalGap();
    }
    _lastTicks = SDL_GetTicks();
}

void Credits::think()
{
    State::think();

    unsigned long int nt = SDL_GetTicks();
    if (nt - _lastTicks > 50)
    {
        _position.ry() -= 1;
        long int _lastY = 0;
        for (auto ui: _lines)
        {
            ui->setY(ui->y() - 1);

            if ((ui->y() > -30) && (ui->y() < Game::getInstance()->renderer()->height() + 10))
            {
                ui->setVisible(true);
            }
            else
            {
                ui->setVisible(false);
            }
            _lastY = ui->y();
        }
        _lastTicks = nt;

        if (_lastY < -30) onCreditsFinished();
    }
}

void Credits::handle(Event::Event* event)
{
    if (event->name() == "keyup" ||
        event->name() == "mouseup") onCreditsFinished();
}

void Credits::onCreditsFadeDone()
{
    fadeClear();
    popMouseState();
    popState();
}

void Credits::onStateActivate(Event::State* event)
{
    fadeIn(0, 0, 0);
}

} // State
} // Falltergeist
