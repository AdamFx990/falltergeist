#include "EnumHelper.h"

namespace Falltergeist
{
namespace Helpers
{
// ctor
EnumHelper::EnumHelper() {}

// ======= //
// SPECIAL //
// ======= //

int EnumHelper::statToInt(const STAT s)
{
    switch (s)
    {
        case STAT::STRENGTH    : return 0;
        case STAT::PERCEPTION  : return 1;
        case STAT::ENDURANCE   : return 2;
        case STAT::CHARISMA    : return 3;
        case STAT::INTELLIGENCE: return 4;
        case STAT::AGILITY     : return 5;
        case STAT::LUCK        : return 6;
    }
    return -1;
}

STAT EnumHelper::intToStat(const int i)
{
    switch (i)
    {
        case  0: return STAT::STRENGTH    ;
        case  1: return STAT::PERCEPTION  ;
        case  2: return STAT::ENDURANCE   ;
        case  3: return STAT::CHARISMA    ;
        case  4: return STAT::INTELLIGENCE;
        case  5: return STAT::AGILITY     ;
        case  6: return STAT::LUCK        ;
        default: return STAT::NONE        ;
    }
}

// ===== //
// SKILL //
// ===== //

int EnumHelper::skillToInt(const SKILL s)
{
    switch (s)
    {
        case SKILL::SMALL_GUNS    : return  0;
        case SKILL::BIG_GUNS      : return  1;
        case SKILL::ENERGY_WEAPONS: return  2;
        case SKILL::UNARMED       : return  3;
        case SKILL::MELEE_WEAPONS : return  4;
        case SKILL::THROWING      : return  5;
        case SKILL::FIRST_AID     : return  6;
        case SKILL::DOCTOR        : return  7;
        case SKILL::SNEAK         : return  8;
        case SKILL::LOCKPICK      : return  9;
        case SKILL::STEAL         : return 10;
        case SKILL::TRAPS         : return 11;
        case SKILL::SCIENCE       : return 12;
        case SKILL::REPAIR        : return 13;
        case SKILL::SPEECH        : return 14;
        case SKILL::BARTER        : return 15;
        case SKILL::GAMBLING      : return 16;
        case SKILL::OUTDOORSMAN   : return 17;
        default                   : return -1;
    }
}

SKILL EnumHelper::intToSkill(const int i)
{
    switch (i)
    {
        case  0: return SKILL::SMALL_GUNS    ;
        case  1: return SKILL::BIG_GUNS      ;
        case  2: return SKILL::ENERGY_WEAPONS;
        case  3: return SKILL::UNARMED       ;
        case  4: return SKILL::MELEE_WEAPONS ;
        case  5: return SKILL::THROWING      ;
        case  6: return SKILL::FIRST_AID     ;
        case  7: return SKILL::DOCTOR        ;
        case  8: return SKILL::SNEAK         ;
        case  9: return SKILL::LOCKPICK      ;
        case 10: return SKILL::STEAL         ;
        case 11: return SKILL::TRAPS         ;
        case 12: return SKILL::SCIENCE       ;
        case 13: return SKILL::REPAIR        ;
        case 14: return SKILL::SPEECH        ;
        case 15: return SKILL::BARTER        ;
        case 16: return SKILL::GAMBLING      ;
        case 17: return SKILL::OUTDOORSMAN   ;
        default: return SKILL::NONE          ;
    }
}

// ======//
// TRAIT //
// ======//

int EnumHelper::traitToInt(const TRAIT t)
{
    switch (t)
    {
        case TRAIT::FAST_METABOLISM: return  0;
        case TRAIT::BRUISER        : return  1;
        case TRAIT::SMALL_FRAME    : return  2;
        case TRAIT::ONE_HANDED     : return  3;
        case TRAIT::FINESSE        : return  4;
        case TRAIT::KAMIKAZE       : return  5;
        case TRAIT::HEAVY_HANDED   : return  6;
        case TRAIT::FAST_SHOT      : return  7;
        case TRAIT::BLOODY_MESS    : return  8;
        case TRAIT::JINXED         : return  9;
        case TRAIT::GOOD_NATURED   : return 10;
        case TRAIT::CHEM_RELIANT   : return 11;
        case TRAIT::CHEM_RESISTANT : return 12;
        case TRAIT::SEX_APPEAL     : return 13;
        case TRAIT::SKILLED        : return 14;
        case TRAIT::GIFTED         : return 15;
        default                    : return -1;
    }
}

TRAIT EnumHelper::intToTrait(const int i)
{
    switch(i)
    {
        case  0: return TRAIT::FAST_METABOLISM;
        case  1: return TRAIT::BRUISER        ;
        case  2: return TRAIT::SMALL_FRAME    ;
        case  3: return TRAIT::ONE_HANDED     ;
        case  4: return TRAIT::FINESSE        ;
        case  5: return TRAIT::KAMIKAZE       ;
        case  6: return TRAIT::HEAVY_HANDED   ;
        case  7: return TRAIT::FAST_SHOT      ;
        case  8: return TRAIT::BLOODY_MESS    ;
        case  9: return TRAIT::JINXED         ;
        case 10: return TRAIT::GOOD_NATURED   ;
        case 11: return TRAIT::CHEM_RELIANT   ;
        case 12: return TRAIT::CHEM_RESISTANT ;
        case 13: return TRAIT::SEX_APPEAL     ;
        case 14: return TRAIT::SKILLED        ;
        case 15: return TRAIT::GIFTED         ;
        default: return TRAIT::NONE           ;
    }
}

void EnumHelper::iterate(STAT *sp)
{

}

void EnumHelper::iterate(SKILL *sp)
{

}

void EnumHelper::iterate(TRAIT* tp)
{

}

} // Helpers
} // Falltergeist

