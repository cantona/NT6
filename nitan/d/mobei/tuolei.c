// Room: /d/mobei/tuolei.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "拖雷營帳");
        set("long", @LONG
拖雷是鐵木真的四兒子，也是大汗最鍾愛的兒子。他聰明梯透，行軍打
戰的才華遠在諸兄之上。
LONG
        );
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/tuolei" : 1,
        ]));
        set("exits", ([ /* sizeof() == 1 */
                "east" : __DIR__"road",
        ]));
        set("coor/x", -220);
        set("coor/y", 5250);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}