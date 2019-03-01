// Last Modified by Winder on May. 15 2001
// fruit.c

#include <ansi.h>
#include <dbase.h>

int is_food()
{
        return 1;
}
void init()
{
        if (!query("decay") && userp(environment()))
        {
                set("decay", 1);
                remove_call_out("stats");
                call_out("stats", 280,0);
        }
  add_action("do_eat", "eat");
}
int do_eat(string arg)
{
        mapping gifts;
        object me = this_player();
        object ob = this_object();
        object core;
        string msg, *list;
        int i, temp, sign;

        if( !living(this_player()) || this_player()->query_temp("noliving") )
                return 1;
        if( me->query("jing") < 0 || me->query("qi") < 0 )
                return notify_fail("你太累了，實在沒力氣吃什麼了。\n");
        if( !this_object()->id( arg ) ) return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");
        if( me->is_fighting() )
                me->start_busy(2);
        if( !query( "fruit_remaining" )  )
                return notify_fail("你拿著這個" + ob->name() + "，看了半天覺得無處下嘴。\n");
        if( (int)me->query("water") >= (int)me->max_food_capacity() ||
                (int)me->query("food") >= (int)me->max_water_capacity() )
        {
                if ( msg = query( "over_msg" ) ) notify_fail( msg );
                else notify_fail("吃那麼多？？真貪心，小心撐死了……\n");
                return 0;
        }
        addn( "fruit_remaining", -1);
        set( "value", 0);
        if ( query( "fruit_remaining" ) )
        {
                me->addn("food" ,  query( "food_supply" ) );
                me->addn( "water" , query( "water_supply" ) );

// hamlet的想法：食物對天賦有影響 (trill)
// 可以在food,fruit等加個mapping gifts
// 這樣對gifts有影響

                if ( gifts = query("gifts") )
                {
                        list = keys( gifts );
                        for( i = 0; i < sizeof( list ); i ++ )
                        {
                                me->addn( "hamlet_food/" + list[ i ],
                                        query("gifts/" + list[ i ] ) );
                                temp = me->query( "hamlet_food/" + list[ i ] );
                                sign = ( temp > 0 ) ? 1 : -1 ;
                                temp *= sign;
                                if (temp >= 500  && random( 2000 - temp ) == 0 && me->query("age")<22)
                                {
//如果這個player年紀小<22，就改善先天的天賦
//否則 只影響後天的天賦就 query_per()這類了..
//現在這個東西太麻煩，而且我們對先天後天的天賦使用沒有明確的概念
//所以我就把它都改成先天的了。──lala，１９９８－０１－０７

//原來的獎勵可以吃到30 30 35 35 的天賦 進行了限制
//-- qingyun 2004.10.13
//這個東西是別的mud的吧
//原本是建立在不能迅速降食物基礎上，因為俠客行有沙漠
//這個東西等同于送天賦給知道的人 
                                        if (me->query(list[i])>=30 )
                                                sign = 0;
                                        if (me->query("gift/hamlet/"+list[i])>0)
                                                sign=0;
                                        if (me->query(list[i])<10 )
                                                sign = 0;
                                        if (sign>0)
                                        {
                                                me->addn("gift/hamlet/"+list[i],1);
                                                me->addn( list[ i ] , sign );
                                                me->set( "hamlet_food/" + list[ i ], 0);
                                                tell_object( me, YEL"由于你日常的飲食習慣而造成了你天賦的改變！\n"NOR );
                                        }
                                }
                        }
                }
                if ( msg = query( "eat_msg" ) ) message_vision( msg, me, ob );
                else message_vision( RED"$N拿起$n，狠狠地咬了幾口，大讚道：味道好極了！\n" NOR, me, ob);
        }
        else
        {
//吃到最後一口就變成個水果核
                if ( msg = query ("end_msg" ) ) message_vision( msg , me, ob );
                else message_vision(RED"$N吃完最後一口$n，心滿意足的說：真不錯。\n", me,ob);
                if ( query("core") )
                {
                        core = new( "/clone/misc/core.c" );
                        core->set_name(query("core"), query("core_id") );
                        if ( query("core_unit") )
                                core->set("unit", query("core_unit"));
                        else core->set("unit", query("unit") );
                        if ( query("core_long") )
                                core->set("long", query("core_long") );
                        core->move( environment( this_object() ) );
                }
                remove_call_out( "stats" );
                destruct( this_object() );
        }
        return 1;
}

int stats( int i )
{
        string base_long, base_name;
        object core, env;
        int life;

//        if( !life = query( "life" )*240  ) return -1;
                if( !life = query( "life" )*20  ) return -1;

        switch ( i )
        {
                case 0:
                        set("base_long", query("long") );
                        set("base_name", query("name") );
                        call_out("stats", life/4, 1);
                        break;
                case 1:
                        base_long = query("base_long");
                        set("long",base_long+"，上面好象有些斑點，不過還不算顯眼。\n");
                        call_out("stats", life/4, 2);
                        break;
                case 2:
                        base_name = query("base_name");
                        base_long = query("base_long");
                        set("name","有點爛了的"+base_name );
                        set("long",base_long+"，可惜已經開始爛了。\n");
                        call_out("stats", life/4, 3);
                        break;
                case 3:
                        base_name = query("base_name");
                        base_long = query("base_long");
                        set("name", "爛" + base_name );
                        set("long",base_long+"，可惜已經爛了，散發出一股異味。\n");
                        call_out("stats", life/4, 4);
                        break;
                default :
                        if ( query("core") )
                        {
                                core = new( "/clone/misc/core.c" );
                                core->set_name(query("core"), query("core_id"));
                                if ( query("core_unit") )
                                        core->set("unit", query("core_unit"));
                                else
                                        core->set("unit", query("unit") );
                                if ( query("core_long") )
                                        core->set("long", query("core_long") );
                                if ( env = environment( this_object() ) )
                                        core->move( env );
                        }
                        tell_room( environment(this_object()), this_object()->query("name")+"終于完全爛掉了。\n" );
                        destruct( this_object() );
                        break;
        }
        return i;
}
