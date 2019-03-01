// /guanwai/tulu.c

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long", @LONG
這是一條用黃土舖就的道路。許多馬車不斷來往，似乎在搬運石料。
你抬頭了望，一輛輛滿載石料的車子往西北城中而去，而一輛輛的空車
卻源源不斷的開向東邊。直弄得土路上塵土飛揚。
LONG );
        set("exits", ([
                "east" : __DIR__"shichang",
                "northwest" : __DIR__ "nancheng",
        ]));

        set("outdoors", "guanwai");
        set("coor/x", 4000);
	set("coor/y", 9220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
