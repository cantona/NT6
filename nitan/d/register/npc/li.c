// li

inherit NPC;

void greeting(object me);

void create()
{
        set_name("李自成", ({ "li zicheng", "li"}));
        set("long", "他面透煞氣，暴戾異常，看得你心裡毛毛的。\n");
        set("gender", "男性");
        set("age", 49);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("per", 20);

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

        command("nod"+query("id", me));
        command("say 這位" + RANK_D->query_respect(me) +
                "，哈哈，你來得正好！咱們講究的就是心狠手辣\n"
                "什麼正派人士，全是偽君子，我們要把他們統統殺光！");
}

void check_leave(object me, string dir)
{
        if (dir == "out")
        {
                message_vision("$N對$n狂笑道：上啊！殺光那幫偽君子！\n",
                               this_object(), me);
                command("chat 哈哈！你們這些偽君子小心了！");
                set("character", "心狠手辣", me);
        } else
        if (dir == "south")
        {
                command("heng");
                command("say 膽小鬼！");
        }
}