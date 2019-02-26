// tujiu.c
// Last Modified by winder on May. 25 2001

inherit NPC;
void random_leave();
void random_eat();
void create()
{
        set_name("禿鷲", ({ "tu jiu"}) );
        set("race", "飛禽");
        set("age", 17);
        set("long", "漠北一種兇猛的飛鳥,以腐屍為食。\n");
        set("str", 26);
        set("cor", 24);
        set("combat_exp",80000);
        set("chat_chance", 6);
        set("chat_msg", ({
                "禿鷲在你頭頂盤旋，似乎在尋找下手的機會。\n",
                "禿鷲落在你前面不遠的巖石上，不懷好意的盯住你。\n",
                (:random_leave:),
                (:random_eat:),
        }));
        set_temp("apply/attack", 20);
        set_temp("apply/armor", 20);

        setup();
}
void init()
{
        object ob;
        ::init();
        if (interactive(ob=this_player())&&!is_fighting())
        {
                 remove_call_out("eat_corpse");
                call_out("eat_corpse",1,ob);
        }
        add_action("do_kill","kill");
        add_action("do_kill","hit");
        add_action("do_kill","fight");
}
void eat_corpse(object ob)
{
        object corpse;
        corpse=present("corpse",environment());
        if (corpse)
        {
                message_vision("$N一點點啄食着$n，時不時振起散亂的羽毛。\n",this_object(),corpse);
                return;
        }
        return;
}
void random_leave()
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
        "enter":        "裏",
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
        message_vision("$N一聲驚叫，振翅向"+dir+"飛去。\n",this_object());
        move(where[i]);
        tell_room(where[i],"一隻禿鷲飛了過來，在空中盤旋。\n");
        return;
}
void do_kill(string arg)
{
        if (!arg||arg!="tu jiu") return;
        random_leave();
        return;
}
void random_eat()
{
        object corpse;
        corpse=present("corpse",environment());
        if (corpse)
        {
                message_vision("$N一點點啄食着$n，時不時振起散亂的羽毛。\n",this_object(),corpse);
                return;
        }
        return;
}