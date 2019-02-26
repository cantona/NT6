#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "白瓷觀音像" NOR, ({ "guanyin xiang", "guanyin", "xiang"}) );
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", HIW "經唐三彩燒製的白瓷觀音像，非常的昂貴。\n" NOR);
                set("value", 1500);
        }
}