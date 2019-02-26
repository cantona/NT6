//by daidai

inherit ROOM;
#include <ansi.h>
#define QUESTJINSHE "quest/金蛇劍法/"

void create()
{
        set("short",HIG "練武場" NOR);
        set("long", @LONG
這是温家堡的練武場，一塊空蕩蕩的場地。
LONG);
        set("exits", ([ 
          "out" : "/d/xiangyang/wen/damen",

]));
            set("quest",1);
        setup();
}
void init()
{
  object me,wen1, wen2, wen3, wen4, wen5;
  me = this_player();
  if( query_temp(QUESTJINSHE+"start_kill", me )
         && !me->query_condition("killer")
          && !query(QUESTJINSHE+"pass", me )
          && !query(QUESTJINSHE+"over", me) )
  {
   
     wen1=new(__DIR__"npc/wenfangshan");
     set("kill_id",query("id",  me), wen1);
     wen1->move(environment(me));      
     wen2=new(__DIR__"npc/wenfangwu");
     set("kill_id",query("id",  me), wen2);
     wen2->move(environment(me));        
     wen3=new(__DIR__"npc/wenfangshi");
     set("kill_id",query("id",  me), wen3);
     wen3->move(environment(me));    
     wen4=new(__DIR__"npc/wenfangda");
     set("kill_id",query("id",  me), wen4);
     wen4->move(environment(me));    
     wen5=new(__DIR__"npc/wenfangyi");
     set("kill_id",query("id",  me), wen5);
     wen5->move(environment(me));    
     remove_call_out("killme");
     call_out("killme", 3, me);        
    }      
}
void killme(object me)
{
      if(!me) return;

  if( query_temp(QUESTJINSHE+"start_kill", me )
                 &&!me->query_condition("killer")
                   && !query_temp(QUESTJINSHE+"over", me))//增加一個標記（原來的有點亂了）
   
  {

  }  
}
int valid_leave(object me, string dir)
{
       if (me->is_fighting())
                return notify_fail(RED"\n温家五老大聲喝道：哪裏走。一把攔住你，你竟然無法離開。\n"NOR);
       if (present("heiyi ren",this_object()))
                return notify_fail(RED"\n温家五老大聲喝道：哪裏走。一把攔住你，你竟然無法離開。\n"NOR);
                if(me->query_condition("killer")) 
                          return notify_fail(RED"\n怎麼進來的？？這裏等wiz吧。\n"NOR);
           if( query_temp(QUESTJINSHE+"kill", me )
                && query_temp(QUESTJINSHE+"have_kill", me)){
              delete_temp(QUESTJINSHE+"start_kill", me);
              delete_temp(QUESTJINSHE+"kill", me);
              delete_temp(QUESTJINSHE+"have_kill", me);
    
              }
        return ::valid_leave(me, dir);
}

