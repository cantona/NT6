// poison.h
// Last Modified by winder on Feb. 28 2001

void init()
{
//        add_action("do_tu", "tu");
        add_action("do_make", "make");
        add_action("do_dian", "dian");
}

int do_make(string arg)
{
        object fire, me = this_player();
        object obj=this_object();
     
        if(!arg || (arg!="huo yan" && arg != "huoyan" && arg != "huodui"))
                return notify_fail("你要做什麼？\n");

        if( !objectp(fire=present("fire",me)) && (query("neili", me)<500) )
                return notify_fail("你身上沒有火種，怎麼升火？\n");
        if(me->query_skill("poison", 1) < 60)
        {
                message_vision("$N打著火折將$n點燃，冒出一縷奇異的毒煙！\n",me,this_object());
                message_vision("$N嚇了一大跳，連忙將$n胡亂一扔，遠遠躲了開去！\n",me,this_object());
//                this_object()->add_amount(-1);
                destruct(obj);
                return 1;
        }
        if(present("huo yan", environment(me)))
                return notify_fail("這裡已經有火燄了，還要升什麼火？\n");
        if(!fire)
        {
                addn("neili", -100, me);
                message_vision(HIR"\n$N口中吐出一口青煙，將手中$n"HIR"用內力一搓一拋，轟地一聲燃起一堆熊熊火燄！\n\n"NOR, me, this_object());
        }
        else message_vision( HIR"\n$N將手中$n"HIR"用火種點燃，然後向地下使勁一扔，燃起了一堆熊熊火燄！\n\n"NOR, me, this_object());    
        new("/d/xingxiu/npc/obj/huoyan")->move(environment(me));
//        this_object()->add_amount(-1);
        destruct(obj);
        return 1;         
}
/*
int do_tu(string arg)
{
        string me, what;
        object ob;
           
        if( !arg || sscanf(arg, "%s on %s", me, what)!=2 || !id(me) )
                return notify_fail("命令格式: tu <藥> on <武器>。\n");

        ob = present(what, this_player());

        if( !ob ) return notify_fail("你身上沒有" + what + "這樣東西。\n");
        if( !query("weapon_prop", ob))return notify_fail("只能塗在武器上。\n");

        else return notify_fail("你要先將藥粉點燃才行。\n");

        return 0;        
}
*/
int do_dian(string arg)
{
        object me,ob,ob1;

        ob = this_object();
        me = this_player();
        if( !arg || arg != query("id", ob) )
                return notify_fail("你要點燃什麼東西？\n");

        if(!objectp(ob1 = present("fire", me)))
                return notify_fail("你先要找個火種。\n");

        message_vision("$N打著火折將$n點燃，冒出一縷奇異的毒煙！\n",me,ob);
        if(me->query_skill("poison", 1) > 79)
        {
                new(query("drug2", ob))->move(me);
//                ob->add_amount(-1);
        destruct(ob);
                return 1;
        }
        else
        {
                message_vision("$N嚇了一大跳，連忙將$n胡亂一扔，遠遠躲了開去！\n",me,ob);
//                ob->add_amount(-1);
        destruct(ob);
                return 1;
        }
}

int drink_drug(object ob)
{        
        string poison=query("poison", ob);
        this_player()->apply_condition(poison, (int)this_player()->query_condition(poison) + random(8));
        return 0;
}
 
