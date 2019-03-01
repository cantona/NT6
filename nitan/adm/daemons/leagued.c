// leagued.c

#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

// 同盟聲望最大是10億
#define MAX_LEAGUE_FAME         1000000000

// 每個同盟最多有100個仇人
#define MAX_HATRED_PERSON       100

// 當仇人超過的時候每次移除多少個
#define HATREDP_REMOVED         10

mapping league_fame;
mapping last_league_fame;

// 同盟對仇人仇恨度的排序
private int sort_hatred(string id1, string id2, mapping hatred);

void create()
{
        seteuid(getuid());
        restore();
        set_heart_beat(1800 + random(30));
        if (! mapp(league_fame)) league_fame = ([ ]);
}

void remove()
{
        save();
}

public void mud_shutdown()
{
        save();
}

// 心跳：維護同盟的通常信息
private void heart_beat()
{
        int t;
        int last;
        string *all_fam;
        string fam;

        t = time();
        last = query("last_check");
        if ((t / 86400) != (last / 86400))
        {
                // 天數發生了變化：復制同盟的名望信息
                all_fam = keys(league_fame) - ({ 0 });
                last_league_fame = ([ ]);

                foreach (fam in all_fam)
                        last_league_fame[fam] = league_fame[fam];
        }
        set("last_check", t);

        // 保存同盟的最新信息
        save();
}

// 返回同盟聲望：如果參數為空，返回mapping類型，包含了所有同
// 盟的聲望；如果參數是人物， 則返回該人物所在的那個同盟的聲
// 望；如果參數是同盟，則返回該同盟的聲望。
public mixed query_league_fame(mixed ob)
{
        string fname;

        if (stringp(ob))
                return league_fame[ob];

        if (objectp(ob))
        {
                if( stringp(fname=query("league/league_name", ob)) )
                        return league_fame[fname];
                else
                        return 0;
        }

        return league_fame;
}

// 查詢昨天的同盟名望信息
public mapping query_all_last_league_fame()
{
        if (! mapp(last_league_fame))
                // 沒有昨天的信息，返回今天的
                return league_fame;

        // 返回昨天的同盟聲望信息
        return last_league_fame;
}

// 查詢同盟的仇恨信息：輸入的ob可以是同盟的名字，也可是同盟
// 中的人物。
public mapping query_league_hatred(mixed ob)
{
        mapping hatred;
        string fname;

        if (objectp(ob))
                fname=query("league/league_name", ob);
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! mapp(hatred = query(fname + "/hatred")))
                return 0;

        return hatred;
}

// 變化同盟聲望：輸入的ob可以是同盟的名字，也可是同盟中的人
// 物。
public void add_league_fame(mixed ob, int n)
{
        int new_fame;
        string fname;

        if (objectp(ob))
                fname=query("league/league_name", ob);
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || undefinedp(query(fname + "/member")))
                return;

        // 計算新的同盟聲望
        new_fame = league_fame[fname] + n;
        if (new_fame < 0) new_fame = 0;
        if (new_fame > MAX_LEAGUE_FAME)
                new_fame = MAX_LEAGUE_FAME;
        league_fame[fname] = new_fame;
}

