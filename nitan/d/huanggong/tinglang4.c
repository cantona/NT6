// Room: /d/huanggong/tinglang4.c

inherit ROOM;

void create()
{
        set("short", "廳廊");
        set("long", @LONG
飛檐雕欄的廳廊. 兩邊是喜人的花草, 站在這兒, 隱約聽得到後宮
裏嬪妃宮女們嬉笑的聲音, 宮裏的人來來往往的, 顯得井井有條, 看來
宮裏的規矩挺嚴的.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 3 */
                "west"  : __DIR__"gong7",
                "east"  : __DIR__"gong8",
                "south" : __DIR__"tinglang5",
        ]));
        set("objects", ([ /* sizeof() == 3 */
                __DIR__"npc/laowu" :1,
        ]));

	set("coor/x", -2790);
	set("coor/y", 7781);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}