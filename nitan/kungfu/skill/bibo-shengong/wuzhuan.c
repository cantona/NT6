// Code of JHSH
// wuzhuan.c 奇門五轉

#include <ansi.h>

//inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        string msg;
        int i, extra;

        if( query_temp("wuzhuan", me) )
                return notify_fail("你正在運用「奇門五轉」心法！\n");

        if( me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("你所用的內功與「奇門五轉」心法相悖！\n");

        if( me->query_skill("bibo-shengong", 1) < 100 )
                return notify_fail("你的內功修為火候未到，還未領悟「奇門五轉」！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠，勁力不足以施展「奇門五轉」！\n");
        
        if( me->query_skill("qimen-wuxing", 1) < 120 )
                return notify_fail("你的奇門五行修為不夠，還未領悟「奇門五轉」！\n");

        msg = HIG "$N臉上青氣大盛，腳下緩緩踩着九宮八卦方位，頭頂冒出騰騰白氣，";
        msg += "四面隱隱傳來潮湧之聲，碧波神功已發揮到極致！\n"NOR;

        addn("neili", -200, me);
        
        extra = (int)me->query_skill("qimen-wuxing",1);
        addn_temp("apply/attack", extra/2, me);
        addn_temp("apply/defense", extra/2, me);
        addn_temp("apply/dodge", extra/30, me);

        set_temp("wuzhuan", 1, me);
        set_temp("wuzhuan_hit", extra/60+random(2), me);

        
        call_out("remove_effect", extra/2, me, extra);

        message_vision(msg, me);

        return 1;
}

void remove_effect(object me, int extra)
{
        if (!me) return;

        addn_temp("apply/attack", -extra/2, me);
        addn_temp("apply/defense", -extra/2, me);
        addn_temp("apply/dodge", -extra/30, me);

        delete_temp("wuzhuan_hit", me);
        delete_temp("wuzhuan", me);
        message_vision(CYN"$N只覺真氣運轉不暢，不得不放慢步法，調息吐納。\n"NOR,me);
}