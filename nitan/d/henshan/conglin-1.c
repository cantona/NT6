inherit ROOM;

void create()
{
        set("short", "叢林");
        set("long", @LONG
這裡是衡山深處的一片樹林，據說黃金白玉虎曾在這裡出沒。
LONG);
        set("exits", ([ 
               "south"       : __DIR__"shanlu14",
        ]));

        set("outdoors", "henshan");

        if (random(10) == 1)
                set("objects", ([
                        "/kungfu/class/misc/goldtiger"  :  1,
                ]));    

	set("coor/x", -6950);
	set("coor/y", -5500);
	set("coor/z", 20);
	setup();
}
