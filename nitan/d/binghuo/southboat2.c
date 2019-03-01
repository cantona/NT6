// Room: /binghuo/southboat2.c
// Date: Oct.28 1999 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "木筏");
        set("long", @LONG
此木筏是島上參天古木紮就，豎立主桅副桅，這些木材因生于寒
冰之地，木質致密，硬如鐵石。帆布和帆索都用樹筋獸皮來編織、搓
結。筏上水腌肉，存貯清水的皮袋皆已具備。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "binghuo");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
