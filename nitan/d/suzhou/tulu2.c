// Room: /d/suzhou/tulu2.c
// Last Modified by Winder on May. 15 2001

inherit ROOM;

void create()
{
        set("short", "土路");
        set("long",@long
你來到了一條土路上。西南邊有條江，遠遠看去不甚寬闊。往東北
邊走可以找到是去蘇州的官道。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "northeast" : __DIR__"tulu1",
                "southwest" : __DIR__"jiangbian",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1040);
	set("coor/y", -1080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}