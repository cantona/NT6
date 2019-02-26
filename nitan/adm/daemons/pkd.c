// 增加獲取積分，積分可兑換物品，及可以到特殊地點或接受傳承等
// pkd.c

#include <ansi.h>
#include <localtime.h>

inherit F_DBASE;

#define ENTRY_ROOM      "/d/pk/entry"
#define READY_ROOM      "/d/pk/ready"
#define PK_ROOM         "/d/pk/turen"

// the state of daemon
nosave int state;

#define SLEEPING        0
#define GET_READY       1
#define STARTING        2

#define GET_READY_TIME  180

nosave object *total = ({ });
nosave int ready_time = 0;

// 四次比賽列表
nosave mapping *tlist = ({
([      "name" : "屠人熱身賽",
        "time" : ({ 2200, 2210, }),
        "exp"  : ({ 1000, 300000 }),
        "last_day" : 0,
]),
([      "name" : "屠人準備賽",
        "time" : ({ 400, 410, }),
        "exp"  : ({ 1000, 600000 }),
        "last_day" : 0,
]),
([      "name" : "屠人選拔賽",
        "time" : ({ 1000, 1010, }),
        "exp"  : ({ 1000, 2000000 }),
        "last_day" : 0,
]),
([      "name" : "屠人大賽",
        "time" : ({ 1600, 1610 }),
        "exp"  : ({ 1000, 2000000000 }),
        "last_day" : 0,
])
});

nosave int selected;

private void change_state(int new_state);
private void init_player(object me);
private int  start_competition();
private void message_competition(string msg);
private void auto_check();
private void give_bouns(object me);
private void kickout_players();
private void restore_status(object me);
private void send_invite_message();

// 外部可調用的函數
int check_out(object me);

// return the time of prompt
int is_pking()              { return state == STARTING; }
int is_ready()              { return state == GET_READY; }

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "比賽精靈");
        //write("比賽精靈已經啟動。\n");
        state = SLEEPING;
        set_heart_beat(30);
}

int clean_up()
{
        return 1;
}

// join in competition
int join_competition(object ob)
{
        mapping cnd;

        if (state != SLEEPING)
                return notify_fail("現在屠人場正在舉行活動，你還是等等再説吧。\n");

        if( query("combat_exp", ob)<800000 )
                return notify_fail("你這點本事就別進去啦。\n");

        if (mapp(cnd = ob->query_condition()) && sizeof(cnd))
        {
                if (! undefinedp(cnd["hunger"]))
                        return notify_fail("你還是先找點吃的東西再説吧。\n");

                if (! undefinedp(cnd["killer"]))
                        return notify_fail("官府正在通緝你，你還敢在這兒拋頭露面？\n");

                if (! undefinedp(cnd["bandage"]))
                        return notify_fail("你還是等包紮的傷口止住了血再説吧！\n");

                if (! undefinedp(cnd["putizi_drug"]))
                        return notify_fail("你剛服完菩提子不久，好好運功夫吸納吧！\n");

                if (! undefinedp(cnd["vote_clear"]))
                        return notify_fail("現在玩家正在對你進行表決，你別到處亂走。\n");

                return notify_fail("你現在狀態不佳，還是別進去了。\n");
        }

        if (! arrayp(total))
                total = ({ ob });
        else
        if (member_array(ob, total) == -1)
                total += ({ ob });

        message_competition((ultrap(ob) ? "大宗師" : "") +
                            ob->name(1) + "進入屠人場。");

        init_player(ob);
        set_heart_beat(1);
        return 1;
}

