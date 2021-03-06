// riyue-guanghua.c 日月光華
// By haiyan

#include <combat.h> 
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return 1;
        return force == "riyue-xinfa" || force == "pixie-jian";
}

int query_neili_improve(object me)
{
    int lvl;
    lvl = (int)me->query_skill("riyue-guanghua", 1);
    return lvl * lvl * 22 * 15 / 100 / 200;
}

int valid_learn(object me)
{
        if( !query("special_skill/ghost", me)){
    if( query("gender", me) == "男性" && 
         (int)me->query_skill("riyue-guanghua", 1) > 49 )
            return notify_fail("你六根未淨，難以領會更高深的「日月光華」。\n");

    if( query("gender", me) == "女性" )
            return notify_fail("你無法領會「日月光華」這門絕學。\n");
        }

    if( query("character", me) == "光明磊落" )
            return notify_fail("你心中暗想：我為人光明磊落，這種邪教功夫學來做甚。\n");

    if ( (int)me->query_skill("xixing-dafa", 1) > 0 )
            return notify_fail("你已學了吸星大法，不能修煉日月光華。\n");

    if( query("dex", me)<25 )
            return notify_fail("你的身手不夠靈活，無法領會日月光華的祕要。\n");

    if ((int)me->query_skill("riyue-xinfa", 1) < 100)
            return notify_fail("你的日月心法火候還不夠，難以領會日月光華。\n");

    if ((int)me->query_skill("force", 1) < (int)me->query_skill("riyue-guanghua", 1))
            return notify_fail("你的基本內功水平有限，不能領會更高深的日月光華。\n");

    return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("日月光華只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
/*
    mapping sk;
    string *skname;
    int i, k=0;

    if (mapp(query("reborn", this_player())))
        return __DIR__"riyue-guanghua/" + func;

    sk=this_player()->query_skills();
    skname=sort_array( keys(sk), (: strcmp :) );

    for(i=0; i < sizeof(sk); i++)
    {
        if (SKILL_D(skname[i])->valid_enable("force"))  k++;
    }

    if ( k >=10 )
    {
        tell_object(this_player(), "你體內不同內力互相沖撞，難以施展日月光華。\n");
        return 0;
    }
*/

    return __DIR__"riyue-guanghua/" + func;
}
