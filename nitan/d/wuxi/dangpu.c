// Room: /d/wuxi/dangpu.c
// Winder 2000/02/22 

inherit ROOM;

int do_quit();
void create()
{
        set("short", "當鋪");
        set("long", @LONG
這是一家以買賣公平著稱的當鋪，一個五尺高的櫃枱擋在你的面前，
櫃枱上擺着一個牌子 (paizi)，櫃枱後坐着馮老闆，一雙精明的上上下
下打量着你。
LONG
        );
        set("no_fight", 1);
        set("no_steal", 1);
        set("no_beg",1);
//        set("no_clean_up", 0);
        set("item_desc", ([
                "paizi" : "公平交易\n
sell        賣 
buy         買
value       估價
",
        ]));
        set("objects", ([
                __DIR__"npc/feng" : 1,
        ]));
        set("exits", ([
                "south" : __DIR__"westroad1",
        ]));

        set("coor/x", 1030);
	set("coor/y", -720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}