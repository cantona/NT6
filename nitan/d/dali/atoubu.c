//Room: /d/dali/atoubu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","阿頭部");
        set("long",@LONG
阿頭部是烏雜蠻的部落，和附近的烏蠻一樣，也屬於烏夷。這裏
山高林密，不熟的人輕率進山，很容易迷路喪命。深山對烏夷獵人來
説卻是聚寶盆，山中野物皆是美味。
LONG);
        set("objects", ([
           __DIR__"npc/lieren": 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "north"      : __DIR__"lushui",
            "westup"     : __DIR__"gaolishan1",
            "southeast"  : __DIR__"yixibu",
        ]));
	set("coor/x", -19210);
	set("coor/y", -6890);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}