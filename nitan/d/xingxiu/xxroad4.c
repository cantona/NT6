// Room: /d/xingxiu/xxroad4.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
你走在一條在山壁上人工開鑿出來崎嶇的小路上，這裏寒風凜冽，
西面是望不見底的深澗。
LONG );
        set("exits", ([
                "southdown" : __DIR__"tianroad3",
                "north" : __DIR__"xxroad5",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xingxiu");
        set("coor/x", -51000);
        set("coor/y", 20110);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}