// honghua1.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("綠營會眾", ({ "hong hua","hong","hua" }) );
        set("gender", "男性");
        set("age", 25);
        set("long",
                "這是位手執長槍的綠營清兵，紅花會在江南聲勢大盛，綠營也
多有會眾。\n");
        set("combat_exp", 20000);
        set("shen_type", 1);
        set("attitude", "heroism");

        set("apply/attack",  30);
        set("apply/defense", 30);

        set_skill("club", 60);
        set_skill("unarmed", 50);
        set_skill("parry", 50);
        set_skill("dodge", 50);

        setup();

        carry_object("/clone/weapon/changqiang")->wield();
        carry_object("/d/city/obj/junfu")->wear();
        add_money("silver", 20);
}
void init()
{
        object ob;
        if (random(2) == 1)
        message_vision(HIY "綠營會眾悄悄告訴$N：身在綠營心在漢！\n" NOR, 
                this_player());
        else
        message_vision(HIY "綠營會眾衝着$N擠了擠眼説：狗皇帝是從青樓地道被當家的逮着的！\n" NOR, 
                this_player());
}
