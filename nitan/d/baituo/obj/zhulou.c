// Code of JHSH
// zhulou.c 竹簍
// maco

#include <ansi.h>
inherit ITEM;

int no_limit_amount(){ return 1; }
void create()
{
        set_name("竹簍", ({ "zhu lou", "lou", "basket"}) );
        set_weight(1000);
        set_max_encumbrance(100000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "一個竹條編成的簍子，是歐陽世家的人專門用來捕蛇的。\n");
                set("material", "bamboo");
                set("value", 100);
        }
        setup();
}

void init()
{
        add_action( "do_catch", "catch" );
        add_action( "do_catch", "buzhuo" );
        add_action( "do_free", "free" );
        add_action( "do_free", "fang" );
}

int is_container() {return 1;}

int do_catch(string arg)
{
        object obj = this_object(), me = this_player();
        object snake;

        if (me->is_busy()
         || query_temp("pending/exercising", me) )
                return notify_fail("你現在正忙着呢。\n");

        if(me->is_fighting())
                return notify_fail("先解決眼前的敵人再説吧。\n");

        if ( !arg )
                return notify_fail("你要捕捉什麼？\n" );

        snake = present(arg, environment(me));

        if( !objectp(snake = present(arg, me)) && !objectp(snake = present(arg, environment(me)))) 
                return notify_fail("你要捕捉什麼？\n" );

        if( query("race", snake) != "蛇類" )
                return notify_fail("這竹簍是用來捉蛇的。\n");

        if( query("keeper", obj) != query("id", me) )
                return notify_fail("這不是你的竹簍，還是別亂動的好。\n");

        if( query("who_breed", snake) )
                return notify_fail("這條"+snake->name()+"是歐陽世家培養出來的，即使捉了，也不能進行育種。\n");

        if( snake->query_lord() != me && living(snake) 
         && query("caught", snake) != query("id", me) )
                return notify_fail(snake->name()+"並非你所馴養，直接動手捉相當危險。\n");

        if( !query("bt_snake", snake) )
                return notify_fail("這不是歐陽世家蛇谷的品種。\n");

        if( snake->move(obj) ) 
        {
                message_vision("$N將"+snake->name()+"捉了起來，從尾巴起慢慢放進竹簍。\n", me, snake);
                delete("frightened", snake);
                if( !query("caught", snake) )
                me->improve_skill("training",atoi(query("snake_poison", snake)));

                set("caught",query("id",  me), snake);
        return 1;
        }
        else return 0;
}

int do_free(string arg)
{
        object me, obj, snake, *inv;
        int i;
        me = this_player();
        obj = this_object();

        if( !arg )
                return notify_fail("你想把什麼放出竹簍？\n");

        if( me->is_busy() )
                return notify_fail("你正忙着呢。\n");

        if( query("keeper", obj) != query("id", me) )
                return notify_fail("這不是你的竹簍，還是別亂動的好。\n");

        if(arg=="all") {

                if( me->is_fighting() )
                        return notify_fail("你還在戰鬥中！一次祗能放一條蛇。\n");

                inv = all_inventory(obj);
                if( !sizeof(inv) )
                        return notify_fail("那裏面沒有任何東西。\n");

                for(i=0; i<sizeof(inv); i++) {
                        if( query("race", inv[i]) != "蛇類")continue;
                        inv[i]->move(environment(me));
                        message_vision("$N將一條$n放出竹簍。\n"NOR, me, inv[i]);
                }
                write("竹簍裏的蛇全被放出來了。\n");
                return 1;

        }

        if( !objectp(snake = present(arg, obj)) )
                return notify_fail("竹簍裏沒有這個生物。\n");

        if( !snake->is_character() || snake->is_corpse() )
                return notify_fail("那並不是活物，直接用拿的就可以了。\n");

        message_vision("$N將一"+query("unit", snake)+"$n放出竹簍。\n"NOR,me,snake);

        snake->move(environment(me));

        if( me->is_fighting() ) me->start_busy(1);

        return 1;
}

int reject(object ob)
{
        if( query("race", ob) == "蛇類"){
                notify_fail("請用捕捉(catch | buzhuo)指令。\n");
                return 1;
                }

        notify_fail("這竹簍是用來捉蛇的。\n");
        return 1;
}