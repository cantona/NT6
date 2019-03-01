// Room: /d/quanzhou/chengtiansi.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "承天寺");
        set("long", @LONG
這是泉州市民祭天求安的寺廟，以保佑年年得以五谷豐登，風調雨順。寺
內廣場中央有一法壇。承天寺西方通往刺桐南路。
LONG );
        set("exits", ([
                "west"      : __DIR__"southroad2",
                "northeast" : __DIR__"guitangxiang",
        ]));
        set("objects", ([
                "/d/hangzhou/npc/seng" : 1,
        ]));
	set("coor/x", -890);
	set("coor/y", -7700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}