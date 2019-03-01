inherit ROOM;

void create()
{
        set("short", "雜貨舖");
        set("long", @LONG
這是一家小小的雜貨舖，平時就賣些日常用品，只見貨櫃上放著
各式各樣的貨物，老板正忙著招呼客人，進門處放著一個招牌(zhaop
ai)，上面寫著些許小字。
LONG );
        set("item_desc", ([
                "zhaopai": "請用 \"list\" 列出貨物表，\"buy\" 向老板購物。\n",
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