// Room: /d/quanzhou/xuetang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "學堂");
        set("long", @LONG
這是城裏的一所學堂，城中的子弟便在此上課。學堂裏的櫃子裏擺
滿了書籍。教書先生便是響譽泉州的歐陽詹先生。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"guitangxiang",
        ]));
        set("objects", ([
                __DIR__"npc/ouyangzhan" : 1,
        ]));
	set("coor/x", -890);
	set("coor/y", -7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}