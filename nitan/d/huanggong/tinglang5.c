// Room: /d/huanggong/tinglang5.c

inherit ROOM;

void create()
{
        set("short", "廳廊");
        set("long", @LONG
飛檐雕欄的廳廊. 兩邊是喜人的花草, 站在這兒, 隱約聽得到後宮
裡嬪妃宮女們嬉笑的聲音, 宮裡的人來來往往的, 顯得井井有條, 看來
宮裡的規矩挺嚴的.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 3 */
                "east"  : __DIR__"gong10",
                "west"  : __DIR__"gong9",
                "south" : __DIR__"tinglang6",
                "north" : __DIR__"tinglang4",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2790);
	set("coor/y", 7771);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}