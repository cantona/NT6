// Room: /d/huashan/jzroad2.c

inherit ROOM;
void create()
{
        set("short", "鬆樹林");
        set("long", @LONG
這是一片鬆樹林。中間一條小路，兩邊都是黑森森的幾丈高的鬆
樹。快出林了，可以看到東邊好高的一道大山。
LONG );
        set("exits", ([
                "west" : __DIR__"jzroad1",
                "east" : __DIR__"jzroad3",
        ]));
        set("outdoors", "huashan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

