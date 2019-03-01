// story:feng 鳳舞

#include <ansi.h>

mixed random_gift();

inherit F_CLEAN_UP;

nosave mixed *story = ({
        "路人：這位大哥，這附近最近有什麼奇怪的事情發生嗎？",
        "樵夫：聽說最近東邊的湖畔經常會飛來一只鳳凰。",
        "路人：原來真有這事....",
        "樵夫：唉！又是個來送死的。",
        "路人：聽說上回老五看到了鳳凰起舞，結果身法大漲，現在尋常人都打不過他了。",
        "......",
        "湖邊，鳳凰看著水中的倒影，陶醉在自己的美麗中，翩翩起舞。",
        "周圍隨著鳳舞刮起了旋風。",
        "呼～～～～",
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
        mapping ips;
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

        if( query("gift/feng", ob)>4 || random(5) )
        {
                msg = HIR + ob->name(1) + "被一陣旋風刮起，重重摔在了地上。" NOR;
                if( query("combat_exp", ob)<1000000 || 
                    query("qi", ob)<1000 )
                        ob->unconcious();
                else
                {
                        set("qi", 10, ob);
                        set("eff_qi", 10, ob);
                        set("jing", 1, ob);
                        set("eff_jing", 1, ob);
                }
        } else
        {
                msg = HIG "聽說" + ob->name(1) +
                      HIG "無意中看到了鳳凰起舞。" NOR;
                addn("dex", 1, ob);
                addn("gift/feng", 1, ob);
        }
        return msg;
}

