// playboy.c

inherit NPC;

void create()
{
        set_name("花花公子", ({ "playboy" }) );
        set("nickname", "採花大盜");
        set("gender", "男性" );
        set("age", 19);
        set("long", "這是個流裏流氣的花花公子。\n");
        set("attitude", "friendly");
        set("shen_type", -1);

        set("str", 21);
        set("int", 23);
        set("con", 22);
        set("dex", 20);

        set("max_qi", 400);
        set("max_jing", 200);
        set("neili", 100);
        set("max_neili", 100);
        set("combat_exp", 30000+random(10000));
        set("score", 10000);
        setup();
        add_money("silver", 10);
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
        if (! ob || environment(ob) != environment())
                return;

        if( query("gender", ob) == "女性" )
        {
                if (random(2) == 1)
                        say("花花公子色迷迷説：" + RANK_D->query_respect(ob) +
                            "幹嘛那麼着急趕路，陪我玩玩不行嗎？\n");
                else
                        say("花花公子唱道：路邊的野花不採白不採~~。這位" +
                            RANK_D->query_respect(ob) + "你説是嗎？\n");
        }
}