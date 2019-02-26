// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// chen.c 陳家洛

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("陳家洛", ({ "chen jialuo", "chen","jialuo" }));
        set("title", HIR "紅花會總舵主" NOR);
        set("long", 
"他一副模樣直是個富貴人家的紈褲子弟，丰姿如玉，目朗似星，輕
袍緩帶，手中搖着一柄摺扇，神采飛揚，氣度閒雅，吐屬斯文。服
飾儼然是個貴介公子。\n");
        set("nickname", HIW"玉面神龍"NOR);
        set("gender", "男性");
        set("class", "scholar");
        set("age", 22);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 30);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("level", 40);       
        set("max_qi", 3500);
        set("max_jing", 1200);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 150);
        set("combat_exp", 2000000);
        set("score", 500000);

        set_skill("literate", 700);
        set_skill("force", 600);
        set_skill("dodge", 600);
        set_skill("unarmed", 600);
        set_skill("parry", 600);
        set_skill("cuff", 600);
        set_skill("strike", 600);
        set_skill("hand", 600);
        set_skill("finger", 600);
        set_skill("claw", 600);
        set_skill("zhanshen-xinjing", 600);
        set_skill("zhuangzi-wu", 600);
        set_skill("baihua-cuoquan", 600);
        set_skill("martial-cognize", 600);

        map_skill("dodge", "zhuangzi-wu");
        map_skill("force", "zhanshen-xinjing");
        map_skill("unarmed", "baihua-quan");
        map_skill("hand", "baihua-cuoquan");
        map_skill("parry", "baihua-cuoquan");
        map_skill("claw", "baihua-cuoquan");
        map_skill("strike", "baihua-cuoquan");
        map_skill("cuff", "baihua-cuoquan");

        prepare_skill("unarmed", "baihua-cuoquan");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed.hong" :),
                (: perform_action, "unarmed.luan" :),   
                (: perform_action, "unarmed.yi" :),                            
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
        
        create_family("紅花會", 2, "總舵主");
        setup();
        carry_object("/clone/cloth/jinduan")->wear();
        carry_object("/clone/cloth/yaodai")->wear();
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "歷練" :
        case "歷煉" :
        case "鍛鍊" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "百花錯亂" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/baihua-cuoquan/luan",
                           "name"    : "百花錯亂",
                           "sk1"     : "baihua-cuoquan",
                           "lv1"     : 180,
                           "dodge"   : 150,
                           "free"    : 1,
                           // "gongxian": 420,
                           "shen"    : 38000, ]));
                break;

        case "百花錯易" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/baihua-cuoquan/yi",
                           "name"    : "百花錯易",
                           "sk1"     : "baihua-cuoquan",
                           "lv1"     :  130,
                           "force"   :  180,
                           "free"    :  1,
                           // "gongxian":  580,
                           "shen"    : 43000, ]));
                break;

        case "戰神轟天訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/baihua-cuoquan/hong",
                           "name"    : "戰神轟天訣",
                           "sk1"     : "baihua-cuoquan",
                           "lv1"     : 180,
                           "sk2"     : "zhanshen-xinjing",
                           "lv2"     : 180,
                           "neili"   : 3000,
                           "free"    : 1,
                           // "gongxian": 1200,
                           "shen"    : 68000, ]));
                break;

        case "化蝶" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                       ([ "perform" : "can_perform/zhuangzi-wu/hua", 
                          "name" : "化蝶", 
                          "sk1" : "zhuangzi-wu", 
                          "lv1" : 150, 
                          "neili" : 1000, 
                          "free" : 1, 
                          "shen" : 40000, 
                       ])); 
                break; 


        default:
                return 0;
        }
}

int recognize_apprentice(object ob, string skill)
{
        if (ob->query_skill(skill, 1) >= 600)
        {
                command("say 夠了！我就教你到這裏吧，武功還是"
                        "要靠自己多研究才是！");
                return -1;
        }              

        if( query_temp("can_learn/chen/baihua-cuoquan", ob) )
                return 1;

        if (skill == "baihua-cuoquan")
        {
                message_vision("$N看了看$n，點點頭道：你我既然如此有緣，我就傳授你百花錯拳。\n",
                               this_object(), ob);
                set_temp("can_learn/chen/baihua-cuoquan", 1, ob);
                return 1;
        }

        command("say 我只能傳授你百花錯拳和相關的武功，你可不要為難我。");
        return -1;
}

void unconcious()
{
        die();
}
