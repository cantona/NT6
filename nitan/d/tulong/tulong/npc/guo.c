#include <ansi.h>

inherit NPC;

void create()
{
        set_name("過三拳", ({ "guo sanquan", "guo", "sanquan"}) );
        set("long",
                  "這是神拳門掌門人過三拳。身材高大，雙\n臂肌肉結實，一看就知道是外家好手。\n");
        set("attitude", "heroism");
        set("title", HIR "神拳門掌門人" NOR);
        set("age", 56);
        set("combat_exp", 800000);

        set_skill("unarmed", 100+random(50));
        set_skill("parry", 100+random(50));
        set_skill("dodge", 100+random(50));
        set_skill("force", 100+random(50));

        set("max_qi", 1000+random(500)); 
        set("max_jing", 1000+random(500)); 


        setup();

        carry_object("/d/beijing/npc/obj/cloth6")->wear();
}

int accept_fight(object who)
{
        command("say 我不和你蠻打，只和你比(bi)一些拳腳上的功夫。");
        return 0;
}

int accept_hit(object who)
{
        command("say 我不和你蠻打，只和你比(bi)一些拳腳上的功夫。");
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

int begin(object me)
{
        command("bow");
        command("say 閣下對不住了，今日我如不趁人之危，定會死於閣下之手！");
        command("say 我神拳門絕技，乃是使用手上功夫，先吃我三拳再説。");

        message_vision(HIR "\n$N喝道：小心了！我這第一拳乃“催筋斷骨”！\n" NOR,
                           this_object());
        COMBAT_D->do_attack(this_object(), this_player(),query_temp("weapon"));

        message_vision(HIR "\n$N喝道：好！看我第二拳“崩山裂石”！\n" NOR,
                           this_object());
        COMBAT_D->do_attack(this_object(), this_player(),query_temp("weapon"));

        message_vision(HIR "\n$N喝道：第三拳來了！這式叫做“橫掃千軍，直摧萬馬”！\n" NOR,
                           this_object());
        set_temp("apply/attack", 250, this_object());
        set_temp("apply/damage", 250, this_object());
        COMBAT_D->do_attack(this_object(), this_player(),query_temp("weapon"));
        set("anti",me);
        set_temp("bi", 1, me);
        if( query("max_neili", me)>2000)die();
        return 1;
}

void die()
{
        if (objectp(query("anti")))
        {
                message_vision(HIR "\n\n$N一拳端端正正的擊中了$n" HIR
                                   "的小腹。\n" NOR,
                                   this_object(),query("anti"));

                message_vision(HIR "人身的小腹本來極是柔軟，但$N" HIR
                                   "着拳時如中鐵石，剛知不妙，已狂噴鮮血。\n" NOR,
                                   this_object(),query("anti"));

                set_temp("win_guo", 1, query("anti"));
                delete_temp("bi", query("anti"));
        }
::die();
}

void init()
{
        add_action("do_get","get");
        add_action("do_bi","bi");
}

int do_get(string arg)
{
        object obj;
        string what,where;
        if(!arg) return 0;
        if (objectp(obj=present("mai jing",environment()))) return 0;
        if(sscanf(arg,"%s from %s",what, where) !=2) return 0;
        obj=this_object();
        if(where == "ding")
        {
                message_vision(CYN "$N哼了一聲。\n" NOR,
                                   obj);
                message_vision(CYN "$N説道：要想得到寶刀，先過我三拳！\n" NOR,
                                   obj);
                delete_temp("bi", this_player());
                return 1;
        }
        return 0;
}

int do_bi()
{
        object me=this_player();
        if (objectp(present("mai jing",environment()))) return 0;
        begin(me);
        return 1;
}
