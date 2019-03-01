// Room: /d/wuxi/road4.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "大驛道");
        set("long", @LONG
快馬加鞭，走在江南平坦的驛道上，微風拂面，揚柳搖擺，心情
也變得十分愉快。驛道直直地向東西方延伸過去。向東遠遠地就已經
看見蘇州的北平門了，道上的行人也多了不少。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "southeast"  : "/d/suzhou/road1",
                "west"       : __DIR__"road3",
        ]));
        set("coor/x", 1110);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}