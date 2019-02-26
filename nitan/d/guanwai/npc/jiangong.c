// jiangong 監工

#include <ansi.h>

inherit NPC;

mixed ask_mine();
mixed ask_transit();
int   do_mine(string arg);
int   working(object me);
int   halt_working(object me);

void create()
{
        set_name("監工", ({ "jian gong", "jiangong" }));
        set("long", "這是一個監工，眼光不斷閃爍，不知"
                    "道在打什麼壞主意\n");
        set("gender", "男性");
        set("age", 38);
        set("no_get", 1);
        set_skill("unarmed", 100);

        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);

        set("combat_exp", 500000);
        set("shen_type", 1);
        set("inquiry", ([
                "job"  : "你是想採礦(mine)啊，還是運貨(transit)？",
                "工作" : "你是想採礦(mine)啊，還是運貨(transit)？",
                "採礦" : (: ask_mine :),
                "mine" : (: ask_mine :),
                "運貨" : (: ask_transit :),
                "transit" : (: ask_transit :),
        ]));
        setup();

        set("chat_chance", 1);
        set("chat_msg", ({
                "監工喝道：快！快給我幹！\n",
                "監工一揚鞭子，罵道：他奶奶的，你給我放老實點。\n",
                "監工打量着四周，不知道在打什麼主意。 \n",
                "監工狠狠的抽了一個人幾下，罵道：怎麼把石頭掉到地上了，你這笨蛋。\n",
        }));
}

void init()
{
        add_action("do_mine", "move");
        add_action("do_mine", "mine");
}

mixed ask_mine()
{
        object me;
        object *obs;

        me = this_player();
        if( query_temp("job/move", me) )
                return "讓你搬的石料你搬了沒有？再胡鬧我抽死你！";

        if( query("combat_exp", me)<50000 )
                return "你這點經驗也來採石場混？隨便一大哥看你不順眼就把你放到了。";

        if( query("combat_exp", me)>300000 )
                return "大俠你也來搬石頭？免了免了，我還是另找人吧！";

        if( query("qi", me)<60 )
                return "我看你上氣不接下氣了嘛，還是算了吧，我可不想鬧出人命來。";

        if (me->query_str() < 25)
                return "我説你有多點力氣，也來湊熱鬧？";

        if (! interactive(me))
                return "...";

        obs = filter_array(all_inventory(environment()),
                           (: interactive($1) &&
                              $1 != $(me) &&
                              query_temp("job/move", $1) && 
                              query_ip_number($1) == query_ip_number($(me)) :));
        if (sizeof(obs) > 0)
                return "現在已經有" + obs[0]->name() + "幹活呢，你歇着吧。";

        set_temp("job/move", 1, me);
        return "好，你就去山上搬石料下來(move)，我這工資可不菲哦。";
}

int do_mine(string arg)
{
        object me;

        me = this_player();
        if (me->is_busy())
                return notify_fail("你正忙着呢，彆着急。\n");

        if( !query_temp("job/move", me) )
                return notify_fail("你又沒領活，瞎忙活啥？\n");

        set_temp("job/step", 1, me);
        me->start_busy(bind((: call_other, __FILE__, "working" :), me),
                       bind((: call_other, __FILE__, "halt_working" :), me));
        tell_object(me, "你開始工作。\n");
        return 1;
}

int working(object me)
{
        string msg;
        int finish;
        int b;

        if( !query_temp("job/step", me) )
                set_temp("job/step", 1, me);

        if (! living(me))
        {
                delete_temp("job/move", me);
                delete_temp("job/step", me);
                return 0;
        }

        finish = 0;
        switch(query_temp("job/step", me) )
        {
        case 1:
                me->receive_damage("qi", 1);
                msg = "$N快步的朝山上走去。";
                break;
        case 2:
                me->receive_damage("qi", 1);
                msg = "$N走到山腰，道：我是來搬石料的。";
                break;
        case 3:
                me->receive_damage("qi", 1);
                msg = "來往的工人掃了$N一眼，似乎沒看到。一個爆破手道：嗨，那兒，去那兒搬。";
                break;
        case 4:
                me->receive_damage("qi", 6);
                msg = "$N趕到爆破的地方，選了一塊正合適自己的石料，抗在肩頭。";
                break;
        case 5:
        case 7:
        case 9:
                me->receive_damage("qi", 8);
                msg = "$N扛着石料，一步一步往山下挨。";
                break;
        case 6:
                me->receive_damage("qi", 9);
                msg = "$N喘了口氣，掂了掂肩頭的石料，繼續前進。";
                break;
        case 8:
                me->receive_damage("qi", 10);
                msg = "$N覺得肩頭的石料越來越重，只好換一下肩扛。";
                break;
        default:
                me->receive_damage("qi", 5);
                msg = "$N把石料扛到$n那裏，把石料裝上車子，總算鬆了口氣。";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                object ob;
                if (me->query_str() >= 30)
                        msg += "$n看了$N搬的石料，訝道：厲害"
                               "啊，這麼大塊石料也搬下來了！\n";
                else
                        msg += "$n看了$N搬的石料，道：行，幹得"
                               "不賴！喏，這是你的工錢。\n";
                delete_temp("job/move", me);
                delete_temp("job/step", me);

                // 本地石料增多
                environment(me)->improve_product_amount("stone",
                                                        15 + (me->query_str() - 30) * 4 + random(8));

                b = 70 + random(40);
                GIFT_D->delay_work_bonus(me, ([ "exp" : b, "pot" : b / 3 ]));
                me->improve_skill("unarmed", (b + 1) / 2);

                ob = new("/clone/money/coin");
                ob->set_amount(100 + (me->query_str() - 25) * 10);
                ob->move(me, 1);
        }

        msg = replace_string(msg, "$N", "你");
        msg = replace_string(msg, "$n", name());
        tell_object(me, msg);
        if (finish)
        {
                return 0;
        }

        addn_temp("job/step", 1, me);
        return 1;
}

