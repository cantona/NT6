// baidiao.c
// Last Modified by winder on May. 25 2001

inherit NPC;
mixed random_leave();
void create()
{
        set_name("大白雕", ({ "bai diao", "diao"}) );
        set("race", "飛禽");
        set("age", 18);
        set("long", "生長在大草原中的一種猛禽。\n");
        set("str", 28);
        set("cor", 24);
        set("combat_exp",180000);
        set("env/wimpy",50);
        set("chat_chance", 6);
        set("chat_msg", ({
                "大白雕在雲層中盤旋，雙翅掠過重重白雲。\n",
                "雲層中一道閃電劈下，在你眼前閃過一道金光。\n",
                (:random_leave:),
        }));
        set_temp("apply/attack", 28);
        set_temp("apply/armor", 28);

        setup();
}
void init()
{
        object ob;
        ::init();
        ob=present("tu jiu",environment());
        if (!ob) ob=present("hei jiu",environment());
        if (ob)
        {
                set_leader(ob);
                kill_ob(ob);
        }
        add_action("do_kill","kill");
        add_action("do_kill","hit");
        add_action("do_kill","fight");
        return;
}

mixed random_leave()
{
mapping default_dirs = ([
        "east":         "東",
        "west":         "西",
        "south":        "南",
        "north":        "北",
        "eastup":       "東邊",
        "westup":       "西邊",
        "southup":      "南邊",
        "northup":      "北邊",
        "eastdown":     "東邊",
        "westdown":     "西邊",
        "southdown":    "南邊",
        "northdown":    "北邊",
        "southeast":    "東南",
        "southwest":    "西南",
        "northeast":    "東北",
        "northwest":    "西北",
        "up":           "上",
        "down":         "下",
        "out":          "外",
        "enter":        "裡",
]);

        mapping exits;
        string *dirs,*where,dir;
        int i;

        if( !mapp(exits=query("exits", environment())))return ;
        dirs = keys(exits);
        where=values(exits);
        i=random(sizeof(dirs));
        
        if( !undefinedp(default_dirs[dirs[i]]) ) dir = default_dirs[dirs[i]];
        else dir =dirs[i];
        message_vision("$N一聲長鳴，振翅向"+dir+"飛去。\n",this_object());
        move(where[i]);
        tell_room(where[i],"一只大白雕飛了過來，在雲層中盤旋。\n");
        return;
        return 1;
}
void do_kill(string arg)
{
        if (!arg||arg!="bai diao") return;
        random_leave();
        return;
}
