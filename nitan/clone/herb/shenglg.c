#include "herb.h"

void create()
{
        set_name(NOR + CYN "生龍骨" NOR, ({ "sheng longgu", "sheng", "longgu", "herb_shenglg" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + CYN "海馬的骨絡，乃是常見的中藥藥材。\n" NOR);
                set("base_unit", "根");
                set("base_value", 4000);
                set("base_weight", 120);
        }
        setup();
}