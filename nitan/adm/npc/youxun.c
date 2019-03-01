// youxun.c
// pal 1997.05.28

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

nosave object *receiver;

object *query_receiver() { return receiver; }

int ask_fee();
int ask_bomb();
int ask_shedu();
int ask_duwan();
int ask_list();
int filter_listener(object user);

void create()
{
        set_name("遊訊", ({ "you xun", "you", "xun", "youxun" }) );
        set("nickname", HIG "滑不留手" NOR);
        set("gender", "男性" );
        set("age", 42);
        set("long", "他就是專門打探、販賣消息的遊訊。\n");
        set("attitude", "friendly");

        set("max_jing", 500);
        set("max_qi", 500);
        set("str", 21);
        set("int", 29);
        set("con", 21);
        set("dex", 35);
        set("combat_exp", 250000);

        set("inquiry", ([
                "name" : "小的就是遊訊，不知您要打聽點什麼？",
                "rumor": "不是小的吹牛，誰的謠言我都能查出來。",
                "fee"  : (: ask_fee :),
                "收費" : (: ask_fee :),
                "bomb" : (: ask_bomb :),
                "炸彈" : (: ask_bomb :),
                "蛇毒" : (: ask_shedu :),
                "毒藥" : (: ask_duwan :),
                "核彈" : (: ask_list :),
                "打聽" : "嘿嘿嘿，你想打聽誰？鄙人消息那個靈通...",
                "核炸彈"   : (: ask_list :),
                "核子飛彈" : (: ask_list :),
                "核子炸彈" : (: ask_list :),
                "核子導彈" : (: ask_list :),
                "飛毛腿"   : (: ask_list :),
                "飛毛腿導彈": (: ask_list :),
                "礦泉水"    : "被飛彈炸了？來兩瓶解解渴！",
                "發呆神功" : "想學麼(idle-force)？鄙人教，不收錢的。",
        ]));

        set("vendor_goods", ({
                "/clone/gift/feidan",
                "/clone/gift/feimao",
                "/clone/gift/kuangquan",
        }));

        set("chat_chance", 1);
        set("chat_msg",({
                "遊訊嘻嘻道：小的我沒別的本事，就會打聽消息，就算是巫師造謠，我也能知道。\n",
                "遊訊亮出一指道：便宜啊，幾兩銀子就能查條謠言，這可真是跳樓價。\n",
                "遊訊賊眯眯的說：天算地算不如人算，可是再怎麼算我遊某都知道。\n",
        }));

        set_skill("dodge", 150);
        set_skill("unarmed", 50);
        set_skill("idle-force", 2100);

        setup();
        carry_object("d/city/obj/cloth")->wear();

        if (! clonep(this_object()))
        {
                move("/d/city/kedian");
                message_vision("$N笑嘻嘻道：來了來了，我來了。\n", this_object());
                set("startroom", "/d/city/kedian");
        }

        set_temp("bomb_count", 1);
}

/*
void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
*/

mixed accept_ask(object ob, string topic)
{
        object fob, *obs;

        if( topic == query("id", ob) )
        {
                command("laugh " + topic);
                return 1;
        }

        if (topic[0] > 160)
        {
                if( time()-query_temp("ask_youxun_time", ob)<2 )
                {
                        tell_object(ob, HIY "遊訊朝你一瞪眼睛：『別吵！問問題是吧？問那麼急幹嘛？』\n" NOR);
                        return 1;
                }

                set_temp("ask_youxun_time", time(), ob);
                obs = livings();
                obs -= users();
                obs = filter_array(obs, (: remove_ansi($1->name(1)) == $2 && environment($1) :), topic);
                if (sizeof(obs) > 4)
                {
                        obs = 0;
                        message_vision(CYN "$N" CYN "憤聲暗罵，對$n"
                                CYN "瞪著眼睛道：『叫" + topic + "的人滿大街都是，"
                                "自己不會找？』\n" NOR, this_object(), ob);
                        return 1;
                } else
                if (sizeof(obs) > 0)
                {
                        obs = 0;
                        set_temp("pending/ask_youxun", topic, ob);
                        /*
                        message_vision(CYN "$N" CYN "嘿嘿姦笑兩聲，對$n"
                                CYN "小聲道：『沒有問題，不過得要一兩黃"
                                "金，不二價！』\n" NOR, this_object(), ob);
                        */
                        tell_object(ob, CYN "遊訊嘿嘿姦笑兩聲，對你"
                                        CYN "小聲道：『沒有問題，不過得要一兩黃"
                                        "金，不二價！』\n" NOR);
                        return 1;
                } else
                        return;
        }

        fob = find_player(topic);
        if (! fob || ! ob->visible(fob)) fob = find_living(topic);
        if (! fob || ! ob->visible(fob) || ! environment(fob))
                return;

        set_temp("pending/ask_youxun", topic, ob);
        /*
        message_vision(CYN "$N" CYN "嘿嘿姦笑兩聲，對$n"
                       CYN "小聲道：“沒有問題，不過得要10兩"
                       "白銀，不二價！”\n" NOR, this_object(), ob);
        */
        tell_object(ob, CYN "遊訊嘿嘿姦笑兩聲，對你"
                        CYN "小聲道：“沒有問題，不過得要10兩"
                        "白銀，不二價！”\n" NOR);
        return 1;
}

