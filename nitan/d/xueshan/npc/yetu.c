// yetu.c 野兔

inherit NPC;

void create()
{
        set_name("野兔", ({ "ye tu", "hare" ,"tu"}) );
        set("race", "野獸");
        set("age", 5);
        set("long", "一隻好可愛的小野兔，你似乎看到了香噴噴的兔肉。\n");
        set("attitude", "peaceful");
        
        set("limbs", ({ "頭部", "身體", "前腳", "後腳", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 500);

        set_temp("apply/attack", 2);
        set_temp("apply/defense", 5);
        set_temp("apply/damage", 2);
        set_temp("apply/armor", 1);

        setup();
}

void die()
{
        object ob;
        message_vision("$N悽慘的嚎了幾聲，死了。\n", this_object());
        if( random(3) >1 )      {
                ob = new("/d/xueshan/npc/turou");
                ob->move(environment(this_object()));
        }
        else    
                message_vision("天空中突然出現一隻禿鷲，把$N叼走了。\n", this_object());
        destruct(this_object());
}