// nuhai-kuangtao.c    怒海狂濤

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return 1;
        return force == "yunv-xinfa" ||
               force == "jiuyang-shengong";
}


int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("nuhai-kuangtao", 1);
        return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_learn(object me)
{
        if( query("gender", me) == "無性" )
                return notify_fail("你無根無性，陰陽難調，不能修習怒海狂濤。\n");

        if( query("gender", me) == "女性" )
                return notify_fail("怒海狂濤是剛猛內功，不適宜女孩子學。\n");


        if ((int)me->query_skill("yunv-xinfa", 1) < 50)
                return notify_fail("你的玉女心法火候還不夠。\n");

        if ((int)me->query_skill("sword", 1) < 50)
                return notify_fail("你的基本劍法火候還不夠。\n");

        if ((int)me->query_skill("force", 1) < 50)
                return notify_fail("你的基本內功火候還不夠。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("怒海狂濤只能用學(learn)來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"nuhai-kuangtao/" + func;
}

mapping curing_msg(object me)
{
        return ([
"apply_short" : me->name()+"盤膝坐在地上，四周隱隱有風聲海嘯，氣息激盪。",
"start_self"  : HIG"你盤膝而坐，內力源源不斷的流轉全身，開始運功療傷。\n"NOR,
"on_self"     : HIM"你耳邊隱隱風雷陣陣，碧海狂嘯，體內真氣彭湃，傷勢漸漸好轉。\n"NOR,
"start_other" : HIG""+me->name()+"盤膝坐下，片刻間，隱隱傳來風聲海嘯，空氣裏真力激盪。\n"NOR,
"finish_self" : HIG"你感到海嘯聲漸漸消退，內力充沛，傷勢已然痊癒，站起身來。\n"NOR,
"finish_other" :me->name()+"一聲長嘯，如同滔天海浪席捲而來，待其挺身而立，卻是精神飽滿。\n",
"unfinish_self" :"你感到內力斷斷續續，無法繼續療傷，如此下去，勢必走火入魔，只得暫緩療傷。\n",
"unfinish_other":me->name()+"搖晃起身，臉上一陣抽搐，好像傷勢十分嚴重。\n",
"halt_self"   : "你深吸一口氣，摒除耳邊波浪嘯聲，壓下真氣，站起身來。\n",
"halt_other"  : me->name() +"深吸口氣，站起身來，傷勢似乎有所好轉。\n",
        ]);
}
