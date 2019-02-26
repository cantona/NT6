inherit ROOM;

void create()
{
        set("short", "雪山別院");
        set("long", @LONG
這裏是雪山寺的分部，當年貢唐倉大喇嘛不遠萬里進京面聖，被
封為國師，就在此處宣揚佛法。
LONG );
        set("exits", ([
                "east" : "/d/beijing/road5",
        ]));
        set("objects" , ([
                __DIR__"npc/seng-bing1" : 4,
                __DIR__"npc/zhike" : 1,
                CLASS_D("xueshan") + "/guoshi" : 1 ,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if( query("id", me) == "sengbing"
           && dir == "east")
                return 0;

        return ::valid_leave(me, dir);
}