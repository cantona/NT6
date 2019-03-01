// Room: bingqidian.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "兵器鋪");
        set("long", @LONG
這着是一家小小店面的兵器鋪，可是賣的兵器可不尋常。種類固
然中土難得一見，能用的人更是稀少。掌櫃的拿着眼瞟得你直發毛。
你轉臉就看到牆上的招牌(zhaopai)。
LONG );
        set("item_desc", ([
                "zhaopai": "請用 \"list\" 列出貨物表，\"buy\" 向老闆購物。\n",
        ]));
        set("objects", ([
                __DIR__"npc/tanghuai" : 1,
        ]));
//         set("no_clean_up", 0);
        set("exits", ([
            "southeast" : __DIR__"northroad1",
        ]));

        set("coor/x", -15240);
	set("coor/y", -1800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}