//Room: /d/dali/milin.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","密林");
        set("long",@LONG
此處山道狹窄，林木特別茂密，山民踏出來的小道被縱橫交錯的
林木遮擋阻礙著，行路者不停地用刀劈砍開路，才能順利前進。四面
青山峭立，叢林中時常有鳥獸驚走，偶爾還能看見美麗的孔雀飛過。
LONG);
        set("objects", ([
                "/clone/beast/qingshe": 1,
        ]));
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "northeast"  : __DIR__"yangzong",
            "southup"    : __DIR__"shanjian",
        ]));
	set("coor/x", -19030);
	set("coor/y", -6890);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}