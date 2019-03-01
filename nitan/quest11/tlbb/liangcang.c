inherit ROOM;
#include <ansi.h>
int do_jump(string arg);
int do_dianhuo(string arg);
void create()
{
    set("short", "後倉");
    set("long", @LONG
　　這是蒙古大軍的囤糧之所，所謂兵馬未動，糧草先行，
這裡的糧食和草料堆積如山。一隊隊巡邏兵來回守衛，戒備
森嚴。
LONG);
	set("quest",1);
	set("exits", ([
		//"west" : __DIR__"sleep_room",
			"south" : __DIR__"zhongying",
        ]));
    setup();
}



int valid_leave(object me, string dir)
{
  if(present("liao bing",environment(me)))  return notify_fail("遼兵一把將你攔住：哪裡跑！\n" );
  return ::valid_leave(me, dir);
}
void init()
{
  object me,obj;
  me = this_player();
  if(me->query_condition("killer"))
  {
   message_vision(HIC"\n突然$N似乎氣血有些不順，跟著一個趔趄倒了下去。\n"NOR,me); 
   tell_object(me,HIR"你突然感到一股力量吸引著你，瞬間你失去知覺。\n"NOR);
   tell_room(environment(me),HIR"\n只見，地上突然出現一個裂洞，"+ me->name()+ "一頭紮了下去，瞬間消失。\n"NOR, ({}));
   me->move(__DIR__"shanlu1"); 
   tell_room(environment(me), HIR"\n半空中，似乎一個人掉了下來，你定眼一看竟然是"+ me->name()+ "。\n"NOR, ({}));
   me->unconcious();
   return;
  }
  add_action("do_jump", ({"jump","tiao"}));
  if(!me->query("quest/天龍八部/大遼救援篇/start")) return;
  if(me->query("quest/天龍八部/大遼救援篇/over")) return; 
  if(!me->query_temp("quest/天龍八部/大遼救援篇/godaliao")) return; 
  

  obj=new(__DIR__"npc/liaobing");
  obj->set("teamleader",1);
  obj->set("fight_id",me->query("id"));
  obj->move(environment(me)); 
  add_action("do_dianhuo", ({"dianhuo","burn"}));
}
int do_jump(string arg)
{
	object me;
	me = this_player();
	message_vision(HIC"$N看準了牆邊一堆糧草，一躍而上，順勢在糧草輕輕一點，身子又飄出許尺。\n"NOR, me);
	me->move("/d/xingxiu/daliao/shulin");
	message_vision(HIC"$N一躍而起，環顧四周，這裡竟然就是遼營的門前那片樹林。\n"NOR, me);
	me->start_busy(1);
	return 1;
} 
int do_dianhuo(string arg)
{
	object me, ob,*obj;
	int i;
	me = this_player();
	ob = this_object();
	if (!me) return 0;
	if(!me->query_temp("quest/天龍八部/大遼救援篇/godaliao")) return 0; 
	if (present("liao bing", ob))
		return notify_fail("遼兵就在這裡，先解決掉遼兵再說。\n");
	if (me->is_busy() || !arg )
		return notify_fail("你等等想好了燒什麼再說。\n");    
	if (arg!="liang cao" && arg!="liangcao" && arg!="cao" )
		return notify_fail("你等等想好了燒什麼再說。\n"); 
	if(me->query_temp("quest/天龍八部/大遼救援篇/dianhuo"))
		return notify_fail(HIR"火勢已經上來，趕快離開這裡去搭救蕭峰。\n"NOR);    

	//只能一個人做
	obj = users();
	i = sizeof(obj);
	while(i--) {
		if ( obj[i]->query_temp("quest/天龍八部/大遼救援篇/dianhuo") && obj[i]!=me) 
		{
			me->delete_temp("quest/天龍八部");
			me->delete_temp("quest/busy");//任務沖突標志取消
			me->delete("quest/天龍八部/time");
			me->delete("quest/天龍八部/combat_exp");
			me->move(__DIR__"shanlu1"); 
			tell_object(me,HIR"已經有"+obj[i]->query("name")+RANK_D->query_respect(obj[i]) +"點火營救去了，不需要你了。\n"NOR);
			log_file("quest/TLBB", sprintf("%s(%s)解救蕭峰點火，但和%s(%s)沖突失敗。經驗：%d。\n", me->name(1),me->query("id"), obj[i]->name(1),obj[i]->query("id"), me->query("combat_exp")) ); 
			return 1;  
		}
	}
	message_vision(HIC"\n$N悄悄轉到糧草陰處，點起一把火，迅速竄到另外一個角落，用契丹話大叫：“走水啦！走水啦！”。果然，營中立即一團混亂，\n"
		             +"$N只要見到沒有遼兵的地方，就是一把火，霎時間燒起了七八個火頭。\n"NOR, me);
	message_vision(HIY"\n$N忽見東邊狼煙沖天而起，那正是遼兵追來的訊號。$N心頭一凜，還是趕快離開，去營救蕭峰得好。 \n\n"NOR, me);
	log_file("quest/TLBB", sprintf("%s(%s)大遼點火成功。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) ); 
	me->set_temp("quest/天龍八部/大遼救援篇/dianhuo",1);
	me->start_busy(1);
	return 1;
} 
