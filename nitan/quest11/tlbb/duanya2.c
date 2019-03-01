// update by Lklv for new nanyang city 2001.10.11

#include <ansi.h>
inherit ROOM;
#define QUESTDIR3 "quest/天龍八部/蕭峰身世篇/"

void create()
{
	set("short", "斷崖");
	set("long", @LONG
前面是一處十分陡峭的斷崖，險峻異常，難以爬越。這裡離黃河不遠，黃
河流淌到這裡，河床寬闊。黃色的河水在靜靜地向東流去，使人忘記它發
洪水時的狂威。
LONG
	);
           set("quest",1);
	set("outdoors", "黃河");
	set("exits", ([
		"north" : __DIR__"yidao4",
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
  if (!me->query_temp(QUESTDIR3+"help")) return;
  if(present("xiao feng", environment(me)))return;
  me->start_busy(1);
  obj=new(__DIR__"npc/xiaofeng");
  obj->set("qi", obj->query("max_qi")/3);
  obj->set("eff_qi", obj->query("max_qi")/3);
  obj->set("jing", obj->query("max_jing"));
  obj->set("eff_jing", obj->query("max_jing"));
  obj->add("neili", obj->query("max_neili")*2);
  obj->set("jingli", obj->query("max_jingli"));
  if(obj->is_busy()) obj->start_busy(-1);	  
  if(!present("xiao feng", environment(me)))
  {
      obj->move(environment(me));
  }
}
int valid_leave(object me, string dir)
{
   object obj;
   if(obj=present("xiao feng", environment(me)))
   {
	   message_vision(HIY"\n$N點了點頭道：“$n既然要走了，我也離開這裡了，我先找一個地方療傷再說。”\n" NOR, obj,me); 
       message_vision(HIY"\n$N微一凝神，運起混天氣功，全身骨節發出一陣爆豆般的聲響！\n" NOR, obj); 
	   message_vision(HIY"\n$N向$n招了招手，道：“等我傷勢痊癒，我就會去找你的。”\n" NOR, obj,me); 
	   message_vision(HIY"\n$N跳下斷崖，一轉眼不見蹤影了。\n" NOR, obj); 
       destruct(obj);
   }
   return ::valid_leave(me, dir);
}

