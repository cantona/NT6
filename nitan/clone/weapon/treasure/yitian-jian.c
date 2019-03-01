// yitianjian.c 倚天劍
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>;
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name("倚天劍", ({ "yitian jian", "sword", "jian" }) );
        set_weight(15000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 50000);
//                set("no_drop", "1");
                set("material", "iron");
                set("long", "這是天下第一利器，有“倚天不出，誰與爭鋒”之說。\n");
                set("wield_msg", "直如矯龍吞水，長虹冠日一般，$n已在$N手中，天地為之變色。\n");
                set("unwield_msg", "$N將$n插回腰間，華光頓斂，天地間只聞龍鳴。\n");
        }
           init_sword(170);
        enable_commands(); 
        setup();
}

int init()
{
        if( query("id", environment(this_object())) != "zhangwuji" )
        {    
                remove_call_out("destyitianjian");
                call_out("destyitianjian", 5400+random(1800));
                return 1;
        }
        else 
        return 0;
}

void destyitianjian()
{
        object ob;
        message_vision("突然有個黑衣人匆匆和你擦身而過，消失在街口拐角處，糟糕，你的$N丟了。\n",this_object());
        destruct(this_object());
/*        message("channel:rumor", MAG"【謠言】某人："+"遺失多年的倚天劍又重現江湖啦。\n"NOR, users());*/
}

