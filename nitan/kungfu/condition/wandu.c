#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "qianzhu_wandushou"; }

string chinese_name() { return "穿心劇毒"; }

string update_msg_others()
{
       return HIB "只見$N" HIB "毒氣上湧，臉浮現出一層黑氣，不住的顫抖。\n" NOR;
}

string update_msg_self()
{
        return HIB "你只覺毒氣攻心，頭暈目眩，一陣説不出的噁心。\n" NOR;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] / 5;
}