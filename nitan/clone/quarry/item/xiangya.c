#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIW "象牙" NOR, ({ "xiang ya", "xiang", "ya" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "成年巨象的牙齒，可加工為藝術品，頗為珍貴。\n" NOR);
                set("base_unit", "根");
                set("base_value", 50000);
                set("base_weight", 1000);
        }
        setup();
        set_amount(1);
}