// /d/yixing/cldating.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;

void create()
{
        set("short", "大廳");
        set("long", @LONG
大廳中一股肅殺威嚴之氣。廳堂極為寬大，能容下數十人之眾。只
見四周桌上點着明晃晃的巨燭，正中空着一張虎皮交椅。不時有幫眾經
過這裏，都是屏息靜氣地低頭走過。。
LONG );

        set("exits", ([
                "out"   : __DIR__"cldamen",
                "north" : __DIR__"clzoulang1",
        ]));
        set("objects",([
                __DIR__"npc/cl_bei" : 1,
        ]));
        set("coor/x", 279);
	set("coor/y", -1011);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}