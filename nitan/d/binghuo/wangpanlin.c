// Room: /binghuo/wangpanlin.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
王盤山是個小島，山石樹木亦無可觀之處。東南角有個港灣，桅
檣高聳，停泊著十來艘大船，想是巨鯨幫、海沙派一幹人的座船。林
裡兩個劍客正在比劍，招數巧妙狠辣，原來兩人並非練習劍法，竟是
真打真鬥。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "wangpan");
        set("exits", ([
                "southeast" : __DIR__"wangpangang",
                "southwest" : __DIR__"wangpangu2",
                //"west"      : __DIR__"wangpanshan",
        ]));
        set("objects", ([
                __DIR__"npc/gao" : 1,
                __DIR__"npc/jiang" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
