#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "附魔卷軸" NOR, ({ "enchant scroll", "scroll" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "附魔卷軸用來輔助日魂月魄附魔屬性用的，可確保附魔時裝備不會銷毀。\n" NOR);
                set("unit", "張");
                set("value", 500000);
                set("no_sell", 1);
        }
        setup();
}

