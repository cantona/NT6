#include <ansi.h>
inherit NPC;

void create()
{
        set_name("趙齊賢", ({ "zhao qixian", "zhao", "qixian" }));
        set("title", HIR "御前侍衛" NOR);
        set("age", 32);
        set("gender", "男性");
        set("long", "一個其貌不揚的中年男子，但身上竟著御前侍\n衛的裝束。他便是御前侍衛趙齊賢。\n");
        set("attitude", "peaceful");

        set("str", 30);
        set("dex", 30);
        set("combat_exp", 100000);
        set("shen_type", 1);

        set_skill("unarmed", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("sword", 100);
        set_skill("force", 100);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 60);
        set_temp("apply/armor", 60);

       set("chat_chance_combat", 10);
        set("chat_msg_combat", ({
                "趙齊賢喝道：太歲頭上居然敢動土？\n",
        }));
        setup();
        carry_object("/d/beijing/npc/obj/sword4")->wield();
       carry_object("/d/beijing/npc/obj/guanfu2")->wear();
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && 
                (int)ob->query_condition("killer")) {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }
}

int accept_fight(object me)
{
        command("say 這可是你活膩了自找的，休得怪我無情。\n");
        me->apply_condition("killer", 500);
        kill_ob(me);
        return 1;
}
