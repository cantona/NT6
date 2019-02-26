// story:lighting 電擊

#include <ansi.h>

mixed random_gift();

nosave mixed *story = ({
        "電母：這...這是啥？",
        "雷公：怎麼了你？",
        "電母杏目圓睜：豈有此理！快説，你背地裏都瞞着我幹些什麼？",
        "雷公：變態！",
        "電母：你...",
        "...",
        "嘿...",
        "哎呦...",
        "噼啞！！！！！！！！！！！～～～～～",
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
        object ob;
        string msg;

        obs = filter_array(all_interactive(), (: ! wizardp($1) &&
                                                 environment($1) &&
                                                 query("outdoors", environment($1)) &&
                                                 !query("env/no_story", $1) &&
                                                 !query("doing", $1):));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        
        if( query("gift/lighting", ob) || random(5) )
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
                msg = HIC "霎那間" + ob->name(1) + "渾身火花四射，猶如天神一般，神威凜凜。" NOR;
                addn("con", 1, ob);
                addn("gift/lighting", 1, ob);
        }
        return msg;
}
