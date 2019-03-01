#include <ansi.h>

inherit ITEM;

mapping chinese_dirs = ([
  "north":        "北",
  "south":        "南",
  "east":         "東",
  "west":         "西",
  "northup":      "北邊",
  "southup":      "南邊",
  "eastup":       "東邊",  
  "westup":       "西邊",
  "northdown":    "北邊",
  "southdown":    "南邊",
  "eastdown":     "東邊",
  "westdown":     "西邊",
  "northeast":    "東北",
  "northwest":    "西北",
  "southeast":    "東南",
  "southwest":    "西南",
  "up":           "上",
  "down":         "下",
  "enter":        "裡",
  "out":          "外",
  ]);

mapping turn_dirs = ([
  "north":        "northwest",
  "south":        "southeast",
  "east":         "northeast",
  "west":         "southwest",
  "northeast":    "north",
  "northwest":    "west",
  "southeast":    "east",
  "southwest":    "south",
  ]);

mapping drive_dirs = ([
  "westup":       "southdown",
  "southdown":    "down",
  "down":         "eastdown",
  "eastdown":     "northup",
  "northup":      "up",
  "up":           "westdown",
  "westdown":     "enter",
  "enter":        "southup",
  "southup":      "out",
  "out":          "eastup",
  "eastup":       "northdown",
  "northdown":    "westup",
  ]);

void create()
{
  string name = "鏢車";

  set_name(name, ({"biaoche", "che"}));
  set_weight(300000);
  set_max_encumbrance (1000000);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("short", name+"(Biaoche)");
    set("long", "一輛紅木鏢車，扯出一個幡子，上面寫著“福威鏢局”四個大字。\n");
    set("unit", "輛");
    set("material", "metal");
    set("value", 1000000);
    set("dir", "north");
    set("speed", 0);
    set("fuel", 10000);
    set("miles", 0);
  }
  setup();
}

void automate();

int init()
{
  add_action("do_enter", "enter");
  add_action("do_out", "out");
  add_action("do_look", "look");
  add_action("do_turn", "turn");
  add_action("do_drive", "drive");
  add_action("do_speedup", "speedup");
  add_action("do_slowdown", "speeddown");
  add_action("do_stop", "stop");
  automate();
  return 1;
}

int test_busy ()
{
  object me = this_object();
  object who = this_player();

  if( query_temp("is_busy", me) )
  {
    tell_object (who,"動作別太猛，車子會搞壞的！\n");    
    return 1;
  }
  set_temp("is_busy", 1, me);
  remove_call_out ("reset_busy_temp");
  call_out ("reset_busy_temp",1,me);
  return 0;
}

void reset_busy_temp (object me)
{
  set_temp("is_busy", 0, me);
}

int is_in ()
{
  object me = this_object();
  object who = this_player();
  return environment(who) == me; 
}

int is_driver ()
{
  object me = this_object();
  object who = this_player();

  if( query("driver", me) != who )
  {
    tell_object (who,"別亂動，你又不是鏢頭！\n");  
    return 0;
  }
  return 1;
}

int report_outside_objects ()
{
  object me = this_object();
  object who = this_player();
  object where = environment(me);
  mixed *inv = all_inventory(where);
  int i;

  if (sizeof(inv) <= 1)
    return 1;

  tell_object (who,"外面有：");  
  for (i=0; i < sizeof(inv); i++)
  {
    if (inv[i] != me)
      tell_object(who,query("name", inv[i])+"("+query("id", inv[i])+")");
  }
  tell_object (who,"\n");  
  return 1;
}

int report_inside_objects ()
{
  object me = this_object();
  object who = this_player();
  mixed *inv = all_inventory(me);
  int i;

  if (sizeof(inv) == 0)
    return 1;

  tell_object (who,"車裡有：");  
  for (i=0; i < sizeof(inv); i++)
  {
    tell_object(who,query("name", inv[i])+"("+query("id", inv[i])+")");
  }
  tell_object (who,"\n");  
  return 1;
}

int report_dir ()
{
  object me = this_object();
  object who = this_player();
  object where = environment(me);
  mapping exits=query("exits", where);
  string *dirs;
  int i;

  if (! exits)
    return 1;

  dirs = keys(exits);

  tell_object (who,"四面的出口是：");  
  for (i=0; i < sizeof(dirs); i++)
  {
    tell_object (who,chinese_dirs[dirs[i]]+"("+dirs[i]+")");    
  }
  tell_object (who," [車頭朝向："+chinese_dirs[query("dir", me)]+
                   "("+query("dir", me)+")]\n");
  return 1;
}

