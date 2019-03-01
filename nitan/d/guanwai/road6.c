// /guanwai/road6.c
inherit ROOM;

void create()
{
        set("short", "大道");
        set("long", @LONG
你走在一條碎石鋪成的大道上，道兩旁種着筆直通天的白楊樹，放眼向
兩側望去，全是無邊無際的田野，天邊處彷彿有幾座低矮的丘陵，為平坦的
大地增加了幾許柔和的曲線。路上漸漸的出現了一些積雪。
LONG );
        set("exits", ([
                "north" : __DIR__"road7",
                "south" : __DIR__"road5",
        ]));
        set("objects",([
                __DIR__"npc/sanhu" : 1,
        ]));
//        set("no_clean_up", 0);
         set("outdoors", "guanwai");
        set("coor/x", 3990);
	set("coor/y", 9190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
