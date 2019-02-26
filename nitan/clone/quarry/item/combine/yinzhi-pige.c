#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + WHT "銀質皮革" NOR, ({ "yinzhi pige", "yinzhi", "pige" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT  "一張泛着銀光的皮革，是製作甲衣的上好材料。\n" NOR);
                set("base_unit", "張");
                set("unit", "張");
                set("base_value", 100);
                set("base_weight", 1000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}