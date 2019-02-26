// wulaoda.c

inherit NPC;

string ask_me();

void create()
{
        set_name("烏老大", ({ "wu laoda", "wu" }));
        set("gender", "男性");
        set("age", 47);

        set("inquiry", ([
                "屠人大賽" : (: ask_me :),
                "屠人比賽" : (: ask_me :),
                "屠人賽"   : (: ask_me :),
                "屠人"     : (: ask_me :),
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        add_action("do_sign", "sign");
        add_action("do_join", "join");
}

void unconcious()
{
        die();
}

void die()
{
        message_vision("$N打了個噴嚏，隨即恢復正常。\n", this_object());
}

string ask_me()
{
        object me;

        me = this_player();
        if (PK_D->is_pking())
                return "現在屠人大賽正在舉行呢，你想幹什麼？";

        if (PK_D->is_ready())
                return "很好，現在屠人大賽正要開始，你要報名麼(sign)？";

        return "屠人大賽？你慢慢等着吧。要是無聊，現在要是想進去玩玩(join)也行。";
}

int do_join()
{
        if (PK_D->is_pking())
                return notify_fail("烏老大眼睛一彈，喝道：“現在裏面正比賽呢，你這些人等等吧。”\n");

        if (PK_D->is_ready())
                return notify_fail("烏老大懶懶道：“要想正式比賽就進去，其他人先等着。”\n");

        message_vision("$N賠笑對$n道：“我進去溜達溜達，放行可好？”\n",
                       this_player(), this_object());

        if (PK_D->join_competition(this_player()))
        {
                message("vision", this_player()->name() + "一溜小跑進了屠人場。\n",
                        environment());
                return 1;
        }

        return 0;
}

int do_sign()
{
        object me;
        string msg;
        object ob;

        me = this_player();
        message_vision("$N陪着笑臉對$n道：“您好，您好，我也來籤個到。”\n",
                       me, this_object());
        if( query("combat_exp", me)<1000 )
        {
                message_vision("$n抬頭看了看$N，不屑道：“就你"
                               "這點本事？只好參加被屠大賽！”\n",
                               me, this_object());
                return 1;
        }

        if (stringp(msg = PK_D->reject_join(me)))
        {
                command("say " + msg);
                return 1;
        }

        foreach (ob in deep_inventory(me))
                if (ob->is_character())
                {
                        command("say 你背的誰？去比賽還拖家帶口的？快給我滾！");
                        message_vision("$N飛起一腳，把$n踢倒在地！\n",
                                       this_object(), me);
                        me->receive_damage("qi", 50);
                        return 1;
                }

        message_vision("$n點點頭，對$N道：“好吧，你先進"
                       "去準備吧。”\n$N點點頭，向北面的"
                       "準備室走去。\n", me, this_object());
        me->move("/d/pk/ready");
        message("vision", me->name() + "精神抖擻的走了進來。\n",
                environment(me), ({ me }));
        return 1;
}
