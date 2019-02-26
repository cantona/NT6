// midao1.c 密道


inherit ROOM;

void create()
{
        set("short", "祕密通道");
        set("long", @LONG
這是一條很長的祕密通道，也許好久沒人來過了，密道中充滿
了一種潮濕的氣味，隱約可以感覺到四周是冰冷的石壁，你什麼也
看不見，只可以靠摸索着前進。
LONG );
        set("exits", ([
               "north" : __FILE__,
               "east" : __DIR__"midao2",
               "west" : __FILE__,
               "south" : __FILE__,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3090);
        set("coor/y", -25000);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}