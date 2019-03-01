// shuozhuo.c 手鐲

#include <armor.h>
#include <ansi.h>

inherit WRISTS;

void create()
{
        set_name(HIG "手鐲" NOR, ({ "shou zhuo", "zhuo" }));
        set("long", "這是一對玉鐲，瑩滑溫潤，光潔無瑕，真是稀世罕有。\n");
        set("weight", 300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "對");
                set("value", 50000);
                set("material", "玉");
                set("armor_prop/armor", 2);
                set("female_only", 1);
        }
        setup();
}        

