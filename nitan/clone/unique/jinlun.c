#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name( HIY  "日月金輪" NOR,({ "riyue jinlun" ,"lun" ,"jinlun" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("unique", 1);
                set("long",HIY"這是一柄金光閃閃的法輪。\n" NOR);
                set("value", 10000);
                set("material", "gold");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg","$N將手中的$n放回腰間。\n");
        }
        init_hammer(200);
        setup();
}
