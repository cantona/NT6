inherit ROOM;

void create()
{
        set("short", "鰲府大院");
        set("long", @LONG
你走進大院，迎面是一個大花園，花園中假山水池，很是美觀。
池中立着一塊巨大無比的翡翠，顯然是鰲狠搜刮來的寶物。水池的兩
旁種滿了花草，鬱鬱葱葱，樹木枝葉茂密，遮蓋了大半個院子，顯得
陰森恐怖。北邊一條長長的木製長廊，通往鰲府的大廳。
LONG );
        set("exits", ([
                "north" :  "/d/beijing/aofu_dating",
                "south" :  "/d/beijing/aofu_zoulang1",
        ]));
        set("objects", ([
                "/d/beijing/npc/yuanding" : 1,
        ]));

	set("coor/x", -2820);
	set("coor/y", 7760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}