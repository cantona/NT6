// fu

#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(YEL"黃銅鎖" NOR, ({ "huangtong suo", "suo" }));
               set("long", "又名同心鎖，寓意鎖住情人的心。\n");
        set("weight", 1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 5000);
                set("material", "銅");
                set("armor_prop/armor", 2);
                }
        setup();
}        