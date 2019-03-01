#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "帝王符圖-陽" NOR, ({ "diwang futu6", "diwang", "futu6" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", HIR "傳說乃上古黃帝，炎帝及蚩尤留下的圖騰碎片，外形殘缺不全，似乎看不出什麼特別的。\n" NOR);
                set("value", 0);
                set("no_give", 1);
                set("no_drop", 1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}