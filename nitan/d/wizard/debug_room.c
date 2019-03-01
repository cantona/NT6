// /d/wizard/guest_room.c

#include <ansi.h>
#include <room.h>
inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", HIM "試劍亭" NOR);
        set("long", @LONG
這裡是天神用來調試程序的地方。
LONG );

        set("exits", ([
                "east": __DIR__"wizard_room",
        ]));


        set("coor/x", 9990);
        set("coor/y", 10000);
        set("coor/z", 10000);
        setup();
}