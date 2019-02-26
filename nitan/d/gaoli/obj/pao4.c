#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(YEL "白邊黃色長袍" NOR, ({ "chang pao", "cloth","changpao","pao"}));
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一件白色滾邊黃色長袍，做工似乎比較簡單。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 10);
                set("value", 100);
                set("wear_msg","$N把$n迎風一展，緩緩的披在身上。\n");
                set("remove_msg","$N輕輕的把$n從身上脱了下來。\n");
        }
        setup();
}
