inherit ROOM;

void create()
{
        set("short", "兵營大門");
        set("long", @LONG
你正站在兵營的門口，面對著一排簡陋的營房，可以看到穿著制服的
官兵正在操練，不時地傳來吶喊聲。老百姓是不允許在此觀看的，你最好
趕快走開。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"bingyin",
                  "south" : __DIR__"wroad4",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/guanbing" : 2,
        ]));
	set("coor/x", -7030);
	set("coor/y", 2190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if (! wizardp(me) && objectp(present("guan bing", environment(me))) && 
                dir == "north")
                return notify_fail("官兵攔住了你的去路。\n");
        return ::valid_leave(me, dir);
}