// 同盟間仇殺
public void league_kill(object killer, object victim)
{
        int kexp;
        int vexp;
        string vfam;
        string kfam;
        string kid;
        int fame_delta;
        mapping hatred;
        mixed *d;

        // 只有玩家之間的仇殺才計算在內
        if (! objectp(killer) || ! playerp(killer) ||
            ! objectp(victim) || ! playerp(victim))
                return;

        // 巫師之間的比劃可不能算數
        if (wizardp(killer) || wizardp(victim))
                return;

        // 查看這兩個玩家所處的結義同盟
        kfam=query("league/league_name", killer);
        vfam=query("league/league_name", victim);

        if (killer->is_brother(victim) && killer->is_killing(query("id",victim))) 
                // 殺死結拜兄弟，威望降低10%
                addn("weiwang", -query("weiwang", killer)/10, killer);

        if (! stringp(kfam) && ! stringp(vfam))
                // 都不在同盟內，不必繼續了
                return;

        kexp=query("combat_exp", killer);
        vexp=query("combat_exp", victim);

        if (kfam == vfam)
        {
                if( !killer->is_killing(query("id", victim)) )
                        // 失手所殺，不予理會
                        return;

                // 兄弟間殘殺？不與理會，直接扣除聯盟和個人1/10威望。
                add_league_fame(kfam, -league_fame[kfam] / 10);
                addn("weiwang", -query("weiwang", killer)/10, killer);
                return;
        }

        if (kexp < vexp * 3 && vexp >= 100000)
        {
                // 殺手的經驗不是遠遠的大于對方，並且被殺的
                // 人有一定的經驗，這將導致同盟聲望的降低。
                fame_delta=vexp+query("score", killer)*2+
                             query("weiwang", killer)*10;
                fame_delta /= 1000;
        } else
                // 對手經驗太少，或是差距太大，不影響聲望
                fame_delta = 0;

        // 查看殺手所在的同盟是否仇恨死者：如果仇恨，則能夠
        // 帶動聲望的變化。
        if (stringp(kfam))
        {
                string path;

                path=kfam+"/hatred/"+query("id", victim);
                d = query(path);
                if (arrayp(d) && sizeof(d) >= 2 && intp(d[1]))
                {
                        // 仇恨死者，同盟獲得額外的聲望
                        if (d[1] > 2000)
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                        "聽說" + killer->name(1) + "擊斃了" +
                                        victim->name(1) + "，為" +
                                        kfam + "出了一口惡氣。");
                        fame_delta += d[1] / 3;

                        // 對此人的仇恨降低(降低的要比增加的要多)，
                        // 具體可以看fame_delta 與仇恨度公司的差異
                        d[1] -= fame_delta;
                        if (d[1] <= 0)
                                delete(path);
                        else
                                set(path, d);
                }
        }

        // 調整兩個同盟的聲望
        add_league_fame(killer,  fame_delta);
        add_league_fame(victim, -fame_delta);

        // 統計該殺手對本門的殘害程度
        if (! stringp(vfam))
                return;

        // 仇恨程度和聲望的變化都是在一個數量級上(K經驗)，但
        // 是仇恨程度低于聲望的變化。
        vexp = vexp / 1000 + 1;
        if (vexp > 5000)
                vexp = (vexp - 5000) / 16 + 2000;
        else
        if (vexp > 1000)
                vexp = (vexp - 1000) / 4 + 1000;

        kid=query("id", killer);
        if (! mapp(hatred = query(vfam + "/hatred")))
        {
                set(vfam + "/hatred/" + kid,
                    ({ killer->name(), vexp }));
                return;
        }

        // 每個同盟最多記錄若幹個仇人
        if (! undefinedp(d = hatred[kid]))
        {
                if (! arrayp(d) || sizeof(d) < 2 ||
                    ! intp(d[1]) || ! stringp(d[0]))
                {
                        // 這個ID的數據出了故障
                        d = 0;
                }
        } else
        if (sizeof(hatred) >= MAX_HATRED_PERSON)
        {
                string *ids;
                int i;

                // 過濾去掉一些人，為什麼不去掉一個？這是為
                // 了防止過濾頻繁的進行過濾操作。
                ids = sort_array(keys(hatred),
                                 (: sort_hatred :), hatred);
                for (i = 0; i < sizeof(ids) && i < HATREDP_REMOVED; i++)
                        map_delete(hatred, ids[i]);
        }

        if (! arrayp(d))
                d = ({ killer->name(1), vexp });
        else
        {
                d[0] = killer->name(1);
                d[1] += vexp;
        }

        // 記錄這個人的信息
        hatred[kid] = d;
}

