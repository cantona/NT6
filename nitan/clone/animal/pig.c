// clone/animal/pig.c
// Last Modified by winder on Aug. 1 2002

inherit NPC;

void create()
{
        set_name("小豬", ({"xiao zhu", "pig"}));
        set("race", "走畜");
        set("age", 5);
        set("long", "一頭臭氣熏天的小豬。\n");
        set("attitude", "peaceful");
        set("verbs", ({ "bite" }) );
        set("combat_exp", 100);
        
        set_temp("apply/attack", 5);
        set_temp("apply/defense", 5);
        set_temp("apply/damage", 4);
        set_temp("apply/armor", 1);

        setup();
}

void die()
{
        object ob;
        int i;

        message_vision("$N低低地哼了一聲，倒在地上一動也不動了。\n", this_object());
        i = random (5);
        switch (i)
        {
                case 1:
                        ob = new(__DIR__"obj/pork");
                        break;
                default:
                        ob = new(__DIR__"obj/pork");
                        break;
        }

        ob->move(environment(this_object()));
        destruct(this_object());
}