inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
你走在一條塵土飛揚的黃土路上，兩旁滿是陰森森的樹林。西面
不遠就是衡陽縣城了。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "northeast": __DIR__"hsroad2",
                "west"     : __DIR__"hengyang2",
        ]));

	set("coor/x", -6870);
	set("coor/y", -5700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}