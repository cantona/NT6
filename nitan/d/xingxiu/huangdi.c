// Room: /d/xingxiu/huangdi.c
// Last Modified by winder on Apr. 25 2001

inherit ROOM;
void create()
{
        set("short", "山前荒地");
        set("long", @LONG
你站在石山前的荒地上。這兒人跡罕見，放眼望去，盡是枯樹敗草。
朔風蕭殺，令人心驚膽顫。路邊有幾個星宿弟子在練功，同時監視著行
人一舉一動。你沒事，還是快回吧。
LONG);
        set("objects", ([
                CLASS_D("xingxiu")+"/feitian" : 1,
                __DIR__"npc/xxdizi" : 1,
        ]));
        set("exits", ([
         "south"     : __DIR__"xxh2",
                "northup"   : __DIR__"riyuedong1",
        ]));
        set("outdoors", "xingxiu");
        set("coor/x", -50000);
        set("coor/y", 20300);
        set("coor/z", 0);
        setup();
//        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if (dir =="northup" && present("feitian zi", environment(me)) &&
                (!myfam || myfam["family_name"] != "星宿派") &&
                query("combat_exp", me)<100000 )
                return notify_fail("飛天子擋住了你：像你這樣糟糕的邪派弟子怎麼可以去拜見我們老仙？\n");
        return ::valid_leave(me, dir);
}
