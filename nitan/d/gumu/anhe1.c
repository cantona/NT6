// Room: /d/gumu/anhe1.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", HIR"暗河"NOR);
        set("long", @LONG
原來這正是一條地下暗河，此處水聲已是轟轟，聲勢極為駭人。你
腳下一處踏空，便有水流直衝咽喉。此潛流不知來自何處，更不知通往
何方。
LONG        );

        set("exits", ([
                "northup"  : __DIR__"shishi6",
                "eastdown" : __DIR__"qianliu1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3000);
        set("coor/y", -50);
        set("coor/z", 30);
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
                set_temp("last_damage_from", "在暗河中被淹", me);
                me->unconcious();
                me->die();
                return;
        }
}
