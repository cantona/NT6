// Room: /d/taiwan/banxianshe.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "半線社");
        set("long", @LONG
半線社位于台灣西部平原中段，為平埔族遊獵之地。明鄭時代已有
漢人聚居，清初隸諸羅縣，閩海居民相繼東渡，移墾台灣西部中段，此
地才漸漸繁盛起來。
LONG );
        set("exits", ([
                "northeast" : __DIR__"maolishe",
                "west"      : __DIR__"lugang",
                "southwest" : __DIR__"taiwanfu",
                "southeast" : __DIR__"riyuetan",
        ]));
        set("objects", ([
                __DIR__"npc/nongfu": 2,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2510);
        set("coor/y", -7000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
