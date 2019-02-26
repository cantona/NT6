inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
這裏是一排青石鋪砌的石階，往北可以通往蕭湘書院，往南則是
一片翠綠的竹林。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "southdown" : __DIR__"zizhulin",
                "north" : __DIR__"shuyuan1",
        ]));
        set("coor/x", -7090);
	set("coor/y", -2080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}