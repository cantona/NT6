// Room: /d/fuzhou/wushan.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
        set("short", "福州于山");
        set("long", @LONG
于山因戰國時于越族在此居住而得名。相傳閩越王無諸曾於九月九
日大宴於此，又稱“九日山”，于山之麓的白塔，又稱定光塔，系唐王
審知為了向死去的父母報恩而建。登上白塔榕城歷歷如畫。
LONG );
        set("exits", ([
                "northdown" : __DIR__"dongdajie",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -70);
	set("coor/y", -6190);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}