inherit NPC;
inherit F_GUARDER;

void create()
{
        set_name("李管家", ({ "li guanjia", "li", "guanjia" }));
        set("gender", "男性" );
        set("age", 25);
        set("long", "這是個和藹可親的大管家。\n");
        set("attitude", "friendly");
        set("shen_type", -1);
        set("class", "fighter");

        set("str", 23);
        set("int", 23);
        set("con", 22);
        set("dex", 20);

        set("max_qi", 5000);
        set("qi", 5000);
        set("max_jing", 5000);
        set("jing",5000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 0);

        set("combat_exp", 250000);
        set("score", 20000);

        set_skill("force", 160);
        set_skill("dodge", 160);
        set_skill("unarmed", 160);
        set_skill("parry", 160);
        set_skill("chanchu-bufa", 160);
        set_skill("changquan", 160);

        map_skill("dodge", "chanchu-bufa");
        map_skill("parry", "changquan");
        map_skill("unarmed", "changquan");

        create_family("歐陽世家", 0, "管家");

        set("coagents", ({
            ([ "startroom" : "/d/baituo/dating",
               "id"        : "ouyang feng" ]),
        }));
        setup();
        carry_object("/d/baituo/obj/baipao")->wear(); 
        carry_object("/d/baituo/obj/key"); 
}

void attempt_apprentice(object ob)
{
        if( query("born_family", ob) != "歐陽世家" )
        {
                command("shake");
                command("say 你是哪裏來的？居然敢來白駝山添亂？");
                return;
        }

        command("say 呵呵，我不收徒，去找歐陽莊主吧。");
        return;
}