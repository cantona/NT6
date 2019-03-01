//Room: /d/dali/dasenlin.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","大森林");
        set("long", @LONG
此去向北是無量山區和大森林，這裡已經林木茂密人跡罕至了，
南面是大理到中原的官道大路。
LONG );
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "south"   : "/d/dali/dianchi",
            "north"   : "/d/dali/heisenlin",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19080);
	set("coor/y", -6850);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}