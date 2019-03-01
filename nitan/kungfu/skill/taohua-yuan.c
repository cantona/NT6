// taohua-yuan.c 桃花怨

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "chuixiao-jifa"; }

int valid_learn(object me)
{
        if (me->query_skill("chuixiao-jifa", 1) < 50)
                return notify_fail("你的吹蕭技法水平太差，還是先練好再說吧！\n");

        if (me->query_skill("chuixiao-jifa", 1) < me->query_skill("taohua-yuan", 1))
                return notify_fail("你的吹蕭技法水平有限，無法領會更精妙的桃花怨。\n");

        return 1;
}

int practice_skill(object me)
{
        object ob;

        if( !objectp(ob=query_temp("handing", me)) || 
            ! ob->valid_as_xiao())
                return notify_fail("不拿根簫在手上，你怎麼練習？\n");

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

        lvl = me->query_skill("chuixiao-jifa", 1) / 2 +
              me->query_skill("taohua-yuan", 1);

        if (lvl < 100)
                return;

        // special effort
        obs = all_inventory(environment(me)) - ({ me });
        obs->receive_heal("jing", random(lvl / 10) + 10);
        message("visoin", HIG "你聽了" + me->name() +
                HIG "的曲子，覺得神情氣爽，精神也好多了。\n" NOR,
                obs);
}