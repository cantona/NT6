//bagua1.c

inherit ITEM;
inherit F_UNIQUE;
#include <ansi.h>
 
void create()
{
        set_name(HIC"「洛書」"NOR, ({ "luoshu","shu", }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","這是一本用薄絹寫成的書。上書二字古篆：“洛書”。\n書皮泛黃，看來已經保存很久了。\n" );
                set("value", 0);
                set("material", "silk");
                set("skill", ([
                        "name":       "count",
                        "jing_cost":  40,
                        "difficulty": 30,
                        "max_skill":  149,
                        "min_skill":  100
                ]) );
        }
}