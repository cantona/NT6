//yijing0.c
inherit ITEM;
inherit F_UNIQUE;
#include <ansi.h>
 
void create()
{
        set_name(HIY"「易經序卦篇」"NOR, ({ "yijing xugua","yijing0", }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","這是一本用薄絹寫成的書。上書：“易經序卦篇”。\n書皮泛黃，看來已經保存很久了。\n");
                set("value", 0);
                set("material", "silk");
                set("skill", ([
                        "name":       "qimen-wuxing",
                        "jing_cost":  20,
                        "difficulty": 20,
                        "max_skill":  25,
                        "min_skill":  0
                ]) );
        }
}