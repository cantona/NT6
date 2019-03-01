#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit "/inherit/condition/damo";

string name() { return "damo_shangshen"; }

string chinese_name() { return "傷神之擾"; }

string update_msg_others()
{
        return HIM "$N" HIM "搖頭晃腦，連眼睛都睜不開了，看上"
               "去困倦之極。\n" NOR;
}

string update_msg_self()
{
        return HIR "只覺得自己精神不濟，疲憊不堪，看來是受到達"
               "摩傷神劍的幹擾。\n" NOR;
}

string die_msg_others()
{
        return HIR "$N" HIR "費力的吸入幾口氣，撲騰兩下，就再"
               "也沒有半點動靜。\n" NOR;
}

string die_reason()
{
        return "精神衰竭身亡了";
}

int jing_damage(object me, mapping cnd)
{
        int d;

        d = cnd["level"];

        if (d > 300 )
                d = 100 + (d - 300) / 12;
        else
        if (d > 60)
                d = 60 + (d - 60 ) / 6;
        d /= 3;
        if (d < 10) d = 10;

        return d / 2 + random(d);
}
