// jiangong 監工

#include <ansi.h>

inherit NPC;

mixed ask_mine();
mixed ask_transit();
int  do_move(string arg);
int  working(object me);
int  halt_working(object me);

void create()
{
        set_name("監工", ({ "jian gong", "jiangong" }));
        set("long", "這是一個監工，手持長鞭，眼光一眨不眨的"
                    "盯著眾人，口中吆喝個不停。\n");
        set("gender", "男性");
        set("age", 32);
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
                "監工打量著四周，不知道在打什麼主意。 \n",
                "監工狠狠的抽了一個人幾下，罵道：怎麼把礦石掉到地上了，你這笨蛋。\n",
        }));

        carry_object("clone/weapon/changbian")->wield();
}

void init()
{
        add_action("do_mine", "mine");
}

mixed ask_mine()
{
        object me;
        object *obs;

        me = this_player();
        if( query_temp("job/mine", me) )
                return "不是讓你去採麼？你幹完了？少在我面前玩花樣！";

        if( query("combat_exp", me)<80000 )
                return "滾開，就你這點本事，下井被砸死都不知道。";

        if( query("qi", me)<120 )
                return "我看你已經快死了，還是快滾吧！";

        if (me->query_str() < 28)
                return "我說你有多點力氣，也來湊熱鬧？";

        if (! interactive(me))
                return "...";

        obs = filter_array(all_inventory(environment()),
                           (: interactive($1) &&
                              $1 != $(me) &&
                              query_temp("job/mine", $1) && 
                              query_ip_number($1) == query_ip_number($(me)) :));
        if (sizeof(obs) > 0)
                return "現在已經有" + obs[0]->name() + "幹活呢，你歇著吧。";

        set_temp("job/mine", 1, me);
        return "好，你下井去採(mine)些礦石上來，放到那邊的車上，幹了活官府自然會給錢。";
}

int do_mine(string arg)
{
        object me;
        object *obs;

        me = this_player();
        if (me->is_busy())
                return notify_fail("你正忙著呢，別著急。\n");

        if( !query_temp("job/mine", me) )
                return notify_fail("你又沒領活，瞎忙活啥？\n");

        // 查看當時採礦的有多少人
        obs = filter_array(all_inventory(environment(me)),
                           (:userp($1) && query_temp("job/step", $1):));
        if (sizeof(obs) >= 10)
                return notify_fail("現在採礦的人好多，排"
                                   "隊等著下井，你只好先等會兒。\n");

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
        object bonus;

        if( !query_temp("job/step", me) )
                set_temp("job/step", 1, me);

        if (! living(me))
        {
                delete_temp("job/mine", me);
                delete_temp("job/step", me);
                return 0;
        }

        finish = 0;
        switch(query_temp("job/step", me) )
        {
        case 1:
                me->receive_damage("qi", 1);
                msg = "$N快步的朝井上走去。";
                break;
        case 2:
                me->receive_damage("qi", 1);
                msg = "$N走到井口，道：我是來採礦石的。";
                break;
        case 3:
                me->receive_damage("qi", 1);
                msg = "井口幾個人看了看$N，一個人擺了擺手，讓你坐到籃子裡。";
                break;
        case 4:
                me->receive_damage("qi", 1);
                msg = "$N坐在籃中，井口的人開始放繩，只聽吱吱嘎嘎的，你慢慢的向下墜去。";
                break;
        case 5:
                me->receive_damage("qi", 1);
                msg = "$N眼前越來越黑，可是繩子還是放個不停。";
                break;
        case 6:
                me->receive_damage("qi", 1);
                msg = "忽然$N的眼前一亮，原來是一盞油燈，昏暗的火燄不斷的跳動。";
                break;
        case 7:
                me->receive_damage("qi", 1);
                msg = "繩子還是不斷的向下放，漫漫似乎沒有盡頭。";
                break;
        case 8:
                me->receive_damage("qi", 1);
                msg = "籃子忽然停住了，看來是到了地方，$N不禁鬆了一口氣。";
                break;
        case 9:
                me->receive_damage("qi", 3);
                msg = "$N看到有一些人正在努力的幹活，$N連忙趕上去，也拿起鏟子。";
                break;
        case 10:
                me->receive_damage("qi", 6);
                msg = "$N慢慢的收集藍色的礦石，將它們放到籃中。";
                break;
        case 11:
                me->receive_damage("qi", 8);
                msg = "$N覺得分量差不多了，跨進籃中，拉了拉繩子。";
                break;
        case 12:
                me->receive_damage("qi", 1);
                msg = "等了片刻，籃子忽然晃了晃，$N漸漸的向上升了上去。";
                break;
        case 13:
                me->receive_damage("qi", 1);
                msg = "光線越來越亮，終于到了洞口，只見井口幾個人忙得滿頭大汗。";
                break;
        case 14:
                me->receive_damage("qi", 7);
                msg = "$N不及道謝，連忙扛起籃子，奔大車去了。";
                break;
        case 15:
                me->receive_damage("qi", 6);
                msg = "$N趕到大車旁邊，“嘩啦啦”將礦石撒到車中。";
                break;
        default:
                me->receive_damage("qi", 4);
                msg = "$N摸了摸了汗，看看空籃子，總算是幹完一趟了。";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                if (me->query_str() >= 35)
                        msg += "$n看了$N採上來的礦石，點點頭道：很好"
                               "！這一趟弄了不少啊！\n";
                else
                        msg += "$n看了$N搬的石料，道：還行，馬馬虎虎"
                               "吧。走，那邊領工錢去。\n";

                // 本地礦石增多
                environment(me)->improve_product_amount("cuprum_ore",
                                                        10 + (me->query_str() - 28));

                delete_temp("job/mine", me);
                delete_temp("job/step", me);

                if( query("combat_exp", me)<500000 )
                {
                        b = 100 + random(170);
                        GIFT_D->delay_work_bonus(me, ([ "exp" : b, "pot" : b / 3 ]));
                        me->improve_skill("unarmed", (b + 1) / 2);
                }

                bonus = new("/clone/money/coin");
                bonus->set_amount(150 + (me->query_str() - 28) * 10);
        }

        msg = replace_string(msg, "$N", "你");
        msg = replace_string(msg, "$n", name());
        tell_object(me, msg);
        if (finish)
        {
                tell_object(me, "你去管事的那裡領到了工錢。\n");
                bonus->move(me, 1);
                return 0;
        }

        addn_temp("job/step", 1, me);
        return 1;
}

