//tangfeng@SJ 2004
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "左營");
	set("long", @long
這裏是南院左營，眾多會議和軍事部署都是這裏進行的，是契丹的核
心地帶，有重兵把守。
long);
	set("exits", ([
                "east" : __DIR__"zhongying",
	]));
   set("outdoors", "西域");
   set("quest",1);
   setup();
}
void init()
{
  object me,obj1,obj2;
  me = this_player();
 if(me->query_condition("killer"))
  {
   message_vision(HIC"\n突然$N似乎氣血有些不順，跟着一個趔趄倒了下去。\n"NOR,me); 
   tell_object(me,HIR"你突然感到一股力量吸引着你，瞬間你失去知覺。\n"NOR);
   tell_room(environment(me),HIR"\n只見，地上突然出現一個裂洞，"+ me->name()+ "一頭紮了下去，瞬間消失。\n"NOR, ({  }));
   me->move(__DIR__"shanlu1"); 
   tell_room(environment(me), HIR"\n半空中，似乎一個人掉了下來，你定眼一看竟然是"+ me->name()+ "。\n"NOR, ({  }));
   me->unconcious();
   return;
  }
  if(!me->query("quest/天龍八部/大遼救援篇/start")) return;
   if(me->query("quest/天龍八部/大遼救援篇/over")) return; 
  if(!me->query_temp("quest/天龍八部/大遼救援篇/godaliao")) return; 
 
  obj1=new(__DIR__"npc/liaobing");
  obj1->set("teamleader",1);
  obj1->set("fight_id",me->query("id"));
  obj1->move(environment(me)); 
  if(obj1->query_skill("wuxing-zhen")<200)
     obj1->set_skill("wuxing-zhen",200);
  obj1->command("lineup form wuxing-zhen");

  obj2=new(__DIR__"npc/liaobing");
  obj2->set("party","sl");
  obj2->set("fight_id",me->query("id"));
  obj2->move(environment(me)); 
  if(obj2->query_skill("wuxing-zhen")<200)
     obj2->set_skill("wuxing-zhen",200);
  obj1->command("lineup with "+obj2->query("id"));
  obj2->command("lineup with "+obj1->query("id"));  
  add_action("do_push","push");

}

int do_push(string arg)
{
  object me,obj;
  int skill;
  me = this_player();
  skill = me->query_skill("force");
  if ( arg != "anshi" && arg != "anmen" ) return 0;
  if (me->is_fighting())return 0;
  if (skill<100)
  {
	  message_vision("$N猛吸一口氣，用力推了推暗室，可是依然紋絲不動，看來還需要再練練才行。\n", me);
	  return 1;
  }
  if(!me->query_temp("quest/天龍八部/大遼救援篇/dianhuo"))
  {
	  obj=new(__DIR__"npc/liaobing");
	  obj->set("teamleader",1);
	  obj->set("fight_id",me->query("id"));
	  obj->move(environment(me)); 
	  tell_object(me,HIR"\n暗室之外，御營親兵，層層包圍。你剛要推開暗室，邊上又跳過一個遼兵。\n"NOR);
	  return 1;
  }
  if(present("liao bing",this_object()))
  {
	  tell_object(me,HIR"\n還是先解決遼兵，再來開這暗室。\n"NOR);
	  return 1;
  }
  if( !query("exits/west") ) {
 	   message_vision("$N猛吸一口氣，用力推了推暗室，竟然打開一條通向暗室的通道。\n", me);
	   log_file("quest/TLBB", sprintf("%s(%s)找到暗室，特此紀錄。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) ); 
     set("exits/west", __DIR__"anshi");
     remove_call_out("close_path");
     call_out("close_path", 15);
  }	
  return 1;
}	
void close_path()
{
        if(!query("exits/west")) return;
        message("vision","一會會，嗵的一聲，牆又恢復原樣。\n", this_object() );
        delete("exits/west");      
}

int valid_leave(object me, string dir)
{
  if(present("liao bing",environment(me)))  return notify_fail("遼兵一把將你攔住：哪裏跑！\n" );
  return ::valid_leave(me, dir);
}
