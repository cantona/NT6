// story:challenge 挑戰

#include <ansi.h>

// 內部函數
string show_time();
mixed  create_challenger();
mixed  master_opinion(int n);
mixed  continue_story(int n);
int    find_respond(object ob);

// 外部可以調用的函數
void   stop_story();
string cannot_respond(object ob);
void   respone_for_challenge(object me);

mixed *story = ({
        (: show_time :),
        "一個神祕的人來到了中原...",
        (: create_challenger :),
        (: master_opinion, 1 :),
        (: master_opinion, 2 :),
        (: master_opinion, 3 :),
        (: master_opinion, 4 :),
});

#define NOT_READY                       0
#define CHALLENGER_IS_WAITING           1
#define NO_USER_CAN_RESPOND             2
#define CHALLENGER_KILLED_BY_ULTRA      3
#define CHALLENGER_IS_TOO_CHEAP         4
#define CHALLENGER_IS_FIGHTING          5

int stop;               // FLAG: 是否需要終止故事
int too_cheap;          // FLAG: 敵人的水平是否太差(相比最高水平玩家而言)
int next;               // continue_story函數根據改值繼續
string accepted;        // 應戰者姓名
object cob;             // 挑戰者
object rob;             // 應戰者
object *ultra ;         // 大宗師

string *too_cheap_msg = ({
        "$N怒道：“誰敢這麼説？你算是什麼人？”",
        "“砰”的一聲，$N被打得飛了出去，眼看是活不成了。",
        "達摩祖師：“罪過！罪過！”",
});

string *fenco = ({
        "王語嫣", "黃蓉", "趙敏", "苗若蘭",
        "袁紫衣", "水笙", "阿珂", "嶽靈珊",
        "霍青桐", "小龍女",
});

string *fenmsg = ({
        "快快快！$C！快快快！",
        "衝啊！$C！衝啊！$C！",
        "$C，加油！$C加油！",
        "$C努力呀！就看你的啦！",
        "$C不要退，往上衝！加油！加油！加油！",
});

string *menco = ({
        "胡斐", "苗人鳳", "狄雲", "段譽",
        "尹志平", "韋小寶", "令狐沖", "陳家洛",
        "楊過", "石破天", "張無忌", "袁承志",
});

string *menmsg = ({
        "$N，不要怕，往上攻！",
        "$N！攻他上身，他拳腳功夫不行！",
        "$N！攻他下三路，他下盤不穩！",
        "$N快攻他正手，他正手反應慢！",
        "$N還不快攻他反手，他反手力道不行！",
});

string prompt() { return HIR "【 挑  戰 】" NOR; }

void create()
{
        seteuid(getuid());
        stop = 0;
        too_cheap = 0;
        accepted = 0;
        cob = 0;
        rob = 0;
        ultra = 0;
}

mixed query_story_message(int step)
{
        if (stop) return 0;
        return step < sizeof(story) ? story[step] :
                                      continue_story(step - sizeof(story));
}

string show_time()
{
        return (random(2)) ? "不知不覺之間，時間到了" + NATURE_D->game_time() + "。"
                           : "歲月如梭，説話間就到了" + NATURE_D->game_time() + "。";
}

mixed create_challenger()
{
        object ob;

        ob = NPC_D->create_challenger();

        if (! ob)
        {
                stop_story();
                return "結果迷路了...";
        }

        ob->move("/d/city/guangchang");
        message("vision", ob->name() + "大搖大擺的走了過來，當街一立！\n",
                          environment(ob));
        CHANNEL_D->do_channel(this_object(), "rumor", "聽説" +
                "從"+query("nation", ob)+"來了一個名叫"+
                ob->name(1) + "的人。");
        next = NOT_READY;
        cob = ob;
        return ob->name() + "：“" + ob->challenge() + "”";
}

