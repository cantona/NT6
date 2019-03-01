//Room: /d/dali/yanan2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","沿池小路");
        set("long", @LONG
這是一條沿著滇池南岸的小路，柳蔭夾岸，清風襲人。遠望滇池
湖面，碧波盪漾，飛鳥戲水，遙遙可見遊船、漁船輕帆浮雲。端地是
人間仙境。此路向西直上滇池西岸的群山。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "east"    : "/d/dali/yanan1",
            "westup"  : "/d/dali/bijishan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19090);
	set("coor/y", -6880);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}