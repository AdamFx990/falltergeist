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

// Checks if the state has been initalised. if not, begin initalising
bool Menu::isInitalised()
{
    if (_initialized) return true;
    
    State::init();
    setModal(true);
    
    return false;
}

// ====== //
// States //
// ====== //

void Menu::pushState(State* state)
{
    fadeDoneHandler().clear();
    Game::getInstance()->pushState(state);
}

void Menu::popState()
{
    fadeDoneHandler().clear();
    Game::getInstance()->popState();
}

// ========== //
// Background //
// ========== //

// Creates the background image then re-calculate state position
Image* Menu::createBackground(std::string bgImage)
{
    // Create background
    Image* background = new Image(bgImage);
    // Calculate & set position
    const Point menuSize = background->size();
    State::setPosition((_rendSize - menuSize) / 2);
    
    return background;
}

// ====== //
// Labels //
// ====== //

// Set the font & colour used by labels & labelled buttons
void Menu::setFont(const std::string font, const SDL_Colour colour)
{
    _font = font;
    _txtColour = colour;
}

// Returns a label using this state's current font & colour
TextArea* Menu::createLabel(const Point& origin,
                            const std::string text,
                            const TextArea::VerticalAlign va,
                            const TextArea::HorizontalAlign ha) const
{
    TextArea *label = createLabel(origin, text);
    label->setVerticalAlign  (va);
    label->setHorizontalAlign(ha);

    return label;
}

// Returns a label using this state's current font & colour
TextArea* Menu::createLabel(const Point& origin, const std::string text) const
{
    TextArea *label = new TextArea(text, origin);
    label->setFont(_font, _txtColour);
   
    return label;
}

// ======= //
// Buttons //
// ======= //

// Returns a button with a linked event handler
ImageButton* Menu::createButton(const Point& origin,
                                const ImageButton::Type btnType,
                                const std::function<void(Event::Mouse*)> onClick) const
{
    ImageButton *button = new ImageButton(btnType, origin);
    button->mouseClickHandler().add(onClick);

    return button;
}

// Creates a button with a centred label and adds it to the UI
void Menu::createLabelledButton(const Point &origin,
                                const Point &labelOffset,
                                const std::string text,
                                const ImageButton::Type btnType,
                                const std::function<void(Event::Mouse*)> onClick)
{
    const auto va = TextArea::VerticalAlign::CENTER;
    const auto ha = TextArea::HorizontalAlign::CENTER;
    // Create a button at the origin
    ImageButton* button = createButton(origin, btnType, onClick);
    // Offset the label's origin so it appears inside the button
    TextArea* label = createLabel(origin + labelOffset, text, va, ha);
    // Button width - 2 so it's always at least 1px inside the button's borders.
    label->setSize(button->size() - 4);

    addUI(button);
    addUI(label);
}

// Creates a button with a centred label and adds it to the UI
void Menu::createLabelledButton(const Point &origin,
                                const Point &labelOffset,
                                const int labelWidth,
                                const std::string text,
                                const ImageButton::Type btnType,
                                const std::function<void(Event::Mouse*)> onClick)
{
    const auto va = TextArea::VerticalAlign::CENTER;
    const auto ha = TextArea::HorizontalAlign::CENTER;
    // Create a button at the origin
    ImageButton* button = createButton(origin, btnType, onClick);
    // Offset the label's origin so it appears inside the button
    TextArea* label = createLabel(origin + labelOffset, text, va, ha);
    // Set label to the specified width (usually when the button is a red circle).
    label->setWidth(labelWidth);

    addUI(button);
    addUI(label);
}

// Creates a button with a aligned label and add it to the UI
void Menu::createLabelledButton(const Point &origin,
                                const Point &labelOffset,
                                const std::string text,
                                const TextArea::HorizontalAlign ha,
                                const std::function<void(Event::Mouse*)> onClick)
{
    const TextArea::VerticalAlign va = TextArea::VerticalAlign::CENTER;
    // Create a button at the origin
    ImageButton* button = createButton(origin, ImageButton::Type::SMALL_RED_CIRCLE, onClick);
    // Offset the label's origin so it appears inside the button
    TextArea* label = createLabel(origin + labelOffset, text, va, ha);
    // Set label to the specified width (usually when the button is a red circle).

    addUI(button);
    addUI(label);
}

// returns two arrow buttons (up[0] | down[1]). 
std::array<ImageButton*, 2> Menu::createUpDownArrows(const Point &origin) const
{
    std::array<ImageButton*, 2> buttons;
    buttons[0] = new ImageButton(ImageButton::Type::SMALL_UP_ARROW, origin);
    const Point pos(origin.x(), origin.y() + 24);
    buttons[1] = new ImageButton(ImageButton::Type::SMALL_DOWN_ARROW, pos);
    return buttons;
}

// ===== //
// Fades //
// ===== //

// Fade in for state push
void Menu::fadeInFor(const std::function<void(Event::State*)> event,
                     const int red, const int green, const int blue)
{
    fadeInit(event);
    fadeIn(red, green, blue);
}

// Fade out for state pop
void Menu::fadeOutFor(const std::function<void(Event::State*)> event,
                      const int red, const int green, const int blue)
{
    fadeInit(event);
    fadeOut(red, green, blue);
}

void Menu::fadeInit(const std::function<void(Event::State*)> event)
{
    fadeDoneHandler().clear();
    fadeDoneHandler().add(event);
}

} // namespace State
} // namespace Falltergeist