#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC "帝王符圖碎片-26" NOR, ({ "diwang suipian26", "diwang", "suipian" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", HIC "傳説乃上古黃帝，炎帝及蚩尤留下的圖騰碎片，外形殘缺不全，似乎看不出什麼特別的。\n" NOR);
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