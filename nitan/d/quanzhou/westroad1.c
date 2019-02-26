// Room: /d/quanzhou/westroad1.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "刺桐西路");
        set("long", @LONG
這是泉州的主要幹道，筆直寬廣，車水馬龍，熱鬧非凡。西邊便是
著名的開元寺及西門吊橋。北邊有一家雜貨鋪。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"westroad2",
                "east"  : __DIR__"guangchang",
                "north" : __DIR__"zahuopu",
        ]));
	set("coor/x", -910);
	set("coor/y", -7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}