// 花圃 huapu1.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "花圃");
        set("long", @LONG
這裏是蝴蝶谷的花圃，是『見死不救』胡青牛用來種各種各樣藥
材的，裏面種滿了諸般花草。
LONG );

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
                "west" : __FILE__,
                "east" : __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
        ]));

        setup();
}

void init()
{
        object ob;
        int jing, jing_cost;

        ob = this_player();
        jing=query("jing", ob);
        jing_cost=random(query("kar", ob))*2+10;

        addn("jing", -jing_cost, ob);
        if(jing < jing_cost)
         ob->unconcious();
}

int valid_leave(object me, string dir)
{
        if (random(10) > 5)
              addn_temp("mark/steps", 1, me);
        if (random(10) < 5)
              addn_temp("mark/steps", -1, me);
        
        if( query_temp("mark/steps", me) >= 5){
            me->move(__DIR__"caojing");
            delete_temp("mark/steps", me);
              return notify_fail("你亂走一氣，忽然眼前一亮，來到一處草徑。\n");
        }  
        if( query_temp("mark/steps", me) <= 0){
            me->move(__DIR__"niupeng");
            delete_temp("mark/steps", me);
              return notify_fail("你累得半死，卻頹然發現又走回了牛棚。\n");
        }      
        return ::valid_leave(me, dir);
}