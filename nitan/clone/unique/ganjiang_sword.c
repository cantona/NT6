// Copyright (C) 2003, by Lonely. All rights reserved. 
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// ganjiang-sword.c 干將
// for only one object in mud  

#include <ansi.h>  
#include <weapon.h>  
inherit SWORD;  
inherit F_UNIQUE;  

void create() 
{ 
        set_name(HIB "干將" NOR, ({"ganjiang sword", "ganjiang", "sword"})); 
        set_weight(15000);  
        if (clonep())  
                set_default_object(__FILE__);  
        else {  
                set("unit", "把"); 
                set("long", sort_msg(HIB "干將、莫邪是兩把劍，但是沒有人能分開它們。干將、莫"
                                     "邪是兩個人，同樣，也沒有人能將他（她）們分開。干將、莫"
                                     "邪是干將、莫邪鑄的兩把劍。干將是雄劍，莫邪是雌劍。干將"
                                     "是丈夫，莫邪是妻子。干將很勤勞，莫邪很温柔。干將為吳王"
                                     "鑄劍的時候，莫邪為干將扇扇子，擦汗水。三個月過去了，幹"
                                     "將歎了一口氣。莫邪也流出了眼淚。莫邪知道干將為什麼歎氣"
                                     "，因為爐中採自五山六合的金鐵之精無法熔化，鐵英不化，劍"
                                     "就無法鑄成。干將也知道莫邪為什麼流淚，因為劍鑄不成，自"
                                     "己就得被吳王殺死。干將依舊歎氣，而在一天晚上，莫邪卻突"
                                     "然笑了。看到莫邪笑了，干將突然害怕起來，干將知道莫邪為"
                                     "什麼笑，干將對莫邪説：莫邪，你千萬不要去做。莫邪沒説什"
                                     "麼，她只是笑。干將醒來的時候，發現莫邪沒在身邊。干將如"
                                     "萬箭穿心，他知道莫邪在哪兒。莫邪站在高聳的鑄劍爐壁上，"
                                     "裙裾飄飛，宛如仙女。莫邪看到干將的身影在熹微的晨光中從"
                                     "遠處急急奔來。她笑了，她聽到干將嘶啞的喊叫：莫邪，莫邪"
                                     "依然在笑，但是淚水也同時流了下來。干將也流下了眼淚，在"
                                     "淚光模糊中他看到莫邪飄然墜下，他聽到莫邪最後對他説道："
                                     "干將，我沒有死，我們還會在一起。鐵水熔化，劍順利鑄成。"
                                     "一雄一雌，取名干將莫邪，干將只將“干將”獻給吳王。干將"
                                     "私藏“莫邪”的消息很快被吳王知曉，武士將干將團團圍住，"
                                     "干將束手就擒，他打開劍匣絕望地向裏面問道：莫邪，我們怎"
                                     "樣才能在一起？劍忽從匣中躍出，化為一條清麗的白龍，飛騰"
                                     "而去，同時，干將也突然消失無蹤。在干將消失的時候，吳王"
                                     "身邊的“干將”劍也不知去向。而在千里之外的荒涼的貧城縣"
                                     "，在一個叫延平津的大湖裏突然出現了一條年輕的白龍。這條"
                                     "白龍美麗而善良，為百姓呼風喚雨，荒涼的貧城縣漸漸風調雨"
                                     "順，五穀豐登，縣城的名字也由貧城改為豐城。可是，當地人"
                                     "卻時常發現，這條白龍幾乎天天都在延平津的湖面張望，象在"
                                     "等待什麼，有人還看到它的眼中常含着淚水。六百年過去了。"
                                     "一個偶然的機會裏，豐城縣令雷煥在修築城牆的時候，從地下"
                                     "掘出一個石匣，裏面有一把劍，上面赫然刻着“干將”二字，"
                                     "雷煥欣喜異常，將這把傳誦已久的名劍帶在身邊。有一天，雷"
                                     "煥從延平津湖邊路過，腰中佩劍突然從鞘中跳出躍進水裏，正"
                                     "在雷煥驚愕之際，水面翻湧，躍出黑白雙龍，雙龍向雷煥頻頻"
                                     "點頭意在致謝，然後，兩條龍脖頸親熱地糾纏廝磨，雙雙潛入"
                                     "水底不見了。在豐城縣世代生活的百姓們，發現天天在延平津"
                                     "湖面含淚張望據説已存在了六百多年的白龍突然不見了。而在"
                                     "第二天，縣城裏卻搬來了一對平凡的小夫妻。丈夫是一個出色"
                                     "的鐵匠，技藝非常精湛，但他只用心鍛打掙不了幾個錢的普通"
                                     "農具卻拒絕打造有千金之利的兵器，在他幹活的時候，他的小"
                                     "妻子總在旁邊為他扇扇子，擦汗水。這是兩把中的一把：干將。"
                                     "干將是一把摯情之劍。\n" NOR));
        set("value", 100000);  
        set("material", "steel"); 
        set("no_sell", "我的天…你…你知道這是啥麼？這你也敢拿來賣？");  
        set("unique", 1);  
        set("rigidity", 500);  
        set("replica_ob", "/clone/weapon/changjian"); 
        set("no_put",1);  
        set("no_steal",1);    
        set("wield_msg",HIB"$N[噌]的一聲抽出一把干將，干將似一條黑龍，象是等待着什麼。\n"NOR);  
        set("unwield_msg",HIB"$N把手中的干將插入劍鞘。\n"NOR);  
     } 
     init_sword(750);  
     setup(); 
} 

mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return HIB "干將似一條黑龍一般咬向$n，" 
               HIB "$n只感到恐慌。\n" NOR; 
}