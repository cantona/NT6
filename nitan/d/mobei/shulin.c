// Room: /d/mobei/shulin.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "雜樹林");
        set("long", @LONG
風動樹林，樹葉刷刷作響，昏黃的月光下幾隻綠幽幽的眼睛在林中
無聲的移動。突然響起的尖叫令人毛骨悚然，又突兀的停止，東面向上
是荒山山頂，出了林子就是草原。
LONG);
        set("outdoors","mobei");
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/zhucong" : 1,
        ]));
        set("exits", ([ /* sizeof() == 2 */
                "eastup" : __DIR__"hill1",
                "west"   : __DIR__"caoyuan1",
        ]));
        set("coor/x", -220);
        set("coor/y", 5230);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}