// li.c
// Last Modified by Winder on May. 15 2001

inherit NPC;

void greeting(object);
void init();
void create()
{
        set_name("李教頭", ({ "li"}) );
        set("gender", "男性" );
        set("age", 25);
        set("long", "這是個和藹可親的教頭。\n");
        set("attitude", "friendly");
        set("shen_type", -1);

        set("str", 23);
        set("int", 23);
        set("con", 22);
        set("dex", 20);

        set("max_qi", 400);
        set("max_jing", 500);
        set("neili", 300);
        set("max_neili", 300);
        set("combat_exp", 250000);
        set("score", 20000);
        set("env/wimpy", 60);

        set_skill("force", 80);
        set_skill("dodge", 90);
        set_skill("parry", 80);
        set_skill("cuff", 80);
        set_skill("staff", 80);
        set_skill("hamagong", 70);
        set_skill("strike",80);
        set_skill("chanchu-bufa", 130);
        set_skill("lingshe-zhangfa", 120);
        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("staff", "lingshe-zhangfa");
        prepare_skill("cuff", "hamaquan");
        prepare_skill("strike", "hamagong");
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "strike.hama" :),
                (: exert_function, "powerup" :),
                (: exert_function, "reserve" :),
                (: exert_function, "recover" :),
        }) );
        create_family("歐陽世家", 0, "教頭");

        set("chat_chance", 2);
        set("chat_msg", ({
                "李教頭說道：勤學苦練方可出神功。\n",
                "李教頭鼓勵小弟子們不畏艱苦，好好練功。\n",
                "李教頭拍拍學徒的頭說：好樣的！\n",
        }) );
        setup();
}

void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if( query("family/family_name", ob) == "歐陽世家" )
        {
                message_vision("李教頭沖著$N點點頭，微微笑了笑。\n",ob);
                return;
        }

        message_vision("李教頭對$N嚷道：小家伙，你瞎逛什麼呢？\n",ob);
}


int accept_fight(object ob)
{
        if( query("family/family_name", ob) == "歐陽世家" )
        {
                if( query("combat_exp", ob)<1000 )
                        return notify_fail("李教頭笑道：你的經驗太低了，還是先找陪練童子比劃幾招吧。！\n");
        }
        return 1;
}

void attempt_apprentice(object ob)
{
        command("say 我們追隨歐陽世家，不收徒。");
        return;
}
