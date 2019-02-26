#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "碧玉瓷馬" NOR, ({ "biyu cima", "biyu", "cima"}) );
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", HIW "經唐三彩燒製的碧玉陶瓷馬，非常的昂貴。\n" NOR);
                set("value", 1500);
        }
}