mixed master_opinion(int n)
{
        object ob;
        object *u;

        if (n == 1)
                ultra = NPC_D->query_ultra_master();

        ultra -= ({ 0 });
        if (! sizeof(ultra))
                ultra = NPC_D->query_ultra_master();

        if (! cob)
        {
                stop_story();
                return "怎麼人突然吭都不吭一聲就溜走了？";
        }

        ob = ultra[random(sizeof(ultra))];
        ultra -= ({ ob });

        if (n < 4)
        {
                ob->force_me("chat "+query("opinion/msg", cob)[n-1]);
                return 1;
        }

        u = filter_array(all_interactive(), (: find_respond :));
        if (! sizeof(u))
        {
                if (! too_cheap)
                {
                        ob->force_me("chat 可惜啊可惜，現在江湖中竟然"
                                     "無人能收拾此人！");
                        next = NO_USER_CAN_RESPOND;
                        return 1;
                }

                if( query("nation", cob) == "日本" )
                {
                        ob->force_me("chat 哼！哪裏來的日本鬼子？吃" +
                                     RANK_D->query_self(ob) + "一招！");
                        next = CHALLENGER_KILLED_BY_ULTRA;
                        return 1;
                }

                ob->force_me("chat 哈哈！中原能收拾你的人多了！你武功"
                             "太差，不值得讓人出手，滾吧！");
                next = CHALLENGER_IS_TOO_CHEAP;
                return 1;
        }

        if (sizeof(u) < 10)
        {
                ob->force_me("chat* sigh");
                ob->force_me("chat 江湖能收拾此人的固然不少，不過合適"
                             "的確是寥寥無幾。");
        } else
        {
                ob->force_me("chat* heng");
                ob->force_me("chat 這人來找死！能擺平它的人大有人在！");
        }
        message("vision", HIG + ob->name(1) + "告訴你：你何不出手應"
                          "戰(accept)？揚我中華武林威風！\n", u);
        next = CHALLENGER_IS_WAITING;
        return 1;
}

mixed continue_story(int n)
{
        string msg;

        if (! cob)
                return 0;

        switch (next)
        {
        case CHALLENGER_IS_TOO_CHEAP:
                if (n >= sizeof(too_cheap_msg))
                {
                        stop_story();
                        return 0;
                } else
                        return replace_string(too_cheap_msg[n], "$N", cob->name(1));
                return;

        case CHALLENGER_KILLED_BY_ULTRA:
                cob->force_me("chat 八格呀路！");
                CHANNEL_D->do_channel(this_object(), "rumor", "聽説日本"
                        "鬼子" + cob->name(1) + "被打得他媽都認不出他來了。");
                destruct(cob);
                stop_story();
                return 0;

        case NO_USER_CAN_RESPOND:
                cob->force_me("chat* haha");
                stop_story();
                CHANNEL_D->do_channel( this_object(),
                        "rumor","聽説來自"+query("nation", cob)+
                        "的" + cob->name(1) + "在中國居然沒有對手，真是"
                        "中原武林的奇恥大辱！");
                return cob->name(1) + "：“中原武林，不過如此！我去了！”";

        case CHALLENGER_IS_FIGHTING:
                if (! rob || environment(rob) != environment(cob))
                {
                        stop_story();
                        if (rob)
                        {
                                addn("weiwang", -query("weiwang", rob)/10, rob);
                                rob->lost();
                        }
                        CHANNEL_D->do_channel( this_object(),
                        "rumor","聽説"+accepted+"在和"+query("nation", cob)+
                        "" + cob->name(1) + "交手的時候臨陣脱逃，使中原武林蒙羞！");
                        return cob->name(1) + "狂笑不止：“懦夫！中國都是一些懦夫！哈哈！”";
                }

                if (random(3)) return 1;
                if( query("gender", rob) == "男性" )
                        msg = fenco[random(sizeof(fenco))] + "大聲喊道：" +
                              fenmsg[random(sizeof(fenmsg))];
                else
                        msg = menco[random(sizeof(menco))] + "大聲喊道：" +
                              menmsg[random(sizeof(menmsg))];
                msg = replace_string(msg, "$N", rob->name(1));
                msg = replace_string(msg, "$C", RANK_D->query_respect(rob));
                return msg;
        }

        switch (n)
        {
        case 1:
                return cob->name(1) +
                       (random(2) ? "：“怎麼，沒人敢應戰麼？那我就再等等！”"
                                  : "：“嘿嘿，都是一些膽小鬼！”");

        case 3:
                return cob->name(1) +
                       (random(2) ? "似乎等得很不耐煩。"
                                  : "一會兒看看天空，一會兒望望地面，看起來很是悠閒。");

        case 5:
                return cob->name(1) +
                       (random(2) ? "：“怎麼，還有沒人敢應戰麼？真是讓我失望！”"
                                   : "：“説什麼中土武學博大精深，原來都是謠傳。”");

        case 7:
                return cob->name(1) +
                       (random(2) ? "搖搖頭，又歎歎氣，一副不屑的樣子。”"
                                   : "哼了一聲，滿臉盡是不屑。");

        case 9:
                return cob->name(1) +
                       (random(2) ? "：“算了！我看我還是走吧！”"
                                   : "：“我也算是來過了，看來還是不要在這浪費時間了。”");

        case 10:
                return cob->name(1) +
                       (random(2) ? "：“中原武林，全都是一些縮頭烏龜！算了，我走了！”"
                                   : "：“哈哈哈哈！什麼武術？都是一些騙人的東西！我走了！”");

        case 11:
                CHANNEL_D->do_channel(this_object(), "rumor", "聽説來自" +
                        query("nation", cob)+"的"+cob->name(1)+"在中國"
                        "耀武揚威了一番後安然的回國去了，真是恥辱。");
                return 0;
        }

        return 1;
}

