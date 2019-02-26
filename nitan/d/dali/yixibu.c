//Room: /d/dali/yixibu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","易溪部");
        set("long",@LONG
易溪部也是烏夷族烏雜蠻的部落。這裏處半坡地，附近有不少農
田，但農業落後，需要換季輪耕，因而村民經常遷徙，鎮子裏除了祭
祀大屋外，其它房屋都很簡陋。
LONG);
        set("objects", ([
           __DIR__"npc/shaonu": 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "northwest"  : __DIR__"atoubu",
            "south"      : __DIR__"wuyiminju4",
            "east"       : __DIR__"biluoshan",
        ]));
	set("coor/x", -19200);
	set("coor/y", -6900);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}