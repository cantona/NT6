// luteplaying.c 繞樑琴藝
// Last Modified by winder on Jun. 10 2000

#include <ansi.h>;
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

void init();
int do_play(string arg);

int valid_learn(object me)
{
        int lvl;
        if( query("int", me)<24 && me->query_int()<32 )
                return notify_fail("琴棋書畫乃是極其風雅之事，" +RANK_D->query_respect(me)+"似乎太過于俗氣了些。\n");

        if( query("shen", me)<-10000 )
                return notify_fail("你殺人如麻，倘若不能先平息了心頭魔念，哪裡又會有心思彈琴下棋？\n");

        lvl = (int)me->query_skill("luteplaying", 1);

        if( lvl>29 && query("kar", me) != 29 && 
                query("family/master_name", me) != "何足道" )
                return notify_fail("限于天資，你只能修習這個程度了。\n");

        return 1;
}

void init()
{
        add_action("do_play", "play");
}

int do_play(string arg)
{
        object me = this_player();

        if( !arg && (arg != "music") && (arg != "zheng") && (arg != "gu zheng"))
                return notify_fail("你要做什麼？\n");

        if ( present("gu zheng", this_player()) &&
                ((arg == "music") || (arg == "zheng") || (arg == "gu zheng")) )
        {
                if ( me->query_skill("luteplaying", 1) < 30 )
                {
                        message_vision("$N擺出一張古箏，錚錚琮琮彈了幾聲，只聽得曲調雜亂無章，宛如鬼哭狼號。\n", me);
                        me->receive_damage("jing", random(20) );
                        me->receive_damage("qi", random(20) );
                        return 1;
                }
                if ( me->query_skill("luteplaying", 1) >100 )
                {
                        message_vision("$N擺出一張古箏，錚錚琮琮彈了幾聲，只聽得曲調平和，洋洋洒洒，頗有佳意。\n", me);
                        return 1;
                }
                me->receive_damage("jing", 10);
                me->receive_damage("qi", 10);
                me->improve_skill("art", (int)me->query_int()/4 + (int)me->query_skill("art", 1)/10);
                tell_object(me, "你擺出一張古箏，調了調弦，彈了起來，你只覺得連日來煩燥的心情好了許多。\n");

                message_vision("只見"+query("name", me)+
                "雅興大發，竟彈起曲子來，你只覺得時而金戈鐵馬、大漠平沙。。。。。。\n"
                "時而小橋流水、幾戶人家。。。。。。萬般氣象，你心情頓時寧靜了許多。\n",
                environment(me), ({me}) );

                return 1;
        }
        return 1;
}


int practice_skill(object me)
{
        return notify_fail("繞樑琴藝只能靠學習來提高。\n");
}
int help(object me)
{
        write(HIC"\n繞樑琴藝："NOR"\n");
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
