// road2.c 小路

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
説是路，其實是人才草原上走過留下的痕跡，天長日久就漸漸行成了。
這隻哈薩克部族在這裏定居已久，可以看見到處是這種原始的道路。北邊
好像有一間小草棚。
LONG);
        
        set("exits", ([
            "southwest" : __DIR__"road1",
            "north" : __DIR__"room-ji",
            "northeast" : __DIR__"caoyuan6",
            
        ]));

         set("objects", ([
                    __DIR__"npc/bird" : 1

        ]));

        set("outdoors", "hasake");
        
        setup();
        replace_program(ROOM);
}