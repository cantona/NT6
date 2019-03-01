inherit ROOM;

void create()
{
        set("short", "小溪");
        set("long",@LONG
這是神龍島東南的一處小溪。
LONG);

	set("exits", ([
		"north"  : __DIR__"lin1.16", 		
		"south" : __DIR__"xiaoxi2",

	]));

        set("outdoors", "shenlong");
        setup();
}
