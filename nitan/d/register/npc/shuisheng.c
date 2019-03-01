// shuisheng 水笙

inherit NPC;

void greeting(object me);
int do_register(string arg);
int do_decide(string arg);

void create()
{
        set_name("水笙", ({ "shui sheng","shuisheng"}));
        set("long", "她輕妝淡抹，眉目之中深深的透露哀思。\n");
        set("gender", "女性");
        set("age", 22);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 25);

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

        add_action("do_register", "register");
        add_action("do_decide", "decide");

        remove_call_out("greeting");
        call_out("greeting", 0, me);
}

void greeting(object me)
{
        if (! objectp(me) || environment(me) != environment(this_object()))
                return;

        if( !query("registered", me) )
        {
                command("tell"+query("id", me)+"你還沒有注冊，快注冊(register)吧。");
                command("tell"+query("id", me)+"你務必注冊你個你能夠收取信件的地址"
                        "，\n以備口令丟失的時候能夠收取更新的口令。");
                return;
        }

        if( !stringp(query("character", me)) )
        {
                command("tell"+query("id", me)+"你還沒有選擇品質，快去附近選選吧。");
                return;
        }

        if (! wizardp(me))
        {
                command("tell"+query("id", me)+"咦，你怎麼跑到這裡來了？");
                if( !stringp(query("born", me)) )
                {
                        message_vision("$N被昏昏沉沉的扔了出去。\n", me);
                        delete("born", me);
                        me->move("/d/register/yanluodian");
                        message_vision("啪的一聲，$N被扔到了地上。\n", me);
                        return;
                }

                message_vision("$N被昏昏沉沉的扔了出去。\b", me);
                me->move(VOID_OB);
                message_vision("啪的一聲，$N被扔到了地上。\n", me);
                return;
        }

        command("look"+query("id", me));
}

int do_register(string arg)
{
        object me;
        string id, address;

        if (! objectp(me = this_player()))
                return 0;

        if( query("registered", me) )
        {
                command("say 你不是已經注冊過了嗎？不用再注冊了。");
                return 1;
        }

        if (! arg || ! stringp(arg))
        {
                command("shake"+query("id", me));
                command("say 注冊的email地址你得給我啊。請輸入register 你的email地址");
                return 1;
        }

        if (strlen(arg) > 64 || sscanf(arg, "%s@%s", id, address) != 2)
        {
                command("say 我怎麼沒有見過這麼怪的email地址？你看看清楚好嗎？");
                return 1;
        }

        set_temp("email", arg, me);
        command("nod"+query("id", me));
        command("tell"+query("id", me)+"好，你的email地址是："+arg+
                "，如果沒有\n錯誤，你就決定(decide)吧。");
        command("tell"+query("id", me)+"請注意，由于本站不採用mail確認，所以
你即使注冊一個你無法收信的地址，系統也不能識別。當你決定採用
這個信箱地址以後，它將成為確認你身份的唯一途徑，這個注冊的信
箱地址是永遠不能改變的。當你丟失了你的密碼以後系統的管理人員
可以將修改後的口令發送到你注冊的信箱中，如果你出于某種目的不
願意注冊你的信箱，那麼管理人員將不為你的密碼負任何責任，這意
味著你必須自己保管好你的密碼。");
        return 1;
}

int do_decide(string arg)
{
        object me;
        object link_ob;

        if (! objectp(me = this_player()))
                return 0;

        if( query("registered", me) )
        {
                command("say 行了行了，我已經知道你的地址了，不用再說啦！\n");
                return 1;
        }

        if( !stringp(query_temp("email", me)) )
        {
                command("say 你要決定什麼？是決定注冊嗎？要是那"
                        "樣請你先注冊你的email地址。");
                return 1;
        }

        command("say 好了！你的email地址已經注冊了！現在快去附近選你的品質吧。");
        set("email",query_temp("email",  me), me);
        set("registered", 1, me);
        me->save();
        return 1;
}