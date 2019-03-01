// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <armor.h>
#include <ansi.h>
inherit CLOTH;
inherit F_UNIQUE; 

void create()
{
        set_name(YEL"軟□甲"NOR, ({ "ruanwei jia", "jia" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", MAG"這是一件黑黝黝的甲衣，看上去極輕極軟，但卻生滿倒刺，刀劍不損，正是桃花島鎮島之寶軟□甲。\n"NOR);
                set("material", "steel");
                set("unit", "件");
                set("value", 500000);
                set("rigidity", 20000); 
                set("replica_ob", "/clone/cloth/ruanjia"); 
                set("wear_msg", HIY "$N穿上一件軟□甲。\n" NOR);
                set("unequip_msg", HIY "$N將軟□甲脫了下來。\n" NOR);
                set("armor_prop/armor", 260);
                set("armor_prop/armor_vs_force", 200);
        }
        setup();
}

mixed valid_damage(object me, object victim, int damage, object weapon)
{
        string result;
        if ( weapon )
                return damage*2/3;
        else {
                damage = damage/2;
                if (damage > 0)
                    me->receive_wound("qi", damage/4, victim);
                result = "只見$N大叫一聲急忙收手，手上已被軟□甲刺得鮮血淋漓。\n";
                result+="($N"+COMBAT_D->eff_status_msg(query("qi", me)*100/query("max_qi", me))+")\n";
                return ([ "msg": result, "damage": damage+random(damage) ]);
        }
}
                
