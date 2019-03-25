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
#include "../../Game/Game.h"
#include "../../functions.h"

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
    // dtor
    virtual ~Menu() override;

protected:
    // ====== //
    // States //
    // ====== //
    void pushState(State* state);
    // ========== //
    // Background //
    // ========== //
    virtual void setPosition();

    Image* createBackground(std::string bgImage);
    // ====== //
    // Labels //
    // ====== //
    virtual void setFont(const std::string font, const SDL_Colour colour);

    TextArea* createLabel(const Point &origin,
                          const std::string text) const;
    
    TextArea* createLabel(const Point &origin,
                          const std::string text,
                          const TextArea::VerticalAlign va,
                          const TextArea::HorizontalAlign ha) const;
    // ======= //
    // Buttons //
    // ======= //
    ImageButton* createButton(const Point &origin,
                              const ImageButton::Type btnType,
                              const std::function<void(Event::Mouse*)> onClick) const;

    void createLabelledButton(const Point &origin,
                              const Point &labelOffset,
                              const std::string text,
                              const ImageButton::Type btnType,
                              const std::function<void(Event::Mouse*)> onClick);

    void createLabelledButton(const Point &origin,
                              const Point &labelOffset,
                              const int labelWidth,
                              const std::string text,
                              const ImageButton::Type btnType,
                              const std::function<void(Event::Mouse*)> onClick);
    // ===== //
    // Fades //
    // ===== //
    void fadeInFor (const std::function<void(Event::State*)> event);
    void fadeOutFor(const std::function<void(Event::State*)> event);

private:
    SDL_Color _txtColour;
    std::string _font;
    Graphics::Size _rendSize;
    Graphics::Size _menuSize;
    Graphics::Point _menuOrigin;

    void fadeInit(const std::function<void(Event::State*)> event);
    void fadeIn () const;
    void fadeOut() const;

};

} // namespace State
} // namespace Falltergeist

#endif // FALLTERGEIST_STATE_MENU_H