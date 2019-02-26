// Room: /d/wuxi/road10.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "林蔭道");
        set("long", @LONG
一條不寬的林蔭道，兩排香樟樹在路兩邊搭起了一個天然的涼蓬，
中間夾雜着一些楊柳樹，在風中搖搖蕩蕩，令人心曠神怡。北面是通
向無錫城裏去的。再向南就要到太湖了。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "north"   : __DIR__"road7",
                "south"   : __DIR__"road11",
        ]));
        set("objects", ([
                __DIR__"npc/shusheng" : 1,
        ]));
        set("coor/x", 1040);
	set("coor/y", -800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}