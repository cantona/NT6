// poison_dust.c

inherit COMBINED_ITEM;

void create()
{

        set_name("蒙汗藥", ({ "menghan yao", "yao" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",
                        "這是極普通的蒙汗藥\n" );
                set("unit", "包");
                set("base_value", 700);
                set("base_unit", "份");
                set("base_weight", 30);
                set("can_pour", 1);
                set("can_drug", 1);
                set("poison_type", "slumber_drug");
                set("poison", 20);
        }
        set_amount(1);
}