int recognize_apprentice(object me, string skill)
{
        if (skill != "idle-force")
        {
                if( me->add_temp("illegal_learn",1)>3 )
                {
                        command("say 滾！你煩不煩？！");
                        message_vision("$n一腳把$N踢出門外！\n",
                                       me, this_object());
                        set_temp("illegal_learn", 2, me);
                        me->move("/d/city/beidajie1");
                        me->unconcious();
                } else
                        command("say 我只教發呆神功，不傳其它武功！");
                return -1;
        }

        message_vision("$N向$n請教發呆神功的訣竅。\n", me, this_object());

        if( query_temp("learned_idle_force", me) )
        {
                if( me->add_temp("too_many_xue",1)>3 )
                {
                        command("say 你好羅嗦！！！");
                        message_vision("$n飛起一腳把$N踢出門外！\n",
                                       me, this_object());
                        set_temp("too_many_xue", 1, me);
                        me->move("/d/city/beidajie1");
                        me->unconcious();
                } else
                        command("say 你先把我剛才教你的領悟好再說吧！");
                return -1;
        }

        command("say 聽好了！發呆神功宗旨：!@#$%^&");

        if( query("potential", me)<query("learned_points", me)+10 )
        {
                write("你聽得稀裡糊塗，看來是潛能不夠了。\n");
                return -1;
        }

        if (me->query_skill("idle-force", 1) > 2100)
        {
                write("你聽完了心想，這些我都懂啊，看來遊訊也就知道這麼多了。\n");
                return -1;
        }

        set_temp("learned_idle_force", 1, me);
        addn("learned_points", 10, me);
        write(HIG "你聽了心中頗有所得，馬上進行發呆練習！\n" NOR);
        return -1;
}

void append_receiver(object ob)
{
        if (! receiver)
                receiver = ({ ob });
        else
                if (member_array(ob, receiver) == -1)
                        receiver += ({ ob });
}

