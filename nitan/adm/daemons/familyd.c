// familyd.c 保存所有的門派信息

#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

// 門派聲望最大是10億
#define MAX_FAMILY_FAME         1000000000

// 每個門派最多有100個仇人
#define MAX_HATRED_PERSON       100

// 當仇人超過的時候每次移除多少個
#define HATREDP_REMOVED         10

mapping family_fame = ([
        "少林寺"   : 10000000,
        "武當派"   : 8000000,
        "丐幫"     : 7000000,
        "全真教"   : 5000000,
        "華山派"   : 4500000,
        "段氏皇族" : 4000000,
        "慕容世家" : 4000000,
        "雪山寺"   : 3500000,
        "靈鷲宮"   : 3500000,
        "峨嵋派"   : 3000000,
        "桃花島"   : 2500000,
        "神龍教"   : 2000000,
        "古墓派"   : 1500000,
        "星宿派"   : 1200000,
        "逍遙派"   : 1000000,
        "血刀門"   : 800000,
        "華山劍宗" : 600000,
        "歐陽世家" : 500000,
        "關外胡家" : 400000,
]);

// 門派ID對應的門派名字
nosave mapping family_name = ([
        "shaolin"  : "少林寺",
        "wudang"   : "武當派",
        "gaibang"  : "丐幫",
        "quanzhen" : "全真教",
        "huashan"  : "華山派",
        "duan"     : "段氏皇族",
        "murong"   : "慕容世家",
        "xueshan"  : "雪山寺",
        "lingjiu"  : "靈鷲宮",
        "emei"     : "峨嵋派",
        "taohua"   : "桃花島",
        "shenlong" : "神龍教",
        "gumu"     : "古墓派",
        "xingxiu"  : "星宿派",
        "xiaoyao"  : "逍遙派",
        "xuedao"   : "血刀門",
        "jianzong" : "華山劍宗",
        "ouyang"   : "歐陽世家",
        "hu"       : "關外胡家",
]);

mapping last_family_fame;

// 門派對仇人仇恨度的排序
private int sort_hatred(string id1, string id2, mapping hatred);

void create()
{
        seteuid(getuid());
        restore();
        set_heart_beat(1800);
}

void remove()
{
        save();
}

public void mud_shutdown()
{
        save();
}

// 心跳：維護門派的通常信息
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
                // 天數發生了變化：複製門派的名望信息
                all_fam = keys(family_fame) - ({ 0 });
                last_family_fame = family_fame;
                family_fame = ([ ]);

                foreach (fam in all_fam)
                        family_fame[fam] = last_family_fame[fam];
        }
        set("last_check", t);

        // 保存門派的最新信息
        save();
}

// 返回門派聲望：如果參數為空，返回mapping類型，包含了所有門
// 派的聲望；如果參數是人物， 則返回該人物所在的那個門派的聲
// 望；如果參數是門派，則返回該門派的聲望。
public mixed query_family_fame(mixed ob)
{
        string fname;

        if (stringp(ob))
                return family_fame[ob];

        if (objectp(ob))
        {
                if( stringp(fname=query("family/family_name", ob)) )
                        return family_fame[fname];
                else
                        return 0;
        }

        return family_fame;
}

// 查詢昨天的門派名望信息
public mapping query_all_last_family_fame()
{
        if (! mapp(last_family_fame))
                // 沒有昨天的信息，返回今天的
                return family_fame;

        // 返回昨天的門派聲望信息
        return last_family_fame;
}

// 查詢門派的仇恨信息：輸入的ob可以是門派的名字，也可是門派
// 中的人物。
public mapping query_family_hatred(mixed ob)
{
        mapping hatred;
        string fname;

        if (objectp(ob))
                fname=query("family/family_name", ob);
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || ! mapp(hatred = query("hatred/" + fname)))
                return 0;

        return hatred;
}

