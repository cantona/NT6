// Code of JHSH        
// pozhen.c

#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        object env,owner;
        string msg;

        env = environment(me);
        if (!env)
                return notify_fail("這裏什麼地方也不是！\n");
        if( !query("th_buzhen", env) )
                return notify_fail("這裏並無布有奇門陣法。\n");
        
        if( !objectp(owner=find_player(query("th_zhen_owner", env))) || 
            environment(owner) != env)
        {
                set("long",query("org_desc",  env), env);
                set("exits",query("org_exits",  env), env);
                set("cost",query("org_cost",  env), env);
                delete("org_desc", env);
                delete("org_cost", env);
                delete("org_exits", env);
                delete("th_buzhen", env);
                delete("th_pozhen", env);
                delete("th_zhen_owner", env);
        
                tell_object(env, CYN"一陣青霧升騰而起又四散而去，四面景緻猛然一變。\n"NOR);
                return 1;
        }

        if( me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("你所用的內功與「奇門陣法」心法相悖！\n");

        if( me->query_skill("bibo-shengong", 1) < 80 )
                return notify_fail("你的內功修為火候未到，還未領悟「奇門陣法」！\n");

        if( query("jingli", me)<query("max_jingli", me)*80/100 )
                return notify_fail("你的精力不夠，不足以破解「奇門陣法」！\n");

        if( query("jing", me)<query("max_jing", me)*80/100 )
                return notify_fail("你的精不夠，不足以破解「奇門陣法」！\n");

        if( me->query_skill("qimen-wuxing", 1) < 80 )
                return notify_fail("你的奇門五行修為不夠，還未領悟「奇門陣法」！\n");

        set("jing",query("max_jing",  me)/2, me);
        set("jingli",query("max_jingli",  me)/2, me);

        if( query("id", me) != query("th_zhen_owner", env) && 
        me->query_skill("qimen-wuxing",1)<query("th_pozhen", env)*3/4){
                message_vision(CYN"$N坐在地上冥思苦想，突然臉色大變，口吐鮮血！\n"NOR,me);
                me->unconcious();
                return 1;
        }

        msg = HIW"$N凝思片刻，陣法的種種生克變化已全盤瞭然於胸，仰天一聲長笑，袍袖一拂，\n";
        msg += "掠入陣中，掌劈腳挑，頓時飛沙走石，不一刻，陣中陰霾戾氣已消散得無影無蹤！\n"NOR;
        message_vision(msg, me);
        
        set("long",query("org_desc",  env), env);
        set("exits",query("org_exits",  env), env);
        set("cost",query("org_cost",  env), env);
        delete("org_desc", env);
        delete("org_cost", env);
        delete("org_exits", env);
        delete("th_buzhen", env);
        delete("th_pozhen", env);
        delete("th_zhen_owner", env);

        return 1;
}