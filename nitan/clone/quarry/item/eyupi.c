#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(NOR + CYN "鱷魚皮" NOR, ({ "eyu pi", "eyu", "pi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + CYN "鱷魚的皮革，非常的堅硬，相信"
                            "可以賣個好價錢，。\n" NOR);
                set("base_unit", "張");
                set("base_value", 10000);
                set("base_weight", 800);
        }
        setup();
        set_amount(1);
}