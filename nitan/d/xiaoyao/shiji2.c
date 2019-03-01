// shiji2.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "石級");
        set("long", @LONG
這是一段長長的石級，四周由于缺乏光亮，難免有那麼點陰森森的
感覺，石級向著東西兩面伸展，一眼望去，不可以望到盡頭。
LONG );
        set("exits", ([
                "east" : __DIR__"shishi2",
                "west" : __DIR__"shidong",
                "north" : __DIR__"fangjian2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50010);
        set("coor/y", -21040);
        set("coor/z", -40);
        setup();
        replace_program(ROOM);
}