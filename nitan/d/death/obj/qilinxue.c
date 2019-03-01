// boots.c 麒麟靴
 
#include <armor.h>
#include <ansi.h>
 
inherit BOOTS;
 
void create()
{
        set_name(HIR "麒麟靴" NOR, ({ "qilin xue", "xue", "boots" }) );
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "leather");
                set("unit", "雙");
                set("long", HIR "這是一雙用上麒麟皮作的皮靴，據說可以赴湯蹈火。用以保護足部。\n" NOR);
                set("value", 100000);
                set("armor_prop/dodge", 80);
        }
        setup();
}