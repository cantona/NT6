// zhang.c 張天師

#include <ansi.h>

inherit KNOWER;

int ask_me();

void create()
{
        set_name("張天師", ({ "zhang tianshi", "zhang" }));
        set("age", 57);
        set("gender", "男性");
        set("long", "這是一位仙風神骨，道貌岸然的法師。\n");
        set("attitude", "peaceful");

        set("str", 28);
        set("int", 35);
        set("con", 38);
        set("dex", 31);

        set("max_qi", 8000);
        set("max_jing", 8000);
        set("max_neili", 8000);

        set_skill("magic", 200);
        set_skill("taoism", 350);

        set("chat_chance_combat", 3);
        set("chat_msg_combat", ({
                "張天師搖搖鈴鐺，道：天靈靈，地零零，太上老君還不顯靈？\n",
                "張天師呼呼的吹了幾口氣。\n",
        }));

        set("inquiry", ([
                "開光" : (: ask_me :),
                "沒錢" : "沒錢就去賺，跟我説什麼。",
                "窮"   : "看你也是一副窮命。",
                "魔法" : "魔法？什麼玩藝？",
                "法術" : "法術還分很多種呢，道術、妖術、仙術不一而足。",
                "道術" : "道術？這可是本源正宗！",
                "妖術" : "妖術啊，趨於下乘，不足為提。",
                "仙術" : "仙術只好算是中乘，還是不能和道術相比。",
                "浸入" : "你要是不行我可以幫你看看(show)浸入需要用什麼物品。",
        ]));

        setup();
        carry_object("/clone/cloth/dao-cloth")->wear();
}

void init()
{
        add_action("do_show", "show");
        add_action("do_summon", "summon");
}

int ask_me()
{
        command("heihei");
        command("say 我只給神兵利器開光，尋常刀劍莫提！要"
                "你本人的，我可不能幫你做壞事！");
        tell_object(this_player(), GRN "張天師在你耳邊悄悄説："
                    "你把要開光的拿出來給我看看(show)！\n" NOR);
        return 1;
}

int do_summon(string arg)
{
        if (! wizardp(this_player()))
        {
                command("say 你在我面前瞎抓個什麼勁？別地試去！");
                return 1;
        }

        return 0;
}

int do_show(string arg)
{
        object money;
        object ob, imbue_ob;
        object me;
        int n;

        if (! arg)
                return notify_fail("你要亮出什麼東西？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上沒有這種東西。\n");

        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的裝備再説！\n");

        message_vision("$n拿出一"+query("unit", ob)+ob->name()+
                       "對$N説：“拜託拜託...”\n",
                       this_object(), me);

        if( query("money_id", ob) )
        {
                command("say 你亮出錢幹什麼？想獻給觀裏？那就給我好了。");
                return 1;
        }

        if( !query_temp("paid/張天師", me) )
        {
                command("heihei");
                command("say 這...怎麼也的有點意思意思吧？你"
                        "説十兩黃金怎麼樣？當然多些我也不反對。");
                return 1;
        }

        if( stringp(query("magic/imbue_ob", ob)) )
        {
                imbue_ob=new(query("magic/imbue_ob", ob));
                if (! objectp(imbue_ob))
                {
                       command("say 你的物件有點問題，得和巫師聯繫！");
                       return 1;
                }
                tell_object(me, HIG "張天師悄悄對你説道：“恩...我看看，應該用" +
                            imbue_ob->name() + HIG "浸入它才能進一步激發它的潛力。”\n");
                delete_temp("paid/張天師", me);
                destruct(imbue_ob);
                return 1;
        }

        if( mapp(query("magic/imbue_ok", ob)) )
        {
                command("say 哦！我看它現在已經不需要在浸入了，"
                        "要發揮潛力得用別的法子了。\n");
                return 1;
        }

        if (! ob->is_item_make())
        {
                command("heng");
                command("say 這...這...我看還是算了吧！");
                return 1;
        }

        if( ob->item_owner() != query("id", me) )
        {
                command("kick"+query("id", me));
                command("say 你以為本山人的仙術是矇事的啊，這分明不是你的！");
                return 1;
        }

        if( query("can_summon/"+query("id", ob), me) )
        {
                if (ob->weapon_level() > 1)
                {
                        command("poor"+query("id", me));
                        command("say 它現在還不到浸入的時候..."
                                "你要先聖化它才行啊！");
                } else
                {
                        command("kok"+query("id", me));
                        command("say 你和它已經有緣了！我説你的"
                                "記性怎麼這麼差？");
                }
                return 1;
        }

        message("vision", sort_string(HIM + name() + "從口袋中摸出一張黃色"
                                "的符紙，抽出背後的桃木劍，"
                                "將那符紙點燃了，掃過" + ob->name() + HIM "，然"
                                "後用桃木劍穿了，手舞足蹈，口中唸唸有詞："
                                "“太上老君急急如律賜令！”説罷一抖掌中劍，"
                                "喝道：“疾”！\n" NOR, 64), environment());
        message_vision("焰光劃出一道光華，$N發了發呆，也不知道算是怎麼回事。\n",
                       me);
        command("say 行了，行了！你可以走了。");
        delete_temp("paid/張天師", me);
        set("can_summon/"+query("id", ob), base_name(ob), me);
        log_file("static/item", sprintf("%s %s sancitfy %s(%s)\n",
                        log_time(), log_id(me),
                        filter_color(ob->name(1)),query("id", ob)));
        return 1;
}

int accept_object(object who, object ob)
{
        if( !query("money_id", ob) )
        {
                command("say 這玩藝我可沒啥興趣！");
                return 0;
        }

        if (ob->value() < 50000)
        {
                command("say 算是給觀裏的香火麼？那我就收下了！");
                return 1;
        }

        if (ob->value() < 100000)
        {
                command("say 唉！看你也算有點心意，我就替你開一次光吧！");
                set_temp("paid/張天師", 1, who);
                destruct(ob);
                return 1;
        }

        command("say 好...好...這麼照顧本觀，我能幫你點什麼？");
        set_temp("paid/張天師", 1, who);
        destruct(ob);
        return 1;
}

void fight_ob(object ob)
{
        ::fight_ob(ob);
        message_vision("$N冷笑一聲，道：“這年頭，什麼人都有。”説完伸手一指$n。\n",
                       this_object(), ob);
        ob->unconcious();
}

int accept_fight(object who)
{
        command("say 沒興趣。");
        return 0;
}

int accept_ansuan(object who)
{
        return notify_fail("你剛想暗算，可是眼前一花，看不太清楚。\n");
}

void receive_damage(string type, int n)
{
        return;
}

void receive_wound(string type, int n)
{
        return;
}
