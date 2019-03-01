// Room: /d/nanyang/kedian2.c
// Last Modified by winder on Nov. 20 2001

inherit ROOM;

void create()
{
        set("short", "客店二樓");
        set("long", @LONG
這是一間很大的客房，陳設十分簡陋。靠牆放了十幾張小木床，不
少客人正和衣而臥，滿屋子都是呼呼的打酣聲。西邊有張床是空的，你
躡手躡腳地走了過去。
LONG );
        set("sleep_room",1);
        set("exits", ([
                "down" : __DIR__"kedian1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -6930);
	set("coor/y", 770);
	set("coor/z", 10);
	setup();
}

int valid_leave(object me, string dir)
{

        if( dir == "down")delete_temp("rent_paid", me);

        return ::valid_leave(me, dir);
}