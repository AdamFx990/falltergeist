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
#ifndef FALLTERGEIST_STATE_MENU_H
#define FALLTERGEIST_STATE_MENU_H

// C++ standard includes
#include <functional>

// Falltergeist includes
#include "../../State/State.h"
#include "../../UI/ImageButton.h"
#include "../../UI/TextArea.h"
#include "../../UI/Image.h"
#include "../../Graphics/Point.h"
#include "../../Event/Mouse.h"
#include "../../Base/Delegate.h"

// Third party includes

namespace Falltergeist
{
namespace State
{
using namespace UI;

class Menu : public State
{
public:
    // ctor
    Menu();

    // Automatically place a fullscreen menu in the centre of the renderer
    inline void centreMenu() // TODO: remove hardcoded values
    { setPosition((Game::getInstance()->renderer()->size() - Point(640, 480)) / 2); }

    TextArea* createLabel (const Point origin,
        const std::string* text, const TextArea::HorizontalAlign alignment);
    ImageButton* createButton(const Point origin,
        const ImageButton::Type type, std::function<void(Event::Mouse*)> onClick);
    void createLabelledButton(Point origin, const Point labelOffset,
        const std::string* text, const ImageButton::Type type, std::function<void(Event::Mouse*)> onClick);

};

} // State
} // Falltergeist
#endif // FALLTERGEIST_STATE_MENU_H