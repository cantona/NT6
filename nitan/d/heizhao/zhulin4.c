// Room: /heizhao/zhulin4.c
// Date: Oct.28 1999 by Winder
inherit ROOM;

void create()
{
        set("short", "竹林");
        set("long",@LONG
鳳尾森森，龍吟細細，竿竿青竹縱橫交錯，遮蔽天日。這裏人
跡罕至，微風拂過竹林，發出沙沙之聲，你只覺綠蔭森森，幽靜無
比，令人煩俗盡消。林中一道道石子鋪成的羊腸小道向前延伸。
LONG );
        set("outdoors", "taoyuan");
        set("exits", ([
            "west" : __DIR__"zhulin1",
            "east" : __DIR__"zhulin2",
            "north": __DIR__"houyuan",
            "south": __DIR__"zhulin4",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -5020);
        set("coor/y", -1100);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}