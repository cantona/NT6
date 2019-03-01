inherit ROOM;

void create()
{
        set("short", "林間大道");
        set("long", @LONG
這裡是一條林間大道，在樹叢中蜿蜒。這裡已是湖南境內。北邊
是湖北。路邊有可供路人休息的小茶亭。
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "west"        : "/d/heizhao/shanlu1",
                "northwest"   : "/d/heizhao/shanlu6",
                "southwest"   : "/d/tiezhang/lx",
                "east"   : __DIR__"chating",
                "north"  : __DIR__"hsroad7",
                "south"  : __DIR__"hsroad5",
        ]));

	set("coor/x", -6930);
	set("coor/y", -5690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}