// scan
private void heart_beat()
{
        mixed lt;
        int ti;
        int i;
        int last_day;

        seteuid(ROOT_UID);
        lt = localtime(time());
        ti = lt[LT_HOUR] * 100 + lt[LT_MIN];

        switch (state)
        {
        case SLEEPING:
                last_day = time() / 86400;
                for (i = 0; i < sizeof(tlist); i++)
                {
                        if (ti < tlist[i]["time"][0] || ti > tlist[i]["time"][1])
                                // not change state
                                continue;
                        if (last_day == tlist[i]["last_day"])
                                // this day has do it
                                break;
                        tlist[i]["last_day"] = last_day;
                        selected = i;

                        // chanage state to "GET_READY";
                        change_state(GET_READY);
                        break;
                }
                break;

        case GET_READY:
                if (time() < ready_time + GET_READY_TIME)
                        break;

                // change state to "GET_READY_2";
                change_state(STARTING);
                break;

        case STARTING:
                break;
        }

        if (sizeof(total))
                auto_check();
}

// the daemon change to a new state
private void change_state(int new_state)
{
        mixed lt;
        int n;

        lt = localtime(time());
        switch (new_state)
        {
        case GET_READY:
                // kickout the player now in competition
                kickout_players();

                ready_time = time();
                message_competition("聽説一年一度的" + tlist[selected]["name"] + "馬上就要"
                                    "舉行了，不知道今年的冠軍是誰？");
                set_heart_beat(1);
                send_invite_message();
                break;

        case STARTING:
                if (! (n = start_competition()))
                {
                        message_competition("聽説今年的" + tlist[selected]["name"] + "因故"
                                            "取消了，真是沒勁。");
                        new_state = SLEEPING;
                } else
                {
                        message_competition("聽説今年的" + tlist[selected]["name"] +
                                            "吸引了" + chinese_number(n) +
                                            "名高手！走...看看熱鬧去。");
                        set_heart_beat(1);
                }
                break;

        default:
                total = ({ });
                break;
        }

        // change to new state
        state = new_state;
        if (state == SLEEPING)
                set_heart_beat(30);
        return;
}

// set player's override functions
private void init_player(object me)
{
        tell_object(me, HIY "你眼前忽然一花...\n" NOR);
        me->set_override("unconcious", (: call_other, __FILE__, "check_out" :));
        me->set_override("die", (: call_other, __FILE__, "check_out" :));
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        set_temp("backup/killer", me->query_killer(), me);
        set_temp("backup/want", me->query_want(), me);
        set_temp("in_pkd", 1, me);

        me->move(sprintf(PK_ROOM "%d", random(12) + 1));
        tell_object(me, HIY "你定神一看，這才發現自己已經到了" +
                            environment(me)->short() + HIY "。\n");
        set("backup/condition", me->query_condition(), me);
        me->clear_condition();
}

// kickout the players in competition when formal competition
// get ready
private void kickout_players()
{
        object ob;
        string room;
        mapping my;

        if (! arrayp(total))
                return;

        foreach (ob in total)
        {
                if (! objectp(ob))
                        continue;
                room = base_name(environment(ob));
                if (! sscanf(room, PK_ROOM "%*s"))
                        // not in pk room
                        continue;

                my = ob->query_entire_dbase();
                my["eff_qi"] = my["max_qi"];
                my["eff_jing"] = my["max_jing"];
                my["qi"] = 1;
                my["jing"] = 1;

                tell_object(ob, HIC "\n烏老大走了過來，嚷嚷道：“清場了！清場了，都快走吧！”\n" NOR);

                restore_status(ob);
                ob->move(ENTRY_ROOM);
                message("vision", "只見" + ob->name() + "悻悻的走了出來。\n",
                        environment(ob), ({ ob }));
                if (! living(ob))
                        ob->revive();
        }

        total = ({ });
}

// start competition, overide all the player's unconcios/die
// function
private int start_competition()
{
        object env;
        object *obs;
        object shadow;
        int i;

        env = find_object(READY_ROOM);
        if (! objectp(env))
                return 0;

        obs = filter_array(all_inventory(env), (: userp($1) && ! wizardp($1) :));
        if (sizeof(obs) < 2)
                return 0;

        if (sizeof(obs) == 2)
        {
                if( query("couple/couple_id", obs[0]) == query("id", obs[1]) )
                {
                        message_vision("烏老大在外面喊道：“就你們夫妻"
                                       "倆個參加？還是算了吧。”\n", obs[0]);
                        return 0;
                }
        }

        message("vision", "一個黑影走了過來，打開"
                "了門，冷冷道：“都進去吧！”\n", env);

        for (i = 0; i < sizeof(obs); i++)
        {
                reset_eval_cost();
                init_player(obs[i]);
        }

        set_heart_beat(1);
        message("vision", HIG "屠人比賽已經開始，快動手吧！\n", obs);
        return sizeof(total = obs);
}

