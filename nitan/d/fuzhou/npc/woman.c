// woman.c

inherit NPC;

void create()
{
        set_name("少婦",({ "woman" }) );
        set("gender", "女性" );
        set("age", 25);
        set("long", "這是個美麗少婦，雙目含情，一對胸脯鼓鼓囊囊。\n");
        set_temp("apply/defense", 6);
        set("combat_exp", 700);
        set("shen", 100);
        set("shen_type", 1);
        set("str", 14);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object(CLOTH_DIR"cloth")->wear();
}
void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) )
        {
                case 0:
                        say("少婦低聲説道：這位" + RANK_D->query_respect(ob) + "，瞧我這頑皮小兒，奴家該怎麼辦啊？\n");
                        break;
                case 1:
                        say("少婦嗚咽着説道：這位" + RANK_D->query_respect(ob) + "，奴家的那個死鬼不知道又到哪裏鬼混去了，您幫我管教一下小兒吧。\n");
                        break;
        }
}