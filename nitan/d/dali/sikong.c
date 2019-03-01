//Room: /d/dali/sikong.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","司空堂");
        set("long", @LONG
這裡是大理國司空堂。堂內無余物，四壁卻堆滿了書籍。想來主
人愛書如命，即便工余亦手不釋卷。
LONG );
        set("objects", ([
            CLASS_D("dali")+"/batianshi" : 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "south"  : "/d/dali/zonglichu",
        ]));
	set("coor/x", -19121);
	set("coor/y", -6841);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}