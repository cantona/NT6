// smith.c

#include <ansi.h>
#include <mine_def.h>

inherit NPC;
inherit F_DEALER;

string ask_me();
int  do_gu(string arg);
int  do_dapi(string arg);
int  do_cuihuo(string arg);
int  do_repair(string arg);
void reward(object me);
protected void rong_he(object, object);
string identify_mine_stone(object who);
protected string *can_epurate = ({
        IRON_MINE,
        IRON_RES_CU,
        IRON_RES_JING,
        BLACK_IRON,
});

// no create_function: inherit by other NPC

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
        add_action("do_look", ({"guankan", "kan"}));
        add_action("do_gu", "gu");
        add_action("do_dapi", "dapi");
        add_action("do_cuihuo", "cuihuo");
        add_action("do_repair", "repair");
        add_action("do_repair", "xiuli");
        add_action("do_epurate", "tilian");     // 提煉、精煉礦
        add_action("do_ronghe", "ronghe");
}

void setup()
{
        set("inquiry/job",    (: ask_me :));
        set("inquiry/工作",   (: ask_me :));
        set("inquiry/repair", "你想要修(repair)點什麼？");
        set("inquiry/修理",   "你想要修(repair)點什麼？");
        set("inquiry/鑑定",   (: identify_mine_stone :));

        ::setup();
}

string ask_me()
{
        object me = this_player();

        if (query("combat_exp", me) > 50000)
                return "讓您老幹這個未免屈尊了吧？";

        if (query("qi", me) < 50)
                return "你還是歇會兒吧！要是出了人命我可承擔不起。";

        if (query_temp("smith/gu", me))
                return "讓你鼓風箱，你怎麼還磨蹭(gu)？";

        if (query_temp("smith/dapi", me))
                return "叫你打的坯你打了沒有(dapi)？";

        if (query_temp("smith/cuihuo", me))
                return "幹活怎麼盡偷懶？快給我淬火去(cuihuo)！";

        switch(random(3))
        {
        case 0:
                set_temp("smith/gu", 1, me);
                return "好！你幫我鼓一會兒風箱(gu)。";

        case 1:
                set_temp("smith/dapi", 1, me);
                return "這樣吧，你幫我打一下坯吧(dapi)！";

        case 2:
                set_temp("smith/cuihuo", 1, me);
                return "去幫我把這些剛出爐的淬一下火(cuihuo)。";
        }
}

