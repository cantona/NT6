//Cracked by Kafei
//music.h 樂器
#include <ansi.h>

int do_lianxi(string arg)
{
        string msg;
        object ob, me, where, weapon;
        int cost;

        string* zither_msg = ({
        "輪指","瑣","滾拂","撥刺","進退","吟猱","綽注",
        "兩引上","罨","帶起","撮指","打圓","抹挑","勾剔",
        });

        string* flute_msg = ({
        "顫指", "吐音", "歷音","花舌音", "飛指顫音",
        });

        me = this_player();
        where = environment(me);
        weapon=query_temp("weapon", me);
        if( query("pigging", where) )
                return notify_fail("你還是專心拱豬吧！\n");

        if( query("sleep_room", where) )
                return notify_fail("在睡房裡不能練習演奏樂器，這會影響他人。\n");

        if( query("no_fight", where) )
                return notify_fail("這裡不適合練習演奏樂器。\n");

        if (me->is_busy())
                return notify_fail("你現在正忙著呢。\n");

        if( me->is_fighting() )
                return notify_fail("你無法在戰鬥中專心下來練習演奏！\n");

        if(!arg || !objectp(ob = present(arg, me)) )
                return notify_fail("你要練習演奏什麼？\n");

        if( !query("shape", ob) || 
        (query("shape", ob) != "flute" && query("shape", ob) != "zither") )
                return notify_fail("你不能練習演奏"+ob->name()+"。\n");

        if( ob != weapon )
                return notify_fail("你必需先裝備"+ob->name()+"。\n");

        if( (int)me->query_skill("music", 1) < 10 ) {
                if( query("shape", ob) == "zither" )
                message_vision("$N手撫$n，彈了幾下，所成調子嚴重走音。\n"NOR, me, ob);
                if( query("shape", ob) == "flute" )
                message_vision("$N將$n放在唇邊一吹，結果發出一陣五音不全的聲響。\n"NOR, me, ob);
                return 1;
        }

        if( query("potential", me)<1 )
                return notify_fail("你的潛能已達極限，沒有辦法領悟更精妙的樂理。\n");


        cost=50+random(40)*(40-query("int", me))/20;
        if (cost < 10) cost = 10; // minimum cost

        if( query("jing", me)>cost){
                if( query("shape", ob) == "zither"){
                msg = zither_msg[random(sizeof(zither_msg))] ;
                message_vision("$N手撫$n，反覆練習著「"+msg+"」的技巧。\n"NOR, me, ob);
                if( query("family/family_name", me) == "桃花島" && me->query_skill("music",1)<333 )
                me->improve_skill("music", me->query_int()*2 + 1);
                }
                else if( query("shape", ob) == "flute"){
                msg = flute_msg[random(sizeof(flute_msg))] ;
                message_vision("$N手按$n，徐徐吹奏，專心練習著「"+msg+"」的技巧。\n"NOR, me, ob);
                if( query("family/family_name", me) == "桃花島" && me->query_skill("music",1)<333 )
                me->improve_skill("music", me->query_int()*2 + 1);

                }
                else return notify_fail("你左看看，右看看，實在不知道該怎麼演奏"+ob->name()+"。\n");
                }
        else {
                cost=query("jing", me);
                if (cost < 0) cost = 0;
                write("你現在過于疲倦，無法專心下來練習演奏樂器。\n");
                return 1;
        }

        me->receive_damage("jing", cost/2, "心力絞瘁死了");
        addn("jingli", -cost/4, me);
        if( random(3) == 0)addn("potential", -random(2), me);
        return 1;
}