int report_view ()
{
  object me = this_object();
  object who = this_player();
  object where = environment(me);

  tell_object (who,"≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n");  
  tell_object (who,"從車窗裡可以看到：");  
  tell_object(who,query("short", where)+"\n");
  tell_object(who,query("long", where)+"\n");
  report_outside_objects();
  report_dir();
  tell_object (who,"≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡≡\n");  
  return 1;
}

int report_short ()
{
  object me = this_object();
  object who = this_player();
  string strspeed;
  int i, len = 15;

  strspeed="速度："+sprintf("%d",query("speed", me));
  for (i = sizeof(strspeed); i < len; i++)
    strspeed = strspeed + " ";
  tell_object (who,"\n");  
  tell_object (who,"       ___________ _
                        __/ .::::.-'-(/-/)                          
                     _/:  .::::.-' .-'\/\_`,        
                    /:  .::::./   -._-.  d\|         
                     /: (""""/    '.  (__/||            
                      \::).-'  -._  \/ \\/\|                          
              __ _ .-'`)/  '-'. . '. |  (i_O                          
          .-'      \       -'      '\|                                
     _ _./      .-'|       '.  (    \\  
  .-'   :      '_  \         '-'\  /|/ 
 /      )\_      '- )_________.-|_/^\           
 (   .-'   )-._-:  /        \(/\'-._ `.    
  (   )  _//_/|:  /          `\()   `\_\      
   ( (   \()^_/)_/             )/      \\ 
    )  _.-\\.\(_)__._.-'-.-'-.//_.-'-.-.)\-'/._.-''     
..-.-.-   _o\ \\\     '::'   (o_ '-.-' |__\'-.-;~   
          \ /  \\\__          )_\    .:::::::.-'\       
     :::''':::::^)__\:::::::::::::::::'''''''-._ \\n"); 
  if( query("driver", me) )
    tell_object(who,"鏢頭："+query("driver",query("name",  me)));


  tell_object (who,"\n");  
  report_inside_objects();
  return 1;
}

int do_enter (string arg)
{
  object me = this_object();
  object who = this_player();

  if (arg != "biaoche")
    return 0;

  if (is_in())
    return 0;

  if( query("speed", me)>0 )
  {
    tell_object (who,"跳進正在行駛的車子會有生命危險！\n");  
    return 1;
  }

  message_vision ("$N跳上了車。\n",who);
  who->move(me);
  if( !query("driver", me) || 
      environment(query("driver", me)) != me )
  {
    set("driver", who, me);
    message_vision ("$N坐在車頭上。\n",who);
  }
  else
    message_vision ("$N坐在車廂裡。\n",who);
  return 1;
}

int do_out (string arg)
{
  object me = this_object();
  object who = this_player();

  if (! is_in())
    return 0;

  if( query("speed", me)>0 )
  {
    tell_object (who,"跳出正在行駛的車子會有生命危險！\n");  
    return 1;
  }

  if( query("driver", me) == who )
  {
    set("driver", 0, me);
  }

  message_vision ("$N輕輕跳下車。\n",who);
  who->move(environment(me));
  message_vision ("$N跳出車，將帷幄掩上。\n",who);
  return 1;
}

int do_look (string arg)
{
  object me = this_object();
  object who = this_player();

  if (! is_in())
  {
    if (arg == "biaoche")
    {
      tell_object(who,"這是一"+query("unit", me)+query("name", me)+
                   "(enter)。\n");
      return 1;
    }
    return 0;
  }
  report_view();
  report_short();
  return 1;
}

int do_turn (string arg)
{
  object me = this_object();
  object who = this_player();
  string dir=query("dir", me);

  if (! is_in())
    return 0;

  if (! is_driver())
    return 1;

  if (test_busy())
    return 1;

  if( query("speed", me) == 0 )
  {
    tell_object (who,"先讓車子動起來再轉彎。\n");
    return 1;  
  }

  dir = turn_dirs[dir];
  tell_object (who,"你揚了揚鞭，調整鏢車的方向。\n");  
  message_vision(query("name", me)+"車頭朝"+chinese_dirs[dir]+
                  "一拐……\n",me);
  set("dir", dir, me);
  return 1;
}

int do_drive (string arg)
{
  object me = this_object();
  object who = this_player();
  string dir=query("dir", me);

  if (! is_in())
    return 0;

  if (! is_driver())
    return 1;

  if (test_busy())
    return 1;

  if( query("speed", me) == 0 )
  {
    tell_object (who,"先讓車子動起來再轉彎。\n");
    return 1;  
  }

  dir = drive_dirs[dir];
  tell_object (who,"你揚了揚鞭，調整鏢車的方向。\n");  
  message_vision(query("name", me)+"車頭朝"+chinese_dirs[dir]+
                  "一拐……\n",me);
  set("dir", dir, me);
  return 1;
}

int do_speedup (string arg)
{
  object me = this_object();
  object who = this_player();
  int s=query("speed", me);

  if (! is_in())
    return 0;

  if (! is_driver())
    return 1;

  if (test_busy())
    return 1;

  if (s == 0)
  {
    s += 2+random(4);
    tell_object (who,"你揮動馬鞭，趕車向前。\n");  
    message_vision ("馬輕嘶一聲，鏢車動了起來。\n",me);
  }
  else if (s < 45)
  {
    s += 4+random(8);
    tell_object (who,"你用力抽了一鞭。\n");  
    message_vision(query("name", me)+"輕輕地加速。\n",me);
  }
  else if (s < 90)
  {
    s += 8+random(16);
    tell_object (who,"你用力抽了一鞭。\n");  
    message_vision(query("name", me)+"嗖地一聲加快了速度！\n",me);
  }
  else 
  {
    s += 16+random(32);
    tell_object (who,"你使勁地抽打馬匹。\n");  
    message_vision(query("name", me)+"發瘋似地加速！\n",me);
  }
  if (s > 320)
    s = 320;
  set("speed", s, me);
  return 1;
}

int do_slowdown (string arg)
{
  object me = this_object();
  object who = this_player();
  int s=query("speed", me);

  if (! is_in())
    return 0;

  if (! is_driver())
    return 1;

  if (test_busy())
    return 1;

  if (s == 0)
  {
    tell_object (who,"車子已經停了。\n");  
  }
  else if (s < 45)
  {
    s -= 4+random(8);
    tell_object (who,"你輕輕地拉了拉韁繩。\n");  
    message_vision(query("name", me)+"慢慢減速。\n",me);
  }
  else if (s < 90)
  {
    s -= 8+random(16);
    tell_object (who,"你拉了拉韁繩。\n");  
    message_vision(query("name", me)+"明顯地慢了下來。\n",me);
  }
  else 
  {
    s -= 16+random(32);
    tell_object (who,"你使勁地拉了拉韁繩。\n");  
    message_vision(query("name", me)+"在飛弛中減速。\n",me);
  }
  if (s < 0)
    s = 0;
  set("speed", s, me);
  return 1;
}

int do_stop (string arg)
{
  object me = this_object();
  object who = this_player();
  int s=query("speed", me);

  if (! is_in())
    return 0;

  if (! is_driver())
    return 1;

  if (test_busy())
    return 1;

  if (s == 0)
  {
    tell_object (who,"車子已經停了。\n");  
  }
  else if (s < 20)
  {
    s = 0;
    tell_object (who,"你猛地一拉韁繩。\n");  
    message_vision(query("name", me)+"輕輕一顛，停了。\n",me);
  }
  else if (s < 45)
  {
    s = 0;
    tell_object (who,"你使勁拉了一下韁繩！\n");  
    message_vision(query("name", me)+"突然急劇地減速！\n",me);
    message_vision ("馬一聲長嘶，，人立起來！\n",me);
    tell_object (who,"你猛地蹌了一下！\n");  
  }
  else if (s < 100)
  {
    s -= 40+random(40);
    tell_object (who,"你瘋狂地拉著韁繩！\n");  
    message_vision(query("name", me)+"突然急劇地減速！\n",me);
    message_vision(query("name", me)+"劇烈地震動著！\n",me);
    tell_object (who,"你一陣頭暈，差一點吐了出來！\n");  
  }
  else 
  {
    s -= 60+random(60);
    tell_object (who,"你不顧一切地拉緊韁繩！\n");  
    message_vision(query("name", me)+"突然急劇地減速！\n",me);
    message_vision(query("name", me)+"可怕地震動著，馬匹口角溢出血來！\n",me);
    tell_object (who,"強烈的震動中你一陣劇烈頭痛！\n");  
    who->unconcious();
  }
  if (s < 0)
    s = 0;
  set("speed", s, me);
  return 1;
}


void collision ()
{
  object me = this_object();
  object who=query("driver", me);
  int s=query("speed", me);
  string *hits = ({
    "沖出了路",
    "滑進路邊的草叢中",
    "撞進一個大土堆",
    "滑進一灘爛泥",
    "闖進一個小木棚",
    "沖向一大叢灌木叢",
    "撞向一片小樹",
  });
  string how;

  if (s == 0)
    how = "極輕地";
  else if (s < 20)
    how = "□當一聲";
  else if (s < 40)
    how = "嘩啦一聲";
  else if (s < 60)
    how = "砰地一聲";
  else if (s < 80)
    how = "轟地一聲";
  else if (s < 100)
    how = "象脫韁野馬一樣地";
  else if (s < 150)
    how = "極瘋狂地";
  else 
    how = "天塌地裂般地";

  if (s < 50)
  {
    message_vision(query("name", me)+how+hits[random(sizeof(hits))]+
                    "。\n",me);
    message_vision(query("name", me)+"停了下來。\n",me);
  }
  else if (s < 100)
  {
    message_vision(query("name", me)+how+hits[random(sizeof(hits))]+
                    "！\n",me);
    message_vision(query("name", me)+"在一陣強烈的震動中停了下來！\n",me);
    tell_object (who,"你一陣目眩！\n");  
  }
  else
  {
    message_vision(query("name", me)+how+hits[random(sizeof(hits))]+
                    "！\n",me);
    message_vision(query("name", me)+"在一陣極可怕的震動中發出巨響！\n",me);
    message_vision ("一切又突然安靜了下來停了下來。\n",me);
    tell_object (who,"你一剎那覺得窗外的所有東西向你猛地撲來又突然停止！\n");  
    who->unconcious();
  }
  set("speed", 0, me);
}

void display_me ()
{
  object me = this_object();
  string name=query("name", me);
  int s=query("speed", me);
  string msg = 0;

  if (s == 0)
  {
    set("short", "停在路上的"+name+"(biaoche)");    
  }
  else if (s < 30)
  {
    set("short", "慢慢行駛的"+name+"(biaoche)");
    msg = name+"慢慢地駛著。\n";
  }
  else if (s < 50)
  {
    set("short", "行駛中的"+name+"(biaoche)");
    msg = name+"正在行駛著。\n";
  }
  else if (s < 110)
  {
    set("short", "飛駛的"+name+"(biaoche)");
    msg = name+"飛快地行駛著。\n";
  }
  else 
  {
    set("short", "狂駛中的"+name+"(biaoche)");
    msg = name+"發瘋似地狂駛著。\n";
  }
  if (msg && 
      random(10) == 0)
    message_vision (msg,me);
}

void check_speed ()
{
  object me = this_object();

  if( query("speed", me)>0 && 
      (!query("driver", me) || 
        environment(query("driver", me)) != me) )
  {
    set("speed", 0, me);
    message_vision(query("name", me)+"沒有鏢頭了。\n",me);
    message_vision(query("name", me)+"吱地一聲歪歪斜斜地停了。\n",me);
  }
}

object find_room (string dest)
{
  object me = this_object();
  object where = environment(me);

  if (!dest)
    return 0;
  return find_object(dest);
}

object find_exit ()
{
  object me = this_object();
  object where = environment(me);
  object who=query("driver", me);
  string dir=query("dir", me);
  object obj = 0;
  mapping dirs;
  string dest;

  if( !mapp(dirs=query("exits", where)) )
  {
    tell_object (who,"這裡好象沒有什麼路可行了。\n");
    return 0;  
  }

  while (obj == 0)
  {
    dest = dirs[dir];
    if (dest)
      obj = find_room(dest);
    if (!dest || !obj)
    {
      dest = dirs[dir+"down"];
      if (dest)
        obj = find_room(dest);
    }
    if (!dest || !obj)
    {
      dest = dirs[dir+"up"];
      if (dest)
        obj = find_room(dest);
    }
    if (!dest || !obj)
    {
        if (random(3) == 0)
          tell_object (who,"前方("+chinese_dirs[dir]+
                           ")沒有什麼路可行了。\n");
        return 0;  
    }

  }

  return obj;
}

void check_move ()
{
  object me = this_object();
  object where = environment(me);
  object exit = 0;

  if( query("speed", me) == 0 )
    return;

  exit = find_exit();

  if (! exit)
  {
    remove_call_out("collision");
    call_out ("collision",1);
  }
  else
  {
    set("car_from/"+query("short", exit),query("short",  where), me);
    message_vision(query("name", me)+"開出"+query("short", where)+"。\n",me);
    me->move(exit);
    message_vision(query("name", me)+"開進"+query("short", exit)+"。\n",me);
  }
}

void automate ()
{
  check_speed ();
  display_me ();
  remove_call_out("check_move");
  call_out("check_move",2); 
  remove_call_out("automate");
  call_out("automate",3);
}
