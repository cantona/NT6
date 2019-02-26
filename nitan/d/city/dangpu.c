// Room: /city/dangpu.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "當鋪");
        set("long", @LONG
這是一家官家開的當鋪，正對着對面的賭場，緊鄰着的則是揚州
有名的妓院麗春院，那些手頭不寬的狂賭客和嫖客自然是這裏的常客
了。一個五尺高的櫃枱擋在你的面前，上面漆的字已經很模糊了，依
稀是『童叟無欺』幾個字。櫃枱上掛着塊牌子 (paizi)，後坐着的唐
老闆，一雙精明的小眼睛上上下下打量着你。
LONG );
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg",1);
	set("item_desc", ([
		"paizi" : "公平交易\n
sell        賣 
buy         買
pawn        當
redeem      贖
value       估價
",
	]));
	set("objects", ([
		"/d/city/npc/tang" : 1,
	]));
	set("exits", ([
		"west" : "/d/city/nandajie1",
	]));

	set("coor/x", 10);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}