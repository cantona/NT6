//Room: /d/dali/kedian2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short", "客店二樓");
        set("long", @LONG
這是一間很大的客房，陳設十分簡陋。靠牆放了十幾張小木牀，
不少客人正和衣而卧，滿屋子都是呼呼的打酣聲。西邊有張牀是空的，
你躡手躡腳地走了過去。
LONG );
        set("sleep_room", "1");
        set("no_fight", "1");
        set("hotel",1);
        set("no_clean_up", 0);
        set("exits", ([
                "down" : __DIR__"kedian",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6950);
	set("coor/z", 10);
	setup();
}

int valid_leave(object me, string dir)
{
        if( dir == "out")delete_temp("rent_paid", me);

        return ::valid_leave(me, dir);
}