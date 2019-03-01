// yideng.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void consider();

void create()
{
        set_name("一燈大師", ({"yideng dashi", "dashi", "yideng"}));
        set("nickname", HIG "天南一帝" NOR );
        set("gender", "男性");
        set("age", 52);
        set("long", 
                "他就是號稱「南帝」的一燈大師，俗名段智興，現已遜位為僧。\n"
                "他身穿粗布僧袍，兩道長長的白眉從眼角垂了下來，面目慈祥，\n"
                "長須垂肩，眉間雖隱含愁苦，但一番雍容高華的神色，卻是一\n"
                "望而知。大師一生行善，積德無窮。\n");
        set("attitude", "peaceful");
        set("class", "bonze");
        
        set("str", 21);
        set("int", 30);
        set("con", 26);
        set("dex", 30);

        set("qi", 3000);
        set("max_qi", 3000);
        set("jing", 3000);
        set("max_jing", 3000);
        set("neili", 3500);
        set("max_neili", 3500);
        set("jiali", 100);
        
        set("combat_exp", 3000000);
        set("score", 0);

        set_skill("force", 200);
        set_skill("dodge", 200);
        set_skill("parry", 200);
        set_skill("finger", 200);
        set_skill("strike", 200);
        set_skill("cuff", 200);
        set_skill("whip", 200);
        set_skill("sword", 200);
        set_skill("axe", 200);
        set_skill("tiannan-bu", 300);
        set_skill("kurong-changong", 200);
        set_skill("duanjia-jian", 300);
        set_skill("duanyun-fu", 300);
        set_skill("wuluo-zhang", 300);
        set_skill("jinyu-quan", 300);
        set_skill("feifeng-bian", 300);
        set_skill("six-finger", 300);
        set_skill("sun-finger", 300);
        set_skill("buddhism", 100);
        set_skill("literate", 100);

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("parry", "six-finger");
        map_skill("finger", "six-finger");
        map_skill("sword", "duanjia-jian");
        map_skill("axe", "duanyun-fu");
        map_skill("whip", "feifeng-bian");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        prepare_skill("finger","six-finger");
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
//                (: perform_action, "sword.jingtian" :),        
                (: perform_action, "finger.yuqi" :),                        
                (: exert_function, "powerup" :),                
                (: exert_function, "recover" :),
                (: exert_function, "regenerate" :),
        }) );

        create_family("大理段家", 17, "弟子");
        setup();
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if ((int)ob->query_skill("kurong-changong",1) < 150 )
        {
                command("say 你的本門內功心法太低了，還是努努力先提高一下吧。");
                return;
        }
        if( query("shen", ob)<10000){
                command("say 我大理段氏向來行俠仗義，您請回吧！");
                return;
        }
        command("say 阿彌陀佛，我就收了你這個徒弟吧。");
        command("recruit "+query("id", ob));
}
