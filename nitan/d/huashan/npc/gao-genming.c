// gao-genming.c

inherit NPC;
inherit F_GUARDER;

// int permit_pass(object me, string dir);

void create()
{
        set_name("高根明", ({ "gao genming","gao","genming" }) );
        set("nickname", "市井豪傑");
        set("gender", "男性");
        set("age", 24);
        set("long",
                "高根明是嶽不羣的第五位弟子。\n");
        set("attitude", "peaceful");

        set("str", 26);
        set("con", 30);
        set("int", 24);
        set("dex", 30);

        set("neili", 900);
        set("max_neili", 900);

        set("combat_exp", 30000);
        set("score", 20000);
        set("shen_type", 1);

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :)
        }) );

        set_skill("unarmed", 50);
        set_skill("sword", 50);
        set_skill("force", 50);
        set_skill("parry", 50);
        set_skill("dodge", 50);
        set_skill("literate", 30);

        set_skill("huashan-sword", 50);
        set_skill("huashan-neigong", 50);
        set_skill("huashan-quan", 50);
        set_skill("feiyan-huixiang", 50);

        map_skill("sword", "huashan-sword");
        map_skill("parry", "huashan-sword");
        map_skill("force", "huashan-neigong");
        map_skill("unarmed", "huashan-quan");
        map_skill("dodge", "feiyan-huixiang");

        set("coagents", ({
                ([ "startroom" : "/d/huashan/qunxianguan",
                   "id"        : "yue buqun" ]),
        }));

        create_family("華山派", 14, "弟子");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

/*
int permit_pass(object me, string dir)
{
        object *inv;
        int i;

        if (! living(this_object()))
                return 1;

        if( query_temp("beg_huashan", me) )
        {
                message_vision("$N眼睛一彈，對$n喝道：“你亂"
                               "跑個啥？是奸細麼？”\n", this_object(), me);
                return -1;
        }

        notify_fail("看來" + name() + "不打算讓你過去。\n");

        inv = all_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! playerp(inv[i])) continue;
                if( query("family/family_name", inv[i]) != "華山派" )
                {
                        message_vision("$N對$n喝道：你背的是誰？還不快快放下！\n",
                                       this_object(), me);
                        return 0;
                }
        }

        if( query("family/family_name", me) && 
            query("family/family_name", me) != "華山派" || 
            !query("family/family_name", me) && 
            query("combat_exp", me)>20000 )
        {
                message_vision("$N對$n道：對不起，不是我們華山派的人"
                               "請勿入本派重地。\n", this_object(), me);
                return 0;
        }

        return 1;
}
*/
