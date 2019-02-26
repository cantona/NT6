// Room: /d/xiangyang/westjie2.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
這兒是很大的十字街口，北邊是西內大街，南面是一座綵樓，樓
前高高的掛着一方大匾，上面用正楷寫着『聚義館』，落款『朱子柳
』。東邊通向中央廣場，西面可達白虎門。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "east"  : __DIR__"westjie1",
                "west"  : __DIR__"westjie3",
                "south" : __DIR__"juyiyuan",
                "north" : __DIR__"westroad1",
        ]));
        set("objects", ([
                __DIR__"npc/wusantong" : 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("coor/x", -7840);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}