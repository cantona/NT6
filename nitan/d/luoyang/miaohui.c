inherit ROOM;

void create()
{
        set("short", "廟會");
        set("long", @LONG
這裡是洛陽城的廟會，只要你身上有兩錢兒，在這裡就會受到熱情的
招呼。任何你不知道的事，你在這裡打聽一下，都可以知道個八九不離十。
整個廟會裡有貨郎，賣肉的，賣玩具的，賣藝的，賣藥的，雜耍的，風味
小吃，應有盡有。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"wanju",
                  "south" : __DIR__"eroad4",
        ]));
        set("objects", ([
                "/d/beijing/npc/xianren" : 2,
        ]));
	set("coor/x", -6950);
	set("coor/y", 2160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}