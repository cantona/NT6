// Room: /xiakedao/lin3.c

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
這是一片茂密的樹林，好像被人設計了一種陣，一走進來，你彷彿迷失了方向。
LONG );
        set("outdoors", "xiakedao");
        set("exits", ([
                "east" : __FILE__,
                "west" : __DIR__"lin2",
                "south" : __FILE__,
                "north" : __FILE__,
                "southeast" : __DIR__"lin4",
                "northeast" : __FILE__,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3000);
        set("coor/y", -21000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}