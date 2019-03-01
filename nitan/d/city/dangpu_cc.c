// Room: /city/dangpu_cc.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "當舖儲藏間");
        set("long", @LONG
這是一家以買賣公平著稱的當舖，一個五尺高的櫃台擋在你的面
前，櫃台上擺著一個牌子(paizi)，櫃台後坐著唐老板，一雙精明的上
上下下打量著你。
LONG );
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg",1);
	set("item_desc", ([
		"paizi" : "公平交易\n
sell        賣 
buy         買
redeem      贖
value       估價
",
	]));

	setup();
	replace_program(ROOM);
}