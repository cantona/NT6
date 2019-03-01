#include <room.h>

inherit ROOM;
void create()
{
        set("short", "靈州西門");
        set("long", @LONG
這是西城門，城門正上方刻著幾個西夏文字。城牆上貼著幾張官府
告示。一條路往西通向城外玄冥峰。
LONG );
        set("exits", ([
                "west"      : "/d/xuanminggu/xiaolu1",
                "southeast" : __DIR__"xidajie",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6295);
        set("coor/y", 2935);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

