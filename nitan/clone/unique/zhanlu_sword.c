// Copyright (C) 2003, by Xlz. All rights reserved. 
// This software can not be used, copied, or modified  
// in any form without the written permission from authors. 
// zhanlu-sword.c 湛
// for only one object in mud  

#include <ansi.h>  
#include <weapon.h>  
inherit SWORD;  
inherit F_UNIQUE;  

void create()  
{ 
        set_name(HIW "湛瀘" NOR, ({"zhanlu sword", "zhanlu", "sword"}));  
        set_weight(15000);  
        if (clonep())  
                set_default_object(__FILE__);  
        else {
                set("unit", "把");  
                set("long", sort_msg(HIW"湛瀘是一把劍，更是一隻眼睛。湛瀘：湛湛然而黑色也" 
                                     "。這把通體黑色渾然無跡的長讓人感到的不是它的鋒利，而"
                                     "是它的寬厚和慈祥。它就象上蒼一隻目光深邃、明察秋的黑" 
                                     "色的眼睛，注視着君王、諸侯的一舉一動。君有道，劍在側" 
                                     "，國興旺。君無道，劍飛棄，國破敗。五金之英，太陽之精" 
                                     "，出之有神，服之有威。歐冶子鑄成此劍時，不禁撫劍淚落" 
                                     "，因為他終於圓了自己畢生的夢想：鑄出一把無堅摧而又不" 
                                     "帶絲毫殺氣的兵器。所謂仁者無敵，湛瀘劍是一把仁道之劍。\n" NOR)); 
                set("value", 100000);  
                set("material", "steel"); 
                set("no_sell", "我的天…你…你知道這是啥麼？這你也敢拿來賣？");  
                set("unique", 1);  
                set("rigidity", 500);  
                set("replica_ob", "/clone/weapon/changjian"); 
                set("no_put",1);  
                set("no_steal",1);
                set("wield_msg",HIW"$N[噌]的一聲抽出一把湛瀘，沒有絲毫殺氣。\n"NOR);  
                set("unwield_msg",HIW"$N把手中的湛瀘插入劍鞘，劍身沒有發出一絲聲音。\n"NOR); 
        }
        init_sword(950); 
        setup(); 
}
mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return HIW "湛瀘從$N手中飛向天空，[嗡]一聲，湛瀘從天空化做長虹回到了$N手中，$n" 
               HIW "只感到驚訝。\n" NOR; 
}