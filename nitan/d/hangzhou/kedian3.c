// kedian3.c
// Date: Nov.1997 by Venus
inherit ROOM;
void create()
{
        set("short", "天外天客店二樓");
        set("long", @LONG
天外天客店果然名不虛傳，好大的一間客房，一張精致的床，窗外
是美麗的西湖，無邊的宜人景致。暖暖的風吹得你昏昏欲睡，這裡正是
睡覺的好地方。
LONG);
        set("sleep_room", "1");
        set("no_fight", "1");
        set("hotel",1);
        set("no_clean_up", 0);
        set("exits", ([
                "out" : __DIR__"kedian2",
        ]));
	set("coor/x", 839);
	set("coor/y", -2071);
	set("coor/z", 9);
	setup();
}

int valid_leave(object me, string dir)
{
        if( dir == "out")delete_temp("rent_paid", me);
        return ::valid_leave(me, dir);
}