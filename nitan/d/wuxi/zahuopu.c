// Room: /d/wuxi/zahuopu.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "雜貨舖");
        set("long", @LONG
這是一家小小的雜貨舖，大箱小箱堆滿了一地，都是一些日常用品。
楊掌櫃懶洋洋地躺在一只躺椅上，招呼著過往行人。據說私底下他也賣
一些貴重的東西。攤上立著一塊招牌(zhaopai)。
LONG );
        set("item_desc", ([
                "zhaopai": "請用 \"list\" 列出貨物表，\"buy\" 向老板購物。\n",
        ]));
        set("exits", ([
                "east" : __DIR__"southroad1",
        ]));
        set("objects", ([
                __DIR__"npc/ma": 1,
        ]));
        set("coor/x", 1030);
	set("coor/y", -740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}