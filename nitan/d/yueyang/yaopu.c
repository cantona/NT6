// Room: /d/yueyang/yaopu.c
// Last Modifyed by Winder on Dec. 4 2001
inherit ROOM;

void create()
{
        set("short", "藥鋪");
        set("long", @LONG
這是一家藥鋪，一股濃濃的藥味讓你幾欲窒息。櫃枱後面是一個大
藥櫃，密密麻麻的的幾百個小抽屜裏你也懶得數了。櫃枱後站在一名小
夥計，一雙賊兮兮的眼睛不時掃過你的腰部。
    櫃上立着一塊招牌(zhaopai)。
LONG );
        set("item_desc", ([
                "zhaopai": "請用 \"list\" 列出貨物表，\"buy\" 購物。\n",
        ]));
        set("objects", ([
                __DIR__"npc/huoji" : 1,
        ]));
        set("exits", ([
                "east" : __DIR__"beijie",
        ]));
	set("coor/x", -6210);
	set("coor/y", -3000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}