#include <ansi.h>
inherit NPC;
void create()
{
        set_name("殷素素", ({ "yin susu", "yin", "susu" }) );
        set("long",
                  "只見她身穿淡綠衫子，清麗不可方物。\n");
        set("attitude", "peaceful");
        set("title", "天鷹教");
        set("nickname", MAG "紫微堂堂主" NOR);
        set("gender","女性");
        set("age", 18);
        set("per", 38);
        set("combat_exp", 800000);

        set_skill("unarmed", 70+random(50));
        set_skill("parry", 70+random(50));
        set_skill("dodge", 70+random(50));

        setup();

        carry_object("/d/beijing/npc/obj/cloth4")->wear();
}

void init()
{
        add_action("do_yun","yun");
        add_action("do_yun","exert");
}

int do_yun(string arg)
{
        object obj;

        obj=this_object();
        if (arg == "roar" )
        {
                message_vision(CYN "\n殷素素喝道：賊子，要想行兇麼？在這裏恐怕由不得你！\n" NOR,
                                   obj);
                return 1;
        }
        return 0;

}

int accept_fight(object who)
{
        command("say 我不和你比，我是陪張公子來參觀的！");
        return 0;
}

int accept_hit(object who)
{
        command("say 我不和你比，我是陪張公子來參觀的！");
        return 0;
}

int accept_kill(object who)
{
        command("say 怎麼，要行兇麼？在這裏恐怕由不得你！");
        return 1;
}

int accept_ansuan(object who)
{
        return notify_fail("你剛想暗算，可是隻見會場裏黑壓壓的擠滿了人，根本看不清楚。\n");
}

void receive_damage(string type, int n)
{
        return;
}

void receive_wound(string type, int n)
{
        return;
}
