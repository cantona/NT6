#include "herb.h"

void create()
{
        set_name(HIR "龍骨伸筋" NOR, ({ "longgu shenjin", "Smilax riparia var. acuminata", "herb_lgjin" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "百合科(菝葜科)植物尖葉牛尾菜(Smilax riparia var. acuminata)的根莖。因其形略似龍骨，堅硬，又有舒筋活絡的功效，故得此名。\n" NOR);
                set("base_unit", "株");
                set("base_value", 50000);
                set("base_weight", 100);
        }
        setup();
}
