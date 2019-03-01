// story:sun 日熾
#include <ansi.h>

inherit F_CLEAN_UP;

mixed random_gift();

nosave mixed *story = ({
        "後羿：哪裡跑！",
        "金烏：糟糕，這下避無可避，該怎麼辦？",
        "後羿：看箭！",
        "「嗖──」",
        "金烏：天殺的，今天就和你拼了！",
        "後羿：早該如此，看我的「百步穿陽」！",
        "金烏：「毀滅之光」！",
        "「嗖──嗖──」",
        "金烏：哎呦……",
        "「哧啦──哧啦──」",
        "後羿抹了抹汗：好險！",
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

        if( query("gift/sun", ob)>4 || random(5)>1 )
        {
                msg = HIR + ob->name(1) + "一聲慘叫，軟軟的倒了下去。" NOR;
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
                msg = HIY "霎那間" + ob->name(1) +
                      HIY "渾身金光閃閃，如沐金濤，神威凜凜。" NOR;
                addn("str", 1, ob);
                addn("gift/sun", 1, ob);
        }
        return msg;
}


