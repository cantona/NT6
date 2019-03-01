// /guanwai/road7.c
inherit ROOM;

void create()
{
        set("short", "大道");
        set("long", @LONG
你走在一條碎石舖成的大道上，道兩旁種著筆直通天的白楊樹，放眼向
兩側望去，全是無邊無際的田野，天邊處仿佛有幾座低矮的丘陵，為平坦的
大地增加了幾許柔和的曲線。呼嘯而過的狂風凍得人直打哆嗦。
LONG );
        set("exits", ([
                "north" : __DIR__"road8",
                "south" : __DIR__"road6",
        ]));
        set("no_clean_up", 0);
         set("outdoors", "guanwai");
        set("coor/x", 3990);
	set("coor/y", 9200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
