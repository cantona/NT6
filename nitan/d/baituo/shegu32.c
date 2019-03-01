// Code of ShenZhou
// shegu.c 蛇谷
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "魔鬼灘");
        set("long", @LONG
這是蛇谷中最荒涼恐怖的地帶，地上連一粒石子都沒有。民間傳
說這裡發生過一些奇怪的事情。灘頭四周的樹木都向一邊歪長著，中
心是一塊巨大的凹陷處，似乎有一股巨大的旋風要把你卷進灘坑裡。
LONG );

        set("exits", ([ 
            "west" : __DIR__"shegu_maze3",
        ]));

        if(random(2) == 0)
                set("objects", ([
                    "/clone/money/gold" : 1+random(3),
                ]));

        set("cost", 2);
        set("hide_snake", 1);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49950);
        set("coor/y", 20160);
        set("coor/z", 20);
        setup();
}

void init()
{
        object me = this_player();

        if( query("race", me) == "蛇類")return ;

        set("enter_shegu", 1, me);
        addn("jingli", -7, me);

        me->affect_by("snake_poison",
                    ([ "level" : 300,
                       "id":query("id", me),
                       "duration" :  20 ]));

        if( query("hide_snake") ) {
                remove_call_out("snake_attack");
                call_out("snake_attack", 3+random(3), me); 
                tell_object(me, HIB"你一走進魔鬼灘，登時覺得四面八方傳來極為濃冽的毒氣，異乎尋常……\n"NOR,);
        }
}

void snake_attack(object me)
{
        object snake, here;
        int i;

        here = this_object();
        i = random(12);

        if ( environment(me) != here) return;

        if( time()-query("last_enter", here)>300 )
                addn("hide_snake", 1);

        if ( query("hide_snake") < 1 ) return;

        addn("hide_snake", -1);
        set("last_enter", time());
        
        if( i == 0 ) snake = new(__DIR__"npc/lt_snake");
        else if( i == 11 ) snake = new(__DIR__"npc/cy_snake");
        else snake = new(__DIR__"npc/pu_snake");

        snake->move(here);

        message("vision", HIR"你突然聽見沙沙異聲，一條"+snake->name()+HIR"從魔鬼灘中心土底竄出，伴隨一陣腥風，向"+me->name()+"張口咬去！\n"NOR, environment(me), me);
        tell_object(me, HIR"你耳中忽聞沙沙異聲，猛然警覺，但見一條"+snake->name()+HIR"從魔鬼灘中心土坑竄出，張口向你咬來！\n"NOR);
        COMBAT_D->do_attack(snake,me,query_temp("weapon", snake));
        snake->kill_ob(me);
}
