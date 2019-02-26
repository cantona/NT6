// Room: /d/gumu/qianliu1.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", HIR"潛流"NOR);
        set("long", @LONG
你沒在水中，只覺水勢甚急，衝得你無法立足。你氣悶異常，只得屏氣摸
索潛行，當真是進退維谷。
LONG        );

        set("exits", ([
                "east"   : __DIR__"qianliu2",
                "westup" : __DIR__"anhe1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2990);
        set("coor/y", -50);
        set("coor/z", -30);
        setup();
}

void init()
{
        object me = this_player();

        me->receive_damage("qi", 50 );
        me->receive_damage("jing", 50 ); 
        message_vision(HIB"$N的真氣正在流失，呼吸十分困難。\n"NOR, me);
        if( query("qi", me)<10 || query("jing", me)<10 )
        {
                set_temp("last_damage_from", "在潛流中被淹", me);
                me->unconcious();
                me->die();   
                return;
        }
}