void stop_story()
{
        stop = 1;
}

// filter the user can respond for this challenge
int find_respond(object ob)
{
        if( query("combat_exp", ob)>query("combat_exp", cob)*3 )
        {
                too_cheap++;
                return 0;
        }

        if( query("combat_exp", ob) < query("combat_exp", cob) / 2 )
                return 0;

        return 1;
}

// check the user
string cannot_accept(object ob)
{
        if (! cob)
                return "現在還沒有挑戰者！\n";

        if (rob == ob)
                return "你正在應戰呢！\n";

        if (accepted)
                return "這次挑戰已經被" + accepted + "接下了。\n";

        if (next != CHALLENGER_IS_WAITING)
                return "你等會兒，在大宗師面前搶什麼茬兒？\n";

        if( query("combat_exp", ob) < query("combat_exp", cob) * 3 )
                return "挑戰者的水平太低了，你要是出手實在是有失身份！\n";

        if( query("combat_exp", ob) < query("combat_exp", cob) / 2 )
                return "你的武功和挑戰者相比差的太遠，還是不要丟我們中"
                       "國人的臉了！\n";;

        return 0;
}

// accept challenger
void accept_for_challenge(object me)
{
        string fam;

        fam=query("family/family_name", me);
        if (! fam) fam = ""; else fam += "高手";
        me->force_me("chat* heng");
        me->force_me("chat " + cob->name(1) + "少要猖狂，我來了！");
        CHANNEL_D->do_channel(this_object(), "rumor", "聽説" + fam +
                   me->name(1) + "挺身而出，接下了" + cob->name(1) + "的挑戰！");
        rob = me;
        accepted = me->name(1);
        if (environment(cob) != environment(me))
        {
                tell_object(me, HIG "你飛也似的趕到了" + environment(cob)->short() + HIG "。\n");
                message("vision", me->name() + "突然急急忙忙的走了。\n",
                                  environment(me), ({ me }));
                me->move(environment(cob));
                message("vision", me->name() + "急急忙忙的趕了過來。\n",
                                  environment(me), ({ me }));
        }
        next = CHALLENGER_IS_FIGHTING;
        cob->competition_with(me);
}

void remove()
{
        if (cob)
        {
                if (environment(cob))
                {
                        message("vision", cob->name() + "聳聳肩，哈哈大笑，飄然而去。\n",
                                environment(cob));
                }
                destruct(cob);
        }
}
