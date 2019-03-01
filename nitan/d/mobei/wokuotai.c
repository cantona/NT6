// Room: /d/mobei/wokuotai.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "窩闊台營帳");
        set("long", @LONG
窩闊台是鐵木真的三兒子，也是將來的大汗。他為人仁和寬厚，和
諸兄弟及親兵大將也均交好。他的營帳也十分樸素。
LONG
        );
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/wokuotai" : 1,
        ]));
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"road",
        ]));
        set("coor/x", -200);
        set("coor/y", 5250);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}