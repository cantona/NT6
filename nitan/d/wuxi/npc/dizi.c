// dizi.c
inherit NPC;
int do_bi(string arg);
void greeting(object);
void init();
void create()
{
        set_name("武館弟子", ({ "wuguan dizi", "dizi"}) );
        set("gender", "男性" );
        set("age", 16);
        set("long", "這是個陪人練功的武館弟子。\n");
        set("attitude", "friendly");
        set("shen_type", 0);

        set("str", 21);
        set("int", 21);
        set("con", 21);
        set("dex", 20);

        set("max_qi", 200);
        set("combat_exp", 10000);
        set("score", 500);
        set_skill("force", 20);
        set_skill("dodge", 20);
        set_skill("unarmed", 20);
        set_skill("parry",20);
        setup();
}

void init()
{
        object ob;
        add_action("do_bi","bi");
        if( interactive(ob = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if( query("combat_exp", ob)<10000 )
        message_vision("武館弟子沖著$N叫道：快來跟我比劃幾招。(bi dizi)\n",ob);
}

int do_bi(string arg)
{
        object ob=this_player();
        if(!arg||arg!="dizi") return  notify_fail("你要和誰比劃？\n");
        if( query("combat_exp", ob)>10000 )
                return notify_fail("武館弟子搖頭道：以你的武功，我不能做你的陪練。\n");
        say("武館弟子同意作你的陪練。\n");
        set("combat_exp",query("combat_exp", ob));
        command("hit"+query("id", ob));
        if(query("qi")<40)
                message_vision("武館弟子對$N大加讚賞!\n",ob);
        else
                message_vision("武館弟子對$N笑笑道：努力吧。\n",ob);

        set("eff_qi",200);
        set("qi",200);
        set("combat_exp",10000);
        return 1;
}

int accept_fight(object ob)
{
        message_vision("武館弟子對$N叫道：那我就不讓你了！\n",ob);
        return 1;
}

