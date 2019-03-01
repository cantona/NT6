#include "herb.h"

void create()
{
        set_name(NOR + MAG "頭頂一顆珠" NOR, ({ "trillium tschonoskii", "herb" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "植物延齡草(Trillium tschonoskii)的根莖或成熟果實。因這種植物有3片葉輪生于莖的頂端，花單生于輪生葉之上，開花後結出圓球形的果實，成熟後黑紫色 ......\n" NOR);
                set("base_unit", "顆");
                set("base_value", 300000);
                set("base_weight", 20);
        }
        setup();
}

