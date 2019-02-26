// Room: /d/suzhou/wenmeige.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "問梅閣");
        set("long", @LONG
問梅閣內的桌凳、花窗、地坪、書畫皆取材於梅花，並懸匾額“綺
窗春訊”。閣前種植了許多枝梅，以符閣名。曾為舊時文人著書、繪畫
之處。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"zhenquting",
                "south" : __DIR__"lixuetang",
        ]));
        set("objects", ([
                __DIR__"npc/lady4" : 1,
        ]));
	set("coor/x", 1150);
	set("coor/y", -1080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}