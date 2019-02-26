// Room: /d/quanzhou/kaojiaochang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "考教場");
        set("long", @LONG
這裏是武館的考教場，面積甚大。有許多武館子弟在此習武，拳打
腳踢，舞刀弄劍，耍槍揮棒的好不熱鬧。穿過考教場便是武館的前廳。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "east" : __DIR__"wuguangate",
                "west" : __DIR__"dating",
        ]));
        set("objects", ([
                __DIR__"npc/xuetu" : 1,
        ]));
	set("coor/x", -930);
	set("coor/y", -7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}