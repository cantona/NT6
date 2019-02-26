// Room: /d/suzhou/dangpu.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "寶和記");
        set("long", @LONG
這是一家以買賣公平著稱蘇州的當鋪，一個五尺高的櫃枱擋在你的
面前，櫃枱上擺着一個牌子(sign)，櫃枱後坐着位老闆，一雙精明的眼
睛上上下下打量着你。
LONG );
        set("no_fight", 1);
        set("no_steal", 1);
        set("no_beg",1);
        set("no_clean_up", 0);
        set("exits", ([
                "north"  : __DIR__"dongdajie1",
        ]));
        set("item_desc", ([
                "sign" : "公平交易\n
sell        賣 
buy         買
value       估價
",
        ]));
        set("objects", ([
                __DIR__"npc/wang" : 1,
        ]));
	set("coor/x", 1120);
	set("coor/y", -1070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}