// fu

#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIC"玄女靈符" NOR, ({ "xuannv-lingfu", "lingfu" }));
               set("long", "一張普普通通的符紙，據說是九天玄女開過光的，可以保佑婚姻順利。\n");
        set("weight", 100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("value", 5000);
                set("material", "紙");
                set("armor_prop/armor", 2);
                }
        setup();
}        