// zhang.c 張三豐

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("張三豐", ({ "zhang-sanfeng", "zhang" }));
        set("nickname", "邋遢真人");
        set("long", 
                "他就是武當派開山鼻祖、當今武林的泰山北鬥張三豐真人。\n"
                "身穿一件污穢的灰色道袍，不修邊幅。\n"
                "身材高大，年滿百歲，滿臉紅光，須眉皆白。\n");
        set("gender", "男性");
        set("age", 100);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 5000);
        set("max_jing", 3000);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 100);
        set("combat_exp", 2000000);
        set("score", 500000);
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "sword.ren" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
        set_skill("force", 200);
        set_skill("taiji-shengong", 200);
        set_skill("dodge", 150);
        set_skill("tiyunzong", 150);
        set_skill("unarmed", 200);
        set_skill("taiji-quan", 200);
        set_skill("parry", 200);
        set_skill("sword", 200);
        set_skill("taiji-jian", 200);
        set_skill("liangyi-jian", 200);
        set_skill("wudang-jian", 200);
        set_skill("taoism", 150);
        set_skill("literate", 100);

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "liangyi-jian");

        create_family("武當派", 1, "開山祖師");
        set("class", "taoist");

        setup();
        carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob=this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        object *obj, me=this_object();
        int i;

        obj = all_inventory(environment(me));
        command("say 這招好象應該這樣，直中有曲，曲中有直。");
        for(i=0; i<sizeof(obj); i++)
        {
                if( query("id", obj[i]) == "feng-qingyang" )
                {
                    COMBAT_D->do_attack(me,obj[i],query_temp("weapon", me),0);
                    COMBAT_D->do_attack(me,obj[i],query_temp("weapon", me),0);
                }
        }
        return;
}