#include <ansi.h>

inherit NPC;

void create()
{
        set_name("麥鯨", ({ "mai jing", "mai", "jing" }) );
        set("long",
                  "這是巨鯨幫幫主麥鯨，身高七尺，滿面\n扎須，相貌很是威猛。\n");
        set("attitude", "heroism");
        set("title", WHT "巨鯨幫幫主" NOR);
        set("age", 47);
        set("combat_exp", 800000);
        set("max_neili", 1500+random(1000));
 
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
        command("say 我不和你蠻打，只和你比(bi)一些水上功夫。");
        return 0;
}

int accept_hit(object who)
{
        command("say 我不和你蠻打，只和你比(bi)一些水上功夫。");
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
        if (objectp(present("yuan guangbo",environment()))) 
        return 0;

        command("nod");
        command("say 我巨鯨幫的絕技，乃是使用水上功夫。");
        command("say 如今你我各用濕泥糊嘴，比試一下水上功夫，如何？");

        message_vision(HIW "$n和$N各取濕泥，糊上口鼻。\n" NOR,
                           this_object(),me);
        set_temp("bi", 1, me);
        set("anti",me);
        me->apply_condition("nishui",random(4)+1);
        this_object()->apply_condition("nishui",random(10)+10);
        call_out("guo",6,me);
        return 1;
}

void die()
{
        if (objectp(query("anti")))
        {
                message_vision(HIR"\n\n$N掙扎了兩下，一口氣沒接上，倒在地上一動不動了。\n"NOR,this_object());
                set_temp("win_mai", 1, query("anti"));
                delete_temp("bi", query("anti"));
                query("anti")->apply_condition("nishui",0);
        }
::die();
}

void unconcious()
{
        if (objectp(query("anti")))
        {
                message_vision(HIR"\n\n$N掙扎了兩下，一口氣沒接上，倒在地上一動不動了。\n"NOR,this_object());
                set_temp("win_mai", 1, query("anti"));
                delete_temp("bi", query("anti"));
                query("anti")->apply_condition("nishui",0);
        }
::die();
}

void guo(object me)
{
        if (objectp(present("guo sanquan",environment()))) present("guo sanquan",environment())->begin(me);
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

        if(!arg) 
        return 0;

        if (objectp(obj=present("yuan guangbo",environment()))) 
        return 0;

        if(sscanf(arg,"%s from %s",what, where) !=2)
        return 0;

        obj=this_object();
        if(where == "ding")
        {
                message_vision(CYN "$N正色道：這位英雄請了！\n" NOR,
                                   obj);

                message_vision(CYN "$N説道：屠龍寶刀乃不世之寶，要得此刀，需過(bi)了我這關！\n" NOR,
                                   obj);

                delete_temp("bi", this_player());
                return 1;
        }
        return 0;
}
