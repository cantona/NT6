#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit "/inherit/condition/damo";

string name() { return "damo_luanqi"; }

string chinese_name() { return "亂氣之擾"; }

string update_msg_others()
{
        return HIM "$N" HIM "慘哼兩聲，整個人搖搖晃晃，便似"
               "醉酒一般。\n" NOR;
}

string update_msg_self()
{
        return HIR "忽然覺得一陣難受，心虛氣短，看來是受到達"
               "摩亂氣劍的幹擾。\n" NOR;
}

string die_msg_others()
{
        return HIR "$N" HIR "倒在地上呻吟了半天，最後終于漸"
               "漸沒有了聲音。\n" NOR;
}

string die_reason()
{
        return "氣盡身亡了";
}

int qi_damage(object me, mapping cnd)
{
        int d;

        d = cnd["level"];

        if (d > 300 )
                d = 100 + (d - 300) / 12;
        else
        if (d > 60)
                d = 60 + (d - 60 ) / 6;
        if (d < 10) d = 10;

        return d / 2 + random(d);
}
