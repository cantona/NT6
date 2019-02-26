
#include <armor.h>
#include <ansi.h>

inherit MYHEART;

void create()
{
        set_name(NOR + WHT "隱身符" NOR, ({ "yinshen fu", "yinshen", "fu" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "張");
                set("long", HIY "這是一張道符，據説裝備後可以隱藏行蹤。\n" NOR);
                set("value", 10000);
                set("armor_prop/invisible", 1);
                set("special/desc", "裝備後可隱藏行蹤，他人無法查看到你的存在。");
        }
        setup();
}

int query_autoload()
{
        return 1;
}