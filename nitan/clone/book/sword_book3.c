// Last Modified by winder on Jul. 15 2001

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW"雪山劍譜"NOR, ({ "swordbook","book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","這是一本凌霄城的劍法祕籍，封面上寫着四個字“雪山劍法”。\n");
                set("value", 1000);
                set("material", "paper");
                set("skill", ([
                        "name":         "xueshan-sword",
                        "exp_required": 10000,
                        "jing_cost" :   30,
                        "difficulty":   30,
                        "max_skill":    100,
                        "min_skill":    0
                ]) );
        }
}
