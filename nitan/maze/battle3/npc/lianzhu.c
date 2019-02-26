#include <ansi.h>
inherit F_SSERVER; 

mapping exits_name=([
"east":            "東方",
"south":           "南方",
"west":            "西方",
"north":           "北方",
"eastup":          "東上方",
"southup":         "南上方",
"westup":          "西上方",
"northup":         "北上方",
"eastdown":        "東下方",
"southdown":       "南下方",
"westdown":        "西下方",
"northdown":       "北下方",
"northeast":       "東北方",
"northwest":       "西北方",
"southeast":       "東南方",
"southwest":       "西南方",
"up":              "上方",
"southeast":       "東南方",
"southwest":       "西南方",
"up":              "上方",
"down":            "下方",
"enter":           "裏邊",
"out":             "外邊",
]);
int do_she(string arg,object me,object bow,int num);
int do_shoot(string id,object me,object room,string what,int m,object bow,int num);

string exits_reverse(string dir);

string exits_reverse(string dir)
{
 if( dir=="east" ) return "west";
 if( dir=="west" ) return "east";
 if( dir=="south" ) return "north";
 if( dir=="north" ) return "south";
 if( dir=="eastup" ) return "westdown";
 if( dir=="westup" ) return "eastdown";
 if( dir=="southup" ) return "northdown";
 if( dir=="northup" ) return "southdown";
 if( dir=="eastdown" ) return "westup";
 if( dir=="westdown" ) return "eastup";
 if( dir=="southdown" ) return "northup";
 if( dir=="northdown" ) return "southup";
 if( dir=="northeast" ) return "southwest";
 if( dir=="northwest" ) return "southeast";
 if( dir=="southwest" ) return "northeast";
 if( dir=="southeast" ) return "northwest";
 if( dir=="up" ) return "down";
 if( dir=="down" ) return "up";
 if( dir=="enter" ) return "out";
 if( dir=="out" ) return "enter";

 return "";
}

int perform(object me,object target)
{
  object bow;
  int num;

  if( !objectp(bow=query_temp("weapon", me) )
       || !query("is_bow", bow) )
  return notify_fail("弓還沒上手呢，還想用連珠箭法？！\n");

  num=me->query_skill("lianzhu-arrow",1)/100+1;

  if( num < 2 || me->query_skill("arrow",1) < 100 )
  return notify_fail("還是好好練練你的箭法吧！\n");

  message_vision(HIY"$N從箭囊內抽出"HIW+CHINESE_D->chinese_number(num)+HIY"支"HIW"羽箭"HIY"，搭在"
       +query("name", bow)+HIY"上，準備施展生平絕技——"
       +HIR"連珠箭法"+HIY"！！\n"NOR,me);
  input_to("do_she",me,bow,num);
  return 1;
}


int do_she(string arg,object me,object bow,int num)
{
   object ob,room;
   int i,n,m;
   string what;
   mapping exits;

   room=environment(me);
   if( query("no_fight", environment(me)) )
   {
    tell_object(me,"這裏不許戰鬥！\n");
    return 1;
   }

   if( query("duration", bow)<0 )
   {
    message_vision("$N手中的"+query("name", bow)+"“嘣”地一聲斷了！\n",me);
    destruct(bow);
    return 1;
   }

   if( me->query_str()<query("dam", bow)/20 )
   {
    tell_object(me,"你使盡吃奶的力氣也拉不開弓來，看來力氣不夠！\n");  
    return 1;
   }

   if( me->is_busy() )
   {
    tell_object(me,"你現在正忙着呢！\n");
    return 1;
   }

   if( query("qi", me)<400*num || query("jing", me)<100*num )
   {
    tell_object(me,"你現在精氣不夠充盈，連珠箭法恐怕施展不出來！\n"); 
    return 1;
   }

   if( sscanf(arg,"she %s %d",what,n)==2 )
   {
    if( n>query("dam", bow)/200)n=query("dam", bow)/200;
    for(i=0;i<n;i++)
    {
      if( room && mapp(exits=query("exits", room)) && stringp(exits[what]) )
      {
       m=i+1;
       room=find_object(exits[what]);
      }
    }

    if( room==environment(me) )
    {
     tell_object(me,"看清楚點，朝哪裏射呀你？\n");
     return 1;
    }

    if( room)
     {
      if( query("have_quest", room) )
      { 
       tell_object(me,"那裏有神明佐佑，不容你胡來也！\n"); 
       return 1;
      }

      "/cmds/std/look.c"->look_room(me,room);  
      message_vision(HIY"隨後只見$N立了一個霸王上弓式，朝"HIR
       +exits_name[what]+HIY"把弓拉滿.......\n"NOR,me);
      tell_object(all_inventory(room),HIB"你覺得一股猛烈的殺機從"HIR
       +exits_name[exits_reverse(what)]+HIB"傳來！！\n"NOR);

      tell_object(me,HIR+exits_name[what]+HIW"的情景你一目瞭然，"
                                      +"你把利箭漸漸瞄準了——>\n"NOR);   
      me->start_busy(3+random(3));  
      input_to("do_shoot",me,room,what,m,bow,num);
     } else
      tell_object(me,"看清楚點，朝哪裏射呀你？\n");  

    } else
      tell_object(me,"不會射箭？找人家教教你吧！\n");
    return 1;
}

int do_shoot(string arg,object me,object room,string what,int m,object bow,int num)
{
  int k;

  for(k=0;k<num;k++)
  bow->do_shoot(arg,me,bow,room,what,m);
  if( num>3 ) num=3;
  me->start_busy(num*2);
  return 1;
} 
