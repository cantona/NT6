#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "淡朱菩提樹" NOR, ({ "puti shu", "puti", "shu"}) );
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", HIR "經唐三彩燒製的淡朱菩提樹，非常的昂貴。\n" NOR);
                set("value", 1500);
        }
}