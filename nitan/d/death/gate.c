#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIR "【鬼門關】" NOR);
        set("long", HIR @LONG

                    鬼         門         關

    這裏就是著名的陰間入口「鬼門關」，在你面前矗立著一座高大的
黑色城樓，許多亡魂正哭哭啼啼地列隊前進，因為一進鬼門關就無法再
回陽間了。


LONG NOR );
        set("exits", ([
                "north" : __DIR__"gateway",
        ]) );
        set("objects", ([
                __DIR__"npc/bai":1,
                __DIR__"npc/ghost":1,
        ]) );

        set("no_fight", 1);
        set("no_magic", 1);
        set("no_sleep_room", 1);

        setup();
        replace_program(ROOM);
}