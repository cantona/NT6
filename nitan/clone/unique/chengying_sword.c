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
        set_name(HIR "承影" NOR, ({"chengying sword", "chengying", "sword"})); 
        set_weight(15000); 
        if (clonep()) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "把"); 
                set("long", sort_msg(HIR "遠古的一個黎明，天色黑白交際的一瞬間，一雙手緩緩揚起。雙手合握之中"
                                     "是一截劍柄，只有劍柄不見長劍劍身，但是，在北面的牆壁上卻隱隱投下一個飄"
                                     "忽的劍影，劍影只存片刻，就隨着白晝的來臨而消失，直到黃昏，天色漸暗，就"
                                     "在白晝和黑夜交錯的霎那，那個飄忽的劍影又再次浮現出來。揚起的雙手劃出一"
                                     "條優雅的弧線，揮向旁邊一棵挺拔的古鬆，耳廓中有輕輕的“嚓”的一聲，樹身微"
                                     "微一震，不見變化，然而稍後不久，翠茂的鬆蓋就在一陣温和掠過的南風中悠悠"
                                     "倒下，平展凸露的圈圈年輪，昭示着歲月的流逝。天色愈暗，長劍又歸於無形，"
                                     "遠古的暮色無聲合攏，天地之間一片靜穆。這把有影無形的長劍就是在《列子。"
                                     "湯問》之中被列子激賞的鑄於商朝後來被春秋時衞國人孔周所藏的名劍：承影。\n" NOR));
                                     
                set("value", 100000); 
                set("material", "steel");
                set("no_sell", "我的天…你…你知道這是啥麼？這你也敢拿來賣？"); 
                set("unique", 1); 
                set("rigidity", 500); 
                set("replica_ob", "/clone/weapon/changjian");
                set("no_put",1); 
                set("no_steal",1);   
                set("wield_msg",HIR"$N[噌]的一聲抽出一把承影，漫天烏雲，殺氣四濺。\n"NOR); 
                set("unwield_msg",HIR"$N把手中的承影入劍鞘，烏雲速散，殺氣頓無。\n"NOR); 
        }
        init_sword(500); 
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return HIM "承影夾帶着刺耳的破空聲劃出一道道長虹，霎時間$n"
               HIM "只感到被優雅的氣勢所迷住。\n" NOR;
}
