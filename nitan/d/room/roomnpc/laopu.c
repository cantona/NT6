// laopu.c 掃地老僕

#include "roomnpc.h"

inherit NPC;
inherit F_GUARDER;

void do_wield();
void do_unwield();
int  accept_object(object who, object ob);

void create()
{
        set_name("掃地老僕", ({"lao pu", "saodi laopu"}) );
        set("gender", "男性" );
        set("age", 50 + random(20));
        set("long", "這是一個掃地的老僕人，不過看上去似乎身懷絕技。\n");
        set("attitude", "friendly");

        set("max_qi", 4000);
        set("max_jing", 2000);
        set("max_neili", 4200);
        set("neili", 4200);
        set("jiali", 70);

        set_skill("force", 200);
        set_skill("parry", 200);
        set_skill("dodge", 200);
        set_skill("sword", 200);
        set_skill("cuff",  200);
        set_skill("strike",200);
        set_skill("huashan-neigong", 200);
        set_skill("feiyan-huixiang", 200);
        set_skill("huashan-sword", 200);
        set_skill("hunyuan-zhang", 200);
        set_skill("poyu-quan", 200);

        map_skill("force", "huashan-neigong");
        map_skill("parry", "huashan-sword");
        map_skill("sword", "huashan-sword");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("cuff" , "poyu-quan");
        map_skill("strike", "hunyuan-zhang");

        prepare_skill("cuff", "poyu-quan");
        prepare_skill("strike", "hunyuan-zhang");

        set("chat_chance", 30);
        set("chat_msg", ({
                (: do_unwield :),
        }));

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: do_wield :),
        }));

        setup();

        carry_object("/clone/weapon/gangjian");
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        ::init();
        add_action("do_invite", "invite");
        add_action("do_show", "show");
}

void do_unwield()
{
        command("unwield jian");
}

void do_wield()
{
        command("wield jian");
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
                message_vision("$N愁眉苦臉的對$n道：“可不要和我開這"
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
                               "説罷，老人丟下掃把，飄然而去。\n",
                               this_object(), ob);
                destruct(this_object());
                return 0;
        }

        return ::accept_kill(ob);
}
