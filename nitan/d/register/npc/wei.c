// wei

inherit NPC;

void greeting(object me);

void create()
{
        set_name("韋小寶", ({"wei xiaobao", "wei"}));
        set("long", "他一臉頑皮像，眼神中透露著狡黠，沒有半點正經。\n");
        set("gender", "男性");
        set("age", 21);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 24);

        setup();
        carry_object("/clone/cloth/cloth.c")->wear();
}

void init()
{
        object me;

        ::init();
        me = this_player();
        if (! objectp(me) || ! userp(me))
                return;

        remove_call_out("greeting");
        call_out("greeting", 0, me);
}

void greeting(object me)
{
        if (! objectp(me) || environment(me) != environment(this_object()))
                return;

        command("xixi"+query("id", me));
        command("say 這位" + RANK_D->query_respect(me) +
                "，嘿，在武林中立足，光講仁義是萬萬不行的，\n"
                "只有像我和令狐大俠那樣，狡黠多變，才活得下去！");
}

void check_leave(object me, string dir)
{
        if (dir == "out")
        {
                message_vision("$N對$n笑道：走！多搗點亂，那多有意思？\n",
                               this_object(), me);
                command("chat 嘻嘻！有意思。");
                set("character", "狡黠多變", me);
        } else
        if (dir == "north")
        {
                command("shake");
                command("say 不好玩兒。");
        }
}