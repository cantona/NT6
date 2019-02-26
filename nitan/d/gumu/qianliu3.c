// This program is a part of NT MudLIB

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", HIR"潛流"NOR);
        set("long", @LONG
你沒在水中，只覺水勢甚急，衝得你無法立足。你氣悶異常，只得屏氣摸
索潛行，當真是進退維谷。突覺下面似有股強大吸力把你猛往下扯,你不由自主地往下沉去.
LONG
        );

        setup();
}

void init()
{
        object me;
        me = this_player();
        me->receive_damage("qi", 500 );
        me->receive_damage("jing", 500 );
        message_vision(HIB"$N的真氣正在流失，呼吸十分困難。\n"NOR, me);
        call_out("down", 5, me);
        if( query("qi", me)<10 || query("jing", me)<10 )
        {
                set_temp("die_reason", "在潛流中被淹死", me);
                me->unconcious();
                me->die();
                return ;
        }
}

void down(object me)
{
        tell_object(me, "只覺腳底水流盤旋，一股強大的吸力把你往下拉去...\n");
        me->move(__DIR__"hedi");
}
