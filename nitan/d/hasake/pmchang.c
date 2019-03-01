// pmchang.c 跑馬場

inherit ROOM;

void create()
{
        set("short", "跑馬場");
        set("long", @LONG
這一大遍草地就是哈薩克族人的跑馬場了。廣闊的空間和來往的眾多
商人使它成為這一帶最繁忙的集會地和市場。一年一度的摔跤比賽和跑馬
節也在這裡舉行。
LONG
        );
        set("objects", ([
                    __DIR__"npc/hasake" : 1,
                    __DIR__"npc/niu" : 1,
                    __DIR__"npc/yang" : 1,
                    __DIR__"npc/chen" : 1,
        ]));

        set("exits", ([
            "north" : __DIR__"shop",
            "west" : __DIR__"road",
            "southup" : __DIR__"caochang",
            "east" : __DIR__"caoyuan2",
            "southwest" : __DIR__"shuijing",
        ]));

        set("outdoors", "hasake");
        
        setup();
        replace_program(ROOM);
}