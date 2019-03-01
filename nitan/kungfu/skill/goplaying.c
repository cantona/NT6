// goplaying.c 紋枰手談
// Last Modified by winder on Jun. 10 2000

#include <ansi.h>;
inherit SKILL;

void init();
int do_play(string arg);

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int valid_learn(object me)
{
        int lvl;

        lvl = (int)me->query_skill("goplaying", 1);

        if( query("int", me)<24 && me->query_int()<32 )
        return notify_fail("琴棋書畫乃是極其風雅之事，" +RANK_D->query_respect(me)+"似乎太過于俗氣了些。\n");

        if( query("shen", me)<-10000 )
        return notify_fail("你殺人如麻，倘若不能先平息了心頭魔念，哪裡又會有心思彈琴下棋？\n");

        if( lvl>29 && query("kar", me) != 29 && 
                query("family/master_name", me) != "何足道" )
                return notify_fail("限于天資，你只能修習這個程度了。\n");
        else return 1;
}

int practice_skill(object me)
{
        return notify_fail("紋枰手談只能靠學習來提高。\n");
}
void init()
{
        add_action("do_play", "play");
}

int do_play(string arg)
{
        object me = this_player();

        if ( present("wei qi", this_player()) && ((arg == "wei qi") ||
                (arg == "qi") || (arg == "go")) )
        {
                if ( (me->query_skill("art", 1) < 40) )
                {
                        message_vision("$N擺出一張棋盤，想研究圍棋，卻總覺得心煩意亂，定不下神來。\n", me);
                        me->receive_damage("jing", random(20) );
                        me->receive_damage("qi", random(20) );
                        return 1;
                }
                if ( me->query_skill("art", 1) >100 )
                {
                        message_vision("$N擺出一張棋盤，只覺棋面布局盡在籌幄只之中，無密可研。\n", me);
                        return 1;
                }

                me->receive_damage("jing", 10);
                me->receive_damage("qi", 10);
                me->improve_skill("art", (int)me->query_int()/4 + (int)me->query_skill("art", 1)/10);
                tell_object(me, "你擺出一張棋盤，研究起圍棋來，只覺得心平氣和，很快就仿佛入定了。\n");

                message_vision("只見"+query("name", me)+
                "雅興大發，竟打起棋譜來，對外界仿佛不聞不問，一副莫測高深的模樣。\n",
                environment(me), ({me}) );

        }
        return 1;
}

int help(object me)
{
        write(HIC"\n紋枰手談："NOR"\n");
        write(@HELP

    逍遙派祖師逍遙子學究天人，胸中所學包羅萬象。他共傳下七
門絕藝：繞樑琴藝 (luteplaying)、紋枰手談 (goplaying)、潑墨
丹青(painting)、濟世之術(medicine)、土木機關(construction)、
園藝蒔花(horticulture)、梨園舊藝(dramaturgy)。

        學習要求：
                無。但天賦才氣限制了對更高深境界的努力
HELP
        );
        return 1;
}
