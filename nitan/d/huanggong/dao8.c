// Room: /d/huanggong/dao8.c

inherit ROOM;

void create()
{
        set("short", "宮道");
        set("long", @LONG
這是紫禁內外城間的宮道. 平日裏一些人物出入內宮, 就是走這路
的. 這宮道上每日都有大內侍衞來回巡邏, 出入可要小心. 宮道兩邊高
高的紅牆, 正是為了攔阻入侵高手的.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 2 */
                "east"  : __DIR__"ciningmen",
                "north" : __DIR__"dao7",
                "south" : __DIR__"xihuamen",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2840);
	set("coor/y", 7731);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}