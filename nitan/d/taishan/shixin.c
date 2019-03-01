// Room: /d/taishan/shixin.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "試心石");
        set("long", @LONG
這裡便是蓮花峰的峰頂，由兩塊巨石勾連在一起，據說若果你心存
誠意，登上試心石時石塊便不會動搖，反之則搖動不止。
LONG );
        set("exits", ([
                "southdown" : __DIR__"lianhua",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 50);
	set("coor/y", 310);
	set("coor/z", 210);
	setup();
        replace_program(ROOM);
}