int halt_working(object me)
{
        if( query_temp("job/step", me) >= 4 )
        {
                message_vision("$N把肩頭的石料一仍，罵罵咧咧道："
                               "累死我了，真不是人乾的活！\n", me);
        } else
        {
                message_vision("$N歎了口氣，道：今天不幹了！\n", me);
        }

        delete_temp("job/move", me);
        delete_temp("job/step", me);
        return 1;
}

mixed ask_transit()
{
        string startroom;
        int c;
        object ob;
        object me;
        int amount;

        if (! stringp(startroom = query("startroom")) ||
            find_object(startroom) != environment())
                // not in start room
                return "我...我有點頭暈...";

        me = this_player();

        if( query("score", me)<1000 )
                return "你這人閲歷這些淺，也敢接這差使？";

        if( query("combat_exp", me)<30000 )
                return "一邊兒去！你這人本事太差，我可不放心讓你押貨！";

        if( objectp(query_temp("job/gw_cart", me)) )
                return "上次讓你送的你完事了麼？快去！別羅嗦！";

        if( (amount=query("job/gw_stone", me))>0 )
        {
                amount = (amount + 99) / 20;
                // 五天(MUD時間)內如果貨物還沒有送達，則不能領
                message_sort("$N冷笑一聲，對$n道：“" + me->name(1) +
                             "，上次你送的石料... 哼！你本事"
                             "低微，這次我不多加追究了，可是"
                             "那一車石料豈能就這樣白白的丟了"
                             "？你先賠了" + chinese_number(amount) +
                             "兩白銀再説！”\n",
                             this_object(), me);
                return 1;
        }

        c = environment(me)->query_product_amount("stone");
        if (c < 800)
                return "現在還沒有多少石料呢，不忙運走，你等等吧。";
        else
        if (c < 1200)
                message_vision("$N看了看$n，道：“也好，雖然"
                               "現在還不多，不過也差不多了。”\n",
                               this_object(), me);
        else
        if (c < 2000)
                message_vision("$N點點頭，對$n道：“好吧，就"
                               "快滿一車了，就發了吧。”\n",
                               this_object(), me);
        if (c < 10000)
                message_vision("$N看到$n，招呼道：“正好，正"
                               "打算髮車呢，就你來吧！”\n",
                               this_object(), me);
        else
        if (c < 30000)
                message_vision("$N連忙道：“快準備吧，這裏已"
                               "經有好幾車了！”\n",
                               this_object(), me);
        else
                message_vision("$N看到$n，大喜道：“正好！眼"
                               "看這庫裏就要滿了，你來的正好！”\n",
                               this_object(), me);

        if (c > 3000) c = 3000;
        environment(me)->improve_product_amount("stone", -c);

        // 生成交通工具
        ob = new("/clone/misc/cart");
        set_temp("goods/name", "石料", ob);
        set_temp("goods/id", "stone", ob);
        set_temp("goods/unit", "斤", ob);
        set_temp("goods/amount", c, ob);
        message_sort("$N吆喝兩聲，叫人推過一"+query("unit", ob)+
                     ob->name() + "來，回頭對" + me->name() +
                     "道：“來！你把這車貨物送到長安工部石廠去，"
                     "你別把石頭不當錢，丟了一樣要你的命！”\n",
                     this_object(), me);
        tell_object(me,YEL+name()+"交給你一"+query("unit", ob)+
                        ob->name() + "。\n" NOR);
        ob->move(environment(me));
        ob->set_owner(me);

        // 記錄這次任務的信息
        set("job/gw_stone", c, me);
        set_temp("job/gw_cart", ob, me);
        set_temp("job/info", "gw_stone", ob);
        set_temp("job/owner", me, ob);

        return 1;
}

int accept_object(object who, object ob)
{
        int amount;

        if( !query("money_id", ob) )
                return 0;

        if( (amount=query("job/gw_stone", who))>0 )
        {
                amount = (amount + 99) / 20;
                if (ob->value() < amount * 100)
                {
                        message_vision("$N看了看$n遞過來的錢，大喝"
                                       "道：“就這點？一邊兒去！”\n",
                                       this_object(), who);
                        return 0;
                }

                message_vision("$N鼻子哼了一聲，接過" + ob->name() +
                               "，道：“算了，就不追究你了。”\n",
                               this_object(), who);
                delete("job/gw_stone", who);
        } else
        {
                message_vision("$N眉開眼笑，把" + ob->name() +
                               "接了過來，收入包囊，卻不理會$n。\n",
                               this_object(), who);
        }

        destruct(ob);
        return -1;
}