// send message out
private void message_competition(string msg)
{
        CHANNEL_D->do_channel(this_object(), "rumor", msg);
}

// check all the players who join the competition
private void auto_check()
{
        object ob;
        string msg;
        string room;
        object *lost;
        int i;

        lost = ({ });
        for (i = 0; i < sizeof(total); i++)
        {
                if (! objectp(total[i]))
                        continue;
                room = base_name(environment(total[i]));
                if (! sscanf(room, PK_ROOM "%*s"))
                {
                        // not in pk room
                        restore_status(total[i]);
                        total[i] = 0;
                        continue;
                }
                if( query("qi", total[i])<1 || query("jing", total[i])<1 )
                        lost += ({ total[i] });
        }

        // kickout the players who lost competition
        foreach (ob in lost)
                check_out(ob);

        total -= ({ 0 });
        if (state == SLEEPING)
        {
                if (sizeof(total) < 1)
                        // end of competition. call the change_state
                        // function to restore the normal heart beat.
                        change_state(SLEEPING);

                return;
        }

        if (state != STARTING)
                return;

        if (sizeof(total) < 1)
        {
                msg = "聽説屠人大賽參賽者死的死，逃的逃，現在一個人都沒有啦！";
        } else
        if (sizeof(total) == 1)
        {
                // change the daemon's state
                msg = "聽説本次屠人大賽圓滿結束，" +
                      total[0]->name(1) + "成為屠人冠軍！";
                give_bouns(total[0]);
        } else
        if( sizeof(total) == query("couple/couple_id", 2 && total[0]) == query("id", total[1]) )
        {
                msg = "聽説本次屠人大賽圓滿結束，" +
                      total[0]->name(1) + "和" + total[1]->name(1) +
                      "夫妻雙雙把家還。";
                give_bouns(total[0]);
                give_bouns(total[1]);
        } else
                return;

        message_competition(msg);
        change_state(SLEEPING);
}

private void give_bouns(object me)
{
        int exp;
        int pot;
        int score;
        string msg;

        // lead me out
        restore_status(me);
        tell_object(me, "這次真是爽呆了...\n");
        me->move(ENTRY_ROOM);
        message("vision", me->name() + "慢慢的走了過來，一臉奸笑。\n",
                environment(me), ({ me }));

        // bouns
        pot = me->query_potential_limit();
        pot-=query("potential", me);
        pot = pot / 1000 + 1000;
        exp=query("combat_exp", me)/500+3000;
        score = 100;
        msg = HIG "通過這次大賽，你獲得了 " + (string)exp + " 點經驗";
        if (pot > 0)
        {
                pot = random(pot / 3) + 1;
                msg += "和 " + (string) pot + " 點潛能，";
        } else
        {
                pot = 0;
                msg += "，";
        }
        msg += "以及 " + (string)score + " 點積分。\n" NOR;
        addn("potential", pot, me);
        addn("combat_exp", exp, me);
        addn("top/pk", score, me);
        tell_object(me, msg);
}

// remove overide function
// restore condition
private void restore_status(object me)
{
        mapping my;
        mapping cnd;
        string *ks;
        int i;

        delete_temp("in_pkd", me);
        me->delete_override("unconcious");
        me->delete_override("die");
        me->delete_override("quit");
        me->remove_all_enemy(1);
        me->remove_all_killer();
        me->clear_condition();
        me->receive_damage("qi", 0);
        me->apply_killer(query_temp("backup/killer", me));
        me->apply_want(query_temp("backup/want", me));

        cnd=query("backup/condition", me);
        delete("backup/condition", me);
        delete_temp("block_msg/all", me);
        if (! mapp(cnd)) return;
        ks = keys(cnd);
        for (i = 0; i < sizeof(ks); i++)
                me->apply_condition(ks[i], cnd[ks[i]]);

        my = me->query_entire_dbase();
        if (my["qi"] < 1)       my["qi"] = 1;
        if (my["eff_qi"] < 1)   my["eff_qi"] = 1;
        if (my["jing"] < 1)     my["jing"] = 1;
        if (my["eff_jing"] < 1) my["eff_jing"] = 1;
}

