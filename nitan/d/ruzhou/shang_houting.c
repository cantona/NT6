inherit ROOM;

void create()
{
        set("short", "後廳");
        set("long", @LONG
這裡是商家堡的後廳所在，大廳相當的寬敞明亮，四周的牆
上懸掛滿了各朝名人的真跡。
LONG);
        set("exits", ([
                "north"  : __DIR__"shang_zoulang1",
                "south"  : __DIR__"shang_dating",
                "west"  : __DIR__"shang_xiangw",
                "east"  : __DIR__"shang_xiange",
        ]));
	set("coor/x", -6750);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}