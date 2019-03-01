// Last Modified by winder on Nov. 17 2000

inherit NPC;

int ask_thd();
int ask_price();
int ask_qihang();

void create()
{
        set_name("船老大", ({ "laoda" , "chuanlaoda" }) );
        set("gender", "男性" );
        set("age", 42);
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "老大");
        set("inquiry", ([
                "name"  : "我就是這裡的老大，他們都叫我小馬哥。",
                "rumors": "聽說以前有一艘紅毛鬼子的船遇難後漂流到這裡，唯一的船員就死在那邊的小店裡。",
                "here"  : "這裡是附近唯一的出海漁港了。",
                "chuhai": "客官您要啟航去哪裡啊？難道是桃花...",
                "出海"  : "客官您要啟航去哪裡啊？難道是桃花...",
                "雇船"  : "客官您要啟航去哪裡啊？難道是桃花...",
                "桃花島": (: ask_thd :),
                "taohuadao": (: ask_thd :),
                "價錢": (: ask_price :),
                "price": (: ask_price :),
                "啟航": (: ask_qihang :),
                "qihang": (: ask_qihang :),
        ]) );
        setup();
}

int ask_thd()
{
        object ob=this_player();

        if( query("thd/x", ob) )
        {
                say("船老大瞪大了眼睛，吃驚地說：客官要去那個鬼地方麼？聽說以前去的人都沒有回來過。\n如果您真的要去的話，這個價錢嘛...\n" );
                if( query("family/family_name", ob) != "桃花島" )
                        set_temp("thd_temp", 1, ob);
                else
                {
                        message_vision("$N大喝一聲：“我就是桃花島弟子，你也敢要錢？！”\n", ob);
                        command("fear"+query("id", ob));
                        message_vision("船老大苦著臉對$N說：“客官息怒，小的這就找船家來。”\n", ob);
                        if (query_temp("busy",get_object("/d/taohua/boat")))
                         {
                                command("say 小船已經出海了，客官您先稍等一會兒。\n");
                                write("您可以隨時要求啟航(qihang)了。\n");
                                set_temp("thd_temp", 3, ob);
                        }
                        else {
                                say("船老大一招手，喊過一個艄公來：載這位客官去桃花島。\n");
                                set_temp("thd_target", "thd", ob);
                                delete_temp("thd_temp", ob);
                                ob->move("/d/taohua/boat");
                        }
                }
        }
        else say("船老大搖搖頭，說道：我們只聽說過桃花島，可誰也不知道在哪裡。\n");
        return 1;
}

int ask_price()
{
        object ob=this_player();
        int money = 30000;

        if( query("age", ob)<16 )
                money=(query("age", ob)-13)*1000;
        if( query_temp("thd_temp", ob) )
        {
                say("船老大似笑非笑地說道：我看客官面善，就收您" + MONEY_D->price_str(money) + "吧。\n" );
                command("hehe laoda");
                set_temp("thd_temp", 2, ob);
        }
        else {
                command("?"+query("id", ob));
                command("dunno"+query("id", ob));
        }
        return 1;
}

int accept_object(object who, object ob)
{
        int money = 30000;

        if( query("age", who)<16 )
                money=(query("age", who)-13)*1000;
        if( query("money_id", ob) && ob->value() >= money){
                if( query_temp("thd_temp", who)<2 )
                        say("船老大樂了，說道：您老是有錢沒處花麼？\n");
                else {
                        if (query_temp("busy",get_object("/d/taohua/boat")))  {
                                command("say 小船已經出海了，客官您先稍等一會兒。\n");
                                write("您可以隨時要求啟航(qihang)了。\n");
                                set_temp("thd_temp", 3, who);
                        }
                        else {
                                command("say 船老大說道：好了您哪。\n");
                                say("船老大一招手，喊過一個艄公來：載這位客官去桃花島。\n");
                                set_temp("thd_target", "thd", who);
                                delete_temp("thd_temp", who);
                                who->move("/d/taohua/boat");
                        }
                }
                return 1;
        }
        return 0;
}

int ask_qihang()
{
        object ob=this_player();

        if( query_temp("thd_temp", ob)<3 )
                say("船老大罵道：幹什麼？！想白坐啊？\n" );
        else {
                if (query_temp("busy",get_object("/d/taohua/boat")))  
                        command("say 小船已經出海了，客官您再等一會兒。\n");
                else {
                        command("say 船老大說道：好了您哪。\n");
                        say("船老大一招手，喊過一個艄公來：載這位客官去桃花島。\n");
                        set_temp("thd_target", "thd", ob);
                        delete_temp("thd_temp", ob);
                        ob->move("/d/taohua/boat");
                }
        }
        return 1;
}

void kill_ob(object ob)
{
        ob->remove_killer(this_object());
        remove_killer(ob);
        message_vision("船老大喝問$N：“在我的地盤你也敢撒野？！”\n", ob);
        message_vision("$N連忙賠笑道：“不敢，不敢。”\n", ob);
}
