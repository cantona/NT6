//add by tangfeng@SJ 2004

inherit ROOM;
#include <ansi.h>

int do_action(string arg);
int do_leave(string arg);
int do_stop(string arg);
int do_start(string arg);
int do_full(string arg);
void start(object me);
void rule(object me);
void copy_person(object me);
void destruct_person(object ob);
void destruct_book(object ob);
int do_eat(string arg);

#define QUESTDIR "quest/天龍八部/"
#define QUESTDIR3 "quest/天龍八部/蕭峰身世篇/"
#define QUESTDIR4 "quest/天龍八部/大遼救援篇/"
#define QUESTDIR5 "quest/天龍八部/復興天下篇/"

string* anhao = ({"維","經","摩","法","華","嚴","無","量","壽","大","般","涅","磐","阿","含","金","剛","波","羅","蜜","多","心","佛",
                  "須","提","若","菩","薩","以","滿","恆","河","沙","等","世","界","七","寶","佛","說","是","經","已","長","老","所",
                  "菩","提","及","諸","比","丘","尼","優","婆","塞","優","婆","夷","一","切","世","間","天","人","阿","修","羅","聞",});

void create()
{
	set("short",HIW "少林陣" NOR);
	set("long", @LONG
這是一片空場地，四角分別站著四個少林弟子。一角放著個兵器架。
LONG);
  set("no_get_from", 1); 
  set("quest", 1);
  set("no_sleep_room", 1);
	setup();
}
void init()
{
  object me;
  me = this_player();
  if(me->query_condition("killer"))
  {
   message_vision(HIC"\n突然$N似乎氣血有些不順，跟著一個趔趄倒了下去。\n"NOR,me); 
   tell_object(me,HIR"你突然感到一股力量吸引著你，瞬間你失去知覺。\n"NOR);
   tell_room(environment(me),HIR"\n只見，地上突然出現一個裂洞，"+ me->name()+ "一頭紮了下去，瞬間消失。\n"NOR, ({ me }));
   if(me->query(QUESTDIR3+"bad"))  me->move("/d/shaolin/smdian");
   else if(me->query(QUESTDIR3+"good"))  me->move("/d/shaolin/fzjs2");
   else me->move("/d/xiangyang/damen"); 
   tell_room(environment(me), HIR"\n半空中，似乎一個人掉了下來，你定眼一看竟然是"+ me->name()+ "。\n"NOR, ({ me }));
   message_vision(HIC"$N揉了揉眼睛，看才似乎像一場夢，好像什麼都沒發生。\n"NOR,me); 
   return;
  }
	add_action("do_full", ({"full"}));
  add_action("do_eat",({"eat","drink"}) );
	add_action("do_leave", ({"leave"}));
	add_action("do_start", ({"start"}));
	add_action("do_stop", ({"stop"}));
  add_action("do_action", ({"lian", "learn", "tu", "steal","kill", "guard","beg", "hit", "steal", "fight", "throw", "ansuan"}));   
//remove_call_out("rule")
	call_out("rule",2,me);
}
int do_eat(string arg)
{
     object me = this_player();
     if (me->query("food") < me->query("str")*3+50){
          message_vision(HIC"$N正覺得有些肚子饑，外面走來一個僧人，送給$N一些飯菜。\n"NOR, me);
          message_vision(HIC"$N爽快地大吃一頓，隨手把剩余的飯菜丟了出去。\n"NOR, me);
          me->add("food", me->query("str")*10+100, me);
          return 1;
     }
     else
     if (me->query("water") < me->query("str")*3+50)
     {
          message_vision(HIC"$N正覺得有些喉嚨渴，外面走來一個僧人，送給$N一個水袋。\n"NOR, me);
          message_vision(HIC"$N咕咚咕咚喝了一大口，隨手把水袋丟了出去。\n"NOR, me);
          me->add("water", me->query("str")*10+100, me);
          return 1;
     }
     else  return notify_fail("你喝太多了，吃太多了，不怕撐死？\n");
}