int accept_object(object me, object ob)
{
        string wid;

        if (clonep(this_object()))
        {
                command("hehe");
                command("say 我是真遊訊，如假包換啊！");
                return 1;
        }

        if (ob->id("visible bomb"))
        {
                command("say 不要了？那就還給我吧。");
                return 1;
        }

        if( !stringp(query("money_id", ob)) )
        {
                switch(query_temp("youxun_refused", me) )
                {
                case 0:
                        command("heihei");
                        command("say 這種破爛你留著吧。");
                        set_temp("youxun_refused", 1, me);
                        return 0;

                case 1:
                        message_vision("$N飛起一腳，把$n踢了出去，罵道：搗什麼亂？\n",
                                       this_object(), me);
                        break;

                case 2:
                        message_vision("$N飛起一腳，狠狠的把$n踢了出去，罵道：還來搗亂？\n",
                                       this_object(), me);
                        me->receive_damage("qi", 100);
                        me->receive_wound("qi", 10);
                        break;

                default:
                        message_vision("$N大怒，一招萬佛朝宗，就見$n像紙片一樣飛了出去。\n",
                                       this_object(), me);
                        command("chat* heng "+query("id", me));
                        me->unconcious();
                        break;
                }

                addn_temp("youxun_refused", 1, me);
                me->move("/d/city/beidajie1");
                message_vision("只聽“啪”的一聲，$N狠狠的摔在了地上。\n", me);
                return -1;
        }

        if (ob->value() < 500)
        {
                message_vision("$N接過$n遞過去的" + ob->name() +
                               "，皺了皺眉，道：就這點錢？算了，你不要就給我吧！\n",
                               this_object(), me);
                destruct(ob);
                return 1;
        }

        delete_temp("youxun_refused", me);
        if( stringp(wid=query_temp("pending/ask_youxun", me)) )
        {
                int    i;
                string msg;
                object fob, *obs;

                if (ob->value() < 1000 ||
                    (ob->value() < 10000 && wid[0] > 160))
                {
                        message_vision("$N冷笑一聲道：“就這點錢？"
                                       "你還是打發魯有腳還差不多。”\n",
                                       this_object());
                        return 0;
                }

                delete_temp("pending/ask_youxun", me);

                if (wid[0] > 160)
                {
                        obs = livings();
                        obs -= users();
                        obs = filter_array(obs, (: remove_ansi($1->name(1)) == $2 && environment($1) :) ,wid);
                        if (! sizeof(obs))
                        {
                                message_vision("$N撓撓頭對$n道：“怪事... 剛"
                                               "才我還有他的消息呢，怎麼這麼一會兒...”\n",
                                               this_object(), me);
                                return 0;
                        }
                        msg = " \n據可靠消息，叫" + wid + "的一共有" +
                              chinese_number(sizeof(obs)) + "個人！\n";
                        for (i = 0; i < sizeof(obs); i++)
                                msg+=obs[i]->name(1)+"("+query("id", obs[i])+")"+
                                       "剛才在" + environment(obs[i])->short() + "。\n";
                        destruct(ob);
                        obs = 0;
                        //command("whisper " + me->query("id") + msg);
                        tell_object(me, WHT"遊訊在你的耳邊悄聲說道：" + msg + "\n" NOR); 
                        return 1;
                }

                fob = find_player(wid);
                if (! fob || ! me->visible(fob)) fob = find_living(wid);
                if (! fob || ! me->visible(fob) || ! environment(fob))
                {
                        message_vision("$N撓撓頭對$n道：“怪事... 剛"
                                       "才我還有他的消息呢，怎麼這麼一會兒...”\n",
                                       this_object(), me);
                        return 0;
                }

                destruct(ob);
                /*
                command("whisper"+query("id", me)+
                        " 據可靠消息，這個人剛才在" +
                        environment(fob)->short() + "。");
                */
                tell_object(me, WHT "遊訊在你的耳邊悄聲說道：據可靠消息，這個人剛才在" +
                        environment(fob)->short() + "。\n" NOR);
                return 1;
        }

        if( query_temp("receive_rumor_time", me)<time() )
                set_temp("receive_rumor_time", time(), me);
        addn_temp("receive_rumor_time", ob->value()/3000*60, me);
        message_vision("$N樂得合不攏嘴，連忙接過" + ob->name() +
                       "，點頭哈腰的對$n道：好！好！\n", this_object(), me);
        command("tell "+query("id", me)+
                sprintf(" 要是 %d 分鐘內有人造謠，我一定揭穿他的老底。",
                        (query_temp("receive_rumor_time", me)-time())/60));
        destruct(ob);
        append_receiver(me);
        return 1;
}

int ask_fee()
{
        int n;
        object me;

        me = this_player();
        if( query_temp("receive_rumor_time", me)<time() )
        {
                command("say 不貴不貴，三十兩銀子包管一分鐘！");
                return 1;
        }

        n=query_temp("receive_rumor_time", me)-time();
        n /= 60;
        if (! n)
        {
                command("tell "+query("id", me)+
                        " 馬上到時間啦，再想聽消息，快點拿錢來啊！");
        } else
        {
        command("tell "+query("id", me)+
                        sprintf(" 你還能聽 %d 分鐘的消息。", n));
        }

        message("visoin", name() + "嘀嘀咕咕的對" + me->name() +
                          "說了一些話。\n", environment(me), ({ me }));
        return 1;
}

