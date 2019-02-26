// Room: /d/nanyang/dating.c
// Lklv Modify 2001.10.11
// Tangfeng@SJ 2004

#include <ansi.h>
inherit ROOM;

#define QUESTDIR3 "quest/天龍八部/蕭峯身世篇/"

void xiaofeng1(object me);
void xiaofeng2(object me);
void xiaofeng3(object me);
int do_action(string arg);
int do_jiejiu(string arg);
void copy_person(object ob,int i);
void destruct_person(object ob);
void set_person(object obj1,object obj2,int i);

void create()
{
        set("short", "聚賢莊大廳");
        set("long", @LONG
這是聚賢莊的大廳，大廳內很寬敞，放着幾十張桌子。東首主位的桌子旁
放有三把黑色的太師椅，其中一個椅子上坐着一箇中年男子。他身後的牆上掛
有兩副圓盾、一柄單刀，一杆短槍。
LONG
        );
		set("quest",1);
		set("exits", ([
		"south" : __DIR__"jxzhuang",
		"east" : __DIR__"houyuan",
	]));
	
	set("objects",([
		__DIR__"npc/youju" : 1,
		__DIR__"npc/youji" : 1,
        ]));
	
	setup();
}
void init()
{
  object me,obj;
  me = this_player();
  if (!me->query(QUESTDIR3+"start")) return;
  if (!me->query_temp(QUESTDIR3+"kill")) return;
  if (me->query(QUESTDIR3+"over")) return;
  if (me->query_temp(QUESTDIR3+"jxzhuang")) return;
  if (me->query_temp(QUESTDIR3+"help")) return;
  if (this_object()->query("busy")) 
  {
	  me->move("/d/nanyang/jxzhuang");
	  message_vision(HIR "\n$N發現聚賢莊內打鬥越來越激烈，刀劍無眼，還是走為上策！\n" NOR, me);
	  return;
  }
  if (me->query_condition("killer")) 
  {
	  me->move("/d/nanyang/jxzhuang");
  	  message_vision(HIR "\n$N發現聚賢莊內打鬥越來越激烈，刀劍無眼，還是走為上策！\n" NOR, me);
	  return;
  }
  me->start_busy(2);
  me->set_temp(QUESTDIR3+"jxzhuang",1);
  copy_person(this_object(),3);//複製情節人物，3是用來控制蕭峯有普通招數，其他npc只有絕招  
  obj=present("xiao feng", this_object());
  tell_object(me,HIG"\n你走進大廳內，果然一片混亂。大廳上聚集着三百餘人，大家擠在一團，真能捱到蕭峯身邊的，不過五六人而已，\n"
                      "刀槍劍戟四下舞動，一大半人倒要防備為自己人所傷。\n"NOR); 
  message_vision(HIR "\n$N微一凝神，運起混天氣功，全身骨節發出一陣爆豆般的聲響。\n" NOR, obj);
  remove_call_out("xiaofeng1");
  remove_call_out("busy");
  //避免玩家quest混亂
  this_object()->set("busy",1);
  call_out("busy", 1200);   
  call_out("xiaofeng1",10, me);  
  log_file("quest/TLBB", sprintf("%s(%s)聚賢莊大混亂開始。經驗%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
  add_action("do_action", ({"dazuo", "tuna", "lian", "learn", "du", "guard","steal","kill", "hit", "fight", "throw", "ansuan"}));  
  add_action("do_jiejiu", ({"help","bangzhu","jiejiu", "save"}));
}
void xiaofeng1(object me)
{
	object obj;
	if(!me) return;
	if (!me->query(QUESTDIR3+"start")) return;
	if (!me->query_temp(QUESTDIR3+"kill")) return;
	if (me->query(QUESTDIR3+"over")) return;
	if (me->query_temp(QUESTDIR3+"help")) return;
	if(!present(me,this_object())) 
	{
		tell_object(me,HIG"\n你這種情況竟然臨陣逃脱，實在違背俠義之情。你的江湖威望大幅下降。\n"NOR); 
		me->delete_temp("quest/busy");//任務系統衝突標誌
		me->delete_temp("quest/天龍八部");   
		me->delete(QUESTDIR3+"start");
		me->add("mana",-200);
		if(me->query("mana")<0) me->set("mana",0);
		destruct_person(this_object());//消除所有人物
		return;
	}
	copy_person(this_object(),1);//複製情節人物  ,1是最激烈的戰鬥
	obj=present("xiao feng", this_object());
    message_vision(HIG"\n\n$N果然了得，手掌揚處，砰砰兩聲，又有兩人中了劈空拳倒地，隨勢衝入人羣，肘撞拳擊，掌劈腳踢，霎時間又打倒數人。\n\n"NOR, obj);
    message_vision(HIG"$N對着$n冷笑一聲。\n\n"NOR, obj,me);
	remove_call_out("xiaofeng2");
	call_out("xiaofeng2",20, me);   
	return;
}
void xiaofeng2(object me)
{
  object obj1,obj2;
  if(!me) return;
  if (!me->query(QUESTDIR3+"start")) return;
  if (!me->query_temp(QUESTDIR3+"kill")) return;
  if (me->query(QUESTDIR3+"over")) return;
  if (me->query_temp(QUESTDIR3+"help")) return;
  if(!present(me,this_object())) 
  {
	  tell_object(me,HIG"\n你這種情況竟然臨陣逃脱，實在違背俠義之情。你的江湖威望大幅下降。\n"NOR); 
	  me->delete_temp("quest/busy");//任務系統衝突標誌
	  me->delete_temp("quest/天龍八部");   
	  me->delete(QUESTDIR3+"start");
	  me->add("mana",-200);
	  if(me->query("mana")<0) me->set("mana",0);
	  destruct_person(this_object());//消除所有人物
	  return;
  }
  copy_person(this_object(),0);//複製情節人物 ,0讓所有的人物戰鬥停止
  obj1=present("xiao feng", this_object());
  obj2=present("xuan nan", this_object());
  tell_object(me,HIY"\n一會工夫，大廳情況發生變化。卻見中央讓出一塊空地，只見少林高僧玄難緩步而前，本來是數十人圍攻喬\n"
                      "峯的局面，玄難這一出手，餘人自覺在旁夾攻反而礙手礙腳，自然而然的逐一退下，各人團團圍住，以防喬\n"
                      "峯逃脱，凝神觀看玄難和他決戰。\n"NOR);                    
  message_vision(HIY"\n$N突然深吸一口氣，目露慈光，面帶微笑，內力運轉，竟使全身上下寶光流動，是「金剛不壞體神功」！\n" NOR, obj2); 
  obj2->kill_ob(obj1);
  obj1->start_busy(3);
  obj2->start_busy(3);
  message_vision(HIR"\n$n向$N喝道：“看我袖裏乾坤。”只見$N內力充盈，衣袖拂起，拳勁卻暗藏在袖底發出，正是少林絕技。\n" NOR, obj1,obj2); 
  message_vision(HIW"\n$N料想這招衣袖便是拳勁的掩飾，使其無法看到拳勢來路，攻他個措手不及。當即全神貫注的拆解他袖底所\n"
                      "藏拳招，$N使出「蜻蜓點水」，恰好躲過了$n的攻勢。\n" NOR, obj1,obj2); 
  message_vision(HIY"\n豈料，衣袖之上卻也蓄有極凌厲的招數和勁力，$N當即大喝一聲，孤注一擲，將全身功力匯於一袖之內揮出！\n" NOR,obj2);
  message_vision(HIW"\n$N見他攻到，兩隻寬大的衣袖鼓風而前，便如是兩道順風的船帆，威勢非同小可，大聲喝道：“袖裏乾坤，\n"
                      "果然了得！”呼的一掌，拍向他衣袖。$n的袖力廣被寬博，$N這一掌卻是力聚而凝，只聽得嗤嗤聲響，兩股\n"
                      "力道相互激盪，突然間大廳上似有數十隻灰蝶上下翻飛。\n" NOR, obj1,obj2); 
  tell_object(me,HIB"\n你暗叫一聲“好武功”，蕭峯只如此一掌，便破了渡難的成名絕技。\n"NOR);  
  log_file("quest/TLBB", sprintf("%s(%s)聚賢莊大混亂玄難與蕭峯單幹。經驗%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
  remove_call_out("xiaofeng3");
  call_out("xiaofeng3",15, me);   
  return;
}
void xiaofeng3(object me)
{
  if(!me) return;
  if (!me->query(QUESTDIR3+"start")) return;
  if (!me->query_temp(QUESTDIR3+"kill")) return;
  if (me->query(QUESTDIR3+"over")) return;
  if (me->query_temp(QUESTDIR3+"help")) return;
  if(!present(me,this_object())) 
  {
	  tell_object(me,HIG"\n你這種情況竟然臨陣逃脱，實在違背俠義之情。你的江湖威望大幅下降。\n"NOR); 
	  me->delete_temp("quest/busy");//任務系統衝突標誌
	  me->delete_temp("quest/天龍八部");   
	  me->delete(QUESTDIR3+"start");
	  me->add("mana",-200);
	  if(me->query("mana")<0) me->set("mana",0);
	  destruct_person(this_object());//消除所有人物
	  return;
  }
  copy_person(this_object(),3);//複製情節人物 
  message_vision(HIY"\n玄難突然深吸一口氣，目露慈光，面帶微笑，內力運轉，竟使全身上下寶光流動，是「金剛不壞體神功」！\n" NOR,me); 
  message_vision(HIR"\n玄難似乎漸漸不是對手，羣雄又是全部一擁而上，場面更加混亂，戰鬥越來越是激烈！\n" NOR,me); 
  remove_call_out("xiaofeng4");
  call_out("xiaofeng4",30, me);   
  return;
}
void xiaofeng4(object me)
{
  object obj;
  if(!me) return;
  if (!me->query(QUESTDIR3+"start")) return;
  if (!me->query_temp(QUESTDIR3+"kill")) return;
  if (me->query(QUESTDIR3+"over")) return;
  if (me->query_temp(QUESTDIR3+"help")) return;
  if(!present(me,this_object())) 
  {
	  tell_object(me,HIG"\n你這種情況竟然臨陣逃脱，實在違背俠義之情。你的江湖威望大幅下降。\n"NOR); 
	  me->delete_temp("quest/busy");//任務系統衝突標誌
	  me->delete_temp("quest/天龍八部");   
	  me->delete(QUESTDIR3+"start");
	  me->add("mana",-200);
	  if(me->query("mana")<0) me->set("mana",0);
	  destruct_person(this_object());//消除所有人物
	  return;
  }
  copy_person(this_object(),3);//複製情節人物 
  obj=present("xiao feng", this_object());
  message_vision(HIW"\n瞬間之內，$N發現蕭峯似乎背心、右胸、右肩同時中刀，更不可思議的是蕭峯竟然當即昂立不動，陡然仰天\n"
                      "大叫，聲音直似猛獸狂吼。卻見單正正大呼而前，舉刀往蕭峯胸口刺去。\n"NOR,me);
  tell_object(me,HIR"\n你暗道一聲“不妙”，需要你趕快去解救蕭峯（jiejiu xiao feng）。\n"NOR);
  log_file("quest/TLBB", sprintf("%s(%s)聚賢莊大混亂需要解救蕭峯。經驗%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
  me->set_temp(QUESTDIR3+"can_be_help",1);
  remove_call_out("xiaofeng5");
  call_out("xiaofeng5",10, me); 
  remove_call_out("xiaofeng_over");
  call_out("xiaofeng_over",120, me);  
  return;
}
void xiaofeng5(object me)
{
  if(!me) return;
  if (!me->query(QUESTDIR3+"start")) return;
  if (!me->query_temp(QUESTDIR3+"kill")) return;
  if (me->query(QUESTDIR3+"over")) return;
  if (me->query_temp(QUESTDIR3+"help")) return;
  if (!me->query_temp(QUESTDIR3+"can_be_help")) return;
  if(!present(me,this_object())) 
  {
	  tell_object(me,HIG"\n你這種情況竟然臨陣逃脱，實在違背俠義之情。你的江湖威望大幅下降。\n"NOR); 
	  me->delete_temp("quest/busy");//任務系統衝突標誌
	  me->delete_temp("quest/天龍八部");   
	  me->delete(QUESTDIR3+"start");
	  me->add("mana",-200);
	  if(me->query("mana")<0) me->set("mana",0);
	  destruct_person(this_object());//消除所有人物
	  return;
  }
  copy_person(this_object(),3);//複製情節人物 
  tell_object(me,HIR"\n你趕快去解救蕭峯（jiejiu xiao feng）啊。別發呆了！\n"NOR);
  remove_call_out("xiaofeng5");
  call_out("xiaofeng5",10, me); 
  return;
}
void xiaofeng_over(object me)
{
  if(!me) return;
  if (!me->query(QUESTDIR3+"start")) return;
  if (!me->query_temp(QUESTDIR3+"kill")) return;
  if (me->query(QUESTDIR3+"over")) return;
  if (me->query_temp(QUESTDIR3+"help")) return;
  if (!me->query_temp(QUESTDIR3+"can_be_help")) return;
  if(!present(me,this_object())) 
  {
	  tell_object(me,HIG"\n你這種情況竟然臨陣逃脱，實在違背俠義之情。你的江湖威望大幅下降。\n"NOR); 
	  me->delete_temp("quest/busy");//任務系統衝突標誌
	  me->delete_temp("quest/天龍八部");   
	  me->delete(QUESTDIR3+"start");
	  me->add("mana",-200);
	  if(me->query("mana")<0) me->set("mana",0);
	  destruct_person(this_object());//消除所有人物
	  return;
  }
  tell_object(me,HIC"\n突然一個黑衣人叢房頂跳下來，一個竄身向單正拿去，勢道奇急，正好碰在單正的鋼刀之上。鋼刀順勢落地。廳中登時大\n"
                      "亂，羣雄驚呼叫嚷。黑衣人順手檢起角落一團長繩，用力一甩，趁羣雄紛舉兵刃擋格之際，繩頭陡轉，往蕭峯腰間一纏，\n"
                      "隨即提起。黑衣人隨手倒轉長繩，繞向八九丈外的一株大樹，一拉長繩，頃刻間越過那株大樹，已在落在後院。\n"NOR);
  tell_room(environment(me),HIC"\n突然一個人影化過，卻見單正已經昏倒在地，而蕭峯騰空而起。再仔細看時，人已經落在後院之中。\n"NOR, ({}));                       

  tell_object(me,HIG"\n你這種情況竟然不敢救援，實在違背俠義之情。你的江湖威望大幅下降。\n"NOR); 
  me->delete_temp("quest/busy");//任務系統衝突標誌
  me->delete_temp("quest/天龍八部");   
  me->delete(QUESTDIR3+"start");
  me->add("mana",-200);
  if(me->query("mana")<0) me->set("mana",0);
  log_file("quest/TLBB", sprintf("%s(%s)聚賢莊大混亂沒有解救蕭峯，任務失敗。經驗%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
  destruct_person(this_object());//消除所有人物
  return;
}

int do_jiejiu(string arg)
{
  object obj,room,me;
  me = this_player();
  if (!me->query(QUESTDIR3+"start")) return 0;
  if (!me->query_temp(QUESTDIR3+"kill")) return 0;
  if (me->query(QUESTDIR3+"over")) return 0;
  if (me->query_temp(QUESTDIR3+"help")) return 0;
  if(!arg) return 0;
  if(arg!="xiao feng" && arg!="xiao")
  {
      tell_object(me,HIR"\n沒人用你來解救。\n"NOR);
	  return 1; 
  }
  if (!me->query_temp(QUESTDIR3+"can_be_help"))
  {
      tell_object(me,HIR"\n還不到時候，不需要你解救，蕭峯自能自己應付。\n"NOR);
	  return 1; 
  }
  if(!(obj=present("xiao feng", environment(me))))
  {
      copy_person(this_object(),3);
  }
  obj=present("xiao feng", environment(me));
  obj->set("qi", obj->query("max_qi")/3);
  obj->set("eff_qi", obj->query("max_qi")/3);
  obj->set("jing", obj->query("max_jing"));
  obj->set("eff_jing", obj->query("max_jing"));
  obj->add("neili", obj->query("max_neili")*2);
  obj->set("jingli", obj->query("max_jingli"));
  if(obj->is_busy()) obj->start_busy(-1);	  
 
  tell_object(me,HIC"\n你暗道一聲“不妙”，馬上一個竄身，你勢道奇急，正好碰在單正的鋼刀之上。鋼刀順勢落地。廳中登時大亂，\n"
                      "羣雄驚呼叫嚷。你順手檢起角落一團長繩，用力一甩，趁羣雄紛舉兵刃擋格之際，繩頭陡轉，往蕭峯腰間一纏，\n"
                      "隨即提起。你隨手倒轉長繩，繞向八九丈外的一株大樹，一拉長繩，頃刻間越過那株大樹，已在落在後院。\n"NOR);
  tell_room(environment(me),HIC"\n突然一個人影化過，卻見單正已經昏倒在地，而蕭峯騰空而起。再仔細看時，人已經落在後院之中。\n"NOR, ({}));                       
  if (!(room = find_object("/d/nanyang/houyuan")))
      room = load_object("/d/nanyang/houyuan");
  if(room)
  {
  	me->move(room);  
  	obj->move(room);
    tell_object(me,HIR"\n你跟着又甩長繩，再繞遠處大樹，如此幾個起落，已然走得無影無蹤。\n"NOR);
  }
  else 
  {
	  destruct_person(this_object());//消除所有人物
	  tell_object(me,HIR"\n你跟着又甩長繩，再繞遠處大樹，如此幾個起落，靠，還在原地？？\n"NOR);
	  me->delete_temp("quest/busy");//任務系統衝突標誌
	  me->delete_temp("quest/天龍八部");   
	  log_file("quest/TLBB", sprintf("%s(%s)聚賢莊缺少houyuan.c文件。\n", me->name(1),me->query("id")) );
	  return 1;
  }
  if (!(room = find_object("/d/nanyang/duanya2")))
      room = load_object("/d/nanyang/duanya2");
  if(room)
  {
    tell_room(environment(me),HIC"\n"+me->name()+"又一甩長繩，再繞遠處大樹，如此幾個起落，已然走得無影無蹤。\n"NOR, ({}));                       
  	me->move(room);  
  	obj->move(room);
    tell_object(me,HIG"\n你怕有追兵追趕，連續走過幾個地方，才來到一個斷崖邊停住。\n"NOR);
  }
  else 
  {
    destruct_person(this_object());//消除所有人物
	me->delete_temp("quest/busy");//任務系統衝突標誌
	me->delete_temp("quest/天龍八部");   
    tell_object(me,HIR"\n你跟着又甩長繩，再繞遠處大樹，如此幾個起落，靠，還在原地？？\n"NOR);
	log_file("quest/TLBB", sprintf("%s(%s)聚賢莊缺少duanya2.c文件。\n", me->name(1),me->query("id")) );
    return 1;
  }
  log_file("quest/TLBB", sprintf("%s(%s)聚賢莊大混亂成功解救蕭峯。經驗%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
  me->set_temp(QUESTDIR3+"help",1);
  destruct_person(this_object());//消除所有人物
  return 1;
}
void busy()
{
	this_object()->delete("busy");
	return;
}
int do_action(string arg)
{
	this_player()->start_busy(1);
   	tell_object(this_player(),HIR"\n你正要有所動作，突然感覺這裏太過混亂，還是安靜得好！\n");
   	return 1;
}
int valid_leave(object me, string dir)
{
     if (present("xiao feng", environment(me)))
           return notify_fail(HIR"別忘記了此行的目的，怎能不管蕭峯了，還是靜觀其變！\n"NOR);
     return ::valid_leave(me, dir);
}
void copy_person(object ob,int i)
{
	object obj1,obj2;
	//添加蕭峯
  if(!(obj1=present("xiao feng", ob))) 
  {
 	   obj1=new(__DIR__"npc/xiaofeng");
    obj1->set("no_death",1);
     obj1->move(ob); 
  }
    obj1->set("no_death",1);
  obj1->remove_all_killer(); 
  //添加丐幫宋奚陳吳白
  if(!(obj2=present("wu zhanglao", ob))) 
  {
 	   obj2=new(__DIR__"npc/gbdizi");
		 obj2->set_name("吳長老", ({ "wu zhanglao", "wu","zhanglao"}) );
		 obj2->set("title",HIB"丐幫長老"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); //設置戰鬥還是停止戰鬥,0 停止戰鬥，1戰鬥，2戰鬥但只發絕技，3戰鬥只有xiao feng 出普通招
  if(!(obj2=present("song zhanglao", ob))) 
  {
 	   obj2=new(__DIR__"npc/gbdizi");
		 obj2->set_name("宋長老", ({ "song zhanglao", "song","zhanglao"}) );
		 obj2->set("title",HIM"丐幫長老"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  if(!(obj2=present("xi zhanglao", ob))) 
  {
 	   obj2=new(__DIR__"npc/gbdizi");
		 obj2->set_name("奚長老", ({ "xi zhanglao", "xi","zhanglao"}) );
		 obj2->set("title",HIC"丐幫長老"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  if(!(obj2=present("chen zhanglao", ob))) 
  {
 	   obj2=new(__DIR__"npc/gbdizi");
		 obj2->set_name("陳長老", ({ "chen zhanglao", "chen","zhanglao"}) );
		 obj2->set("title",HIY"丐幫長老"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  if(!(obj2=present("bai shijing", ob))) 
  {
 	   obj2=new(__DIR__"npc/gbdizi");
		 obj2->set_name("白世鏡", ({ "bai shijing", "bai"}) );
		 obj2->set("title",HIC"執法堂主"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  //添加少林玄慈、玄濟
  if(!(obj2=present("xuan nan", ob))) 
  {
 	   obj2=new(__DIR__"npc/sldizi");
		 obj2->set_name("玄難", ({ "xuan nan", "xuan","nan"}) );
		 obj2->set("title",HIY"少林長老"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  if(!(obj2=present("xuan ji", ob))) 
  {
 	   obj2=new(__DIR__"npc/sldizi");
		 obj2->set_name("玄寂", ({ "xuan ji", "xuan","ji"}) );
		 obj2->set("title",HIY"少林長老"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 

  //添加單正譚公譚婆趙錢李
  if(!(obj2=present("shan zheng", ob))) 
  {
 	   obj2=new(__DIR__"npc/otherdizi");
		 obj2->set_name("單正", ({ "shan zheng", "shan","zheng"}) );
		 obj2->set("title",HIB"鐵面判官"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  if(!(obj2=present("tan po", ob))) 
  {
 	   obj2=new(__DIR__"npc/otherdizi");
		 obj2->set_name("譚婆", ({ "tan po", "tan","po"}) );
		 obj2->set("title",HIY"太行山沖霄洞"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  if(!(obj2=present("tan gong", ob))) 
  {
 	   obj2=new(__DIR__"npc/otherdizi");
		 obj2->set_name("譚公", ({ "tan gong", "tan","gong"}) );
		 obj2->set("title",HIY"太行山沖霄洞"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  if(!(obj2=present("zhao qianli", ob))) 
  {
 	   obj2=new(__DIR__"npc/otherdizi");
		 obj2->set_name("趙錢李", ({ "zhao qianli", "zhao"}) );
		 obj2->set("title",HIG"騎驢客"NOR);
     obj2->move(ob); 
  }
  set_person(obj1,obj2,i); 
  //人物添加結束  
  return;	
}
void set_person(object obj1,object obj2,int i)
{
  if(!obj1) return;
  if(!obj2) return;
  //obj1是蕭峯
  if(i>0) obj2->kill_ob(obj1);
  else obj2->remove_all_killer(); 
  if(i==2) 
  {
	  obj1->set_temp("no_fight",1);
	  obj2->set_temp("no_fight",1);
  }
 if(i==3) 
  {
	  obj1->delete_temp("no_fight");
	  obj2->set_temp("no_fight",1);
  }
  if(i==4) 
  {
	  obj2->delete_temp("no_fight");
	  obj1->set_temp("no_fight",1);
  }
  return;
}
void destruct_person(object ob)
{
	object obj;
	if((obj=present("xuan nan", ob))) 
	{
    message_vision(HIR"$N打了個哈哈，竟然走開了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("xiao feng", ob))) 	{
    message_vision(HIR"$N打了個哈哈，竟然走開了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("xuan ji", ob))) 	{
    message_vision(HIR"$N打了個哈哈，竟然走開了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("wu zhanglao", ob))) 	{
    message_vision(HIR"$N打了個哈哈，竟然走開了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("xi zhanglao", ob))) 	{
    message_vision(HIR"$N打了個哈哈，竟然走開了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("song zhanglao", ob))) 	{
    message_vision(HIR"$N打了個哈哈，竟然走開了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("chen zhanglao", ob))) 	{
    message_vision(HIR"$N打了個哈哈，竟然走開了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("bai shijing", ob))) 	{
    message_vision(HIR"$N打了個哈哈，竟然走開了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("shan zheng", ob))) 	{
    message_vision(HIR"$N打了個哈哈，竟然走開了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("tan gong", ob))) 	{
    message_vision(HIR"$N打了個哈哈，竟然走開了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("tan po", ob))) 	{
    message_vision(HIR"$N打了個哈哈，竟然走開了。\n" NOR, obj);
		destruct(obj);
  }
  if((obj=present("zhao qianli", ob))) 	{
    message_vision(HIR"$N打了個哈哈，竟然走開了。\n" NOR, obj);
		destruct(obj);
  }
  return;
}