int do_leave(string arg)
{
		object ob,obj,me;
		ob=this_object();
		me = this_player();
		if(me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && !me->query_temp(QUESTDIR5+"shaolinzhen"))
		{
			message_vision(HIC"$N決定離開這裡，卻聽見一個聲音道：我彌陀佛，施主留步。\n"NOR, this_player());
			return 1;
	  }
		if(me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && me->query_temp(QUESTDIR5+"shaolinzhen"))
         message_vision(HIC"$N輕蔑地看了看四角的僧人，哼了一聲，決定離開"+environment(me)->query("short")+"。\n"NOR, this_player());
    else message_vision(HIC"$N匆匆離開"+environment(me)->query("short")+"。\n"NOR, this_player());
    destruct_book(ob);
    destruct_person(ob);
    tell_room(environment(me),HIR"\n只見，地上突然出現一個裂洞，"+ me->name()+ "一頭紮了下去，瞬間消失。\n"NOR, ({me}));
		if(me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && me->query_temp(QUESTDIR5+"shaolinzhen"))
        me->move("/d/shaolin/smdian");
    else if(me->query(QUESTDIR3+"good"))  me->move("/d/shaolin/fzjs2");
    else me->move("/d/xiangyang/damen"); 
    tell_room(environment(me),HIR"\n只見，地上突然出現一個裂洞，"+ me->name()+ "出現在房間之中。\n"NOR, ({me}));
	message_vision(HIC"$N匆匆地來到"+environment(me)->query("short")+"。\n"NOR, me);
    if(me->query(QUESTDIR3+"good") && me->query_temp(QUESTDIR4+"shaolinzhen") && me->query_temp(QUESTDIR4+"dagouzhen"))
		{
      if(!(obj=present("xuanci dashi", environment(me)))) 
	    {
        obj=new("/kungfu/class/shaolin/xuan-ci");
        obj->move(environment(me));
        message_vision(HIC"$N匆匆地走了過來，神色有些慌張。\n"NOR, obj);
      }
      me->set_temp(QUESTDIR4+"anhao",anhao[random(sizeof(anhao))]+anhao[random(sizeof(anhao))]+anhao[random(sizeof(anhao))]+
                                     anhao[random(sizeof(anhao))]+anhao[random(sizeof(anhao))]);
       message_vision(HIC"$N對$n點了點頭，恭喜$n闖過少林陣法。\n"NOR, obj,me);
       tell_object(me,obj->name()+"在你的耳邊悄聲說道：恩，果然是"+me->query("family/master_name")+"座下"+me->query("family/family_name")+"高手，確實武功了得。\n"NOR);
       tell_object(me,obj->name()+"在你的耳邊悄聲說道：如此說來，還是盡快營救蕭大俠為是。半夜三更，在頌摩崖屆時會有丐幫弟子接應。\n"NOR);
       tell_object(me,obj->name()+"在你的耳邊悄聲說道：注意一定是半夜時刻，另外，可能需要暗號接應，暗號是【"+me->query_temp(QUESTDIR4+"anhao")+"】。\n"NOR);
       message_vision(HIC"$N對$n沖著$n大聲叫到：壯士，加油！\n"NOR, obj,me);
       me->set(QUESTDIR+"time",time());
	  }
	  return 1;
}
int do_stop(string arg)
{
		object me = this_player();
		if(!me->is_fighting()) return 0;
	  if(!me->query_temp(QUESTDIR4+"shaolinzhen")&& !me->query_temp(QUESTDIR5+"shaolinzhen"))  message_vision(HIC"\n$N感到自己有些力不從心，決定暫時中止陣法。\n"NOR, this_player());
    else   message_vision(HIC"\n$N有些玩夠了，你決定停止戰鬥。\n"NOR, this_player());
    tell_object(me,HIR"\n突然你感到一股神力充斥在房間之中，雙方不由自主停止戰鬥。\n"NOR);
    tell_room(environment(me),HIR"\n突然你感覺一股神力充斥在房間之中，雙方不由自主停止戰鬥。\n"NOR, ({ me }));
    me->remove_all_killer();   
    destruct_person(this_object());
    return 1;
}
int do_start(string arg)
{
		object me = this_player();
    if(me->is_fighting()) return 0;
	  if((present("shaolin dizi", this_object()))) 
	  {
	  	tell_object(me,HIR"陣法已經啟動！\n"NOR);
	    return 1;
	  }
    if(this_object()->query("busy")) 
    {
      tell_object(me,HIR"稍微休息一下，陣法馬上重新啟動！\n"NOR);
      return 1;
    }
    destruct_book(this_object());
	  if(!me->query_temp(QUESTDIR4+"shaolinzhen")&& !me->query_temp(QUESTDIR5+"shaolinzhen"))  message_vision(HIC"$N決定嘗試闖一闖這少林陣法，盡快離開這裡。\n"NOR, this_player());
    else   message_vision(HIC"$N決定再次闖一闖這少林陣法。\n"NOR, this_player());
    tell_object(me,HIR"突然你感到一股神力充斥在房間之中，你精神不由一陣。\n"NOR);
    me->remove_all_killer();   
    destruct_person(this_object());
	  remove_call_out("start");
    remove_call_out("busy");
    call_out("busy",120);
    this_object()->set("busy",1);
	  call_out("start",4,me);
    return 1;
}
void busy()
{
  this_object()->delete("busy");
  return;
}
int do_full(string arg)
{
		object me = this_player();
    if(me->is_fighting()) return 0;
    if(me->is_busy()) return 0;
    if(me->query("eff_qi")>=me->query("max_qi") && me->query("eff_jing")>=me->query("max_jing")) return 0;
    
    //療傷
    if(me->query("eff_qi")<me->query("max_qi"))
    {
      me->set("eff_qi",me->query("max_qi"));
      tell_object(me,HIR"突然你感到一股神力充斥在房間之中，你的傷勢竟然康復大半。\n"NOR);
    }
    //療精
    if(me->query("eff_jing")<me->query("max_jing"))
    {
      me->set("eff_jing",me->query("max_jing"));
      tell_object(me,HIR"突然你感到一股神力充斥在房間之中，你的精血完全恢復。\n"NOR);
    }
    me->remove_all_killer();   
    destruct_person(this_object());
    tell_room(environment(me),HIR"突然你感覺一股神力充斥在房間之中，原來"+me->name()+"正在招呼異力療傷！\n"NOR, ({ me }));
    return 1;
}
void start(object me)
{
  if(!me) return;
  if(!present(me,this_object())) 
  {
  	tell_object(me,HIR"身體不舒服？還沒兩秒鐘就走開？好像也跑得太快了點。\n"NOR);
  	return;
  }	
  message_vision(HIC"$N決定闖陣。\n"NOR, me);
  message_vision(HIC"一會，從角落裡緩緩地走出四個僧人，身著錦斕袈裟，估計都在五十開外！\n"NOR, me);
  copy_person(me);
  return;
}
void rule(object me)
{
	object obj;
  if(!me) return;
  if(!present(me,this_object())) 
  {
  	tell_object(me,HIR"身體不舒服？還沒兩秒鐘就走開？好像也跑得太快了點。\n"NOR);
  	return;
  }	
  if(me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && !me->query_temp(QUESTDIR5+"shaolinzhen"))
  {
    if(!(present("shu", this_object())))
    {
       obj=new("/d/shaolin/obj/fojing1");
       obj->move(environment(me)); 
       message_vision(YEL"\n“啪”地一聲，一本"+obj->query("name")+"掉在$N面前。\n"NOR,me);
         obj=new("/d/shaolin/obj/fojing2");
       obj->move(environment(me)); 
       message_vision(YEL"“啪”地一聲，又一本"+obj->query("name")+"掉在$N面前。\n"NOR,me);
    }
   message_vision(HIC"\n只聽一個聲音對道：施主殺性太重，行走江湖只怕到處是一片腥風血雨，還是呆在這裡潛心修我佛法為上！\n"NOR,me);
   message_vision(HIC"這兩本佛經可以修煉佛性，消滅厲氣，其實如果施主能夠領悟其中，對你的武功修為其實也是大有幫助的！\n"NOR, me);
  }
    tell_object(me,HIY"\n要離開這裡只有硬闖少林陣。你可以使用：\n"
                       +"啟動陣法（start）、中止陣法（stop）、離開房間（leave）、恢復自己（full）。\n"
                  +HIR"\n陣法之中，有死亡的可能，請及時中止陣法！\n\n"NOR);
  return;
}
int do_action(string arg)
{
	 if(wizardp(this_player())) return 0;
   tell_object(this_player(),HIR"你正要有所動作，只聽一個聲音道：別亂動！\n");
   return 1;
}
void copy_person(object me)
{
	object obj1,obj2;
	int i;
  //teamleader
  if(!me) return;
  obj1=new(__DIR__"npc/dizi");
  obj1->set("teamleader",1);
  obj1->set("party","sl");
  obj1->set("fight_id",me->query("id"));
  obj1->move(environment(me)); 
  for( i = 0; i <3;i++)
  {
    obj2=new(__DIR__"npc/dizi");
    obj2->set("party","sl");
    obj2->set("fight_id",me->query("id"));
    obj2->move(environment(me)); 
  }
}
void destruct_person(object ob)
{
	object obj;
	int i;
  for( i = 0; i <4;i++)
  {
	  if(!(present("shaolin dizi", ob))) return;
    obj=present("shaolin dizi", ob);
    if(!random(3)) message_vision(HIR"$N點了點頭，緩緩消失在角落裡。\n" NOR, obj);
    else message_vision(HIR"$N道了聲佛號，慢慢地退了出去。\n" NOR, obj);
		destruct(obj);
  }
}
void destruct_book(object ob)
{
	object obj;
	int i;
  for( i = 0; i <2;i++)
  {
	  if(!(present("shu", ob))) return;
    obj=present("shu", ob);
    if(random(2)) message_vision(HIR"一陣風過，$N飄在風裡，消去了。\n" NOR, obj);
    else message_vision(HIR"一晃，$N竟然也跟著消失了。\n" NOR, obj);
		destruct(obj);
  }
}
