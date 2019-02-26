// Room: /d/fuzhou/rongcheng2.c
// Date: Feb.14.1998 by Java
inherit ROOM;

void create()
{
        set("short", "榕城驛二樓");
        set("long", @LONG
這是一間很大的客房，陳設十分簡陋。靠牆放了十幾張小木牀，不
少客人正和衣而卧，滿屋子都是呼呼的打酣聲。你看到西邊有張牀是空
的，就躡手躡腳地走了過去。
LONG );
        set("sleep_room", "1");
        set("no_fight", "1");
        set("hotel",1);
        set("no_clean_up", 0);
        set("exits", ([
            "down" : __DIR__"rongcheng",
        ]));
	set("coor/x", -70);
	set("coor/y", -6170);
	set("coor/z", 10);
	setup();
}
int valid_leave(object me, string dir)
{
        if( dir == "out")delete_temp("rent_paid", me);

        return ::valid_leave(me, dir);
}