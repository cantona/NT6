
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "橫行無忌" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你在門派中倍受尊崇，完成師門任務可獲得額外多5%的獎勵，不需要運用。\n");
}

