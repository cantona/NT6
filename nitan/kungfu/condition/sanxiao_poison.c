// sanxiao_poison.c

#include <ansi.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "sanxiao_poison"; }

string chinese_name() { return "逍遙三笑散之毒"; }

string update_msg_others()
{
       return HIG "$N" HIG "臉上忽然露出詭異的一笑！\n" NOR;
}

string update_msg_self()
{
        return HIG "不知怎麼的，你忽然發現自己控制不了臉部肌肉，不由自主的笑了一下！\n" NOR;
}

string die_msg_others()
{
        return RED "$N" RED "臉上露出詭異的笑容，似乎很幸福。\n" NOR;
}

string die_reason(string name)
{
        return "中了" + chinese_name() + "，幸福的嚥下了最後一口氣";
}

int jing_damage(object me, mapping cnd)
{
        int d;

        d = cnd["level"];
        if (me->query_skill("xingxiu-poison") > 50) d /= 2;
        return d / 2;
}

int qi_damage(object me, mapping cnd)
{
        int d;

        d = cnd["level"];
        if (me->query_skill("xingxiu-poison") > 50) d /= 2;
        return d;
}

