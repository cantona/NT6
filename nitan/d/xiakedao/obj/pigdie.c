// pigdie.c

inherit ITEM;
void init()
{
        add_action("do_ge","ge");
        add_action("do_ge","cut");
}

void create()
{
        set_name("死豬", ({ "pig", "pigdie" }) );
        set("long", "這是一隻死去的野豬，頭部(zhutou)、前腿(forleg)、後腿(backleg)都
長得極為粗壯。\n");
        set_temp("zhutou", 1);
        set_temp("forleg", 1);
        set_temp("backleg", 1);
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("value", 300);
        }
        setup();
}

int do_get(string arg)
{
        object me=this_player();
        object ob=this_object();

        if( !arg ) return notify_fail("你要拿什麼？\n");
        if( (string)arg=="pig")
        {
                if( query("str", me)<25 )
                {
                        message_vision("這隻野豬太沉了，你拿不動。\n", me);
                        return 1;
                }
                message_vision("你扛起一整隻豬，太沉了，真是受不了。\n", me);
                ob->move(me);
                return 0;
        }
}

int do_ge(string arg)
{
        object me=this_player();
        object ob;
        if(!arg||arg=="")
                return notify_fail("你要切什麼東西？\n");
        if( (string)arg=="pig")
                return notify_fail("你要切哪一部分？\n");
        if( (!objectp(present("cut knife", me)) ))
        {
                message_vision("你沒有合適的東西來切。有把菜刀或柴刀之類的就好了。\n", me);
                return 1;
        }

        switch( (string)arg)
        {
                case "zhutou" :
                        if( query_temp("zhutou")==1)
                        {
                                message_vision("你砍下野豬的頭。\n", me);
                                ob=new(__DIR__"zhutou");
                                ob->move(me);
                                set_temp("zhutou" , 0);
                                break;
                        }
                        else
                        {
                                message_vision("這野豬的頭已被人砍走了。\n", me);
                                return 1;
                        }
                case "forleg" :
                        if( query_temp("forleg")==1)
                        {
                                message_vision("你砍下野豬的前腳。\n", me);
                                ob=new(__DIR__"forleg");
                                ob->move(me);
                                set_temp("forleg", 0);
                                break;
                        }
                        else
                        {
                                message_vision("這野豬的前腿已被人砍走了。\n", me);
                                return 1;
                        }
                case "backleg" :
                        if( query_temp("backleg")==1)
                        {
                                message_vision("你砍下野豬的後腳。\n",me);
                                ob=new(__DIR__"backleg");
                                ob->move(me);
                                set_temp("backleg", 0);
                                break;
                        }
                        else
                        {
                                message_vision("這野豬的後腿已被人砍走了。\n", me);
                                return 1;
                        }
        }
        if ((query_temp("zhutou")==0) &&
                (query_temp("forleg")==0) &&
                (query_temp("backleg")==0))
        {
                this_object()->move(environment(me));
                destruct(this_object());
        }
        return 1;
}
