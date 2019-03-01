//yulinjun.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("御林軍", ({ "yulin jun", "jun", "guard" }) );
        set("gender", "男性");
        set("age", 25);
        set("long",
                "這是位守護皇城的御林軍武士，身披戰甲，手執鋼刀。他雙目精光炯炯，警惕地巡視著四周的情形。\n");
        set("combat_exp", 160000);
        set("attitude", "heroism");
        set("str", 25);
        set("max_qi", 750);
        set("max_jing", 600);
        set("neili", 400);
        set("max_neili", 400);
        set("jiali", 15);
        set_skill("blade", 80);
        set_skill("unarmed", 80);
        set_skill("parry", 80);
        set_skill("dodge", 80);
        set_skill("force", 50);

        setup();
        carry_object("/d/changan/npc/obj/blade")->wield();
        carry_object("/d/changan/npc/obj/zhanjia")->wear();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && 
            ob->query_condition("killer")) 
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }       
}

int accept_fight(object me)
{
        message_vision("御林軍士對$N大喝一聲：你活得不"
                       "耐煩了？皇宮前你也敢胡鬧！\n", me);
        kill_ob(me);
        return 1;
}