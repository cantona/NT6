// Room: /city/zahuopu.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "雜貨鋪");
        set("long", @LONG
這是一家小小的雜貨鋪，大箱小箱堆滿了一地，都是一些日常用
品。楊掌櫃懶洋洋地躺在一隻躺椅上，招呼着過往行人。據説私底下
他也賣一些貴重的東西。攤上立着一塊招牌(zhaopai)。
LONG );
	set("item_desc", ([
		"zhaopai": "請用 \"list\" 列出貨物表，\"buy\" 向老闆購物。\n",
	]));
	set("exits", ([
		"north" : "/d/city/dongdajie1",
		"up"    : "/d/city/garments",
	]));
    set("no_fight",1);
    set("no_steal",1);
	set("objects", ([
		"/d/city/npc/yang": 1,
	]));
	set("coor/x", 10);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}