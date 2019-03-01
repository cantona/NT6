inherit ROOM;

void create()
{
        set("short", "觀龍亭");
        set("long",@LONG
這是一處古舊的亭子，不知是什麼年代為誰所建。
LONG);

        set("exits", ([
                "north"  : __DIR__"xiaoxi2",
        ]));

        set("objects", ([
                __DIR__"npc/yufu" : 1, 
        ]));
        //set("no_fight", 1);
        set("outdoors", "shenlong");
        setup();
}
