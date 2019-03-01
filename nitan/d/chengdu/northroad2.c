// Room: northroad2.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "北大街");
        set("long", @LONG
這裏一條北大街橫貫東西。望向北邊，是出城的北門。號稱 "天
下幽" 的青城山，就是從這裏出去。這裏地當當道，行人卻都過往匆
匆，小心翼翼，恨不得銷聲匿跡。因為南邊一幢古色古香的建築，就
是讓天下武林聞風色變的川中唐門。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "east"   : __DIR__"northroad3",
            "west"   : __DIR__"northroad1",
            "south"  : __DIR__"tanggate",
            "north"  : __DIR__"northgate",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15220);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
}
int valid_leave(object me, string dir)
{
        me = this_player();
        if (dir == "south")
        return notify_fail("你一抬足，發現地上有毒，忙抽腿退回。\n");
        else  return 1;
}