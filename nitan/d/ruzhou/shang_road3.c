inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
小鎮旁的一條小路，因為平時過往之人不多的緣故，周圍都
已長滿了雜草。遠遠的向西望去，似乎有一座大宅。
LONG);
        set("exits", ([
                //"west"  : __DIR__"shang_road2",
                "west"  : __DIR__"xiaozheng",
                "north"  : __DIR__"shang_men",
        ]));
        set("outdoors", "ruzhou");
	set("coor/x", -6750);
	set("coor/y", 1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}