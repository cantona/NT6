// shutong.c 書童

#include <ansi.h>

inherit NPC;

string ask_job();
int  do_copy(string arg);
int  working(object me);
int  halt_working(object me);

void create()
{
        set_name("書童", ({ "shu tong", "tong" }));
        set("long", "這是朱先生身邊的小書童，看上去年紀還小。\n");
        set("gender", "男性");
        set("age", 15);
        set("no_get", 1);
        set_skill("literate", 50);

        set("combat_exp", 1000);
        set("inquiry", ([
                "買書" : "還是找朱先生吧！我這裡可不管。",
                "工作" : (: ask_job :),
                "抄書" : (: ask_job :),
                "job"  : (: ask_job :),
                "書"   : "先生那裡書多得很。",
                "借書" : "借？我可沒有書借給你呀！",
        ]));

        setup();
}

void init()
{
        add_action("do_copy", "copy");
}

int accept_object(object who, object ob)
{
        command("say 先生說了，無功不受祿！我不能要你的東西。");
        return 0;
}

string ask_job()
{
        object me;
        object *obs;

        me = this_player();
        if( query_temp("job/copy", me) )
                return "讓你抄的書你抄完了？";

        if( query("combat_exp", me)<1200 )
                return "雖然在這裡只是抄抄書，可是你經驗"
                       "太差，遇到流氓搗亂可不好！";

        if( query("combat_exp", me)>8000 )
                return "大俠你還是別抄書了，我可不敢勞您大架。";

        if( query("qi", me)<20 )
                return "我看你臉色不行啊，先歇會兒吧，我可不想抄書抄出人命來。";

        if( query("jing", me)<10 )
                return "我看你精神不行啊，能抄得了書麼？";

        if (me->query_int() < 25 && me->query_skill("literate", 1) < 20)
                return "您好像稍稍有那麼一點點不太聰明呀！";

        if (! interactive(me))
                return "...";

        obs = filter_array(all_inventory(environment()),
                           (: interactive($1) &&
                              $1 != $(me) &&
                              query_temp("job/copy", $1) && 
                              query_ip_number($1) == query_ip_number($(me)) :));
        if (sizeof(obs) > 0)
                return "我這已經有" + obs[0]->name() + "在幹活了，你等等吧。";

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
                message_vision("$N摸起毛筆，剛想蘸墨，就聽見$n喊道："
                               "拜托拜托，千萬別動文房四寶，我要收拾呢。\n",
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
                object ob;
                msg += "$n看了$N抄寫的書，滿意道：“真好！比我"
                       "強多了。諾，這是先生給你的報酬！你可以\n"
                       "在先生那裡學點文化。”\n";
                delete_temp("job/copy", me);
                delete_temp("job/step", me);

                b = 5 + random(4);
                addn_temp("mark/朱", 20, me);
                addn("combat_exp", b, me);
                me->improve_potential((b + 2) / 3);

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
                if (b > 0)
                {
                        tell_object(me, HIC "\n你獲得了" +
                                    chinese_number(b) +
                                    "點經驗和" +
                                    chinese_number((b + 2) / 3) +
                                    "點潛能。\n\n" NOR);
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