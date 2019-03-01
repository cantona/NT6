inherit ROOM;

void create()
{
        set("short", "獅子巖");
        set("long", @LONG
獅子巖布滿奇形怪狀的巖石，細究則絕類獅子，騰躍伏吼，各肖
其類。到獅子巖，祝融峰已經在望了。
LONG );
        set("exits", ([ 
               "southwest"  : __DIR__"nantian",
               "northup"    : __DIR__"wangritai",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6930);
	set("coor/y", -5510);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}