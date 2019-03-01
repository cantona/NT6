#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit "/inherit/condition/damo";

string name() { return "damo_zheyuan"; }

string chinese_name() { return "折元之擾"; }

string update_msg_others()
{
        return HIM "$N" HIM "臉色忽然大變，黃豆般大的汗珠順"
               "着臉龐涔涔而下。\n" NOR;
}

string update_msg_self()
{
        return HIR "丹田處一陣火起，忽又變得冰涼，想必是受到"
               "達摩折元劍的干擾。\n" NOR;
}

string die_reason()
{
        return "真元崩潰而亡了";
}

int neili_damage(object me, mapping cnd)
{
        int d;

        d = cnd["level"];

        if (d > 300 )
                d = 100 + (d - 300) / 12;
        else
        if (d > 60)
                d = 60 + (d - 60 ) / 6;
        d *= 3;
        if (d < 10) d = 10;

        return d / 2 + random(d);
}
