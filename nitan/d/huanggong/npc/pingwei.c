// pingwei.c
#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("平威", ({ "ping wei", "wei" ,"ping"}));
        set("gender", "無性");
        set("title", HIC"西六宮太監"NOR);
        set("age", 26);
        set("per", 16);
        set("long", "一個肥胖漢子，看似威猛，可惜是個太監。\n");

        set("combat_exp", 3000);
        set("shen_type", 0);

        set_skill("unarmed", 10);
        set_skill("blade", 10);
        set_skill("parry", 10);
        set_skill("dodge", 10);
        
        set_temp("apply/attack", 15);
        set_temp("apply/defense", 15);
        set_temp("apply/damage", 20);

        set("chat_chance", 10);
        set("chat_msg", ({
              (: random_move :),
        }));

        setup();
        add_money("silver", random(10));
        carry_object(__DIR__"obj/tjcloth")->wear();
}
        