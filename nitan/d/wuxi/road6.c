// Room: /d/wuxi/road6.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "大驛道");
        set("long", @LONG
走在這條行人稀少的官道，雖然不會遇見什麼匪盜，但心裏總是有
些忐忑不安。再向北走就快到了要塞了，向南是通向無錫城裏去的路，
路面乾淨得很。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "south"  : __DIR__"road5",
                "north"  : __DIR__"paotai",
        ]));
        set("coor/x", 1040);
	set("coor/y", -660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}