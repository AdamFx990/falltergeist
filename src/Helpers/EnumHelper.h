#ifndef ENUM_HELPER_H
#define ENUM_HELPER_H

#include "../Format/Enums.h"

namespace Falltergeist
{
namespace Helpers
{

class EnumHelper
{
public:
    EnumHelper();
    // SPECIAL Converters //
    static int  statToInt(const STAT s);
    static STAT intToStat(const int  i);
    // SKILL Converters //
    static int   skillToInt(const SKILL s);
    static SKILL intToSkill(const int   i);
    // TRAIT Converters //
    static int   traitToInt(const TRAIT t);
    static TRAIT intToTrait(const int   i);
    // Iterators //
    static void iterate(STAT*  sp);
    static void iterate(SKILL* sp);
    static void iterate(TRAIT* tp);
};

} // Helpers
} // Falltergeist

#endif // ENUM_HELPER_H
