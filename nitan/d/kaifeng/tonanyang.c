// /kaifeng/tonanyang.c
// Last modified by winder 2003.10.20

inherit ROOM;

void create()
{
        set("short", "官道");
        set("long", @LONG
這是條連接開封府與南陽府的官道，由于這條路治安較好
行人也不少。西面通向開封，東面通向南陽。
LONG
        );
        set("exits", ([
                "west" : __DIR__"tokaifeng",
                "east" : "/d/nanyang/yidao3",
        ]));
        set("outdoors", "kaifeng");
        set("no_clean_up", 0);

	set("coor/x", -4990);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}