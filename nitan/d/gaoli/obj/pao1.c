#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIC "白色金絲長袍" NOR, ({ "chang pao", "cloth","changpao","pao"}));
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一件金絲滾邊做工精細的白色長袍，看不出是用什麼質料裁成的。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 35);
                set("value", 100);
                set("wear_msg","$N把$n迎風一展，緩緩的披在身上。\n");
                set("remove_msg","$N輕輕的把$n從身上脱了下來。\n");
        }
        setup();
}
