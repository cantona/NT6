#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC "八寶蓮花座" NOR, ({ "lianhua zuo", "lianhua", "zuo"}) );
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", HIC "經唐三彩燒製的八寶蓮花座，非常的昂貴。\n" NOR);
                set("value", 1500);
        }
}