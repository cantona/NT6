//sengpao.c

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIY"僧袍"NOR, ({ "seng pao", "pao", "cloth" }) );
        set("long", "這是一件尋常的僧袍，是和尚們的普通裝束。\n");     
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 10);
                set("armor_prop/dodge", 3);
        }
        setup();
}