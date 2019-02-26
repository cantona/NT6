#include "herb.h"

void create()
{
         set_name(NOR + BLU "七葉一枝花" NOR, ({ "qiye yizhihua","hua","herb" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + HIY "七葉一枝花(Paris polyphylla)的乾燥根莖。因其葉多為7—10片輪生於莖項，而花單生於輪生葉片之上，故得此名。又因花的外輪花被片形大.似葉狀；內輪花被片退化呈長線狀 ......\n" NOR);
                set("base_unit", "顆");
                set("base_value", 300000);
                set("base_weight", 20);
        }
        setup();
}

