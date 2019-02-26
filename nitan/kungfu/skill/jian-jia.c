// jian-jia.c 蒹葭

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "tanqin-jifa"; }

int valid_learn(object me)
{
        if (me->query_skill("tanqin-jifa", 1) < 30)
                return notify_fail("你的彈琴技法水平太差，還是先練好再説吧！\n");

        if (me->query_skill("tanqin-jifa", 1) < me->query_skill("qiuyue-lai", 1))
                return notify_fail("你的彈琴技法所有有限，無法領會更精妙的蒹葭。\n");

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
                return notify_fail("你現在口乾舌燥，實在是太累了。\n");

        me->receive_damage("jing", 25);
        me->receive_damage("qi", 10);

        return 1;
}

void do_effect(object me)
{
        object *obs;
        int i;

        obs = all_inventory(environment(me));
        for (i = 0; i < sizeof(obs); i++)
        {
                if (! obs[i]->is_character() || obs[i] == me || ! living(obs[i]))
                        continue;

                tell_object(obs[i], HIC "但聽琴韻中奏着「" HIW "蒹葭蒼蒼，白露為霜，所謂伊"
                                    "人，在天一方……" HIC "」\n卻不知琴韻何以如此纏綿，竟"
                                    "似充滿了思慕之情。\n" NOR);

                if( query_temp("love", obs[i]) == query("id", me) )
                {
                        tell_object(obs[i], HIM "你心中驀地一動：他琴中所提的「伊人」難道"
                                            "是我麼？\n" NOR);

                        message("vision", HIM "\n只見" HIM + obs[i]->name() + HIM "的臉微"
                                          "微一紅。\n" NOR, environment(obs[i]), ({obs[i]}));

                        continue;
                }
        }
}