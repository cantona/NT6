#include <ansi.h>
inherit ITEM;
void set_out(object me);

void create()
{
      set_name("錦繡馬車",({"mache"}));
      set_weight(20000); 
      set("short","錦繡馬車");
      set("id","mache");
set("long","這是巫師出遊用的馬車，鎦金彩旆，\n");  
      set_max_encumbrance (1000000000);
      if (clonep()) {
           set_default_object(__FILE__);
                    }
      else {
      set("material", "wood");
      set("no_sell",1); 
      set("sleep_room",1);
      set("if_bed",1);
      set("no_get",1);
      set("unit", "輛"); 
      set("power",1000);
      set("value",100);
            }
      setup();
}

void init()
{
           add_action("do_jump","jump");    
           add_action("do_out","out");
           add_action("do_look","look"); 
           add_action("do_move","drive"); 

}

int do_jump(string str)
{
     object me = this_player();
     object who = this_object(); 

     if (!objectp(environment(who)) || environment(who)==me) {
            return 0;
              }
     if (!str||str!="biaoche") {
      return notify_fail("你想跳上什麼？\n");
                           }
     message_vision("$N揭起帷簾，走了進去。帷簾隨即又垂了下來。\n",me);
     remove_call_out("set_out");
     call_out("set_out",1,me);
     me->move(who);
     message_vision("帷簾掀起，$N走了進來。\n",me);
     return 1;
}

void set_out(object me)
{
     tell_room(environment(this_object()),"拉車的馬一聲長嘶，甩甩耳朵，準備出發了。\n");
     tell_object(me,"準備完畢，可以出發了！\n");
}

int do_out(string arg)
{
     object me = this_player();
     object who = this_object();

     if (environment(me)!=who) {
           return 0;
               }
     if (!environment(who)) {
           return 0;
               } 
     message_vision("$N掀起帷簾，跳下了車。\n",me);     me->move(environment(who));
     message_vision("馬車的帷簾掀了起來，$N從車裏跳到地上。\n",me);
     return 1;     
} 

int do_rob(string arg)
{
     object me = this_player();
     object who = this_object(); 
     object *humen;
     int i, end;
     if (environment(me)==who) {
           return 0;
               } 
        if( query_temp("get_mission", me) )
      return notify_fail("你是鏢頭耶！\n");

     if (!arg||arg!="biaoche") {
      return notify_fail("你想打劫什麼？\n");
                           }

     message_vision("$N攔住鏢車，高聲叫道：“打劫，車上的人統統給我下來！”\n",me);
     set_temp("stopped", 1, who);
     if (arrayp(all_inventory(who)))  humen = all_inventory(who);
     end = sizeof(all_inventory(who));
     for (i=0; i<end; i++) {
         if (!interactive(humen[i])) continue;
         else {
             tell_object(humen[i],query("name", humen[i])+"，有人來打劫了，快下車幫忙吧！\n");
             humen[i]->move(environment(who));       
                 }  
    }
     tell_object(environment(who),"車上的人跳了下來，擺開架式迎戰。\n"NOR,me);
        return 1;     
}

