inherit ROOM;

void create()
{
        set("short", "雜貨鋪");
        set("long", @LONG
這是一家小小的雜貨鋪，平時就賣些日常用品，只見貨櫃上放着
各式各樣的貨物，老闆正忙着招呼客人，進門處放着一個招牌(zhaop
ai)，上面寫着些許小字。
LONG );
        set("item_desc", ([
                "zhaopai": "請用 \"list\" 列出貨物表，\"buy\" 向老闆購物。\n",
        ]));
        set("exits", ([
                "south"    : __DIR__"hengyang2",
        ]));
        set("objects", ([
                __DIR__"npc/qiang": 1,
        ]));

	set("coor/x", -6880);
	set("coor/y", -5690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}