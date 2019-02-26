// hua

inherit NPC;

void greeting(object me);

void create()
{
        set_name("花鐵幹", ({ "hua tiegan", "hua"}));
        set("long", "他一臉來上去大義凜然，卻總讓感覺有點什麼不對。\n");
        set("gender", "男性");
        set("age", 41);
        set("attitude", "peaceful");
        set("shen_type", -1);
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

        command("look"+query("id", me));
        command("say 這位" + RANK_D->query_respect(me) +
                "，這年頭做那種什麼正人君子太吃虧啦，看看\n"
                "我？看看嶽不羣老哥，那才是做人的道理，別猶豫啦！");
}

void check_leave(object me, string dir)
{
        if (dir == "out")
        {
                message_vision("$N對$n奸笑道：上路吧！\n", this_object(), me);
                command("chat 哈哈！江湖上又要...... 嘿嘿！");
                set("character", "陰險奸詐", me);
        } else
        if (dir == "east")
        {
                command("grin");
                command("say 哼，沒眼光！");
        }
}