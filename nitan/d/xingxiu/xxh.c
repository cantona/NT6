// Room: /d/xingxiu/xxh.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "星宿海");
        set("long", @LONG
這裏是天山腳下的星宿海海邊。因方圓幾百裏都是一望無際的湖泊
和沼澤，地形十分險惡。當地牧羊人稱之為“海”。一旦有幾隻離羣的
羊走迷在“海”裏，便再也找不着了。臭名昭著的星宿派總壇便設在海
中央。
    南面有一條捷徑可通往白駝山。
LONG );
        set("exits", ([
                "north"   : __DIR__"xxh1",
                "westup"  : __DIR__"tianroad3",
                "southup" : __DIR__"tianroad2",
        ]));
        set("objects", ([
                CLASS_D("xingxiu")+"/zhaixing" : 1,
                __DIR__"npc/gushou"  : 1,
                __DIR__"npc/haoshou" : 1,
                __DIR__"npc/boshou" : 1,
        ]) );
//        set("no_clean_up", 0);
        set("outdoors", "xingxiu");
        set("coor/x", -50000);
        set("coor/y", 20100);
        set("coor/z", 0);
        setup();
}

/*
int valid_leave(object me, string dir)
{
        if (dir != "north" && dir != "westup")
        {
                return ::valid_leave(me, dir);
        }
        else
        {
                if (objectp(present("zhaixing zi", environment(me))) &&
                        living(present("zhaixing zi", environment(me))))
                {
                        if( (query("shen", me)>100) )
                                return notify_fail("摘星子喝道：這位"+RANK_D->query_respect(me)+"休走！\n");
                }
                return ::valid_leave(me, dir);
        }
}
*/