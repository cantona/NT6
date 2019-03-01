#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIB "淡青螺紋醢" NOR, ({ "luowen hai" }) );
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", HIB "淡青色，內外都有螺旋形的條紋。\n" NOR);
                set("value", 1500);
        }
}