inherit ROOM;

void create()
{
        set("short", "山間平地");
        set("long", @LONG
這裡有點荒涼，小草也長得無精打採的，看來是星宿的底子毒練
多了，毒素都聚集在這裡，連草木也遭了殃。地上零零散散的擺了幾
個木人，有些破舊。
LONG );
        set("exits", ([
                "east"   : __DIR__"wuchang2",
                "westup" : __DIR__"ertai",
        ]));
        set("objects", ([
                "/clone/npc/mu-ren" : 3
        ]));        
        set("outdoors", "xingxiu");
        set("for_family", "星宿派");
        setup();
        replace_program(ROOM);
}