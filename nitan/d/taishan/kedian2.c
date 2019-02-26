// /d/taishan/kedian2.c

inherit ROOM;

void create()
{
        set("short", "客店二樓");
        set("long", @LONG
這是一間很大的客房，陳設十分簡陋。靠牆放了十幾張小木牀，
不少客人正和衣而卧，滿屋子都是呼呼的打酣聲。西邊有張牀是空的，
你躡手躡腳地走了過去。
LONG );
        set("sleep_room",1);
        set("exits", ([
                "down" : __DIR__"kedian",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 80);
	set("coor/y", 30);
	set("coor/z", 10);
	setup();
}

int valid_leave(object me, string dir)
{

        if( dir == "down")delete_temp("rent_paid", me);

        return ::valid_leave(me, dir);
}