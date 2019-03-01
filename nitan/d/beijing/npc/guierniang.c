inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void create()
{
        set_name("歸二娘", ({ "gui erniang", "gui" }));
        set("title", "華山派三十二代高手");
        set("long", 
"一個年邁的老婦，頭發半白，但看起來卻是精神抖擻，\n"
"脾氣相當的火暴。他便是神拳無敵歸心樹的內人──歸\n"
"二娘。\n");
        set("gender", "女性");
        set("age", 68);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 40);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 20);
        
        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 1500);
        set("max_jing", 1500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 50);

        set("combat_exp", 1000000);
        set("score", 20000);

        set_skill("cuff", 100);
        set_skill("force", 100);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set_skill("strike", 100);
        set_skill("sword", 150);
        set_skill("huashan-sword", 150);
        set_skill("zixia-shengong", 150);
        set_skill("poyu-quan", 100);
        set_skill("hunyuan-zhang", 100);
       set_skill("feiyan-huixiang",150);

        map_skill("cuff", "poyu-quan");
        map_skill("force", "zixia-shengong");
       map_skill("dodge", "feiyan-huixiang");
       map_skill("parry", "huashan-sword");
        map_skill("strike", "hunyuan-zhang");
        map_skill("sword", "huashan-sword");

        prepare_skill("strike", "hunyuan-zhang");
        prepare_skill("cuff", "poyu-quan");
       set("chat_chance", 2);
       set("chat_msg", ({
                "歸二娘望了歸鐘一眼，深深的嘆了口氣。\n",
        }) );       


        create_family("華山派", 32, "弟子");

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
        }) );

        setup();
        carry_object("/d/beijing/npc/obj/cloth4")->wear();
        carry_object("/d/beijing/npc/obj/sword1")->wield();

}
