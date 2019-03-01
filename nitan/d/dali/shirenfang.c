//Room: /d/dali/shirenfang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","石人房");
        set("long",@LONG
這裡是鎮南王府的庭院南端的石人房，房中擺著一些大理特產的
石人，看起來栩栩如生。四壁開著小窗口，窗台上放著幾砵小茶花，
窗口欄桿也擋不住窗外四時不盡的綠色和芳香。
LONG);
        set("exits",([ /* sizeof() == 1 */
            "north" : __DIR__"tingyuan",
        ]));
        set("objects",([ /* sizeof() == 1 */
            __DIR__"npc/shi-ren" : 5,
        ]));
	set("coor/x", -19101);
	set("coor/y", -6871);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}