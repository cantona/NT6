// midao2.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "秘密通道");
        set("long", @LONG
這是一段又長又黑的秘密通道，隱約可以感覺到四周是冰冷而堅硬
的石壁，你什麼了看不清楚，只可以靠摸索著前進。
LONG );
        set("exits", ([
                "south" : __DIR__"midao1",
                "north" : __DIR__"midao3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -40000);
        set("coor/y", -5000);
        set("coor/z", -40);
        setup();
        replace_program(ROOM);
}