// 變化門派聲望：輸入的ob可以是門派的名字，也可是門派中的人
// 物。
public void add_family_fame(mixed ob, int n)
{
        int new_fame;
        string fname;

        if (objectp(ob))
                fname=query("family/family_name", ob);
        else
        if (stringp(ob))
                fname = ob;
        else
                fname = 0;

        if (! stringp(fname) || undefinedp(family_fame[fname]))
                return;

        // 計算新的門派聲望
        new_fame = family_fame[fname] + n;
        if (new_fame < 0) new_fame = 0;
        if (new_fame > MAX_FAMILY_FAME)
                new_fame = MAX_FAMILY_FAME;
        family_fame[fname] = new_fame;
}

// 門派間仇殺
public void family_kill(object killer, object victim)
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

        kexp=query("combat_exp", killer);
        vexp=query("combat_exp", victim);
        kfam=query("family/family_name", killer);
        vfam=query("family/family_name", victim);

        if (stringp(kfam) && kfam == vfam)
        {
                // 同門殘殺？
                return;
        }

        if (kexp < vexp * 3 && vexp >= 100000)
        {
                // 殺手的經驗不是遠遠的大於對方，並且被殺的
                // 人有一定的經驗，這將導致門派聲望的降低。
                fame_delta = vexp + query("score", killer) * 2 +
                             query("weiwang", killer)*10;
                fame_delta /= 1000;
        } else
                // 對手經驗太少，或是差距太大，不影響聲望
                fame_delta = 0;

        // 查看殺手所在的門派是否仇恨死者：如果仇恨，則能夠
        // 帶動聲望的變化。
        if (stringp(kfam))
        {
                string path;

                path = "hatred/" + kfam + "/" + query("id", victim);
                d = query(path);
                if (arrayp(d) && sizeof(d) >= 2 && intp(d[1]))
                {
                        // 仇恨死者，門派獲得額外的聲望
                        if (d[1] > 2000)
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                        "聽説" + killer->name(1) + "擊斃了" +
                                        victim->name(1) + "，為" +
                                        kfam + "討回了公道。");
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

        // 調整兩個門派的聲望
        add_family_fame(killer,  fame_delta);
        add_family_fame(victim, -fame_delta);

        // 統計該殺手對本門的殘害程度
        if (! stringp(vfam))
                return;

        // 仇恨程度和聲望的變化都是在一個數量級上(K經驗)，但
        // 是仇恨程度低於聲望的變化。
        vexp = vexp / 1000 + 1;
        if (vexp > 5000)
                vexp = (vexp - 5000) / 16 + 2000;
        else
        if (vexp > 1000)
                vexp = (vexp - 1000) / 4 + 1000;

        kid=query("id", killer);
        if (! mapp(hatred = query("hatred/" + vfam)))
        {
                set("hatred/" + vfam + "/" + kid,
                    ({ killer->name(), vexp }));
                return;
        }

        // 每個門派最多記錄若干個仇人
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

// 去掉所有門派對某個人的仇恨信息
public void remove_hatred(string id)
{
        mapping all_hatred, hatred;
        string fam;

        if (! mapp(all_hatred = query("hatred")))
                // 現在還沒有仇恨信息
                return;

        // 查閲所有的門派
        foreach (fam in keys(all_hatred))
        {
                if (mapp(hatred = all_hatred[fam]))
                        // 去掉該門派對某人的仇恨信息
                        map_delete(hatred, id);

                if (! mapp(hatred) || ! sizeof(hatred))
                        // 這個門派已經沒有仇恨信息
                        map_delete(all_hatred, fam);
        }
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

public string query_family_name(string fid)
{
        string fam;

        if (undefinedp(fam = family_name[fid]))
                fam = fid;
        return fam;
}

public mapping query_all_family_name()
{
        return family_name;
}

// 外部調用高效練功
int query_family_efficient(string fname, string arg)
{
        if( !fname ) return 0;
        return query(fname + "/efficient/" + arg);
}

void set_family_efficient(string fname, string arg, int time)
{
        set(fname + "/efficient/" + arg, time()+time);
        SCHEDULE_D->set_event(time, 0, this_object(), "remove_family_efficient", fname, arg);
}

void remove_family_efficient(string fname, string arg)
{
        delete(fname + "/efficient/" + arg);
        save();
}

public string query_save_file() { return DATA_DIR "familyd"; }
