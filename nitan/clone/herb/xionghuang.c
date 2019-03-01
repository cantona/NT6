#include "herb.h"

void create()
{
        set_name(HIY "雄黃" NOR, ({ "xiong huang", "xiong", "huang", "herb_xionghuang" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "藥性極強的中藥藥材，帶在身上可以防止蛇蟲及身。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 500);
                set("base_weight", 30);
        }
        setup();
}