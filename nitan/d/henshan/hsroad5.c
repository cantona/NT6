inherit ROOM;

void create()
{
        set("short", "林間大道");
        set("long", @LONG
這裏是一條林間大道。這裏是湖南境內。南邊通向南嶺的一個山
口。路東隱隱可以看到一角城牆。西面是一座猛惡山林。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "west"     : "/d/motianya/mtroad1",
                "east"     : __DIR__"hsroad4",
                "north"    : __DIR__"hsroad6",
                "southup"  : __DIR__"hsroad9",
        ]));

	set("coor/x", -6930);
	set("coor/y", -5700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}