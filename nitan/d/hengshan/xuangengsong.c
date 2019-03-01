// Room: /d/hengshan/xuangengsong.c
// Date: Oct. 2 1997 by That

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "懸根鬆");
        set("long", @LONG
就在虎風口這個風口險地，卻有一株古鬆，雖被大風吹得樹根裸露，
千百年來仍迎風挺立，這就是恆山著名的“梵宮懸根”。
LONG);
        set("exits", ([ /* sizeof() == 4 */
                "east"      : __DIR__"hufengkou",
        ]));
        set("objects", ([
                "/clone/medicine/vegetable/chaihu" : random(2),
        ]));
        set("outdoors", "hengshan");
        set("coor/x", 10);
        set("coor/y", 3150);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}
