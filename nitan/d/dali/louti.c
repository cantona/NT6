//Room: /d/dali/louti.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","樓梯");
        set("long",@LONG
這就是通往二樓“迎賓齋”的樓梯，樓梯高有五十餘級，上面鋪
了鮮紅的毛氈，樓梯兩側站了一些素衣衞士，樓上則是貴賓休息的地
方。
LONG);
        set("objects", ([
           __DIR__"npc/weishi": 3,
           CLASS_D("dali")+"/gaoshengtai": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "up"      : __DIR__"zoulang1",
            "south"   : __DIR__"dating",
        ]));
	set("coor/x", -19151);
	set("coor/y", -6911);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}