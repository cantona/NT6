// Room: /d/hengshan/zhandao.c
// Date: Oct. 2 1997 by That

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "梯式棧道");
        set("long", @LONG
棧道懸于壁，由無數的掾舖成，每節掾寬尺許，九節並排在一起，
每根掾插入巖壁，上舖木板，長約十丈，下臨深淵。人必須踏上懸空的
木板，緊攀鐵索，屏息靜氣，緩步挪動，才能過去。
LONG);
        set("exits", ([ /* sizeof() == 4 */
                "southup"   : __DIR__"yunge",
                "northdown" : __DIR__"xuankong2",
        ]));
        set("outdoors", "hengshan");
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 3150);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}
