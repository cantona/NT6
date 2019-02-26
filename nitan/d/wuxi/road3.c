// Room: /d/wuxi/road3.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "大驛道");
        set("long", @LONG
這裏已經進入了蘇州府管轄的地界了，驛道直直地向東西方延伸
開去。路旁是十分精神的的楊柳樹。路上來來去去的，好像是做生意
的商人小販不少。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"road4",
                "west"  : __DIR__"road2",
        ]));
        set("coor/x", 1100);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}