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
#include "../../State/Menus/Menu.h"

// C++ standard includes
#include <string>


// Falltergeist includes
#include "../../Game/Game.h"
#include "../../Graphics/Renderer.h"

// Third party includes

namespace Falltergeist
{
namespace State
{
// ctor
Menu::Menu() : State() {}

TextArea* Menu::createLabel(const Point origin,
    const std::string text, const TextArea::HorizontalAlign alignment)
{
    const SDL_Color col = { 0xb8, 0x9c, 0x28, 0xff };
    const std::string font = "font3.aaf";
    TextArea* label = new TextArea(text, origin);
    label->setFont(font, col);
    label->setHorizontalAlign(alignment);
    return label;
}

// Returns a button with a linked event handler
ImageButton* Menu::createButton(const Point origin,
    const ImageButton::Type type, const std::function<void(Event::Mouse*)> onClick)
{
    ImageButton* button = new ImageButton(type, origin);
    button->mouseClickHandler().add(onClick);
    return button;
}

// Creates a button with a centred label and adds it to the UI
void Menu::createLabelledButton(Point origin, 
    const Point labelOffset, const std::string text,
    const ImageButton::Type type, const std::function<void(Event::Mouse*)> onClick)
{
    auto button = createButton(origin, type, onClick);
    // Offset the label's origin so it appears inside the button
    auto label = createLabel(origin + labelOffset, text, TextArea::HorizontalAlign::CENTER);
    // Button width - 2 so it's always at least 1px inside the button's borders.
    label->setWidth(button->size().width() - 2);
    
    addUI(button);
    addUI(label);
}

} // State
} // Falltergeist