// 去掉所有同盟對某個人的仇恨信息
public void remove_hatred(string id)
{
        mapping dbase, league, hatred;
        string fam;

        if (! mapp(dbase = query_entire_dbase()))
                // 現在還沒有仇恨信息
                return;

        // 查閱所有的同盟
        foreach (fam in keys(dbase))
        {
                reset_eval_cost();

                if (! mapp(league = dbase[fam]))
                        continue;

                if (mapp(hatred = league["hatred"]))
                        // 去掉該同盟對某人的仇恨信息
                        map_delete(hatred, id);

                if (! mapp(hatred) || sizeof(hatred) < 1)
                        // 這個同盟已經沒有仇恨信息
                        map_delete(league, "hatred");
        }

        save();
}

// 查看是否可以創建這個同盟
public mixed valid_new_league(string fname)
{
        if (query(fname + "/member"))
                return "人家早就有叫這個的啦，你就別湊熱鬧了。\n";

        if (! undefinedp(FAMILY_D->query_family_fame(fname)))
                return "江湖賞已經有" + fname + "了，你還想做什麼？\n";

        return 0;
}

// 創建同盟
public void create_league(string fname, int base, object *obs)
{
        mapping league;
        object ob;

        league_fame[fname] = base;
        if (! mapp(last_league_fame))
                last_league_fame = ([ fname : base ]);
        else
                last_league_fame[fname] = base;

        set(fname, ([ "member" : obs->query_id(0),
                      "time"   : time() ]));
        save();

        foreach (ob in obs)
        {
                league = ([ "time" : time(),
                            "league_name" : fname ]);
                set("league", league, ob);
                ob->save();
        }
}

// 解散同盟
public void dismiss_league(string fname)
{
        string *ids;
        string id;

        // 清除名望信息
        map_delete(league_fame, fname);
        if (mapp(last_league_fame)) map_delete(last_league_fame, fname);

        // 清除同盟中的所有玩家的相關信息
        ids = query(fname + "/member");

        if (arrayp(ids))
        {
                // 同盟中還有玩家，清除他們的信息
                foreach (id in ids)
                {
                        // 處理中
                        reset_eval_cost();
                        UPDATE_D->clear_user_data(id, "league");
                }
        }

        // 清除同盟的所有信息
        delete(fname);
}

// 查詢同盟中的弟兄
public string *query_members(mixed ob)
{
        string *member;
        string fname;

        if (objectp(ob))
                fname=query("league/league_name", ob);
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! arrayp(member = query(fname + "/member")))
                return 0;

        return member;
}

// 從同盟中去掉一個人
public varargs void remove_member_from_league(mixed fname, string id)
{
        mapping league;
        string *member;

        if (objectp(fname))
        {
                // fname is user object
                id=query("id", fname);
                if( !stringp(fname=query("league/league_name", fname)) )
                        return;
        } else
        if (! stringp(fname))
                // or fname must be a league name
                return;

        if (! mapp(league = query(fname)) ||
            ! arrayp(member = league["member"]))
                // no such league or no member in the league
                return 0;

        member -= ({ id, 0 });
        if (sizeof(member) < 1)
        {
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "聽說" + fname + "人才凋零，昔日好友盡皆散去，從此江湖再無此字號了。");

                // 清除名望信息
                map_delete(league_fame, fname);
                if (mapp(last_league_fame)) map_delete(last_league_fame, fname);

                // 清除同盟的信息
                delete(fname);
        } else
                league["member"] = member;
}

// 在同盟中增加一個人
public void add_member_into_league(string fname, string id)
{
        string *member;

        if (! arrayp(member = query(fname + "/member")))
                return 0;

        if (member_array(id, member) != -1)
                return 0;

        member += ({ id });
        set(fname + "/member", member);
}

// 排序：升序
private int sort_hatred(string id1, string id2, mapping hatred)
{
        mixed *d1, *d2;

        if (! arrayp(d1 = hatred[id1]) || sizeof(d1) < 2 || ! intp(d1[1]))
                return -1;

        if (! arrayp(d2 = hatred[id2]) || sizeof(d2) < 2 || ! intp(d2[1]))
                return 1;

        return d1[1] - d2[1];
}

public string query_save_file() { return DATA_DIR "leagued"; }
