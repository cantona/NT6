// Room: /d/shaolin/houdian.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "後殿");
        set("long", @LONG
後殿規模不大。兩邊都是水磨石壁，鏤刻著十八羅漢的肖像及佛
謁，正中有一口水井，水面凈如明鏡，純若菩提，名曰佛心乃寺內有
名的清水井。東西面各有個門洞，通向兩側長長的走廊。
LONG );
        set("exits", ([
                "west" : __DIR__"zoulang2",
                "east" : __DIR__"zoulang3",
                "south" : __DIR__"guangchang4",
                "north" : __DIR__"wuchang",
        ]));
        set("valid_startroom",1);
        set("resource/water",1);
        set("objects",([
                CLASS_D("shaolin") + "/hui-ru" : 1,
                CLASS_D("shaolin") + "/kong-jian" : 1,
                __DIR__"npc/seng-bing3" : 2,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        object kj;

        if (dir != "east" &&
            dir != "west" &&
            dir != "north" ||
            ! objectp(kj = present("kong jian", this_object())))
                return ::valid_leave(me, dir);

        return kj->permit_pass(me, dir);
}