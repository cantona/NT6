#include "herb.h"

void create()
{
        set_name(NOR + YEL "江邊一碗水" NOR, ({ "diphylleia sinensis", "herb" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "南方山荷葉(Diphylleia sinensis)的乾燥根莖。因其根莖的每一莖節處有一碗狀小凹窩(莖痕)，且最初是在河邊高山坡林下挖得此藥，故得此名。其根莖黃褐色 ......\n" NOR);
                set("base_unit", "根");
                set("base_value", 300000);
                set("base_weight", 20);
        }
        setup();
}

