// shangtianti.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "上天梯");
        set("long", @LONG
此處絕險，必須面壁挽索，貼身探足前進，步不登高，故名"上天
梯"。北面是下山的路，往南面是金鎖關。西面上去可以通達北峰雲台
峰。
LONG );
        set("exits", ([ /* sizeof() == 4 */
           "southup"   : __DIR__"jinsuo",
           "northdown" : __DIR__"husun",
           "westup"    : __DIR__"canglong",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huashan");
        setup();
        replace_program(ROOM);
}
