// star.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(BLINK HIY "星星" NOR, ({ "star" }) );
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIW "從天空上摘下來一顆星星，這可不是用金錢來"
                            "衡量的，怎麼也算是一番心意阿。\n" NOR);
                set("value", 0);
                set("unit", "顆");
        }
        setup();
}