// Room: /d/quanzhou/micangxiang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "米倉巷");
        set("long", @LONG
這是通往糧倉的小路。由於民間匪盜經常搶劫官府糧倉，都督府震
怒之下，特開此路以利府中官兵增援糧倉。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "southwest" : __DIR__"liangcang",
                "north"     : __DIR__"dudufu",
        ]));
	set("coor/x", -880);
	set("coor/y", -7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}