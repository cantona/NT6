#include <ansi.h>
inherit ITEM;

void create()
{
            set_name(HIY "「紫蓋劍譜」" NOR, ({ "zigai jianpu", "jianpu", "zigai", "pu"}));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__); 
        else{
                set("unit", "本");
                set("long", HIY "封面上寫著「紫蓋劍譜」。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("material", "paper");
                set("skill", ([
                            "name"         :  "zigai-jian",        
                            "exp_required" :  10000,          
                            "jing_cost"    :  20,         
                            "difficulty"   :  20,
                            "max_skill"    :  120
                ]));

       }
}