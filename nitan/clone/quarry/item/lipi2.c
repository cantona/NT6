#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIW "白狐皮" NOR, ({ "baihu pi", "baihu", "pi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "這是一張質地非常不錯的狐狸皮，柔軟光滑之極。\n" NOR);
                set("base_unit", "張");
                set("base_value", 10000);
                set("base_weight", 300);
        }
        setup();
        set_amount(1);
}