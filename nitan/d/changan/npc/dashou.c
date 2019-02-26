//dashou.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("打手", ({ "da shou" }) );
        set("title",MAG "護花使者" NOR);
        set("age", random(25)+15);
        set("long", "一個為羣玉樓效力，正在看門的打手\n");
        set("per",15);
        set("combat_exp", 100000);
        set("no_arrest",1);
        set("attitude", "heroism");
        set("gender", "男性" );
        set_skill("unarmed", 200);
        set_skill("blade",200);
        set_skill("parry", 200);
        set_skill("dodge", 200);

        setup();
        add_money("silver", 6);
        carry_object("/d/changan/npc/obj/cloth")->wear();
        carry_object("/d/changan/npc/obj/blade")->wield();
        
}

void init()
{
        add_action("do_killing", "kill");
}

int do_killing(string arg)
{
        object player, victim, weapon;
        string name;

        player = this_player();
        if (! arg) return 0;
        if (objectp(victim = present(arg, environment(this_object())))
            && living(victim))
        {
                name = (string)victim->name();
                if ((string)name == "打手")
                {
                        message_vision("$N道：敢到來羣玉樓鬧事，我"
                                       "看你活得不耐煩了。\n",
                                       this_object());
                        this_object()->kill_ob(player);
                        player->kill_ob(this_object());
                        return 1;
                }
        }
        return 0;
}