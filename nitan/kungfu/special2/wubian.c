
#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIY "浩月無邊" NOR; }

int perform(object me, string skill)
{
        return notify_fail("由于你在轉世的過程中感應到浩月的無窮智慧，使你的學習能力大大提高。\n"
                       HIY "可提高每次學習次數上限100次，提高每次研究次數上限100次。\n" NOR);
}