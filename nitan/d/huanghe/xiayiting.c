// Room: /huanghe/xiayiting.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "俠義廳");
        set("long", @LONG
這是黃河幫議事的大廳，廳上掛着「俠義廳」三字匾額。廳裏靠
北朝南放着一張虎皮交椅，兩邊擺設着幾副紅木桌椅，非常有氣派。
牆上附庸風雅地掛了幾幅丹青書法。
LONG );
        set("exits", ([
                "east"  : __DIR__"guangchang",
        ]));
        set("objects", ([
                __DIR__"npc/sha" : 1,
                __DIR__"npc/peng" : 1,
                __DIR__"npc/liang" : 1,
        ]));
        set("coor/x", -2020);
        set("coor/y", 520);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}