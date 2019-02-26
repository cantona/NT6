// Room: /d/shaolin/qyping.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "青雲坪");
        set("long", @LONG
這裏便是少室絕頂。極目望去，只見白雲縷縷，如蒼龍繞嶺；嵩
山拔翠，似金剛擎天。山腰五道瀑布飛瀉而下，石級蜿延曲折，宛若
一條長蟲，遊人紛紛其上，已如蟻蛭。面前的平地上寸草不生，正中
三棵巨鬆圍成一圈，圈中央似乎有什麼東西在閃閃發光。
LONG );
        set("exits", ([
                "southdown" : __DIR__"shulin14",
                "enter" : __DIR__"fumoquan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "shaolin");
        setup();
}

int valid_leave(object me, string dir)
{
        if ( dir == "enter" )
        if ( present("fumo dao", me) || present("jingang zhao", me) 
          || present("fumo dao", environment(me)) || present("jingang zhao", environment(me)) )
                return notify_fail("只聽裏面有人説道: 大俠上回已來過此處，此刻身攜重寶，不便進入，\n恕老衲等失禮了。\n");

        return ::valid_leave(me, dir);
}
