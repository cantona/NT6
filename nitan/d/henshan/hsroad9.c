inherit ROOM;

void create()
{
        set("short", "南嶺山口");
        set("long", @LONG
這裏是南嶺的一個山口。南面是嶺南的大鎮佛山，北面是湖南的
地界。嶺南廣東富庶繁盛，頗有豪俠之士。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "northdown" : __DIR__"hsroad5",
                "southdown" : "/d/foshan/nanling",
        ]));
	set("coor/x", -6930);
	set("coor/y", -5710);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}