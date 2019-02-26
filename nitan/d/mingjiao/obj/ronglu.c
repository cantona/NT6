// Code of JHSH
// ronglu.c 熔爐

#include <ansi.h>
inherit ITEM;

int check_busy(object me);

#define OBJ_PATH "/d/mingjiao/obj"

void create()
{
        set_name(HIR"熔爐"NOR, ({ "rong lu", "lu" }) );
        set_weight(9000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是座大熔爐，裏面烈火燃燒，是用來打造火槍的。\n");
                set("unit", "座");
                set("value", 1);
                set("no_get", 1);
        }
}

void init()
{
        add_action("do_fang","fang");
        add_action("do_fang","put");
}

int do_fang(string arg)
{
        object me, ob, jingtie;
        string item, target; 

        me = this_player();
        ob = this_object();
        
        if( me->is_busy() || query_temp("pending/job_busy", me) )
                return notify_fail("你正忙着呢。\n");

        if (!arg || sscanf(arg, "%s in %s", item, target) != 2 )
            return notify_fail("你要將什麼東西放進哪裏？\n");

        if (item != "精鐵" || target != "熔爐")
                return notify_fail("你要將什麼東西放進哪裏？\n");

        if ( !jingtie=present("jing tie",me) )
                return notify_fail("你身上並沒有精鐵。\n");

        if (query_temp("in_use"))
                return notify_fail("這個火爐已經有人在用了！\n");

        message_vision("$N把一"+query("unit", jingtie)+query("name", jingtie)+"放進熔爐。\n",me);
        destruct(jingtie);
        message_vision(HIR"$N放進燃料，拉起風箱，頃刻間就生起一爐熊熊大火！\n"NOR,me);
        
        set_temp("in_use",1);
        set_temp("pending/job_busy", 1, me);
        set_temp("gun_making", 1, me);

        remove_call_out("burning");
        call_out("burning",10+random(5),me,0);
        me->start_busy((: check_busy :));

        return 1;
}

void burning(object me, int stage)
{
        string *burning_msg=({
                HIC"爐火由紅慢慢變青。\n"NOR,
                HIW"爐火由青漸漸轉白。\n"NOR,
                HIW"精鐵"+HIR"已經開始溶化了。\n"NOR,
                HIW"精鐵"+HIR"已經全部溶化了，可以倒進模子了。\n"NOR,
        });

        message_vision(burning_msg[stage],me);
        
        if (stage != 3)
        {
                remove_call_out("burning");
                call_out("burning",10+random(5),me,++stage);
        }
        else
        {
                add_action("do_pour","dao");
                add_action("do_pour","pour");
                delete_temp("pending/job_busy", me);
                set_temp("pouring", 1, me);
        }

}

int do_pour(string arg)
{        
        string item, target;
        int busy_time=0;
        object me=this_player();


        if( me->is_busy() || query_temp("pending/job_busy", me) )
                return notify_fail("你正忙着呢。\n");

        if (!arg || sscanf(arg, "%s in %s", item, target) != 2 )
            return notify_fail("你要將什麼東西倒進哪裏？\n");

        if (item != "鐵水" || target != "火槍模子")
                return notify_fail("你要將什麼東西放進哪裏？\n");

        if (!present("huoqiang muzi",environment(this_object())) )
                return notify_fail("這裏沒有火槍模子。\n");

        if( !query_temp("pouring", me) )
                return notify_fail("好像還沒輪到你吧。\n");

        if( query("jing", me)<100 || query("qi", me)<100 )
                return notify_fail(RED"你已經精疲力竭了！\n"NOR);

        message_vision("$N用土勺把溶化的鐵水小心翼翼的從爐子裏盛出來，慢慢的倒進火槍模子裏。\n",me);
        if (random(10) > 3)
        {
                message_vision("糟糕！$N一不小心，幾滴鐵水濺到了腳上，痛得$N哇哇大叫!\n",me);
                me->receive_wound("qi",100);
                busy_time=3;
        }
        addn("jing", -60, me);
        addn("neili", -80, me);

        busy_time=busy_time+1;
        me->start_busy(busy_time);

        remove_action("do_pour","pour");
        remove_action("do_pour","dao");
        add_action("add_xiaohuang","add");

        return 1;
}

int add_xiaohuang(string arg)
{        
        string item, target;
        object xiaohuang;
        object me=this_player();

        if( me->is_busy() || query_temp("pending/job_busy", me) )
                return notify_fail("你正忙着呢。\n");

        if (!arg || sscanf(arg, "%s in %s", item, target) != 2 )
            return notify_fail("你要將什麼東西放進哪裏？\n");

        if (item != "硝磺" || target != "火槍模子")
                return notify_fail("你要將什麼東西放進哪裏？\n");

        if (!(xiaohuang=present("xiaohuang shi",me)) )
                return notify_fail("你身上並沒有硝磺石。\n");

        if (!present("huoqiang muzi",environment(this_object())) )
                return notify_fail("這裏沒有火槍模子。\n");

        if( !query_temp("pouring", me) )
                return notify_fail("好像還沒輪到你吧。\n");

        if( query("qi", me)<50 || query("jing", me)<50 )
                return notify_fail(RED"你已經精疲力竭了！\n"NOR);

        message_vision("$N往火槍模子裏添了一些硝磺。\n",me);
        destruct(xiaohuang);

        addn("jing", -30, me);

        me->start_busy(1);

        remove_action("add_xiaohuang","add");
        remove_call_out("job_done");
        call_out("job_done",5+random(10),me);

        return 1;
}

void job_done(object me)
{
        object huoqiang;

        message_vision("$N揭開模子，看來鐵水已經凝固。$N澆上一盆冷水，"+
                        "只聽哧哧聲響，一陣刺鼻的濃煙過後，火槍已經制成。\n",me);
        huoqiang=new(OBJ_PATH"/huoqiang");
        huoqiang->move(me);
        remove_action("add_xiaohuang","add");
        delete_temp("in_use");
        delete_temp("gun_making", me);
        me->start_busy(3);

}

int check_busy(object me)
{
        if( query_temp("pending/job_busy", me) )
                return 1;
        return 0;
}
