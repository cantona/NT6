// Room: /d/gumu/anhe2.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", HIR"暗河"NOR);
        set("long", @LONG
原來這正是一條地下暗河，此處水聲已是轟轟，聲勢極為駭人。你
腳下一處踏空，便有水流直衝咽喉。此潛流不知來自何處，更不知通往
何方。慢慢你已感覺水勢漸緩，地勢漸高。
LONG        );

        set("exits", ([
                "northup"  : "/d/quanzhen/shandong1",
                "westdown" : __DIR__"qianliu2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2970);
        set("coor/y", -50);
        set("coor/z", -20);
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

int valid_leave(object me, string dir)
{
        if (dir == "northup")
        {
                write(HIW"\n你出得洞來，強光閃耀，一時之間竟然睜不開眼。\n"NOR);
        }
        return ::valid_leave(me, dir);
}