// Room: /d/huanggong/jiao3.c

inherit ROOM;

void create()
{
        set("short", "城角");
        set("long", @LONG
這裡是內城的一角, 頭上的天空只能見方方的一角. 上面有座漂亮
的角樓.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 3 */
                "south" : __DIR__"dao7",
                "up"    : __DIR__"lou3",
                "east"  : __DIR__"dao6",
        ]));
        set("no_clean_up", 0);

        set("objects", ([
                __DIR__"npc/yulin2"  : 2,
        ]));

	set("coor/x", -2840);
	set("coor/y", 7751);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}