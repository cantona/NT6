// Room: southroad2.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "南大街");
        set("long", @LONG
你正走在成都府的南大街上，這是一條寬敞開闊的大路，一直向
兩邊延伸。路上行人來來往往，好不熱鬧。一些小商小販常在這裏做
些小買賣。南面是南門，北邊一條大道名叫提督街，你一看就知到為
啥那麼安靜了。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "north"  : __DIR__"tiduroad",
            "south"  : __DIR__"southgate",
            "east"   : __DIR__"southroad1",
            "west"   : __DIR__"southroad3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15220);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}