//Room: /d/dali/tusifu.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","土司府");
        set("long", @LONG
土司府是當地傣族世襲土司刀氏的衙門，一座古老的磚木建築物，
門庭居高臨下，莊嚴堅實，門前是寬廣的石階，有點象衙門氣勢，房
屋共三台，佔地約八百畝，分作正廳，議事廳，後廳，廂房。
LONG );
        set("objects", ([
           "/d/dali/npc/datusi": 1,
           "/d/dali/npc/shicong": 2,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "enter"  : "/d/dali/tusimentang",
            "south"  : "/d/dali/dahejiewest",
        ]));
	set("coor/x", -19140);
	set("coor/y", -6890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}