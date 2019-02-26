// Room: /city/zuixianlou3.c
// YZC 1995/12/04

inherit ROOM;

void create()
{
        set("short", "醉仙樓三樓");
        set("long", @LONG
這裏是三樓，一上來就覺得喧鬧無比，和二樓的清雅恰成反比，
簡直讓你不能相信。幾張原本乾淨整潔的桌子也被糟蹋的一塌糊塗。
湯水淌得滿地，酒呃臭屁滿屋。幾位小二鼻青臉腫的躲在屋角，瑟瑟
發抖，地上還有殘留的血跡。
LONG );
        set("objects", ([
                "/d/city/npc/tao1" : 1,
                "/d/city/npc/tao2" : 1,
                "/d/city/npc/tao3" : 1,
                "/d/city/npc/tao4" : 1,
                "/d/city/npc/tao5" : 1,
                "/d/city/npc/tao6" : 1,
        ]));
        set("exits", ([
                "down" : "/d/city/zuixianlou2",
        ]));
//	set("no_clean_up", 0);
	set("coor/x", 10);
	set("coor/y", 20);
	set("coor/z", 20);
	setup();
	replace_program(ROOM);
}