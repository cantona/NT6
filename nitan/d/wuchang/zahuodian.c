//Edited by fandog, 02/15/2000

inherit ROOM;

void create()
{
        set("short", "雜貨店");
        set("long", @LONG
這是一家小小的雜貨店，大箱小箱堆滿了一地，都是一些日常用品。
掌櫃的懶洋洋地躺在一隻躺椅上，招呼着過往行人。據説私底下他也賣
一些貴重的東西。攤上立着一塊招牌(zhaopai)。
LONG );
        set("item_desc", ([
                "zhaopai": "請用 \"list\" 列出貨物表，\"buy\" 向老闆購物。\n",
        ]));
        set("exits", ([
                "east" : __DIR__"hzjie5",
        ]));
        set("objects", ([
                __DIR__"npc/boss": 1,
        ]));
	set("coor/x", -5100);
	set("coor/y", -1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}