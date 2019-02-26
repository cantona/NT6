//tangfeng@SJ 2004
//類似擂台的功能
// /d/shaolin/shifang_copy.c
// 復興天下最後一戰，沒有死亡危險，但難度很大

#include <ansi.h>
inherit ROOM;
#define QUESTDIR3 "quest/天龍八部/蕭峯身世篇/"
#define QUESTDIR5 "quest/天龍八部/復興天下篇/"

void create()
{
    set("short", BLU"石坊"NOR);
    set("long", 
"一個巨大的牌坊橫架在兩片山壁之間，牌坊正上方刻着六個斗大的金字：\n"
"\n\t\t\t『"HIY"天下第一名剎"NOR"』\n\n"+
"字跡有些剝落，看上去年代頗為久遠了。前方是一偏很大的廣場，站滿了前來\n"+
"進香的香客和一些江湖上的豪士。象徵着少林寺的山門殿，就矗立在廣場的另\n"+
"一側。\n"
    );

	set("exits", ([
		"north" : __DIR__"guangchang",
		"south" : __DIR__"shijie11",
	]));

	set("outdoors", "shaolin");
  set("no_death", 1);
  set("no_get_from", 1); 
  set("no_sleep_room", 1);
  setup();
}
void init()
{
	object me,ob,obj;
	me = this_player();
	ob = this_object();
	if (!userp(me)) return;
  if(!me->query(QUESTDIR3+"bad") || !me->query_temp(QUESTDIR5+"zhangxing")||me->query_temp(QUESTDIR5+"zhenfa")||ob->query("busy"))
  {
   if(wizardp(me)) tell_object(me,HIR"測試。\n");
  	me->move("/d/shaolin/shifang");
    return;
  }
  if(!present("xiao feng",ob))
  {
  	obj=new("/d/shaolin/npc/tlbb_npc");
  	obj->set("party","gb");
  	obj->set("fight_id",me->query("id"));
  	obj->move(ob);
  	obj->kill_ob(me);
  }
  if(!present("wuming laoseng",ob))
  {
  	obj=new("/d/shaolin/npc/tlbb_npc");
  	obj->set("party","sl");
  	obj->set("fight_id",me->query("id"));
  	obj->move(ob);
  	obj->kill_ob(me);
  }
  ob->set("busy",me->query("id"));
  remove_call_out("check");
  remove_call_out("busy_pass");
  call_out("busy_pass",600); 
  call_out("check",1,me);
}

void pass_busy()
{
	object me,ob = this_object();
  if(ob->query("busy"))
  {
	  if(userp(me = present(ob->query("busy"),ob)) ) 
	  {
       if(!me->query(QUESTDIR3+"bad") || !me->query_temp(QUESTDIR5+"zhangxing"))
       {
  	     me->move("/d/shaolin/shifang");
         return;
       }      
	  }
             ob->delete("busy");
	}
	return;
}
void check(object me)
{
        object ob;
	if(!me || !living(me)||!present(me,this_object())||me->query("qi")<=1||me->query("jing")<=1)  
	{
		remove_call_out("check");
		if((ob=present("xiao feng",this_object())))
		{
	  	 message_vision(HIW"\n$N冷笑一聲，一臉高傲的神態道：“有誰敢小看丐幫絕技。”\n"NOR, ob);
       destruct(ob);
    }
		if((ob=present("wuming laoseng",this_object())))
		{
	  	 message_vision(HIW"\n$N緩緩地道了聲佛號。\n"NOR, ob);
       destruct(ob);
    }
    if(userp(me))
    { 
    	if(present(me,this_object()))
    	{
       	me->remove_all_killer();   	
    		me->reincarnate();
	  	  message_vision(HIW"\n突然一道神光籠罩着$N，$N的精氣神竟然全部恢復了！\n"NOR, me);
        me->move("/d/shaolin/shifang");
    		tell_object(me,HIR"\n還是乖乖呆在少林潛修佛法算了！\n"NOR);
    		message_vision("$N急急忙忙地來到了"+environment(me)->query("short")+"。\n", me);
    	}
   	  me->delete_temp(QUESTDIR5+"zhenfa");
      log_file("quest/TLBB", sprintf("%s(%s)復興天下最後一戰失敗。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );                  
    }
   	remove_call_out("busy_pass");
    this_object()->delete("busy");
	  return;
	}
	if (!present("xiao feng",this_object())&&!present("wuming laoseng",this_object()))
	{
		  remove_call_out("check");
		  me->remove_all_killer(); 

    	me->reincarnate();
	  	message_vision(HIW"\n突然一道神光籠罩着$N，$N的精氣神竟然全部恢復了！\n\n"NOR, me);
		me->move("/d/shaolin/shifang");
		message_vision("$N急急忙忙地來到了"+environment(me)->query("short")+"。\n", me);
		me->set_temp(QUESTDIR5+"zhenfa",1);
		this_object()->delete("busy");
		log_file("quest/TLBB", sprintf("%s(%s)復興天下最後一戰成功。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );                  
    	return;
	}
  call_out("check",1,me);
}
int valid_leave(object me, string dir)
{
   return notify_fail(HIR"你無法離開這裏。\n"NOR);
}
