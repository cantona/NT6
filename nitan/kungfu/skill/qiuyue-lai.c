// qiuyue-lai.c 秋月籟

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "tanqin-jifa"; }

int valid_learn(object me)
{
        if (me->query_skill("tanqin-jifa", 1) < 50)
                return notify_fail("你的彈琴技法水平太差，還是先練好再說吧！\n");

        if (me->query_skill("tanqin-jifa", 1) < me->query_skill("qiuyue-lai", 1))
                return notify_fail("你的彈琴技法所有有限，無法領會更精妙的秋月籟。\n");

        return 1;
}

int practice_skill(object me)
{
        object ob;

        if( !objectp(ob=query_temp("handing", me)) || 
            ! ob->valid_as_qin())
                return notify_fail("你不拿琴在手上，怎麼練習？\n");

        if( query("jing", me)<80 )
                return notify_fail("你的精神不夠好，沒法練習了。\n");

        if( query("qi", me)<30 )
                return notify_fail("你現在口幹舌燥，實在是太累了。\n");

        me->receive_damage("jing", 25);
        me->receive_damage("qi", 10);

        return 1;
}

void do_effect(object me)
{
        object *obs;
        int lvl;

        lvl = me->query_skill("tanqin-jifa", 1) / 2 +
              me->query_skill("qiuyue-lai", 1);

        if (lvl < 100)
                return;

        obs = all_inventory(environment(me)) - ({ me });
        obs->receive_heal("jing", random(lvl / 10) + 10);
        message("vision", HIC "你聽了" + me->name() + HIC "一首秋"
                          "月籟，便宛如置身于秋夜一般，靈台處一片"
                          "清欣，精神為之一振。\n" NOR, obs);
}