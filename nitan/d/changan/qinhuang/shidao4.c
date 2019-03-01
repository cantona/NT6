// This is a room made by wsl.

inherit ROOM;

void create()
{
    set("short", "石道");
        set("long", @LONG
這是一條陰森的道路，四周是一個個的俑坑，還有無數的骸骨，
看來秦始皇建好這座陵墓後，把全部的施工者都殺死在這裡了，你只
覺得有點毛骨悚然。
LONG );
        set("exits", ([
           "south":__DIR__"shidao3",
           "west":__DIR__"staffroom",
           "east":__DIR__"whiproom",
           "north":__DIR__"shidao5",
]));
        set("objects", ([
             __DIR__"obj/skeleton" : 1+random(10),
]));
    setup();
}