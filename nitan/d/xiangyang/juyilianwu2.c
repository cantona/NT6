// Room: /d/xiangyang/juyilianwu2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "練功場");
        set("long", @LONG
這裏是聚義館中用來練功的地方。有幾個人正在專心致致地練武，
有幾個手持兵器，在互相拆招。身法靈動，猶如穿花蝴蝶一般，你不
禁看花了眼，別的人則坐在地上的蒲團上苦練內力。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "east" : __DIR__"juyiyuan",
        ]));
        set("objects", ([
                "/clone/npc/tong-ren" : 3,
        ]));
        set("coor/x", -7850);
	set("coor/y", -780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}