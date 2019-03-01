//Room: /d/dali/hole.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","大，小芝雲洞");
        set("long", @LONG
帶著火折進入洞內，迂回蛇行，不久，即見一廳豁然開朗，石鐘
乳，石筍，石柱，玲瓏剔透，鬥奇爭勝。光照壁影，如月穿曉巖，溪
雲接水，壁氣侵寒，石光滴翠，清幽可愛。
LONG );
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "out"      : "/d/dali/changhu",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19161);
	set("coor/y", -6801);
	set("coor/z", 29);
	setup();
        replace_program(ROOM);
}