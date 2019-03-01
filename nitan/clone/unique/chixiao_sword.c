// Copyright (C) 2003, by Xlz. All rights reserved.  
// This software can not be used, copied, or modified   
// in any form without the written permission from authors.  
// chi-sword.c 赤
// for only one object in mud   

#include <ansi.h>   
#include <weapon.h>   
inherit SWORD;   
inherit F_UNIQUE;   
void create()   
{ 
        set_name(HIR "赤霄劍" NOR, ({"chixiao sword", "chixiao", "sword"}));   
        set_weight(15000); 
        if (clonep())   
                set_default_object(__FILE__);   
        else {
                set("unit", "把");   
                set("long", HIY "這是一把飾有七彩珠、九華玉的寒光逼人、刃如霜雪的寶劍。\n"
                                "這把劍就是斬蛇起義的赤霄劍，赤霄劍是一把帝道之劍。\n" NOR);
        set("value", 100000);  
        set("material", "steel");  
        set("no_sell", "我的天…你…你知道這是啥麼？這你也敢拿來賣？");   
        set("unique", 1);     
        set("rigidity", 500);   
        set("replica_ob", "/clone/weapon/changjian");  
        set("no_put",1);
        set("no_steal",1); 
        set("wield_msg",HIR"$N[噌]的一聲抽出一把赤劍，忽然從旁邊跳出一條赤龍，圍著$N轉。\n"NOR);   
        set("unwield_msg",HIR"$N把手中的赤劍插入劍鞘，赤龍化做長虹飛到天空，消失了。\n"NOR);    
        } 
        init_sword(900);   
        setup();
}
mixed hit_ob(object me, object victim, int damage_bonus)  
{ 
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return HIR "赤劍[叮]一聲響，霎那，那條赤龍張口就咬$n"  
               HIR "，$n只能冷冷做怕。\n" NOR; 
}