// lbook7.c
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(YEL"「説律」"NOR, ({ "literateb7", "shu7", "book7" }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "本");
                set("long","這本書封皮有點舊，上面寫着「説律」幾個字。\n");
                set("value", 5000);
                set("material", "paper");
                set("skill",
                ([
                        "name": "literate",
                        "exp_required": 0,
                        "jing_cost":    10,
                        "difficulty":   15,
                        "max_skill":    19,
                        "min_skill":    1,
                ]) );
        }
}