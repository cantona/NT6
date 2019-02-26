//Room: /d/dali/nongtian4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","農田");
        set("long",@LONG
一片臨湖的稻田，田裏積滿了水，田埂很高，且乾燥，可以供走
動，田間挖掘了相當多的引水溝渠。南詔雨水充足，河湖眾多，雖然
是山地地區，灌溉也不成問題。此去東邊有些杆欄民居。
LONG);
        set("objects", ([
           __DIR__"npc/nongfu2": 2,
        ]));
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "southwest" : __DIR__"yangzong",
            "east"      : __DIR__"dalangan1",
        ]));
	set("coor/x", -19010);
	set("coor/y", -6870);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}