// Copyright (C) 2003, by Xlz. All rights reserved.   
// This software can not be used, copied, or modified    
// in any form without the written permission from authors.   
// tai-sword.c 泰
// for only one object in mud  

#include <ansi.h>   
#include <weapon.h> 
inherit SWORD;   
inherit F_UNIQUE; 
void create()    
{
        set_name(CYN "泰阿劍" NOR, ({"taie sword", "taie", "sword"})); 
        set_weight(15000); 
        if (clonep())   
                set_default_object(__FILE__);    
        else { 
                set("unit", "把");    
                set("long", sort_msg(CYN"楚國的都城已被晉國的兵馬圍困了三年。晉國出兵伐楚，" 
                                     "是想得到楚國的鎮國之寶：阿劍。世人都説，泰阿劍是歐冶子" 
                                     "和干將兩大劍師聯手所鑄。但是兩位大師卻不這樣認為，他們" 
                                     "説泰阿劍是一把諸侯威道之劍早已存在，只是無形、無跡，但" 
                                     "是劍氣早已存於天地之間，只等待時機凝聚起來，天時、地利" 
                                     "、人和三道歸一，此劍即成。晉國當時因為強大，晉王當然認" 
                                     "為自己最有資格得到這把寶劍，但是事與願違，此劍卻在弱小" 
                                     "的國鑄成，出劍之時，劍身果然天然鐫刻篆體“泰阿”二字，" 
                                     "可見歐冶、干將所言不虛晉王當然咽不下這口氣，於是向楚王" 
                                     "索劍，楚王拒絕，於是晉王出兵伐楚，以索劍之名藉機滅掉楚" 
                                     "國。兵力懸殊，楚國大部分城池很快陷落並且都城也被團團圍" 
                                     "住，一困三年。城裏糧草告罄，兵革無存，危在旦夕。這一天" 
                                     "，晉國派來使者發出最後通牒：如再不交劍，明天將攻陷此城" 
                                     "，到時玉石俱焚！楚王不屈，吩咐左右，明天自己要親上城頭" 
                                     "戰敵，如果城破，自己將用此劍自刎，然後左右要拾得此劍，" 
                                     "騎快馬奔到大湖，將此劍投入湖底，讓泰阿劍永留楚國。第二" 
                                     "天拂曉，楚王登上城頭，只見城外晉國兵馬遮天蔽日，自己的" 
                                     "都城宛如汪洋之中的一葉扁舟，隨時有傾滅危險。晉國兵馬開" 
                                     "始攻城，吶喊聲同山呼海嘯，城破在即。楚王雙手捧劍，長歎" 
                                     "一聲：泰阿劍啊，泰阿劍，我今天將用自己的鮮血來祭你！於" 
                                     "是，拔劍出鞘，引劍直指敵軍。匪夷所思的奇蹟出現了：只見" 
                                     "一把磅礴劍氣激射而出，城外霎時飛砂走石遮天蔽日，似有猛" 
                                     "獸咆哮其中，晉國兵馬大亂。片刻之後，旌旗仆地，流血千里" 
                                     "，全軍覆沒這件事情過後，楚王召來國中智者風胡子問道：泰" 
                                     "阿劍為何會有如此之威？風胡子對楚王道：泰阿劍是一把威道" 
                                     "之劍，而內心之威才是真威，大王身處逆境威武不屈正是內心" 
                                     "之威卓越表現，正是大王的內心之威激發出泰阿劍的劍氣之威" 
                                     "啊！見於《越絕書》。泰阿劍是一把威道之劍！\n"NOR));
        set("value", 100000);   
        set("material", "steel");   
        set("no_sell", "我的天…你…你知道這是啥麼？這你也敢拿來賣？");   
        set("unique", 1);   
        set("rigidity", 500);
        set("replica_ob", "/clone/weapon/changjian");   
        set("no_put",1); 
        set("no_steal",1);  
        set("wield_msg",CYN"$N[噌]的一聲抽出一把泰阿劍，只見一把磅礴劍氣激射而出，霎時，飛砂走石遮天蔽日，"
                              "似有猛獸咆哮其中。\n"NOR);
        set("unwield_msg",CYN"$N把手中的泰阿劍插入劍鞘，天空恢復了平靜。\n"NOR);  
        } 
        init_sword(850);
        setup(); 
}
mixed hit_ob(object me, object victim, int damage_bonus)  
{
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return CYN "泰阿劍[鐺]一聲響，劍身一出，飛砂走石遮天蔽日，"   
              CYN "$n嚇的掉頭想跑。\n" NOR;  
} 