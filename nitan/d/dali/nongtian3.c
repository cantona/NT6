//Room: /d/dali/nongtian3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","農田");
        set("long",@LONG
這裡已經是平原的盡頭，對面就是險峻的山嶺了，一些的農田和
羅伽部村民的房屋零星地分布在山腳下，一些村民正在田裡耕作。有
條道路向東南的山上蜿蜒而去。
LONG);
        set("objects", ([
           __DIR__"npc/nongfu2": 1,
        ]));
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "west"      : __DIR__"nongtian2",
            "southeast" : __DIR__"shanlu7",
        ]));
	set("coor/x", -19050);
	set("coor/y", -6870);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}