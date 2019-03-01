// Room: /d/henshan/hsroad1.c 黃土路
// Modified By Java Feb.14.1998

inherit ROOM;

void create()
{
        set("short", "黃土路");
        set("long", @LONG
你走在一條塵土飛揚的黃土路上，兩旁是陰森森的樹林。這裡向北通往
揚州，往南就進入湖南地界了。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "northeast" : "/d/wudang/wdroad4",
                "south" : __DIR__"hsroad2",
        ]));

        set("no_clean_up", 0);
	set("coor/x", -6860);
	set("coor/y", -5680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}