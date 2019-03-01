inherit ROOM;

void create()
{
        set("short", "客店二樓");
        set("long", @LONG
這是一間很大的客房，陳設十分簡陋。靠牆放了十幾張小木床，
不少客人正和衣而臥，滿屋子都是呼呼的打酣聲。西邊有張床是空的，
你躡手躡腳地走了過去。
LONG );

        
        set("sleep_room", "1");
        set("no_fight", "1");
        set("hotel",1);

        set("exits", ([
                "out" : __DIR__"kedian2",
        ]));

        set("coor/x", -7091);
	set("coor/y", -2041);
	set("coor/z", 9);
	setup();
}

int valid_leave(object me, string dir)
{
        if( dir == "out")delete_temp("rent_paid", me);

        return ::valid_leave(me, dir);
}