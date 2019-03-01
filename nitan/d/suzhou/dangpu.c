// Room: /d/suzhou/dangpu.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "寶和記");
        set("long", @LONG
這是一家以買賣公平著稱蘇州的當舖，一個五尺高的櫃台擋在你的
面前，櫃台上擺著一個牌子(sign)，櫃台後坐著位老板，一雙精明的眼
睛上上下下打量著你。
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