// Code of LXTX
// huolu.c 火爐

#include <ansi.h>
inherit ITEM;

int check_busy(object me);

#define OBJ_PATH "/d/mingjiao/obj"

void create()
{
        set_name(HIR"火爐"NOR, ({ "huo lu", "lu" }) );
        set_weight(9000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是座大火爐，裏面雄火燃燒，可以用來鍊鐵。\n");
                set("unit", "座");
                set("no_get", 1);
        }
}

void init()
{
        add_action("do_tou","tou");
        add_action("do_tou","put");
}

int do_tou(string arg)
{
        object me, ob,kuangshi;
        string item, target; 

        me = this_player();
        ob = this_object();
        
        if( me->is_busy() || query_temp("pending/job_busy", me) )
                return notify_fail("你正忙着呢。\n");

        if (!arg || sscanf(arg, "%s in %s", item, target) != 2 )
            return notify_fail("你要將什麼東西放進哪裏？\n");

        if (item != "礦石" || target != "火爐")
                return notify_fail("你要將什麼東西放進哪裏？\n");

        if ( !kuangshi=present("wujin kuangshi",me) )
                return notify_fail("你身上並沒有礦石。\n");

        if (query_temp("in_use"))
                return notify_fail("這個火爐已經有人在用了！\n");

        message_vision("$N把一"+query("unit", kuangshi)+query("name", kuangshi)+"投進火爐。\n",me);
        destruct(kuangshi);
        message_vision(HIC"$N拉動風箱，火焰由紅慢慢變青，衝起一丈多高！\n"NOR,me);
        
        set_temp("in_use",1);
        set_temp("pending/job_busy", 1, me);
        set_temp("refining", 1, me);

        remove_call_out("burning");
        call_out("burning",3+random(3),me);
        me->start_busy((: check_busy :));

        return 1;
}

void burning(object me)
{
        write(HIW"礦石已經被燒的通紅，看來可以開始錘打了\n"NOR);
        add_action("do_datie","da");
        add_action("do_datie","refine");
        delete_temp("pending/job_busy", me);
}

int do_datie(string arg)
{        
        object me=this_player();

        if( me->is_busy() || query_temp("pending/job_busy", me) )
                return notify_fail("你正忙着呢。\n");

        if (arg != "tie" && arg != "鐵")
                return notify_fail("你要打什麼？\n");

        if (!present("tie chui",me))
                return notify_fail("你沒有鐵錘，用什麼打？\n");

        if( query("neili", me)<50 || query("jingli", me)<50 )
                return notify_fail(RED"你已經精疲力竭了！\n"NOR);

        message_vision("$N揮動大鐵錘，朝着燒紅的鐵礦石狠狠地打了下去！\n",me);
        addn("qi", -30, me);
        set_temp("pending/job_busy", 1, me);

        remove_call_out("job_done");
        call_out("job_done",5+random(10),me);
        me->start_busy( (: check_busy :) );

        return 1;
}

void job_done(object me)
{
        object jingtie;

        if (random(me->query_str()) > 20 || random(10) > 5 )
        {
                message_vision(HIC"經過千錘百煉，精鐵終於煉出來了！$N渾身汗如雨下，幾乎累得喘不過氣來。\n"NOR,me);
                jingtie=new(OBJ_PATH"/jingtie");
                jingtie->move(me);
                remove_action("do_datie","da");
                remove_action("do_datie","refine");
                delete_temp("in_use");
                delete_temp("refining", me);
        }
        else
        {
                tell_object(me,HIR"你擦了擦臉上的汗，看了看礦石，看來還得再打！\n"NOR);
        }
        delete_temp("pending/job_busy", me);
}

int check_busy(object me)
{
        if( query_temp("pending/job_busy", me) )
                return 1;
        return 0;
}
