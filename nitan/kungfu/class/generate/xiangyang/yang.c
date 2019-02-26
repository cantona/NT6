// yang.c 楊過

inherit NPC;

void random_move();

void create()
{
        set_name("楊過", ({"yang guo", "yang"}));
        set("gender", "男性");
        set("age", 26);
        set("long", @LONG
他看上去眉目之間有一股清秀之氣，然而隱隱約約卻讓人感到一陣哀傷之情，
左袖空蕩蕩的，顯然已是殘疾。
LONG );
        set("attitude", "friendly");

        set("str", 35);
        set("int", 36);
        set("con", 34);
        set("dex", 32);

        set("qi", 300000);
        set("max_qi", 300000);
        set("jing", 200000);
        set("max_jing", 200000);
        set("neili", 100000);
        set("max_neili", 100000);
        set("jiali", 500);

        set("combat_exp", 575000000);

        set("couple/id", "xiao longnv");
        set("couple/name", "小龍女");

        set_skill("force", 600);
        set_skill("yunv-xinfa", 600);
        set_skill("surge-force", 600);
        set_skill("sword", 600);
        set_skill("yunv-jian", 600);
        set_skill("quanzhen-jian", 600);
        set_skill("xuantie-jian", 600);
        set_skill("dodge", 600);
        set_skill("yunv-shenfa", 600);
        set_skill("parry", 600);
        set_skill("unarmed", 600);
        set_skill("meinv-quan", 600);
        set_skill("strike", 600);
        set_skill("sad-strike", 600);
        set_skill("fireice-strike", 600);
        set_skill("tianluo-diwang", 600);
        set_skill("literate", 600);
        set_skill("taoism", 600);
        set_skill("medical", 600);
        set_skill("yunv-xinjing", 600);
        set_skill("throwing", 600);
        set_skill("yufeng-zhen", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "surge-force");
        map_skill("sword", "xuantie-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "meinv-quan");
        map_skill("unarmed", "sad-strike");
        map_skill("strike", "tianluo-diwang");

        prepare_skill("unarmed", "sad-strike");

        create_family("古墓派", 3, "弟子");

        set("inquiry", ([
                "王重陽" : "嘿...嘿！",
                "郭靖"   : "他可真是真正的大俠。",
                "黃蓉"   : "黃師叔麼...真不好説啊。",
                "小龍女" : "你打聽我妻子幹什麼？",
        ]));
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.wang" :),
                (: perform_action, "unarmed.xiao" :),
                (: perform_action, "unarmed.tuo" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: random_move :),
        }));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        setup();

        carry_object("/clone/cloth/qingyi")->wear();
}

mixed teach_sad()
{
        object ob = this_player();

        if (ob->query_skill("sad-strike", 1) >= 1)
        {
                command("say 你不是已經會了嗎？");
                return 1;
        }

        if (ob->query("gender") != "男性")
        {
                command("say 我這門武功只適合男性修煉，你還是算了吧！");
                return 1;
        }

        if (ob->query("static/sadly") < 3)
        {
                command("say 你體會不到那種思念妻子的情懷，"
                        "無法領會我的黯然銷魂掌！");
                return 1;
        }

        if (ob->query("character") == "陰險奸詐" || 
            ob->query("character") == "心狠手辣")
        {
                command("say 你一心想着去害人，無法領悟黯然銷魂的境界！");
                return 1;
        }

        if (ob->query("int") < 34)
        {
                command("say 你先天悟性不足，無法領悟黯然銷魂掌。");
                return 1;
        }

        if (ob->query("str") < 34)
        {
                command("say 你先天臂力不足，無法修煉黯然銷魂掌。");
                return 1;
        }

        if ((int)ob->query("max_neili") < 3000)
        {
                command("say 你的內力修為不足，無法練黯然銷魂掌。");
                return 1;
        }
}

void unconcious()
{
        object ob;

        ob = query("mate");
        if (objectp(ob))ob->die_msg();
        
        die();
}

void die_msg()
{
        command("chat 龍兒 ……");
        destruct(this_object());
}

void random_move()
{
        string dir;
        string route;
        object env;

        if (query_temp("dest_now"))
        {
                destruct(this_object());
                return;
        }

        if (XYWAR_D->dest_status() == 1)
        {
                set_temp("dest_now", 1);
        }
}