// send invite message
private void send_invite_message()
{
        object *obs;
        int exp_ul, exp_dl;

        exp_dl = tlist[selected]["exp"][0];
        exp_ul = tlist[selected]["exp"][1];
        obs = filter_array(all_interactive(),
                           (: ! wizardp($1) &&
                              query("combat_exp", $1) >= $(exp_dl) &&
                              query("combat_exp", $1) <= $(exp_ul):));
        if (! sizeof(obs))
                return;

        message("vision", HIR "你收到了烏老大撒下的武林盟帖，邀請你參加這次" +
                          tlist[selected]["name"] + "，有沒有興趣去顯顯身手？\n" NOR,
                obs);
}

int start_by_others(int n)
{
        if (state == STARTING)
                return notify_fail("現在比賽正在進行中。\n");

        if (state == GET_READY)
                return notify_fail("現在比賽正在報名中。\n");

        if (n < 0 || n >= sizeof(tlist))
                return notify_fail("沒有這個等級的比賽(0-" +
                                   (sizeof(tlist) - 1) + ")。\n");
        selected = n;
        change_state(GET_READY);
        return 1;
}

object *query_all_competitor()
{
        return total;
}

// overide function of quit
int check_quit(object me)
{
        message_competition("聽説" + me->name(1) +
                            "臨陣脱逃，溜走了。");
        restore_status(me);
        if (arrayp(total))
                total -= ({ me });

        tell_object(me, "你逃出了屠人場。\n");

        // continue run quit function
        me->move(ENTRY_ROOM);
        message("vision", "只見" + me->name() + "慌里慌張的跑了出來。\n",
                environment(me), ({ me }));
        return 1;
}

// overide function of lost(die/unconcious)
int check_out(object me)
{
        object ob;
        mapping my;
        string msg;
        string room;

        room = base_name(environment(me));
        if (! sscanf(room, PK_ROOM "%*s"))
        {
                // not in pk room
                total -= ({ me });
                return 0;
        }

        my = me->query_entire_dbase();
        my["eff_qi"] = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["qi"] = 1;
        my["jing"] = 1;

        tell_object(me, HIR "\n你覺得眼前一陣模糊...這下完了！\n" NOR);
        if (ob = me->query_last_damage_from())
        {
                msg = "聽説" + me->name(1) + "慘遭" + ob->name(1) + "的毒手，被無情淘汰。";
        } else
                msg = "聽説" + me->name(1) + "運氣不佳，本領有限、已經慘遭淘汰。";
        message_competition(msg);

        restore_status(me);
        total -= ({ me });
        me->move(ENTRY_ROOM);
        message("vision", "一個黑影倏的竄了出來，隨即就是“啪”的"
                "一聲，就見" + me->name() +"摔倒了地上，一副半死不"
                "活的樣子。\n", environment(me), ({ me }));
        tell_object(me, "半昏半迷中，你覺得被人拎了起來，又"
                    "重重的摔倒了地上。\n");
        if (! living(me))
                me->revive();
        return 1;
}

// reject_join?
string reject_join(object me)
{
        int exp;

        if (state == STARTING)
                return "現在" + tlist[selected]["name"] + "正在舉行，"
                       "你還是下次再來吧。";

        if (state != GET_READY)
                return "現在沒要舉行比賽啊？你跑來幹什麼？";

        exp=query("combat_exp", me);
        if (exp < tlist[selected]["exp"][0])
                return "你還是算了吧，你這點經驗就別進去現眼了。";

        if (exp > tlist[selected]["exp"][1])
                return "哦...您武功如此高強，這次還是別和小輩們爭了。";

        return 0;
}
