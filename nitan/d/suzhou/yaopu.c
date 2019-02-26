// Room: /d/suzhou/yaopu.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "立春堂");
        set("long", @LONG
這是一家藥鋪，一股濃濃的藥味讓你幾欲窒息，那是從藥櫃上的幾
百個小抽屜裏散發出來的。藥房先生卻不在店內。一名小夥計站在櫃枱
後招呼着顧客。
LONG );
        set("outdoors", "suzhou");
//        set("no_clean_up", 0);
        set("exits", ([
                "south"  : __DIR__"dongdajie2",
        ]));
        set("objects", ([
                __DIR__"npc/huoji" : 1,
        ]));
	set("coor/x", 1130);
	set("coor/y", -1050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}