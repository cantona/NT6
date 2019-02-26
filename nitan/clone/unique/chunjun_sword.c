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
        set_name(HIW "純鈞劍" NOR, ({"chunjun sword", "chunjun", "sword"})); 
        set_weight(15000); 
        if (clonep()) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "把"); 
                set("long", sort_msg(HIW "純鈞劍，又名純鈎劍。此劍依然是歐冶子在湛盧山上所鑄。"
                                     "尊貴華美之劍。\n" NOR));
                                     
                set("value", 100000); 
                set("material", "steel");
                set("no_sell", "我的天…你…你知道這是啥麼？這你也敢拿來賣？"); 
                set("unique", 1); 
                set("rigidity", 500); 
                set("replica_ob", "/clone/weapon/changjian");
                set("no_put",1); 
                set("no_steal",1);   
                set("wield_msg",HIR"$N[噌]的一聲抽出一把純鈞，漫天烏雲，殺氣四濺。\n"NOR); 
                set("unwield_msg",HIR"$N把手中的純鈞入劍鞘，烏雲速散，殺氣頓無。\n"NOR); 
        }
        init_sword(500); 
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return HIM "純鈞夾帶着刺耳的破空聲劃出一道道長虹，霎時間$n"
               HIM "只感到被優雅的氣勢所迷住。\n" NOR;
}