int do_look(string arg)
{
     object me = this_player();
     object who = this_object();
     object room,*sth,*outsth;
     string str,*str2;
     mapping str1;
     int i, exitcon,objcon,obcon;

     str = "";
     if (arg)  return 0;       
     if (environment(me)!=who)   return 0;
     if (!environment(who))      return 0;
     
     else { 
tell_object(me,"        ______________________\n");
tell_object(me,"       |  _______    _______  |\n");
tell_object(me,"       | |       |  |       | |\n");
tell_object(me,"       | |       |  |       | |\n");
tell_object(me,"       | |_______|  |_______| |\n");
tell_object(me,"       |  _______    _______  |\n");
tell_object(me,"       | |       |  |       | |\n");
tell_object(me,"       | |       |  |       | |\n");
tell_object(me,"       | |_______|  |_______| |\n");
tell_object(me,"       |                      |\n");
tell_object(me,"       |----------------------|\n");
tell_object(me,"       |______________________|\n");
           tell_object(me,query("long", environment(who)));
 
           room = environment(who);
           if( !query("exits", room)){
                    str += "\n    這裏已經沒有路了。\n";
                             }
           else {
           str1=query("exits", room);
           str2 = keys(str1);
           exitcon = sizeof(str2);
           if (exitcon==1) {
                   str += "\n    前面唯一的出口是："+HIG+str2[0]+"。\n"+NOR;
                           }
           else {
              str += "\n    前面的出口有：";
              for (i=0; i<exitcon; i++) {
                    if (i==exitcon-1) {
                       str += "和"+str2[i]+"。\n"+NOR;
                           }
                    else {
                       str += HIG+str2[i]+"、";
                         }
                     }
                 }
           objcon = sizeof(all_inventory(who));
           sth = all_inventory(who);
           str += WHT"    鏢車裏面有：\n"NOR;
           for (i=0; i<objcon; i++) {
                if (!objectp(sth[i])) {
                        continue;
                         }
                else str+=""+HIG+query("name", sth[i])+"\t"+HIG+"("+query("id", sth[i])+")"+"\n"NOR;
                   }
          str += HIW"    鏢車外面有：\n"NOR;
          obcon = sizeof(all_inventory(environment(who)));
          outsth = all_inventory(environment(who));
          for (i=0; i<obcon; i++) {
                if (!objectp(outsth[i])) continue;
                if (query("id", outsth[i])=="biaoche") continue;
                else str += HIG+"    "+query("name", outsth[i])+"\t("+query("id", outsth[i])+")\n"+NOR;
                  }
           write(str);
           return 1;
               }
            }

}
  
int do_move(string arg)
{
     object me = this_player();
     object who = this_object();
     object end;
     mapping exi;
     string *key,*val;
     string filename;
     int i,count;
     
     if (environment(me)!=who) {
             return 0;
                } 
     if( !query_temp("get_mission", me)){
             return notify_fail("你不是鏢頭，不要亂攪和。\n");
                }
     if( query_temp("stopped", who)){
             return notify_fail("有人在劫鏢呢，快護鏢吧。\n");
                }
     if (!arg) {
             return notify_fail("你要去哪兒？\n");
               }
     if( !query("exits", environment(who))){
             return notify_fail("這裏已經沒有路了，你哪兒也去不了。\n");
               }
      exi=query("exits", environment(who));
     key = keys(exi);
     val = values(exi);
     count = sizeof(val);
     for (i=0; i<count; i++) {
          if (arg==key[i]) {
                filename = val[i] + ".c";
                if (file_size(filename)<=0) continue;
                end = load_object(filename);
                tell_room(environment(who),"拉車的馬一聲長嘶，放開四蹄，如離弦之箭般的向着"+query("short", end)+"奔去……\n\n"+NOR);
                tell_room(who,"馬車輕微晃了一下，如離弦之箭般的向着"+query("short", end)+"奔去……\n\n");
                who->move(end);
                if (environment(who)!=end) return 0;
                tell_room(who,"很快，馬車已到了目的地。("+query("short", end)+")\n"+NOR);
                            tell_room(environment(who),"只聽馬蹄聲聲，一輛鏢車開了過來。\n"+NOR);
                return 1;
                   }
           else continue;
             }
           return notify_fail("你確定有這個地方嗎？\n"); 
}
 
int do_open(string arg)
{
     object me = this_player();
     object who = this_object();  
     object silver, env;
     env=environment(who);

        if( query_temp("get_mission", me))return 0;
     if( !query_temp("stopped", who))return 0;

     if (!arg||arg!="biaoche") 
      return notify_fail("你想打開什麼？\n"); 

       if (objectp(who=present("biaotou",environment())))
       return notify_fail("李鏢頭瞪了你一眼喝道：“"+RANK_D->query_self_rude(me)+"，你要幹什麼！”\n");
      silver=new(SILVER_OB);
      set("name", "鏢銀", silver);
      silver->set_weight(0); 
    message_vision("$N打開鏢車，取出了"+query("name", silver)+"。\n",me);
      silver->set_amount(20000+random(20000));
      silver->move(me);  
    message("vision",HIM"\n【謠言】某人：聽説"+HIM+query("name", me)+HIM"在"+HIM+query("short", env)+HIM"把鏢銀劫走啦！\n\n"NOR,users());

      return 1;
}
