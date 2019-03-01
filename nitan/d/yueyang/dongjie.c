// Room: /d/yueyang/dongjie.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "東街");
        set("long", @LONG
這是一條又長又寬的青石大道，打掃得十分幹凈。屋檐下，偶有小
孩淘氣撒尿，立馬就給大人拎著耳朵拖走。原來，北邊就是府衙，西邊
雖然喧鬧，這條街卻十分安靜。南邊是一個茶館。來來往往的客商常去
歇腳，而公人也時有前去飲茶納涼的。
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"zhongxin",
                "south" : __DIR__"chaguan",
                "north" : __DIR__"yamen",
        ]));
        set("objects", ([
                __DIR__"npc/liumang" : 1,
        ]));
	set("coor/x", -6190);
	set("coor/y", -3010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}