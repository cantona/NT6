//Created by Redhat@Sjmud 2009/4/7
//updated by Zhuifeng@SJFY 2010/7/27

inherit ROOM;
#include <ansi.h>
#define QUESTDIR "quest/射鵰英雄傳/風雪驚變/"
void create()
{
	set("short", "楊家小屋");
	set("long", @LONG
這是一座十分清爽的民房，傢俱擺設一應俱全，只是都附着一層灰土。屋
子中間是一張小桌，桌上的杯碗還都沒有撤去，看來主人去的很匆忙。牆上掛
着一杆短柄生了鏽的鐵槍(Tieqiang)。
LONG
	);

	set("item_desc", ([
		"tieqiang" : "一杆用舊了的鐵槍，看起來原來應該有一對的，不知為何只剩了一杆。\n",
	]) );

	set("exits", ([
		"north" : __DIR__"houyuan.c",
	  "south" : __DIR__"qianyuan.c",
	]));

	setup();
}

void init()
{
  object me,obj;
  me = this_player();
  if (me->query(QUESTDIR+"start")
 		 &&!me->query_condition("killer")
		  &&!me->query(QUESTDIR+"over")
		  &&!me->query_temp(QUESTDIR+"have_kill")
     &&!me->query_temp(QUESTDIR+"kill"))
  {
     tell_object(me,HIC"楊鐵心怒氣填膺，開門走出，大聲喝道：“我就是楊鐵心！你們幹甚麼？”兩名兵丁嚇了一跳，丟下火把轉身退開。”\n" 
                       "火光中一名武官拍馬走近，叫道：“好，你是楊鐵心，跟我見官去。拿下了！”四五名兵丁一擁而上。楊鐵心倒轉槍來，\n"NOR+
                    RED"一招“白虹經天”，把三名兵丁掃倒在地，又是一招“春雷震怒”，槍柄跳起一兵，慣入了人堆，喝道：“要拿人，先得説説我犯了甚麼罪。”\n"NOR); 
     message_vision(HIR"\n金兵突然看見$N你衝進來，全體一愣，突然一個金兵甲説道：“敢擋大爺捉拿要犯，給我殺了。”\n"NOR, me);
     obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));      
     obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));        
     obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));    
     remove_call_out("killme");
     call_out("killme", 5, me);        
    }      
}
void killme(object me)
{
	object obj;
  if(!me) return;

  if (me->query(QUESTDIR+"start")
 		 &&!me->query_condition("killer")
 		  &&!me->query_temp(QUESTDIR+"have_kill")
     &&!me->query_temp(QUESTDIR+"kill"))
  {
     obj=new(__DIR__"npc/jinbing");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me)); 
     tell_object(me,HIG"\n\n你只感覺這金兵甲行事為何如此卑鄙，居然不分青紅皂白殺人，不由火氣暴漲，立刻對金兵發動攻擊。\n"NOR); 
     obj->unconcious();
  }  
}
int valid_leave(object me, string dir)
{
       if (me->is_fighting())
                return notify_fail(RED"\n金兵大聲喝道：哪裏走。一把攔住你，你竟然無法離開。\n"NOR);
       if (present("jin bing",this_object()))
                return notify_fail(RED"\n金兵大聲喝道：哪裏走。一把攔住你，你竟然無法離開。\n"NOR);
   		if(me->query_condition("killer")) 
   		          return notify_fail(RED"\n怎麼進來的？？這裏等wiz吧。\n"NOR);
        return ::valid_leave(me, dir);
}

