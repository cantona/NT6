//tangfeng@SJ

#include <ansi.h>
#include <room.h>

inherit ROOM;
#define QUESTDIR2 "quest/天龍八部/天龍營救篇/"

void create()
{
	set("short", HIW"白石路"NOR);
	set("long", @LONG
走進大門，只見紅磚圍牆，白石舖路，從這裡一直通往天王殿，抬頭
望去，寺中亭台樓閣規模宏大，構築精麗，宅地連雲，其氣勢之盛更勝于
五台，普陀等諸處佛門勝地的名山大寺。路旁立滿了無量功德碑，兩邊各
有一小院，院中滿種著鬆竹。
LONG);
	set("outdoors", "天龍寺");
   set("quest",1);
	set("exits", ([             
		"northup" : __DIR__"twd",
		"west" : __DIR__"yz1",
		"east" : __DIR__"yz2",
		"out" : __DIR__"gate",
	]));
	set("objects",([
		__DIR__"npc/liao-huo" : 1,
		__DIR__"npc/wuseng" : 2,
		__DIR__"npc/guest" : 1,
	]));
	setup();
  call_other("/clone/board/tianlong_b", "???");

}
void init()
{
  object me,ob,obj,room;
  me = this_player();
  ob = this_object();
  if (me->query(QUESTDIR2+"start")
     &&me->query_temp(QUESTDIR2+"jiumozhi")
     &&!me->query_temp(QUESTDIR2+"kill_dizi")
     &&!me->query(QUESTDIR2+"over")
     &&!me->query_condition("killer"))
  {
  	//如果有其他玩家在做quest，取消quest，但補償機會
    if(ob->query("busy_id"))
    {
	    if (!(room = find_object(__DIR__"road_copy")))
			room = load_object(__DIR__"road_copy");
		if(!room)
		{
			me->delete_temp("quest/天龍八部");
			me->delete_temp("quest/busy");//任務沖突標志取消 
			//補償玩家機會
			me->delete("quest/天龍八部/time");
			me->delete("quest/天龍八部/combat_exp");  
			tell_object(me,HIR"\n你發現似乎有些問題，你可以詢問巫師。\n");
			log_file("quest/TLBB", sprintf("%s(%s)缺少road_copy.c文件。\n", me->name(1),me->query("id")) );	
			return;
		}
		if(room
			&& ((obj=present(ob->query("busy_id"),room))|| (obj=present(ob->query("busy_id"),ob))) && obj!=me)
		{
			if(present(obj,ob)) message_vision(HIR"\n$N對$n點了點頭。\n",obj,me);
			else message_vision(HIR"\n遠處的山路傳來一陣輕嘯，$N隱約聽得有打鬥的聲音。原來是"+obj->query("family/family_name")+HIR"弟子"+obj->query("name")+HIR"。\n",me);
			tell_object(me,HIY"有"+obj->query("family/master_name")+HIY"座下高徒"+obj->query("name")+HIY"來保護天龍寺，也不犯你出手了。"NOR);
			me->delete_temp("quest/天龍八部");
			me->delete_temp("quest/busy");//任務沖突標志取消 
			log_file("quest/TLBB", sprintf("%s(%s)因為%s(%s)沖突，天龍寺失敗。\n", me->name(1),me->query("id"),obj->name(1),obj->query("id")) );
			//補償玩家機會
			me->delete("quest/天龍八部/time");
			me->delete("quest/天龍八部/combat_exp");  
			return;  
		}
	}
	ob->set("busy_id",me->query("id"));
	me->start_busy(1);
	remove_call_out("go");
	call_out("go", 1,me);   
  }      
}

void go(object me)
{
  object room,ob;
  ob = this_object();
  remove_call_out("go");
  if(!me) 
  {
  	ob->delete("busy_id");
  	return;
  }
  if(!present(me,this_object())) 
  {
	  tell_object(me,HIY"\n讓你保護天龍寺，為何四處亂走？\n"NOR);
	  tell_object(me,HIY"站位錯誤；任務失敗！！\n"NOR);
	  me->delete_temp("quest/天龍八部");
	  me->delete_temp("quest/busy");//任務沖突標志取消 
	  log_file("quest/TLBB", sprintf("%s(%s)天龍寺站位不對，失敗。\n", me->name(1),me->query("id")) );
	  me->delete(QUESTDIR2+"start");
	  ob->delete("busy_id");
	  return;
  }
  if (!(room = find_object(__DIR__"road_copy")))
        room = load_object(__DIR__"road_copy");
  if(!room)
  {
	  tell_object(me,HIY"\n遠處的山路傳來一陣輕嘯，隱約聽得有打鬥的聲音。\n"NOR);
	  tell_object(me,HIY"但是你總是無法找到正確的地點。可以詢問巫師。\n"NOR);
	  me->delete_temp("quest/天龍八部");
	  me->delete_temp("quest/busy");//任務沖突標志取消 
      ob->delete("busy_id");
	  //補償玩家機會
 	  me->delete("quest/天龍八部/time");
	  me->delete("quest/天龍八部/combat_exp");  
  	  log_file("quest/TLBB", sprintf("%s(%s)天龍寺缺少road_copy.c文件。\n", me->name(1),me->query("id")) );
	  return;
  }
  if(room->query("busy_id"))
  {
    tell_object(me,HIY"\n遠處的山路傳來一陣輕嘯，隱約聽得有打鬥的聲音。\n"NOR);
	tell_object(me,HIY"你還是耐心地等待吧。\n"NOR);
    call_out("go", 5,me);   
  }
  else 
  {
  	me->move(room);
	ob->delete("busy_id");
  	log_file("quest/TLBB", sprintf("%s(%s)天龍寺防御站開始戰鬥。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
  }
}
int valid_leave(object me, string dir)
{
		
	if ( me->query("family/family_name") != "天龍寺" 
	 && dir != "out" 
	 && me->query("shen") < 0
	 && objectp(present("liaohuo chanshi", environment(me))))
		return notify_fail("了惑禪師攔住你，說道：天龍寺內不得隨意進出。\n");

	if ( me->query("family/family_name") != "天龍寺" 
	 && dir != "out" 
	 && me->query("shen") < 0
	 && objectp(present("wu seng", environment(me))))
		return notify_fail("武僧攔住你，說道：天龍寺內不得隨意進出。\n");
	return ::valid_leave(me, dir);
}
