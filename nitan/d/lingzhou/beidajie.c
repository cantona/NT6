// Room: /lingzhou/beidajie.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "北大街");
        set("long", @LONG
這是靈州北大街，乾淨、寬敞、安靜。雙人合抱的楊樹十步一株，
整齊的排在路的兩邊。西面和東面都是高高的圍牆，南面通向城中心，
北面就是西夏皇宮大門了。因為是皇城和城中心的唯一連接通道，便不
容許在兩邊開店，顯得特別清靜。
LONG );
        set("exits", ([
                "south" : __DIR__"center",
                "north" : __DIR__"gonggate",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6265);
        set("coor/y", 2935);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}