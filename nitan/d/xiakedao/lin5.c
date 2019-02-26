// /d/xiakedao/lin5.c
// Modified by Zeratul Jan 11 2001

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
這是一片茂密的樹林，好像被人設計了一種陣，一走進來，你彷彿迷失了方向。
LONG );
        set("outdoors", "xiakedao");
        set("exits", ([
                "east" : __DIR__"lin4",
                "west" : __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
                "southeast" : __FILE__,
                "northwest" : __DIR__"lin6",
        ]));
        set("objects", ([
            __DIR__"npc/yezhu" : 1,
        ]));
        setup();
        replace_program(ROOM);
}