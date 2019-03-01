// Room: /d/quanzhou/chuanwu.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "船塢");
        set("long", @LONG
這裡是雲集了全國最好的造船技師和工匠。一眼望去，滿是已完工
和即將完工的各種用途，各種大小的木船。塢內人們忙忙碌碌，一片繁
忙景象。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "west" : __DIR__"portroad4",
        ]));
        set("objects", ([
                __DIR__"npc/kuli" : 1,
        ]));
	set("coor/x", -880);
	set("coor/y", -7760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}