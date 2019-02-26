// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "側房");
        set("long", @LONG
這裏就是温家老二温方義平時起居生活的住處，由於他是
温家五老中最有生意頭腦的人物，所以平時一般都沒在家，在
外面打理生意去了。
LONG
        );
        set("exits", ([ 
                "east" : __DIR__"zoulang1",
        ]));
        set("objects", ([
                __DIR__"npc/wenfangwu" : 1,
        ]));
        set("coor/x", 1590);
        set("coor/y", -1940);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}