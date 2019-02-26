// tangfeng@SJ 2004

#include <ansi.h>
#include <room.h>

inherit ROOM;
#define QUESTDIR3 "quest/天龍八部/蕭峯身世篇/"
#define QUESTDIR4 "quest/天龍八部/大遼救援篇/"
#define QUESTDIR5 "quest/天龍八部/復興天下篇/"

void create()
{
	set("short", "暗室");
	set("long", @LONG
誰能料到大遼營地居所背後有這等一個暗室，不知道平時做何用處。
LONG
	);
           set("quest",1);
	setup();
}
void init()
{
  object me,obj;
  me = this_player();
  me->start_busy(1);
  if (me->query(QUESTDIR4+"start")
     &&me->query_temp(QUESTDIR4+"kill")
     &&!me->query_temp(QUESTDIR4+"breakmen")
     &&!me->query(QUESTDIR4+"over"))
  {
     obj=new("/d/nanyang/npc/xiaofeng");
     if(!present("xiao feng", environment(me)))
                 obj->move(environment(me));     
     me->set_temp(QUESTDIR4+"breakmen",1);   
  }      
    add_action("do_push", "push");
}

int do_push(string arg)
{
        if( arg == "wall" || arg == "牆" || arg == "牆邊")
        {
        message_vision("$N推開這堵牆，打開出口。\n", this_player());
        if( !query("exits/east") ) {
       set("exits/south", __DIR__"zuotang");
        remove_call_out("close_path");
        call_out("close_path", 15);
        }
        return 1;
        }
}
void close_path()
{
        if( !query("exits/east") ) return;
        message("vision","一會會，嗵的一聲，牆又恢復原樣。\n", this_object() );
        delete("exits/east");
}
