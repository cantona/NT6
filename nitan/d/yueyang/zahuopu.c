// Room: /d/yueyang/zahuopu.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "雜貨舖");
        set("long", @LONG
這是一家小小的雜貨舖，好象生意蠻好的樣子，貨物不少，堆得也
亂，老板顯然沒時間整理這個小小店面。這不，你一進來，他就迎了上
來。
    牆上貼著一塊招牌(zhaopai)。
LONG );
        set("item_desc", ([
                "zhaopai": "請用 \"list\" 列出貨物表，\"buy\" 向老板購物。\n",
        ]));
        set("exits", ([
                "west" : __DIR__"beijie",
        ]));
        set("objects", ([
                __DIR__"npc/laoban": 1,
        ]));
	set("coor/x", -6190);
	set("coor/y", -3000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}