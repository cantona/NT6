#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", "轎內");
        set("long", @LONG
你在轎裡剛坐穩，快轎搖了搖，抬起來往前走了。你只覺的轎子
慢慢搖骸搖骸，也不知道走了多久，一路上老覺得昏昏欲睡。。。。。。
LONG );
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}