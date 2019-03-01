#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", HIR "【鬼門大道】" NOR);
       set("long", HIR @LONG

                    鬼     門     大     道

    你走在一條陰森森的路上，濃濃的霧環繞在你的四周，好像永遠都
不會散去似的，整條路前後只看到零星的幾盞燈籠……


LONG NOR );
        set("exits", ([
                "north" : "/d/death/road5",
                "south" : "/d/death/road3",
        ]));

        set("no_fight", 1);
        set("no_sleep_room", 1);

        setup();
        replace_program(ROOM);
}