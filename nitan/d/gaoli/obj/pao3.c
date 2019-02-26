#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(BLU "白邊藍色長袍" NOR, ({ "chang pao", "cloth","changpao","pao"}));
        set_weight(3500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一件白色滾邊做工精細的藍色長袍。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 20);
                set("value", 100);
                set("wear_msg","$N把$n迎風一展，緩緩的披在身上。\n");
                set("remove_msg","$N輕輕的把$n從身上脱了下來。\n");
        }
        setup();
}
