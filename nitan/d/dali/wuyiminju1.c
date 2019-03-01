//Room: /d/dali/wuyiminju1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","烏夷民居");
        set("long", @LONG
這是一所烏夷族的房屋。烏夷民居的建地和走向講究依傍四面山
勢，一般以石為牆和基，以木為樑，結構大致和漢人房屋相仿，皆是
平房，石砌圍牆。這家院內有一圈牲畜，豬牛羊皆有。
LONG );
        set("objects", ([
           "/d/dali/npc/muyangnu": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/dali/wumeng",
        ]));
	set("coor/x", -19170);
	set("coor/y", -6770);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}