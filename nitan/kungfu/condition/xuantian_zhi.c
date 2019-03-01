#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "xuantian_zhi"; }

string chinese_name() { return "玄天寒勁"; }

string update_msg_others()
{
       return HIW "$N" HIW "的痛苦的呻吟了一聲，臉上竟籠"
              "罩了一股薄薄的寒霜。\n" NOR;
}

string update_msg_self()
{
        return HIW "忽然一陣寒氣自丹田的而起，逐步滲透到四"
               "肢白賅，透出陣陣寒意。\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
        return cnd["level"] / 6;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] / 3;
}
