//Room: /d/dali/situ.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","司徒堂");
        set("long", @LONG
這裡是大理國司徒堂。大理君臣勤政愛民，三公勞作自不帶言。
堂內無余物，奇怪的是地上角落還擺了些鐵鏟，孔明燈之類的物事。
LONG );
        set("objects", ([
            CLASS_D("dali")+"/huahegen" : 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "east"  : "/d/dali/zonglichu",
        ]));
	set("coor/x", -19131);
	set("coor/y", -6851);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}