inherit ROOM;

void create()
{
        set("short", "竹林");
        set("long", @LONG
這裡是一片蒼翠的竹林，輕風吹過，竹影搖動。竟讓人心裡格外
安寧。
LONG);
        set("exits", ([
                "east" : __DIR__"shulin",
                "south" : __DIR__"luanshigang",
        ]));

        set("objects", ([
                 "/clone/quarry/tu" : 30 + random(20),
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");

        setup();
}

void init()
{
        object me = this_player();

        if( query("newbie_quest/leixing", me) == "move" )
        set("newbie_quest/completed", 1,  me);
                
}