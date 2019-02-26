// story:witer 聖沐

#include <ansi.h>

inherit F_CLEAN_UP;

mixed random_gift();

nosave mixed *story = ({
        "紅孩兒：菩薩！大事不好了！唐僧他們又惹禍了。",
        "觀音：哦？他們現在應該在五莊觀，出了什麼事？",
        "紅孩兒：他…他們在五莊觀裏偷吃了鎮元大仙的人蔘果！",
        "觀音：啊！有這等事？真是豈有此理！",
        "紅孩兒：他…他們還掀翻了鎮元大仙的人蔘果樹！",
        "觀音：我不要活啦！你下次彙報工作的時候能否把重要的事情排在前面？",
        "紅孩兒：哦。",
        "觀音：不必擔心，只要我這聖水一落地，枯木也可以回春。",
        "「滴答」",
        (: random_gift :),
});

void create()
{
        seteuid(getuid());
}

string prompt() { return HIR "【神話】" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

mixed random_gift()
{
        object *obs;
        object ob, pob;
        string msg;
        mapping my, ips;
        string ip, *ks;

        ips = ([ ]);
        /*
        obs = filter_array(all_interactive(), (: ! wizardp($1) &&
                                                 environment($1) &&
                                                 query("outdoors", environment($1)) && 
                                                 !query("env/no_story", $1) && 
                                                 !query("doing", $1):));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        */

        foreach (pob in all_interactive())
        {
                if( wizardp(pob) || !query("born", pob) || 
                    ! living(pob) || ! environment(pob) ||
                    !query("outdoors", environment(pob)) || 
                    pob->is_ghost() ||
                    query("env/no_story", pob) || 
                    query("doing", pob) || 
                    environment(pob)->is_chat_room())
                        continue;

                ip = query_ip_number(pob);
                if (undefinedp(ips[ip])) ips[ip] = ({ pob }); else ips[ip] += ({ pob });
        }

        if (! sizeof(ips))
                return 0;

        // 隨即抽一個IP
        ks = keys(ips);
        ip = ks[random(sizeof(ks))];

        // 在該IP地址上隨即抽取一個玩家
        ob = ips[ip][random(sizeof(ips[ip]))];
        
        if( query("gift/water", ob)>4 || random(5) )
        {
                msg = HIW "只見" + ob->name(1) +
                      HIW "全身白芒閃耀，神采奕奕，似乎沒有起到什麼作用。" NOR;
 
                my = ob->query_entire_dbase();
                my["jing"]   = my["eff_jing"]   = my["max_jing"];
                my["jingli"] = my["eff_jingli"] = my["max_jingli"];
                my["qi"]     = my["eff_qi"]     = my["max_qi"];
                my["neili"]  = my["max_neili"];
                my["food"]   = ob->max_food_capacity();
                my["water"]  = ob->max_water_capacity();
        } else
        {
                msg = HIC "霎那間" + ob->name(1) +
                      HIC "全身被紫芒籠罩，靈台間光華閃爍，如獲重生。" NOR;
                addn("int", 1, ob);
                addn("gift/water", 1, ob);
        }
        return msg;
}
