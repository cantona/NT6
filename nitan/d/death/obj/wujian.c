// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h> 
#include <weapon.h> 
inherit SWORD; 

void create() 
{ 
        set_name(HIW "無間閃電" NOR, ({"wujian shandian", "wujian", "shandian"})); 
        set_weight(15000); 
        if (clonep()) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "把"); 
                set("long", sort_msg(HIR "眾神采首山之天石為天帝所鑄，對這一把劍還能些什麼呢？"
                                     "天帝！勇氣、智慧、仁愛，一切在於兩個字：聖道。無間閃電"
                                     "是一把無敵之劍，使用方法：裝備後用 smash id 來摧毀對手。\n" NOR));
                set("value", 100000); 
                set("material", "steel");
                set("no_sell", "我的天…你…你知道這是啥麼？這你也敢拿來賣？"); 
                set("rigidity", 500); 
                set("no_put",1); 
                set("no_steal",1);   
                set("wield_msg",HIR"$N[噌]的一聲抽出一把無間閃電，漫天烏雲，電閃雷鳴，殺氣四濺。\n"NOR); 
                set("unwield_msg",HIR"$N把手中的無間閃電插入劍鞘，烏雲速散，雷電消失，殺氣頓無。\n"NOR); 
        }
        init_sword(2100000); 
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        victim->receive_damage("jing", me->query_str() * 200, me);
        victim->receive_wound("jing", me->query_str() * 200, me);
        return HIM "無間閃電夾帶着刺耳的破空聲劃出一道道閃電，霎時間$n"
               HIM "只感到死神來臨。\n" NOR;
}
