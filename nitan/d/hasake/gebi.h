#include <ansi.h>

int valid_leave(object me, string dir)
{
       if( dir == "north")addn_temp("mark/steps", 1, me);
       if( dir == "south")addn_temp("mark/steps", -1, me);
       if( dir == "east")addn_temp("mark/step", 1, me);
       if( dir == "west")addn_temp("mark/step", -1, me);
        
       if( query_temp("mark/steps", me) <= -10 && 
          query_temp("mark/step", me) <= -10){
            me->move("/d/baituo/gebi");
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            tell_room(environment(me), me->name()+"拖着疲憊不堪的身子從戈壁沙漠走了過來。\n",  ({ me }));  
            return notify_fail("突然你眼前出現了一坐小山，形狀宛如駝峯。\n");
            }       
           
       if( query_temp("mark/steps", me) == -12){
            me->move(__DIR__"senlin");
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            tell_room(environment(me), me->name()+"拖着疲憊不堪的身子從戈壁沙漠走了過來。\n",  ({ me }));  
            return notify_fail("突然你走出了大戈壁，來到一森林處。\n");
            }       
           
       if( query_temp("mark/step", me) == 11){
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            me->move(__DIR__"gebi5");
            return notify_fail("");
            }  
       if( query_temp("mark/steps", me) == 11 && 
          query_temp("mark/step", me)<-10){
            me->move(__DIR__"room-ji");
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            tell_room(environment(me), me->name()+"拖着疲憊不堪的身子從戈壁沙漠走了過來。\n",  ({ me }));  
            return notify_fail("啊，出來了！你終於走出大戈壁了！\n");
            }  

       if( (query_temp("mark/steps", me) == 7 && query_temp("gc_n", me)) || 
          (query_temp("mark/steps", me) == -7 && query_temp("gc_s", me)) || 
          (query_temp("mark/step", me) == -7 && query_temp("gc_w", me)) || 
          (query_temp("mark/step", me) == 7 && query_temp("gc_e", me))){
            me->move(__DIR__"lvzhou");
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            delete_temp("gc_n", me);
            delete_temp("gc_s", me);
            delete_temp("gc_w", me);
            delete_temp("gc_e", me);
            tell_room(environment(me), me->name()+"拖着疲憊不堪的身子從戈壁沙漠走了過來。\n",  ({ me }));  
            return notify_fail("運氣真好，你找到了一處沙漠綠洲！\n");
            }
 
       if( (query_temp("mark/steps", me) == 7 && (query_temp("mark/step", me) == 3 || 
           query_temp("mark/step", me) == -3) && query_temp("gc1_n", me)) || 
          (query_temp("mark/steps", me) == -7 && (query_temp("mark/step", me) == 3 || 
           query_temp("mark/step", me) == -3) && query_temp("gc1_s", me)) || 
          (query_temp("mark/step", me) == 7 && (query_temp("mark/steps", me) == 3 || 
           query_temp("mark/steps", me) == -3) && query_temp("gc1_e", me)) || 
          (query_temp("mark/step", me) == -7 && (query_temp("mark/steps", me) == 3 || 
           query_temp("mark/steps", me) == -3) && query_temp("gc1_w", me))){
            me->move(__DIR__"shulin");
            delete_temp("mark/steps", me);
            delete_temp("mark/step", me);
            delete_temp("gc1_n", me);
            delete_temp("gc1_s", me);
            delete_temp("gc1_w", me);
            delete_temp("gc1_e", me);
            tell_room(environment(me), me->name()+"拖着疲憊不堪的身子從戈壁沙漠走了過來。\n",  ({ me }));  
            return notify_fail("咦，你發現這裏已經不是戈壁沙漠了！\n");
            }       
        return ::valid_leave(me, dir);
}

void init()
{
       object me, *ob, *inv, ob1;
       string msg, msg1;
       int i, j;
       me = this_player();
       ob = all_inventory(environment(me));
       msg = YEL"\n突然一股疾風颳到，帶著一大片黃沙，只吹得眾人滿口滿鼻都是沙土，在無邊無際的大沙漠之中，
在那遮天鋪地的大風沙下，便如大海洋中的一葉小舟一般，只能聽天由命，全無半分自主之力。\n"NOR;
       msg1 = HIR"你覺得自己已經筋疲力盡了，身上的黃沙卻越堆越厚……\n"NOR;

       if(ob1 = present("bai shoujuan", me)){
          write(WHT"你依照白手絹上的提示，很快便走出了大戈壁。\n"NOR);
          me->move(__DIR__"caoyuan",1);
          destruct(ob1);
          delete_temp("mark/steps", me);
          delete_temp("mark/step", me);
          tell_room(environment(me), me->name()+"神祕兮兮地從戈壁沙漠走了過來。\n",  ({ me }));  
          write("突然你一不留神，白手絹被風吹走了！\n");
          return;
          }  
       if(userp(me)){ 
         if( query_temp("li_meet", me) == 2){
              message_vision(msg, me); 
              tell_object(me, msg1);
              delete_temp("mark/steps", me);
              delete_temp("mark/step", me);
              me->unconcious();             
              me->move(__DIR__"shulin");
              tell_room(environment(me), "突然一陣輕風吹過，好像有人在你背後出現！\n", ({ me }));  
              return;
              }
         else if( query("water", me)<20 )
              { 
              message_vision(msg1, me);              
                  me->unconcious();
                  me->move(__DIR__"caoyuan"+(1+random(7)));
                  tell_room(environment(me), HIR"突然一陣狂風吹過，掉下一個人來！\n"NOR,  ({ me }));  
                  delete_temp("mark/steps", me);
                  delete_temp("mark/step", me);
                  delete_temp("gc_n", me);
                  delete_temp("gc_s", me);
                  delete_temp("gc_w", me);
                  delete_temp("gc_e", me);
                  delete_temp("gc1_n", me);
                  delete_temp("gc1_s", me);
                  delete_temp("gc1_w", me);
                  delete_temp("gc1_e", me);
              return;
              }
         else if(me->query_skill("dodge", 1) <= 150) { 
              addn("jing", -15, me);
              if( objectp(present("bigu fu", me)) && query("reborn/times", me) < 3 )
              addn("water", -10, me);
              }
         else {
              addn("jing", -5, me);
              if( objectp(present("bigu fu", me)) && query("reborn/times", me) < 3 )
              addn("water", -5, me);
              }
      }
}
