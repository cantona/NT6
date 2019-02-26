#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "tiezhang_yang"; }

string chinese_name() { return "鐵掌純陽勁"; }

string update_msg_others()
{
        return RED "只聽$N" RED "悶哼一聲，雙目凸出，嘴角滲出几絲鮮血。\n" NOR;
}

string update_msg_self()
{
        return RED "你只覺丹田處有如火焚，便似有千萬鋼針一齊扎入體內。\n" NOR;
}

