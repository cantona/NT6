#include <ansi.h>
inherit NPC;
void create()
{
        set_name("元廣波", ({ "yuan guangbo", "yuan", "guangbo" }) );
        set("long", "這是海沙派總舵主元廣波，目光如電，身材彪捍。\n");
        set("attitude", "heroism");
        set("title", HIY "海沙派總舵主" NOR);
        set("age", 15);

        set("max_neili", 1000+random(500));
        set("combat_exp", 800000);

        set_skill("unarmed", 100+random(50));
        set_skill("parry", 100+random(50));
        set_skill("dodge", 100+random(50));
        set_skill("force", 100+random(50));

        set("max_qi", 2500+random(1000));
        set("max_jing", 2500+random(1000));

        setup();

        carry_object("/d/beijing/npc/obj/cloth6")->wear();
}

int accept_fight(object who)
{
        command("say 我不和你蠻打，只和你比(bi)一些我海沙幫的絕技。");
        return 0;
}

int accept_hit(object who)
{
        command("say 我不和你蠻打，只和你比(bi)一些我海沙幫的絕技。");
        return 0;
}

int accept_kill(object who)
{
        command("say 怎麼，想得屠龍刀就非得要行兇不成？");
        return 1;
}

int accept_ansuan(object who)
{
        return notify_fail("你剛想暗算，可是隻見會場裏黑壓壓的擠滿了人，根本看不清楚。\n");
}

int begin()
{
        object me=this_player();
        if (objectp(present("chang jinpeng",environment())))
        return 0;

        command("grin");        
        command("say 我海沙幫的絕技，乃是使用毒鹽害人，如今你我各吃一碗，如何？");

        message_vision(HIW "$N叫手下裝了兩大碗毒鹽，$N和$n各吃一碗。\n" NOR,
                           this_object(),me);

        set_temp("bi", 1, me);
        set("anti",me);
        me->apply_condition("duyan",random(4)+1);
        this_object()->apply_condition("duyan",random(10)+10);
        return 1;
}

void die()
{
        if (objectp(query("anti")))
        {
                command("say 佩服，佩服......");
                message_vision(HIR "\n$N嘶啞着嗓子乾嚎了兩聲，雙眼翻白，跌倒在地，口中吐出一些白沫，就再也沒動了。\n" NOR,
                                   this_object());
                set_temp("win_yuan", 1, query("anti"));
                delete_temp("bi", query("anti"));
        }
::die();
}

void unconcious()
{
        if (objectp(query("anti")))
        {
                command("say 佩服，佩服......");
                message_vision(HIR "\n$N嘶啞着嗓子乾嚎了兩聲，雙眼翻白，跌倒在地，口中吐出一些白沫，就再也沒動了。\n" NOR,
                                   this_object());
                set_temp("win_yuan", 1, query("anti"));
                delete_temp("bi", query("anti"));
        }
::die();
}

void init()
{
        add_action("do_get","get");
        add_action("begin","bi");
}

int do_get(string arg)
{
        object obj,env,ding;
        string what,where;
        if(!arg) return 0;
        if (objectp(obj=present("chang jinpeng",environment(this_object())))) return 0;
        if(sscanf(arg,"%s from %s",what, where) !=2) return 0;
        obj=this_object();

        if(where == "ding")
        {
                message_vision(CYN "$N喝道：無恥小賊，給我住手！你憑什麼得此寶刀？\n" NOR,
                                   obj,this_player());

                message_vision(CYN "$N冷冷地説道：要得此刀，先比(bi)贏了我再説！\n" NOR,
                                   obj,this_player());

                delete_temp("bi", this_player());
                return 1;
        }
        return 0;
}
