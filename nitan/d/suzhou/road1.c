// Room: /d/suzhou/road1.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "麻石大道");
        set("long", @LONG
你走在一條麻石大道上，人來人往非常繁忙，不時地有人騎著馬匆
匆而過。大道兩旁有一些小貨攤，似乎是一處集市。往南面就是號稱天
堂的蘇州城了。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "south"     : __DIR__"beimen",
                "southwest" : __DIR__"huqiu",
                "northeast" : __DIR__"sanglin",
                "northwest" : "/d/wuxi/road4",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
	set("coor/x", 1110);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}