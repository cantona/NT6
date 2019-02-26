// Room: /xiakedao/lin5.c

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
        set("no_clean_up", 0);
        set("coor/x", -3000);
        set("coor/y", -21000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}