// yinyun-ziqi.c 氤氲紫氣
// 武當初級內功
// Created by Lonely

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("yinyun-ziqi", 1);
        return lvl * lvl * 15 * 19 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("yinyun-ziqi", 1);
        int t = 1, j;

        for (j = 1; j < lvl / 10; j++) 
                t *= 2;
        if (t > 5000) t = 5000;
        if( query("gender", me) == "無性" && lvl>49 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的氤氲紫氣神功。\n");

        if( query("class", me) == "bonze" )
                return notify_fail("氤氲紫氣講究陰陽調合，有違佛家六根清淨之意，"
                                +RANK_D->query_respect(me)+"欲修此功，已是罪過。\n");

        if ((int)me->query_skill("force", 1) < 15)
                return notify_fail("你的基本內功火候還不夠。\n");

        if( (lvl>10 && lvl<100 && query("shen", me)<t*200 )
                 || (lvl >= 100 && query("shen", me)<10000) )
                return notify_fail("你的俠義正氣太低了。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("氤氲紫氣只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"yinyun-ziqi/" + func;
}

mapping exercise_msg(object me)
{
        return ([
                "status_msg" : "頭頂氤氣蒸蒸，神色威嚴",
                "start_my_msg" : "盤膝而坐，雙目緊閉，深深吸一口氣引如丹田，慢慢讓一股內息在周身大穴流動，漸入忘我之境。\n",
                "start_other_msg" : "盤膝坐了下來，雙手虛握成拳，不一會，頭頂冒出氤氤紫氣。\n",
                "halt_msg" : "微一簇眉，將內息壓回丹田，長出一口氣，站了起來。\n",
                "end_my_msg" : "將內息在體內運行十二週天，返回丹田，只覺得全身暖洋洋的。\n",
                "end_other_msg" : "長出一口氣，一抖衣襟，站了起來，眼中精光一閃。\n"
        ]);
}

