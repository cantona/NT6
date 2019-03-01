// square.c

inherit ROOM;

void create()
{
        set("short", "廣場");
        set("long", @LONG
這裡是華山派在山頂開辟的一塊平台，平時聚會的時候使用。雖
然不大卻很平整。東北通向練武場，那裡是華山弟子練習功夫的地方，
人來人往，熱鬧非凡。西面有個小店。通常有許多華山派弟子在此買
些物品。北邊的房屋門上掛著一塊匾，上書「群仙觀」，西北方似乎
有條小道通往山上。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "northeast" : __DIR__"wuchang1",
            "northwest" : __DIR__"chaopath1",
            "south"     : __DIR__"yunu",
            "north"     : __DIR__"qunxianguan",
            "west"      : __DIR__"shop",
            "east"      : __DIR__"bingqifang",
        ]));

        set("objects", ([
            __DIR__"npc/gao-genming" : 1,
        ]));

        set("outdoors", "huashan" );

        setup();
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (! objectp(guarder = present("gao genming", this_object())))
                return 1;

        if (dir == "northeast" || dir == "east" || dir == "north")
                return guarder->permit_pass(me, dir);

        return 1;
}