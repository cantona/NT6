// Room: /xiakedao/shidong8.c
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "石洞");
        set("long", @LONG
這是一個石洞，四周是光滑的石壁，石洞內乾乾淨淨，一塵不
染。兩旁點着火把，非常明亮。南面有一扇虛掩的石門(door)。
LONG );
        set("exits", ([
                "east" : __DIR__"shidong7",
               "south" : __DIR__"road5"
        ]));
        set("item_desc", ([
                "door" : "這是一扇極厚的石門。\n"
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : 1,
        ]));
        set("coor/x", -3110);
        set("coor/y", -22100);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (!wizardp(me) && objectp(present("di zi", environment(me))) &&
                dir == "south")
                return notify_fail("俠客島弟子攔住你説：這是本島禁地，請回吧。\n");
        return ::valid_leave(me, dir);
}