int ask_bomb()
{
        object ob;
        object me;
        int n;

        me = this_player();
        if (wizardp(me))
        {
                if (! objectp(ob = present("bomb", this_object())))
                        ob = new("/clone/gift/xianxing");
                command("say 等等，小的這就給你。");
                ob->move(me, 1);
                return 1;
        }

        n=(query_temp("receive_rumor_time", me))-time();
        if (n < 0) n = 0;
        n /= 60;
        if (! n)
        {
                command("shake");
                command("say 你問我這個幹嘛？我不認識你。");
                return 1;
        }

        if (! (ob = present("visible bomb", this_object())) &&
           query_temp("bomb_count") <= 0)
        {
                command("say 可惜，我倒是想給你，可是手頭沒有啦！");
                return 1;
        }

        if (! ob) catch(ob = new("/clone/gift/xianxing"));

        if (! ob)
        {
                command("say 我的炸彈受潮... 給不了你了！");
                return 1;
        }

        command("heihei");
        command("say 看在你照顧我生意的面子上，我就給你一顆炸彈！");
        if (! environment(ob)) ob->move(this_object());
        command("give bomb to "+query("id", me));
        addn_temp("bomb_count", -1);
        remove_call_out("restore_bomb");
        call_out("restore_bomb", 150);
        return 1;
}

private void restore_bomb()
{
        set_temp("bomb_count", 1);
}

void receive_report(object user, string verb)
{
        string msg;

        msg = sprintf("聽說%s(%s)又要發謠言了。",
                      query("name", user),query("id", user));
        if (random(100) < 7)
        {
                command("heihei");
                command("say " + msg);
        }

        if (! receiver)
                return;

        receiver = filter_array(receiver, (: filter_listener :));
        if (! sizeof(receiver))
        {
                receiver = 0;
                return 0;
        }

        message("vision", HIG "遊訊悄悄的告訴你：" + msg + "\n",
                receiver, user);
}

private int filter_listener(object ob)
{
        if (! objectp(ob))
                return 0;

        if (present("rumor generator", ob))
                return 1;

        if( query_temp("receive_rumor_time", ob)>time() )
                return 1;

        delete_temp("receive_rumor_time", ob);
        return 0;
}

int ask_duwan()
{
        object me;
        object ob;

        me = this_player();
        if (! wizardp(me) || wiz_level(me) < 2)
        {
                command("say 你... 你要毒藥幹什麼？下毒可是犯法的！");
                return 1;
        }

        command("consider");
        command("shzi");
        catch(ob = new("/clone/misc/duwan"));
        if (! ob)
        {
                command("say 毒丸出了點問題，我暫時拿不出來了。");
                return 1;
        }
        ob->move(this_object());
        command("give "+query("id", ob)+" to "+query("id", me));
        command("say 這可是丁老怪做的，千萬別我給漏了出去！");
        return 1;
}

int ask_shedu()
{
        object me;
        object ob;

        me = this_player();
        if (! wizardp(me) || wiz_level(me) < 2)
        {
                command("say 你... 你要毒藥幹什麼？下毒可是犯法的！");
                return 1;
        }

        command("heihei");
        command("shzi");
        catch(ob = new("/clone/misc/shedu"));
        if (! ob)
        {
                command("say 蛇毒出了點問題，我暫時拿不出來。");
                return 1;
        }
        ob->move(this_object());
        command("give "+query("id", ob)+" to "+query("id", me));
        command("say 這可是歐陽瘋子弄的，可別說是我給你的啊！");
        return 1;
}

int ask_list()
{
        object me;

        me = this_player();
        if( query_temp("can_buy/youxun/nuclues-bomb", me) )
        {
                command("say 你咋這麼羅嗦？好話不說二遍...");
                return 1;
        }
        command("shzi");
        command("whisper "+query("id", me)+
                " 我身上有不少好東西，便宜得很！核彈才五萬兩黃金一個！");
        set_temp("can_buy/youxun/nuclues-bomb", 1, me);
        return 1;
}

int do_list(string arg)
{
        if (arg && ! id(arg))
                return notify_fail("這裡沒有這個人。\n");

        if( query_temp("can_buy/youxun", this_player()) )
        {
                command("shzi");
                return ::do_list();
        }

        message_vision("$N兩手忙擺，對$n道：“我只賣消息不賣貨，嘿嘿。”\n",
                       this_object(), this_player());
        return 1;
}

int do_buy(string arg)
{
        object me;
        string my_id;

        if (arg && sscanf(arg, "%s from %s", arg, my_id) == 2 && ! id(my_id))
                return notify_fail("這裡沒有這個人。\n");

        me = this_player();
        if( !query_temp("can_buy/youxun", me) )
        {
                message_vision("$N急得雙手亂擺，對$n道：“我說過了不賣"
                               "東西的，我可是老實人！”\n",
                               this_object(), this_player());
                return 1;
        }

        return ::do_buy(arg);
}
