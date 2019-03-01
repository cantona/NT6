// Room: /d/shaolin/guangchang5.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "廣場");
        set("long", @LONG
這是千佛殿前的一個廣場。往北上了台階就是供奉西天諸佛的千
佛殿。往西是供奉地藏王菩薩的地藏殿，往東是供奉白衣觀音大士的
白衣殿。這裡每年都有不少香客聚集舉辦水陸大法會。
LONG );
        set("exits", ([
                "east" : __DIR__"bydian",
                "west" : __DIR__"dzdian",
                "south" : __DIR__"wuchang3",
                "northup" : __DIR__"qfdian",
                "southup" : __DIR__"dmyuan",
        ]));
        set("outdoors", "shaolin");
        setup();
}

int valid_leave(object me, string dir)
{
        if( !query("luohan_winner", me) && !wizardp(me) )
        {
                if (dir == "southup")
                {
                        return notify_fail("你級別不夠，不能進入達摩院。\n");
                }
        }
        return ::valid_leave(me, dir);
}
