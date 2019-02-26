// Room: /d/kunlun/npc/puren.c
// Last Modified by winder on Nov. 14 2000

inherit NPC;

void create()
{
        set_name("僕人", ({"pu ren", "pu"}) );
        set("gender", "男性" );
        set("age", 50);
        set("long",
        "這是個老實巴交的老僕人，雖然衣服上打了很多補丁，卻是十分的整潔。\n"
        "因為長期待在廚房裏，眼睛被煙燻成了一條縫。\n");
        set("attitude", "friendly");
        set("shen_type", 1);

        set("str", 27);
        set("int", 25);
        set("con", 24);
        set("dex", 24);

        set("max_qi", 650);
        set("max_jing", 400);
        set("neili", 150);
        set("max_neili", 150);

               set("combat_exp", 1000+random(800));
        set("score", 1000);

        set_skill("force", 40);
        set_skill("dodge", 30);
        set_skill("unarmed", 25+random(20));
        set_skill("parry", 30);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 15);
        set_temp("apply/damage", 4);
//        create_family("崑崙派", 24, "弟子");
        setup();
        carry_object("/d/kunlun/obj/cloth")->wear();
}

void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;

        say("僕人笑吟吟地説道：這位" + RANK_D->query_respect(ob)
                + "請先入座，" + "我這就給您上茶。\n");
}

void serve_tea(object who)
{
        object obt, obc, obn;
        object room;

        if( !who || environment(who) != environment() ) return;

        if( !query_temp("marks/sit", who))return ;

        if( !objectp(room = environment()) ) return;

        if( query_temp("tea_cup", who) <= 0 )
        {
                obn = new("/d/kunlun/obj/dawancha");
                obn->move(room);
                message_vision("僕人搬出個大茶壺來，將桌上的大碗茶倒滿．\n",
                        who);
        } else
        {
                addn_temp("tea_cup", -1, who);
                obn = new("/d/kunlun/obj/xiangcha");
                obn->move(room);
                message_vision("僕人拿出個紹興小茶壺，沏了杯香茶，放在桌上．\n",
                        who);
        }

        obn = new("/d/kunlun/obj/rice");
        obn->move(room);
        message_vision("僕人盛了一碗剛蒸好的大米飯，放在桌上。\n", who);

        return;
}
