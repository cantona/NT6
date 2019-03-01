//Room: /d/dali/chahua4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","茶花園");
        set("long", @LONG
大理茶花冠絕天下，鎮南王府的茶花自然更非凡品。你站在茶花
園中，北面是一片波光漣灩的湖面。靠岸的柳樹下，有幾盆茶花，嬌
艷照人，在滿園爛漫的茶花圍中，仍驕然出群。
LONG );
        set("objects", ([
           "/d/dali/obj/chahua4": 1,
        ]));
        set("outdoors", "dali");
        set("exits",([ /* sizeof() == 1 */
            "northeast"  : "/d/dali/chahua5",
            "northwest"  : "/d/dali/chahua2",
        ]));
	set("coor/x", -19071);
	set("coor/y", -6871);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}