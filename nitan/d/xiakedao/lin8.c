 // Room: /xiakedao/lin8.c

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
終于走出了樹林，你不禁長長的鬆了口氣。和煦的陽光照在你
的身上，使你感到無比的溫暖。南邊是一座高聳的石山，山上鬱鬱
蒼蒼，生滿樹木。
LONG );
        set("outdoors", "xiakedao");
        set("exits", ([
              "south" : __DIR__"shanmen",
              "north" : __DIR__"lin7",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3000);
        set("coor/y", -22000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}