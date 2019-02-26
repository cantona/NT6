// Room: /d/taishan/baidong.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "柏洞");
        set("long", @LONG
你走到這裏，但見古柏夾道，濃郁遮天，人行其中如入洞穴，雖炎
夏酷暑而涼氣宜人，暑氣頓消。清代張玢題“柏洞”。
LONG );
        set("exits", ([
                "northup" : __DIR__"sihuaishu",
                "south"   : __DIR__"dengxian",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 70);
	set("coor/y", 160);
	set("coor/z", 60);
	setup();
        replace_program(ROOM);
}