#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name(HIG "翠玉牌" NOR, ({ "yupai" }));
        set("long", "\n這是一塊翠綠色的玉牌，晶瑩光潔，完美無瑕，好一塊絕世好玉。\n"+
         "玉身成橢圓狀，正中有"+HIR"海枯石爛"NOR+"四個篆體小字。\n");
        set("weight", 300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("value", 50000);
                set("material", "玉");
                set("armor_prop/armor", 2);
                set("female_only", 1);
        }
        setup();
}
