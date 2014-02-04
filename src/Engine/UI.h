/*
 * Copyright 2012-2013 Falltergeist Developers.
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

#ifndef FALLTERGEIST_UI_H
#define FALLTERGEIST_UI_H

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
class Texture;

class UI
{
protected:
    int _x = 0;
    int _y = 0;
    Texture* _texture = 0;
public:
    UI(int x = 0, int y = 0);
    virtual ~UI();

    int x();
    void setX(int value);

    int y();
    void setY(int value);

    Texture* texture();
    void setTexture(Texture* texture);
};

}
#endif // FALLTERGEIST_UI_H