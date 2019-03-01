// Copyright (C) 2003, by Lonely. All rights reserved. 
// This software can not be used, copied, or modified  
// in any form without the written permission from authors. 
// qixing-sword.c 七星龍淵
// for only one object in mud

#include <ansi.h>  
#include <weapon.h>  
inherit SWORD;  
inherit F_UNIQUE;  

void create() 
{
        set_name(HIC "七星龍淵" NOR, ({"qixing longyuan", "longyuan", "sword"}));  
        set_weight(15000);  
        if (clonep())  
                set_default_object(__FILE__);  
        else {  
                set("unit", "把");  
                set("long", sort_msg(HIC "這把劍傳說是由歐冶子和幹將兩大劍師聯手所鑄。歐冶子"
                                     "和幹將為鑄此劍，鑿開茨山，放出山中溪水，引至鑄劍爐旁成" 
                                     "北鬥七星環列的七個池中，是名“七星”。劍成之後，俯視劍" 
                                     "身，如同登高山而下望深淵，飄渺而深邃仿佛有巨龍盤臥。是" 
                                     "名“龍淵”。此劍鑄造的技藝固然精湛，但它的聞名還在于無" 
                                     "法知道其真實姓名的普通漁翁：魚丈人。話說伍子胥因姦臣所" 
                                     "害，亡命天涯，被楚國兵馬一路追趕，這一天荒不擇路，逃到" 
                                     "長江之濱，只見浩盪江水，波濤萬頃。前阻大水，後有追兵，" 
                                     "正在焦急萬分之時，伍子胥發現上遊有一條小船急速駛來，船" 
                                     "上漁翁連聲呼他上船，伍子胥上船後，小船迅速隱入蘆花盪中" 
                                     "，不見蹤影，岸上追兵悻悻而去，漁翁將伍子胥載到岸邊，為" 
                                     "伍子胥取來酒食飽餐一頓，伍子胥千恩萬謝，問漁翁姓名，漁" 
                                     "翁笑言自己浪跡波濤，姓名何用，只稱：“漁丈人”即可，伍" 
                                     "子胥拜謝辭行，走了幾步，心有顧慮又轉身折回，從腰間解下" 
                                     "祖傳三世的寶劍：七星龍淵，欲將此價值千金的寶劍贈給漁丈" 
                                     "人以致謝，並囑托漁丈人千萬不要泄露自己的行蹤，漁丈人接" 
                                     "過七星龍淵寶劍，仰天長嘆，對伍子胥說道：搭救你只因為你" 
                                     "是國家忠良，並不圖報，而今，你仍然疑我貪利少信，我只好" 
                                     "以此劍示高潔。說完，橫劍自刎。伍子胥悲悔莫名。故事見于" 
                                     "《吳越春秋》。七星龍淵是一把誠信高潔之劍。\n" NOR));
                set("value", 100000);  
                set("material", "steel"); 
                set("no_sell", "我的天…你…你知道這是啥麼？這你也敢拿來賣？");  
                set("unique", 1);  
                set("rigidity", 500);  
                set("replica_ob", "/clone/weapon/changjian"); 
                set("no_put",1);  
                set("no_steal",1); 
                set("wield_msg",HIC"$N[噌]的一聲抽出一把七星龍淵。\n"NOR);  
                set("unwield_msg",HIC"$N把手中的七星龍淵插入劍鞘。\n"NOR);  
                } 
                init_sword(800);  
                setup(); 
} 

mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return HIC "七星龍淵劍身突然冒出一股刺水，攻象$n" 
               HIC "，$n只能硬著頭皮抵擋。\n" NOR; 
} 