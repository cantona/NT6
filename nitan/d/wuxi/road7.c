// Room: /d/wuxi/road7.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "林蔭道");
        set("long", @LONG
一條不寬的林蔭道，兩排香樟樹在路兩邊搭起了一個天然的涼蓬，
中間夾雜著一些楊柳樹，在風中搖搖盪盪，令人心曠神怡。北面是清
名橋，向南一直通向太湖。西邊有一條小道，通向梅村的泰伯廟。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "west"   : __DIR__"road8",
                "south"  : __DIR__"road10",
                "north"  : __DIR__"qingmingqiao",
        ]));
        set("coor/x", 1040);
	set("coor/y", -790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}