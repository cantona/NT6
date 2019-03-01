// jinsuo.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "金鎖關");
        set("long", @LONG
金鎖關山勢形如一把鎖，下面是一片開闊地，兩旁是高聳入雲的
峭壁，中間一條羊腸小道。真是一夫當關，萬夫莫開。
LONG );
        set("exits", ([ /* sizeof() == 4 */
           "southup"   : __DIR__"zhenyue",
           "northdown" : __DIR__"shangtianti",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huashan");
        setup();
        replace_program(ROOM);
}
