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
		__DIR__"npc/wuseng" : 2,
		__DIR__"npc/guest" : 1,
	]));
	setup();
}
void init()
{
  object me;
  me = this_player();
  if (me->query(QUESTDIR2+"start")
     &&me->query_temp(QUESTDIR2+"jiumozhi")
     &&!me->query_temp(QUESTDIR2+"kill_dizi")
     &&!me->query(QUESTDIR2+"over")
     &&!this_object()->query("busy_id"))
  {
     me->start_busy(1);
     message_vision(HIR"\n本來就人丁稀少的天龍寺今日更顯得無比蕭殺。$N臉上露出擔心的神色。\n",me);
     tell_object(me,HIB"你料想這場戰鬥定是非同小可，而這白石路，更是通往內堂的必經之路。\n"NOR); 
     this_object()->set("busy_id",me->query("id"));
     remove_call_out("killme");
     call_out("killme", 20, me);   
  }      
}
void killme(object me)
{
	object obj;
  if(!me) return;
  if(!present(me,this_object())) 
  {
    tell_object(me,HIG"你竟然不在白石路，也算你臨陣逃脫，逃過一劫。只是你的江湖名望大幅下降。\n"NOR); 
    me->delete_temp("quest/天龍八部");
	me->delete_temp("quest/busy");//任務沖突標志取消 
    me->delete(QUESTDIR2+"start");
    me->add("mana",-random(300)-200);
    if(me->query("mana")<0) me->set("mana",0);
    this_object()->delete("busy_id");
	log_file("quest/TLBB", sprintf("%s(%s)沒有一直呆在白石路，失敗。\n", me->name(1),me->query("id")) );
  	return;
  }
  if(me->query_condition("killer"))
  {
    tell_object(me,HIG"這段時間內，你竟然不專心看守白石路，本因不再放心你了，另外你的江湖名望大幅下降。\n"NOR); 
    me->delete_temp("quest/天龍八部");
    me->delete(QUESTDIR2+"start");
	me->delete_temp("quest/busy");//任務沖突標志取消 
    me->add("mana",-random(300)-200);
    if(me->query("mana")<0) me->set("mana",0);
    this_object()->delete("busy_id");
	log_file("quest/TLBB", sprintf("%s(%s)quest期間變成tjf，失敗。\n", me->name(1),me->query("id")) );
  	return;
  }
     obj=new(__DIR__"npc/dlsdizi");
     obj->set("kill_id",me->query("id"));
     obj->set("type",1);
     obj->move(environment(me)); 
     obj->set_leader(me);
     obj=new(__DIR__"npc/dlsdizi");
     obj->set("kill_id",me->query("id"));
     obj->set("type",2);
     obj->move(environment(me)); 
     obj->set_leader(me);
     obj=new(__DIR__"npc/dlsdizi");
     obj->set("kill_id",me->query("id"));
     obj->set("type",3);
     obj->move(environment(me)); 
     obj->set_leader(me);

     //玩家之間避免沖突
     remove_call_out("busy");
     call_out("busy", 1); 
	 return;
}
void busy()
{
	object ob;
	ob=this_object();
	if(!ob->query("busy_id")) return;
    if(present(ob->query("busy_id"),ob)) call_out("busy", 1);   
	else ob->delete("busy_id");
}
int valid_leave(object me, string dir)
{
	if (me->query(QUESTDIR2+"start")
     &&me->query_temp(QUESTDIR2+"jiumozhi")
     &&!me->query_temp(QUESTDIR2+"kill_dizi")
     &&!me->query(QUESTDIR2+"over"))
		return notify_fail(RED"不要亂跑，還是專心點救援天龍寺。\n"NOR);
		
  if(me->is_fighting()) return notify_fail(RED"不要亂跑，還是專心點救援天龍寺。\n"NOR);	
  
	if ( me->query("family/family_name") != "天龍寺" 
	 && dir != "out" 
	 && me->query("shen") < 0
	 && objectp(present("wu seng", environment(me))))
		return notify_fail("武僧攔住你，說道：天龍寺內不得隨意進出。\n");
	return ::valid_leave(me, dir);
}
