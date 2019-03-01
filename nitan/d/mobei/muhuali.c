// Room: /d/mobei/muhuali.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "木華黎營帳");
        set("long", @LONG
木華黎是蒙古的智者，是大汗的軍師。他的營帳中只有幾條氈子隨
便堆放，其他地方到處都是書。據說蒙古文字就是他草創的。
LONG
        );
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/muhuali" : 1,
        ]));
        set("exits", ([ /* sizeof() == 1 */
                "south" : __DIR__"road3",
        ]));

        set("coor/x", -220);
        set("coor/y", 5250);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}