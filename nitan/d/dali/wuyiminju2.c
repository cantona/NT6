//Room: /d/dali/wuyiminju2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","烏夷民居");
        set("long", @LONG
這是一所烏夷族的房屋。烏夷民居的建地和走向講究依傍四面山
勢，一般以石為牆和基，以木為樑，結構大致和漢人房屋相仿，皆是
平房，石砌圍牆。這家院內有一排木架，掛了些山雞、野鴨、羚羊等
獵物，一個獵人正在給獵物剝皮開膛。
LONG );
        set("objects", ([
           "/d/dali/npc/lieren": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "north"  : "/d/dali/wumeng",
        ]));
	set("coor/x", -19170);
	set("coor/y", -6790);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}