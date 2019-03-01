// zhu.c 朱熹

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

string ask_buy();
string ask_job();
int  do_copy(string arg);
int  working(object me);
int  halt_working(object me);

void create()
{
        set_name("朱熹", ({ "zhu xi", "zhu" }));
        set("long", "朱先生被稱為當世第一大文學家，肚子"
                    "裡的墨水比海還要深。\n");
        set("gender", "男性");
        set("age", 65);
        set("no_get", 1);
        set_skill("literate", 20000);

        set_skill("unarmed", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 400000);
        set("shen_type", 1);
        set("inquiry", ([
                "買書" : (: ask_buy :),
                "工作" : (: ask_job :),
                "抄書" : (: ask_job :),
                "job"  : (: ask_job :),
                "書"   : "唉！書到用時方恨少。",
                "借書" : "借？你不還我到哪裡找你？哼！",
        ]));
        set("vendor_goods", ({
                "/clone/book/lbook1",
                "/clone/book/lbook2",
                "/clone/book/lbook3"
        }));
        setup();

        set("chat_chance", 1);
        set("chat_msg", ({
                "朱熹說道：普天之下，莫非王土；率土之濱，莫非王臣。\n",
                "朱熹說道：出家人，小過損益焉；無妄大過，未濟咸困之。\n",
                "朱熹說道：大學之道，在明明德。在親民，在止于至善。 \n",
                "朱熹說道：格物致知，誠意正心，修身齊家，治國平天下。\n",
        }) );
}

void init()
{
        add_action("do_copy", "copy");
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

int recognize_apprentice(object ob)
{
        if( !query_temp("mark/朱", ob) )
                return 0;
        addn_temp("mark/朱", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        object me = this_player();

        if( !query_temp("mark/朱", who) )
                set_temp("mark/朱", 0, who);

        if( query("money_id", ob) && ob->value() >= 2000 )
        {
                message_vision("朱熹同意指點$N一些讀書寫字的問題。\n", who);
                addn_temp("mark/朱", ob->value()/50, who);
                destruct(ob);
                return 1;
        }

        command("say 看清楚學規，至少要二十兩白銀！");
        return 0;
}

string ask_buy()
{
        return "我這可有不少讀書人必讀的書喲!\n";
}

string ask_job()
{
        object me;
        object *obs;

        me = this_player();
        if( query_temp("job/copy", me) )
                return "讓你抄的書你抄完了？";

        if( query("combat_exp", me)<20000 )
                return "雖然我這裡只是抄抄書，可是你戰鬥經驗這麼差，要"
                       "是有小流氓搗亂你怎麼辦？";

        if( query("combat_exp", me)>100000 )
                return "大俠你也來抄書？真是屈就您了，慢走啊！";

        if( query("qi", me)<20 )
                return "我看你臉色不行啊，先歇會兒吧，我可不想抄書抄出人命來。";

        if( query("jing", me)<10 )
                return "我看你精神不行啊，能抄得了書麼？";

        if (me->query_int() < 25 && me->query_skill("literate", 1) < 20)
                return "我說你腦子這麼笨！也來抄書？";

        if (! interactive(me))
                return "...";

/*
        obs = filter_array(all_inventory(environment()),
                           (: interactive($1) &&
                              $1 != $(me) &&
                              query_temp("job/copy", $1) &&
                              query_ip_number($1) == query_ip_number($(me)) :));
        if (sizeof(obs) > 0)
                return "我這已經有" + obs[0]->name() + "在幹活了，你等等吧。";
*/

        set_temp("job/copy", 1, me);
        return "好，你就幫我抄書(copy)吧！筆墨紙硯在這兒。";
}

int do_copy(string arg)
{
        object me;

        me = this_player();
        if (me->is_busy())
                return notify_fail("你正忙著呢，別著急。\n");

        if( !query_temp("job/copy", me) )
        {
                message_vision("$N摸起毛筆，剛想蘸墨，就聽見$n大喝道："
                               "給我放下，別亂動文房四寶。\n",
                               me, this_object());
                return 1;
        }

        set_temp("job/step", 1, me);
        me->start_busy(bind((: call_other, __FILE__, "working" :), me),
                       bind((: call_other, __FILE__, "halt_working" :), me));
        tell_object(me, "你開始工作。\n");
        return 1;
}

int working(object me)
{
        string msg;
        object ob;
        int finish;
        int b;

        if( !query_temp("job/step", me) )
                set_temp("job/step", 1, me);

        if (! living(me))
        {
                delete_temp("job/copy", me);
                delete_temp("job/step", me);
                return 0;
        }

        finish = 0;
        me->receive_damage("jing", 1);
        me->receive_damage("qi", 2);
        switch(query_temp("job/step", me) )
        {
        case 1:
                msg = "$N拿過硯台，慢慢地研墨。";
                break;
        case 2:
                msg = "$N看看墨磨得差不多了，摸起毛筆，輕輕哈了兩口氣。";
                break;
        case 3:
                msg = "$N飽蘸墨汁，翻開四書，攤開紙張，開始謄寫。";
                break;
        case 4:
        case 6:
                msg = "$N聚精會神的抄寫書籍。";
                break;
        case 5:
                msg = "$N蘸了蘸墨，繼續仔細地抄寫。";
        case 7:
                msg = "$N不斷翻動著書籍，紙張越來越厚。";
                break;
        default:
                msg = "$N把書籍抄好，將紙上墨吹幹，裝訂成冊，遞給$n。";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                msg += "$n看了$N抄寫的書，滿意道：還行，儒子可教！"
                       "這是給你的報酬！你可以在我這裡學點文化。\n";
                delete_temp("job/copy", me);
                delete_temp("job/step", me);

                b = 800 + random(100);
                addn_temp("mark/朱", 20, me);
                GIFT_D->delay_work_bonus(me, ([ "exp" : b, "pot" : b / 3 ]));

                if (me->query_skill("literate", 1) < 100)
                        me->improve_skill("literate", (b + 1) / 2);

                ob = new("/clone/money/coin");
                ob->set_amount(50);
                ob->move(me, 1);
        }

        msg = replace_string(msg, "$N", "你");
        msg = replace_string(msg, "$n", name());
        tell_object(me, msg);

        if (finish)
        {
                if (! query("zhufu_mod/head", me) && random(10) == 1) 
                {
                       message_vision("$n對$N嘿嘿一笑，道：幹得不賴，有點"
                                      "意思，這個神之祝福頭盔就算是我送給你的禮物吧。\n",
                                      me, this_object());
                       ob = new("/clone/goods/zhufu_head"); 
                       ob->move(me, 1); 
                       tell_object(me, HIM "\n你獲得了一個" + ob->name() + HIM "！\n" NOR); 
                       set("zhufu_mod/head", 1, me); 
                }
                return 0;
        }

        addn_temp("job/step", 1, me);
        return 1;
}

int halt_working(object me)
{
        message_vision("$N把手中的筆墨紙硯丟到一旁，牢騷道："
                       "什麼呀，根本就不是人幹的活！\n", me);
        delete_temp("job/copy", me);
        delete_temp("job/step", me);
        return 1;
}
