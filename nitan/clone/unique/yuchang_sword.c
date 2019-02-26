// Copyright (C) 2003, by Xlz. All rights reserved. 
// This software can not be used, copied, or modified  
// in any form without the written permission from authors. 
// yuchang-sword.c 魚腸劍
// for only one object in mud  

#include <ansi.h>  
#include <weapon.h>  
inherit SWORD;  
inherit F_UNIQUE;  

void create()  
{  
        set_name(HIY "魚腸劍" NOR, ({"yuchang sword", "yuchang", "sword"}));  
        set_weight(15000);  
        if (clonep())  
                set_default_object(__FILE__);  
        else {  
        set("unit", "把");  
                        set("long", sort_msg(CYN "此劍乃是歐冶子在湛盧山上所鑄，魚腸劍是一把勇絕之劍。\n" NOR));
        set("value", 100000);  
        set("material", "steel"); 
        set("no_sell", "我的天…你…你知道這是啥麼？這你也敢拿來賣？");  
        set("unique", 1);  
        set("rigidity", 500);  
        set("replica_ob", "/clone/weapon/changjian"); 
        set("no_put",1);  
        set("no_steal",1);    
        set("wield_msg",CYN"$N[噌]的一聲抽出一把魚腸劍，漫天烏雲，殺氣四濺。\n"NOR);  
        set("unwield_msg",CYN"$N把手中的魚腸劍插入劍鞘，烏雲速散，殺氣頓無。\n"NOR);  
     }
     init_sword(650); 
     setup(); 
} 

mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
         return CYN "魚腸劍夾帶着刺耳的破空聲劃出一道道長虹，霎時間$n" 
               CYN "只感到心神意亂。\n" NOR; 
}
