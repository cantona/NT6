// Room: /d/suzhou/caixingjing.c
// Last Modified by Winder on May. 15 2001

inherit ROOM;

void create()
{
        set("short", "採香徑");
        set("long",@long
這裡名為採香徑，又稱“一箭徑”，此溪乃吳王夫差陪西施遊山之
必經之水道，也是越伐吳時，范蠡攜西施，駕小舟出逃之處。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "northeast" : __DIR__"shuiwa",
                "northwest" : __DIR__"shuiwa1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1120);
	set("coor/y", -1160);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}