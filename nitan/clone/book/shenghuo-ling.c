// shenghuo-ling 聖火令

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name("聖火令",({ "shenghuo ling", "shenghuo", "ling" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "把");
                set("value", 10000);
                set("material", "steel");
                set("no_drop", "1");
                set("long", "這是一柄兩尺來長的黑牌，非金非鐵。質地堅硬無比，\n"
                            "似透明，令中隱隱似有火焰飛騰，實則是令質映光，顏\n"
                            "色變幻。令上刻得有不少波斯文字。 \n");
                set("wield_msg", HIY "$N“唰”的一聲，從腰間抽出一片黑黝的鐵牌握在手中。\n");
                set("unwield_msg", HIY "$N將聖火令插回腰間。\n" NOR);
        }
        set("skill", ([
                "name"        : "shenghuo-ling",
                "exp_required":  50000,
   	            "family_name" : "明教",
                "jing_cost"   :  40,
                "difficulty"  :  30,
                "max_skill"   :  200,
                "min_skill"   :  100
        ]) );
        init_sword(50);
        setup();
}