int halt_working(object me)
{
        message_vision("$N搖搖頭，沒說話，只是不幹了。\n", me);
        delete_temp("job/mine", me);
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
                return "我看你這人閱歷太淺啊，可不敢讓你運貨。";

        if( query("combat_exp", me)<150000 )
                return "不行不行，你這人本事太差，路上別把貨都丟了！";

        if( objectp(query_temp("job/hz_cart", me)) )
                return "上次讓你送的你完事了麼？快去！少和我羅嗦！";

        if( (amount=query("job/hz_cuprum_ore", me))>0 )
        {
                amount = (amount + 99) / 100;
                // 五天(MUD時間)內如果貨物還沒有送達，則不能領
                message_sort("$N冷笑一聲，對$n道：“" + me->name(1) +
                             "，上次你送的貨...哼！看在你本事"
                             "低微的份上，我不多加追究了，可"
                             "是那車銅礦石豈能就這樣白白的丟"
                             "了？你先賠了" + chinese_number(amount) +
                             "兩黃金，沖抵銅價再說！”\n",
                             this_object(), me);
                return 1;
        }

        c = environment(me)->query_product_amount("cuprum_ore");
        if (c < 300)
                return "現在還沒有多少礦石呢，不忙運走，你等等吧。";
        else
        if (c < 800)
                message_vision("$N看了看$n，道：“也好，雖然"
                               "現在還不多，不過也差不多了。”\n",
                               this_object(), me);
        else
        if (c < 1000)
                message_vision("$N點點頭，對$n道：“好吧，就"
                               "快滿一車了，就發了吧。”\n",
                               this_object(), me);
        if (c < 3000)
                message_vision("$N看到$n，招呼道：“正好，正"
                               "打算發車呢，就你來吧！”\n",
                               this_object(), me);
        else
        if (c < 8000)
                message_vision("$N連忙道：“快準備吧，這裡已"
                               "經有好幾車了！”\n",
                               this_object(), me);
        else
                message_vision("$N看到$n，大喜道：“正好！眼"
                               "看這庫裡就要滿了，你來的正好！”\n",
                               this_object(), me);

        if (c > 1000) c = 1000;
        environment(me)->improve_product_amount("cuprum_ore", -c);

        // 生成交通工具
        ob = new("/clone/misc/cart");
        set_temp("goods/name", "銅礦石", ob);
        set_temp("goods/id", "cuprum_ore", ob);
        set_temp("goods/unit", "斤", ob);
        set_temp("goods/amount", c, ob);
        message_sort("$N一聲呼喊，叫人推過一"+query("unit", ob)+
                     ob->name() + "來，這才對" + me->name() +
                     "道：“你把這車貨物送到長安工部銅廠去，"
                     "你給我聽好了：這可是朝廷的東西！丟了我"
                     "要你的腦袋！去吧！運到了自有賞格！”\n",
                     this_object(), me);
        tell_object(me,YEL+name()+"交給你一"+query("unit", ob)+
                        ob->name() + "。\n" NOR);
        ob->move(environment(me));
        ob->set_owner(me);

        // 記錄這次任務的信息
        set("job/hz_cuprum_ore", c, me);
        set_temp("job/hz_cart", ob, me);
        set_temp("job/info", "hz_cuprum_ore", ob);
        set_temp("job/owner", me, ob);

        return 1;
}

int accept_object(object who, object ob)
{
        int amount;

        if( !query("money_id", ob) )
                return 0;

        if( (amount=query("job/hz_cuprum_ore", who))>0 )
        {
                amount = (amount + 99) / 100;
                if (ob->value() < amount * 10000)
                {
                        message_vision("$N看了看$n遞過來的錢，大喝"
                                       "道：“就這點？一邊兒去！”\n",
                                       this_object(), who);
                        return 0;
                }

                message_vision("$N鼻子哼了一聲，接過" + ob->name() +
                               "，道：“算了，就不追究你了。”\n",
                               this_object(), who);
                delete("job/hz_cuprum_ore", who);
        } else
        {
                message_vision("$N眉開眼笑，把" + ob->name() +
                               "接了過來，收入包囊，卻不理會$n。\n",
                               this_object(), who);
        }

        destruct(ob);
        return -1;
}
