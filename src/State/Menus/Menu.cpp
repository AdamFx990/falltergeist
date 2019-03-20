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
Menu::Menu() : State()
{
    // Initalise with the most commonly used menu font & colour
    _txtColour  = {0xb8, 0x9c, 0x28, 0xff};
    _font = "font3.aaf";
    // Initalise the renderer size var
    _rendSize = Game::getInstance()->renderer()->size();
}
// dtor
Menu::~Menu() {}

// Recalculate the menu's position
void Menu::setPosition()
{
    State::setPosition((_rendSize - Point(640, 480)) / 2);
}

// Set the font & colour used by labels & labelled buttons
void Menu::setFont(const std::string font, const SDL_Colour colour)
{
    _font = font;
    _txtColour = colour;
}

Image* Menu::createBackground(std::string bgImage)
{
    Image* background = new Image(bgImage);
    // Initalise size & position pointers
    _menuSize   = &background->size();
    _menuOrigin = &background->position();
    return background;
}

// Returns a label using this state's current font & colour
TextArea* Menu::createLabel(const Point& origin,
                            const std::string text,
                            const TextArea::HorizontalAlign alignment) const
{
    
    TextArea *label = new TextArea(text, origin);
    label->setFont(_font, _txtColour);
    label->setHorizontalAlign(alignment);
    return label;
}

// Returns a button with a linked event handler
ImageButton* Menu::createButton(const Point& origin,
                                const ImageButton::Type type,
                                const std::function<void(Event::Mouse*)> onClick) const
{
    ImageButton *button = new ImageButton(type, origin);
    button->mouseClickHandler().add(onClick);
    return button;
}

// Creates a button with a centred label and adds it to the UI
void Menu::createLabelledButton(const Point& origin,
                                const Point labelOffset,
                                const std::string text,
                                const ImageButton::Type type,
                                const std::function<void(Event::Mouse*)> onClick)
{
    auto button = createButton(origin, type, onClick);
    // Offset the label's origin so it appears inside the button
    auto label = createLabel(origin + labelOffset, text, TextArea::HorizontalAlign::CENTER);
    // Button width - 2 so it's always at least 1px inside the button's borders.
    label->setWidth(button->size().width() - 2);

    addUI(button);
    addUI(label);
}

/* Creates a number of labelled buttons using text extracted from the game's master.dat.
 * This can be used for any menu providing the buttons are equally spaced and the label
 * text is sorted sequentially when extracted from the .dat */ 
void createLabelledButtons(const Point &origin,
                           const Point &labelOffset,
                           const int buttonCount,
                           const MSG_TYPE msgType,
                           const unsigned msgTxtStartingIndex,
                           const int vertOffset,
                           const ImageButton::Type btnType,
                           const std::function<void(Event::Mouse*)> onClick)
{
    for (int i = 0; i < buttonCount; i++)
    {
        createLabelledButton(
            Point(origin->x, origin->y + (vertOffset * i)), // origin
            labelOffset, // label offset
            _t(msgType, (msgTxtStartingIndex + i)), // text
            btnType, // button sprite
            onClick); // click event
    }
}

} // namespace State
} // namespace Falltergeist