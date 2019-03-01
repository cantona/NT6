inherit ROOM;

void create()
{
        set("short", "黃土路");
        set("long", @LONG
你走在一條塵土飛揚的黃土路上，兩旁滿是陰森森的樹林。東面
不遠就是衡陽縣城了。往西是另外一條大道。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "east"  : __DIR__"hengyang11",
                "west"  : __DIR__"hsroad5",
        ]));

	set("coor/x", -6920);
	set("coor/y", -5700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}