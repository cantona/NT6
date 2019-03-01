// wugui.c

inherit NPC;

void create()
{
        set_name("烏龜", ({ "wu gui", "gui" }) );
        set("race", "野獸");
        set("age", 10);
        set("long", "一只大烏龜，看來歲數不小了。\n");
        set("attitude", "peaceful");

        set("limbs",  ({  "頭部",  "爪子",  "尾巴"  })  );
        set("verbs",  ({  "bite"})  );
        set("str", 26);
        set("cor", 30);
        set("combat_exp", 1000);

        set_temp("apply/attack", 15);
        set_temp("apply/damage", 6);
        set_temp("apply/armor", 2);

        setup();
}

void die()
{
        object ob;
        message_vision("$N翻轉身，死了！\n", this_object());
        ob = new("/clone/medicine/vegetable/guijia");
        ob->move(environment(this_object()));
        destruct(this_object());
}