int do_gu(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("你現在正忙。\n");

        if (!query_temp("smith/gu", me))
        {
                message_vision("$n剛偷偷的拉起鼓風機，鼓了幾陣風。"
                               "就聽見$N對$n大喝道：滾開，亂搞什麼。\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$n拉起鼓風機拼命鼓了起來，$N看了點了點頭。\n",
                       this_object(), me);
        reward(me);
        return 1;
}

int do_dapi(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("你現在正忙。\n");

        if (!query_temp("smith/dapi", me))
        {
                message_vision("$n拿起幾塊生鐵，在手裏掂了掂。"
                               "就聽見$N對$n大喝道：放下，亂搞什麼。\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$n拿着錘子對剛出爐的火熱的生鐵用力敲打着，"
                        "$N“嗯”了一聲，看上去有些滿意。\n",
                       this_object(), me);
        reward(me);
        return 1;
}

int do_cuihuo(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("你現在正忙。\n");

        if (!query_temp("smith/cuihuo", me))
        {
                message_vision("$n剛抄起一個打造好的坯子，"
                               "就聽見$N對$n大喝道：放下，別給我搞壞了。\n",
                               this_object(), me);
                return 1;
        }

        message_vision("$N用鐵鉗抄起一塊火紅的坯子，伸進了水"
                       "池，“哧”的一聲輕煙四冒。\n",
                       me);
        reward(me);
        return 1;
}

void reward(object me)
{
        int exp, pot;
        object coin;
        object ob;

        delete_temp("smith/gu", me);
        delete_temp("smith/dapi", me);
        delete_temp("smith/cuihuo", me);

        coin = new("/clone/money/silver");
        coin->set_amount(1 + random(2));
        coin->move(this_object());
        message_vision("$N對$n道：這是給你的工錢。\n",
                       this_object(), me);
        command("give coin to " + query("id", me));
        if (! query("zhufu_mod/armor", me) && random(10) == 1)
        {
                ob = new("/clone/goods/zhufu_armor");
                //ob->move(this_object());
                message_vision("$N對$n嘿嘿一笑，道：幹得不賴，有點意思，這個神之祝福護甲就算是我送給你的禮物吧。\n",
                               this_object(), me);
                ob->move(me, 1);
                //command("give zhufu armor to " + query("id", me));
                set("zhufu_mod/armor", 1, me);
        }
        if (query("combat_exp", me) < 10000)
        {
                exp = 200 + random(30);
                pot = exp / 3;
                GIFT_D->work_bonus(me, ([ "exp" : exp, "pot" : pot ]));
        }
        me->receive_damage("qi", 30 + random(20));
        me->start_busy(1);
}

int do_repair(string arg)
{
        object me;
        object ob;
        mixed  msg;
        int consistence;
        int cost;
        int max;
        mapping repair;

        if (! arg)
                return 0;

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上好像沒有這樣東西。\n");

        if (undefinedp(consistence = query("consistence", ob)))
                return notify_fail(ob->name() + "似乎不需要在這裏修理吧？\n");

        if (undefinedp(max = query("max_consistence", ob)))
                max = 100;

        if (consistence == max)
                return notify_fail(ob->name() + "現在完好無損，修理做什麼？\n");

        if (! undefinedp(msg = query("no_repair", ob)))
        {
                if (stringp(msg))
                        write(name() + "道：這我可修理不了。\n");
                else
                        write(name() + "道：" + msg);
                return 1;
        }

        if (mapp(repair = query_temp("pending/repair", me)) &&
            repair["item"] == ob)
        {
                if (me->is_busy())
                        return notify_fail("你現在正忙着呢！\n");

                notify_fail("你先帶夠了錢再説。\n");
                if (MONEY_D->player_pay(me, repair["cost"]) != 1)
                        return 0;

                message_vision("$n把" + ob->name() + "遞給了$N。只見$N"
                               "拿起工具，東敲西補，將" + ob->name() +
                               "好好修了修。\n", this_object(), me);
                set("consistence", max, ob);
                message_vision("$N道：“好了！”隨手把" + ob->name() +
                               "還給了$n，$n看了看，滿意的掏出了一些錢"
                               "付了帳。\n", this_object(), me);
                me->start_busy(1 + random(max - consistence) / 20);
                delete_temp("pending/repair", me);
                return 1;
        }

        cost = (max - consistence) * query("value", ob) / 480;
        if (cost >= 100000) cost = ((cost - 100000) / 2 + 100000) / 10000 * 10000; else
        if (cost >= 10000)  cost = cost / 1000 * 1000; else
        if (cost >= 1000)   cost = cost / 100 * 100; else
        if (cost >= 100)    cost = cost / 10 * 10;

        msg = "$n拿出一" + query("unit", ob) + ob->name() +
              "，$N瞥了一眼，道：“要修好它得要" +
              MONEY_D->price_str(cost) + "才行。”\n";
        if (query("family/family_name", me) == "段氏皇族" &&
            ob->item_owner() == query("id", me))
        {
                cost /= 2;
                msg += "$n道：“呦，是您啊，不好意思，打個五折，就" +
                       MONEY_D->price_str(cost) + "吧！”\n";
        } else
        if (me->query_skill("higgling", 1) >= 30 && cost >= 50)
        {
                cost = cost * 500 / (me->query_skill("higgling", 1) + 500);
                switch (random(5))
                {
                case 0:
                        msg += "$n道：“大哥，看在我常年照顧你生意份上，還不給點折扣？”\n";
                        break;

                case 1:
                        msg += "$n道：“你們大老闆可是我的熟人啊，這個，這個...”\n";
                        break;

                case 2:
                        msg += "$n道：“這位大哥好，您最近生意這麼好... 給點折扣如何？”\n";
                        break;

                case 3:
                        msg += "$n道：“太貴了，我實在沒這麼多了，便宜點，便宜點就好。”\n";
                        break;

                case 4:
                        msg += "$n道：“我急修，這樣吧，下次我一定給足，這次您就行個好，便宜點吧。”\n";
                        break;
                }

                if (cost >= 1000)
                        cost = cost / 100 * 100;
                else
                        cost = cost / 10 * 10;
                msg += "$N聳聳肩道：“算了，算了，那就" +
                       MONEY_D->price_str(cost) +
                      "好了。”\n";
        }

        message_vision(msg, this_object(), me);
        tell_object(me, YEL "如果你的確想修理這件物品，請再輸入一次這條命令。\n" NOR);
        set_temp("pending/repair/item", ob, me);
        set_temp("pending/repair/cost", cost, me);
        return 1;
}

string identify_mine_stone(object who)
{
        object *inv;

        if(!who)
                return 0;

        if(!sizeof(inv = filter_array(all_inventory(who), (: $1->is_mine_stone() && !$1->query_check() :))))
                return "你身上沒有需要鑑定的礦石。\n";

        inv->set_check_flag(1);
        return sprintf("都鑑定好了%s。\n",!random(3)?"，沒什麼值錢的東西":"");
}

int do_epurate(string arg)
{
        object tg, ob, me = this_player();
        string mcs, cmcs;
        int ew, value, rtn;

        if(this_object()->is_busy())
                return notify_fail(sprintf("%s説道：等會兒，正忙着呢。\n", name()));

        if(!arg || !objectp(ob = present(arg, me)))
                return notify_fail("你要提煉什麼？\n");

        if(ob->is_mine_stone())         // 提煉礦石
        {
                if(!ob->query_check())
                        ob->set_check_flag(1);

                if( !(mcs = ob->query_mine_class())
                ||  !(cmcs = MINE_D->chinese_mine_class(mcs))
                ||  (member_array(mcs, can_epurate) == -1) )
                        return notify_fail(sprintf("%s搖搖頭説道：這裏不含任何礦物成份。\n", name()));

                if( (ew = ob->query_eff_weight()) < 1 )
                        return notify_fail(sprintf("%s搖搖頭説道：這裏含的%s太少了，沒法提煉。\n", name(), cmcs));

                if(!objectp(tg = MINE_D->query_mine_class_up_ob(mcs)))
                        return notify_fail(sprintf("%s搖搖頭説道：這塊礦石沒法提煉。\n", name()));

                value = MINE_D->query_mine_class_value(tg->query_mine_class()) * ew * 3 / 10;
                if(value < 1)
                        value = 1;

                if(!(rtn=MONEY_D->player_pay(me,value)) || (rtn == 2))
                {
                        destruct(tg);
                        return notify_fail(sprintf("%s説道：提煉這塊礦石裏的%s需要%s。\n",
                                this_object()->name(), cmcs, MONEY_D->money_str(value)));
                }

                message_vision("$N朝着$n點點頭説道：等一會兒。\n", this_object(), me);

                call_out("epurate_it", 1+random(2), me, ob, tg);
                return 1;
        }

        else if(ob->is_iron_class_res())        // 精煉
        {
                int upq;

                if( !(mcs = ob->query_mine_class())
                ||  !(cmcs = MINE_D->chinese_mine_class(mcs))
                ||  (member_array(mcs, can_epurate) == -1)
                ||  !(upq = MINE_D->query_mine_class_up_quantity(mcs)) )
                        return notify_fail(sprintf("%s搖搖頭説道：這東西沒法再精煉了。\n", this_object()->name()));

                if( (ew = ob->query_weight()/100) < upq )
                        return notify_fail(sprintf("%s搖搖頭説道：對%s精煉至少需要 %d 兩，這塊%s不夠。\n",
                                this_object()->name(),cmcs, upq, cmcs));

                if(!objectp(tg = MINE_D->query_mine_class_up_ob(mcs)))
                        return notify_fail(sprintf("%s搖搖頭説道：我這沒法對%s進行精煉了。\n", this_object()->name(), cmcs));

                ew /= upq;
                value = (MINE_D->query_mine_class_value(tg->query_mine_class()) -
                        MINE_D->query_mine_class_value(mcs)*upq) * ew/2;

                if(value < 10)
                        value = 10;

                if(!(rtn=MONEY_D->player_pay(me,value)) || (rtn == 2))
                {
                        destruct(tg);
                        return notify_fail(sprintf("%s説道：對這塊%s進行精煉需要%s。\n",
                                name(), cmcs, MONEY_D->money_str(value)));
                }

                destruct(ob);
                tg->set_weight(ew*100);
                if(!tg->move(me) && !tg->move(environment()))
                {
                        destruct(tg);
                        return notify_fail("異常超重，向巫師報告吧。\n");
                }

                rong_he(me, tg);
                write(sprintf("%s點點頭説道：好了，拿去吧。\n", name()));
                return 1;
        }

        else
                return notify_fail(sprintf("%s搖搖頭説道：這東西沒法提煉。\n", name()));
}

protected void epurate_it(object me, object ob, object tg)
{
        int ew;

        if(!ob || !me || !tg || (environment(me) != environment()))
        {
                if(tg)
                        destruct(tg);
                return;
        }

        ew = ob->query_eff_weight()*9/10;
        if(ew < 1)
                ew = 1;

        if(ob->query_mine_class() == BLACK_IRON)
                tg->set_sum(ew);
        else
                tg->set_weight(ew*100);

        destruct(ob);
        if(!tg->move(me) && !tg->move(environment()))
                destruct(tg);

        rong_he(me, tg);
        message_vision("$N朝着$n點點頭説道：提煉好了，拿去吧。\n", this_object(), me);
}

int do_ronghe(string arg)
{
        object me = this_player(), ob;

        if(!stringp(arg)
        || !sizeof(arg)
        || !objectp(ob = present(arg, me))
        || !ob->is_iron_class_res() )
                return notify_fail("你要熔合什麼？\n");

        rong_he(me, ob);
        write(sprintf("%s點點頭説道：好了。\n", name()));
        return 1;
}

protected void rong_he(object me, object ob)
{
        object *inv;
        string cms;
        int wt;

        if(!objectp(me)
        || !objectp(ob)
        || !ob->is_iron_class_res()
        || !(cms = ob->query_mine_class()) )
                return;

        if( !sizeof(inv = filter_array(all_inventory(me), (: ($1->is_iron_class_res())
                && ($1->query_mine_class() == $(cms))
                && ($1 != $(ob)) :))) )
                return;

        if(cms == BLACK_IRON)
        {
                foreach(object tmp in inv)
                {
                        wt += tmp->query_sum();
                        destruct(tmp);
                }

                ob->add_sum(wt);
                return;
        }

        foreach(object tmp in inv)
        {
                wt += tmp->query_weight();
                destruct(tmp);
        }

        wt += ob->query_weight();
        ob->set_weight(wt);
}