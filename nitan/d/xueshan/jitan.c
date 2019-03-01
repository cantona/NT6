//  jitan.c 祭壇

inherit ROOM;

void create()
{
        set("short","祭壇");
        set("long", @LONG
 這裡是雪山寺祭壇，中間一個高台，青石砌就。周圍擺滿了木柴
和酥油，旁邊一個盛水的顱砵擺著一只法鈴。一些痛苦和可憐的亡靈
可以在這裡獲得超度。
LONG );
        set("outdoors","xueshan");
        set("no_fight","1");
        set("exits",([
                "north" : "/d/xueshan/chang",
        ]));
        set("objects",([
                "/d/xueshan/npc/x_lama": 2,
//                "/d/xueshan/npc/fsgelun": 2,
//                "/d/xueshan/obj/jitan2": 1,
//                "/d/xueshan/obj/faling": 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

/*
int valid_leave(object me, string dir)
{
        object ob;
        ob=(present("fa tan", (environment(me))));
        if (! objectp(ob)) return ::valid_leave(me, dir);
        if( query("name", me) == query("pending", ob )
         && query("burning", ob) )
                return notify_fail("你法事沒做完就想走？\n");
        return ::valid_leave(me, dir);
}
*/