// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// xuanyuan-sword.c 軒轅夏禹 
// for only one object in mud 

#include <ansi.h> 
#include <weapon.h> 
inherit SWORD; 
inherit F_UNIQUE; 

void create() 
{ 
        set_name(HIR "軒轅夏禹" NOR, ({"xuanyuan sword", "xuanyuan", "sword"})); 
        set_weight(15000); 
        if (clonep()) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "把"); 
                set("long", sort_msg(HIR "眾神採首山之銅為黃帝所鑄，後傳與夏禹。在劍身一面刻"
                                     "有日月星辰，一面刻有山川草木。柄一面書農耕畜養之術，一"
                                     "面書四海一統之策。軒轅夏禹劍！對這一把劍還能些什麼呢？"
                                     "黃帝、夏禹！對這樣兩個人我們還能說些什麼呢。勇氣、智慧"
                                     "、仁愛，一切在于兩個字：聖道。軒轅夏禹劍是一把聖道之劍"
                                     "。\n" NOR));
                set("value", 100000); 
                set("material", "steel");
                set("no_sell", "我的天…你…你知道這是啥麼？這你也敢拿來賣？"); 
                set("unique", 1); 
                set("rigidity", 500); 
                set("replica_ob", "/clone/weapon/changjian");
                set("no_put",1); 
                set("no_steal",1);   
                set("wield_msg",HIR"$N[噌]的一聲抽出一把軒轅夏禹，漫天烏雲，殺氣四濺。\n"NOR); 
                set("unwield_msg",HIR"$N把手中的軒轅夏禹插入劍鞘，烏雲速散，殺氣頓無。\n"NOR); 
        }
        init_sword(1000); 
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return HIM "軒轅夏禹夾帶著刺耳的破空聲劃出一道道長虹，霎時間$n"
               HIM "只感到心神意亂。\n" NOR;
}