#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY "榮譽勛章" NOR, ({ "honor emblem", "emblem" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "一枚榮譽勛章，代表至高的榮譽。\n" NOR);
                set("unit", "枚");
                set("value", 500000);
        }
        setup();
}
