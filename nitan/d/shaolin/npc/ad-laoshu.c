// laoshu.c 老鼠

inherit NPC;

void create()
{
        set_name("老鼠", ({ "lao shu", "shu", "mouse" }) );
        set("race", "野獸");
        set("age", 2);
        set("long", "一隻贓兮兮的小老鼠。\n");
        set("attitude", "peaceful");
        
        set("limbs", ({ "頭部", "身體", "前腳", "後腳", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 100);
        set("shen_type", -1);
        set("env/wimpy", 70);

        set("chat_chance", 15);
        set("chat_msg", ({
                (: this_object(), "random_move" :),
        }) );
        
        set_temp("apply/attack", 5);
//      set_temp("apply/damage", 20);
        set_temp("apply/dodge", 20);
        set_temp("apply/armor", 1);

        setup();
}

int random_move()
{
        mapping exits;
        string *dirs;
        int i;

        if( !mapp(exits=query("exits", environment())))return 0;
        dirs = keys(exits);
        i = random(sizeof(dirs));
        //command("say " + "I am going to " + dirs[i] + ".");
        if(exits[dirs[i]][11..15] == "andao" ||
                exits[dirs[i]][11..15] == "rukou" ||
                exits[dirs[i]][11..15] == "wuxin")
                command("go " + dirs[i]);
}


void die()
{
        object ob;
        message_vision("$N悽慘的嚎了幾聲，死了。\n", this_object());
        ob = new("/d/shaolin/npc/shurou");
        ob->move(environment(this_object()));
        destruct(this_object());
}

