#include "roomnpc.h"

inherit CLASS_D("generate") + "/chinese";
inherit F_GUARDER;
inherit F_COAGENT;

int  accept_object(object who, object ob);

string query_save_file()
{
        object env;

        if (!objectp(env = environment()) ||
            strsrch(base_name(env),"/data/room/") == -1 ||
            !query("room_owner_id", env) )
                return 0;

        return sprintf("/data/room/%s/shouwei",query("room_owner_id", env));
}

void create()
{
        ::create();
        set_name(query("name"), ({ query("id"), "shou wei", "guarder" }));
        NPC_D->init_npc_skill(this_object(), 7 + random(2));
        set("gender", "男性" );
        set("age", 30 + random(30));
        set("long", "這是看護莊園的守衞，看上去似乎身懷絕技。\n");
        set("attitude", "friendly");

        set("max_qi", 4800);
        set("eff_qi", 4800);
        set("qi", 4800);
        set("max_jing", 2400);
        set("eff_jing", 2400);
        set("jing", 2400);
        set("max_neili", 5200);
        set("neili", 5200);
        set("jiali", 100);
}

void init()
{
        ::init();
        add_action("do_invite", "invite");
        add_action("do_show", "show");
        add_action("do_vip", "vip");
        add_action("list_vip", "listvip");
        add_action("buy_vip", "buyvip");       
        add_action("add_force", "addforce"); 
        add_action("add_skill", "addskill"); 
}

int accept_object(object who, object ob)
{
        object obn;

        if( !query("money_id", ob) )
                return 0;

        if (is_owner(who))
        {
                message_vision(name() + "對$N施了一禮。\n", who);
                destruct(ob);
                return 1;
        }
        return 0;
}

int accept_hit(object ob)
{
        if (is_owner(ob))
        {
                message_vision("$N連忙擺擺手，對$n道：“可不要和我開這"
                               "種玩笑！”\n", this_object(), ob);
                return 0;
        }

        return ::accept_hit(ob);
}

int accept_fight(object ob)
{
        if (is_owner(ob))
        {
                message_vision("$N嚇了一跳，慌忙對$n道：“小的不敢，小"
                               "的不敢！”\n", this_object(), ob);
                return 0;
        }

        return ::accept_fight(ob);
}

int accept_kill(object ob)
{
        if (is_owner(ob))
        {
                message_vision("$N一聲長歎，道：“既然主人不留我了，罷"
                               "罷罷！合則留，不合則去！我走了。”\n"
                               "説罷，$N一揚手，切下一角衣抉，飄然而去。\n",
                               this_object(), ob);
                destruct(this_object());
                return 0;
        }

        return ::accept_kill(ob);
}
