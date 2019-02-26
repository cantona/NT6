// Room: /d/quanzhou/zahuopu.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "雜貨鋪");
        set("long", @LONG
這是一家小小的雜貨鋪，大箱小箱堆滿了一地，都是一些日常用品。
楊掌櫃懶洋洋地躺在一隻躺椅上，招呼着過往行人。據説私底下他也賣
一些貴重的東西。攤上立着一塊招牌(zhaopai)。
LONG );
        set("item_desc", ([
                "zhaopai" : "請用 list 列出貨物表，buy 向老闆購物。\n",
        ]));
        set("exits", ([
                "south" : __DIR__"westroad1",
        ]));
        set("objects", ([
                __DIR__"npc/chen" : 1,
        ]));
	set("coor/x", -910);
	set("coor/y", -7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}