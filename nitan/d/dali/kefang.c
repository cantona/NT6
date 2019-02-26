//Room: /d/dali/kefang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","客房");
        set("long",@LONG
這是一間客房，靠牆放了一張梨木大牀，上面的被褥盡是蘇
繡，工美絕倫。正中放了一張八仙桌，幾個奇服南人正在高談闊
論。
LONG);
        set("objects", ([
           __DIR__"npc/peicong": 3,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "out"      : __DIR__"zoulang2",
        ]));
	set("coor/x", -19162);
	set("coor/y", -6912);
	set("coor/z", 8);
	setup();
        replace_program(ROOM);
}