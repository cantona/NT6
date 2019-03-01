// 羅漢伏魔神功 luohan-fumogong.c
// Editd By Vin On 29/5/2002

#include <ansi.h>
inherit FORCE;

int valid_force(string force)
{
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;
        string fam;

        fam=query("family/family_name", me);
        lvl = (int)me->query_skill("luohan-fumogong", 1);

        // 喝過玄冰碧火酒並且門派為少林
        if( query("skybook/item/xuanbingjiu", me )
           && fam == "少林派"
            && query("class", me) == "bonze" )
                return lvl * lvl * 15 * 18 / 100 / 200;
        else

        // 沒喝過玄冰碧火酒但門派為少林
        if( query("class", me) == "bonze"
           && fam == "少林派")
                return lvl * lvl * 15 * 15 / 100 / 200;
        else

        // 喝過玄冰碧火的其他門派玩家
        if( query("skybook/item/xuanbingjiu", me) )
                return lvl * lvl * 15 * 12 / 100 / 200;
        else
        // 普通情況
                return lvl * lvl * 15 * 4 / 100 / 200;
}

int valid_enable(string usage)
{ 
        return usage == "force";       
}

int valid_learn(object me)
{
        if( query("character", me) == "心狠手辣" )
                return notify_fail("你心中暗道：此功一點氣勢也無，何苦費力學它。。\n");

        if( query("character", me) == "陰險姦詐" )
                return notify_fail("你心中暗道：此功平淡無奇，何苦為它花費心思。\n");

        if( query("int", me)<30 )
                return notify_fail("你先天悟性不足，難以領會羅漢伏魔神功。\n");

        if( query("con", me)<30 )
                return notify_fail("你先天根骨孱弱，無法修煉羅漢伏魔神功。\n");

        if( query("gender", me) == "無性" && query("luohan-fumogong", me)>29 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的羅漢伏魔神功。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本內功火候不足，不能學羅漢伏魔神功。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不足，不能學羅漢伏魔神功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("羅漢伏魔神功只能用學(learn)的來增加熟練度。\n");
}

int difficult_level(object me)
{
        string fam;
    
        me = this_player();

        fam=query("family/family_name", me);

        if( query("skybook/item/xuanbingjiu", me )
           && fam == "少林派"
            && query("class", me) == "bonze" )
                return 200;
        else

        if( query("class", me) == "bonze"
           && fam == "少林派")
                return 400;
        else

        if( query("skybook/item/xuanbingjiu", me) )
                return 600;
        else
                return 800;
}

string exert_function_file(string action)
{
        return __DIR__"luohan-fumogong/" + action;
}
