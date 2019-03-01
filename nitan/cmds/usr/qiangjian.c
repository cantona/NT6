//MUD強姦命令1.1版
//編程  西遊記--神魔傳說 BT樂樂(adm)

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object obj, old_target;
	int n;
        if(!wizardp(me) ) return notify_fail(HIY"想幹什麼?你瘋了嗎!\n"NOR);
        if((string)me->query("gender") == "女性")
          return notify_fail(RED"想幹什麼?你是女人啊!\n"NOR);

        if( environment(me)->query("no_fight") )
                return notify_fail(HIW" 光天化日之下怎可行淫.\n\n"NOR);
        
        if( me->query("age") <10)
                return notify_fail(HIY" 毛都沒有長齊呢，想幹嘛？\n"NOR);
     

        if( me->query("combat_exp") <= 10)
                return notify_fail(HIY" 你的經驗這麼低，還是練練高吧!\n"NOR);

          if( me->query("con") < 2)
                return notify_fail(HIY" 就你這小身板，還是算了吧!\n"NOR);

        if (!me->query("family/family_name"))
                return notify_fail(HIR"你無門無派，不是江湖中人!\n"NOR);

        if (me->is_busy()) 
                return notify_fail(CYN"你現在正忙著呢！還想幹嘛？\n"NOR);

 

        if(!arg || !objectp(obj = present(arg, environment(me))))
                return notify_fail(CYN" 你想非禮誰？\n"NOR);

        if(!obj->is_character() )
                return notify_fail(CYN" 看清楚一點，那並不是生物。\n"NOR);

        if((string)obj->query("race") == "野獸")
          return notify_fail(CYN" 搞什麼？它又不是人！\n"NOR);

        if(obj==me)     return notify_fail(HIW" 強姦自己? 沒聽說過！\n"NOR);

        if((string)obj->query("gender") == "男性")
          return notify_fail(CYN" 搞同性戀可不行！\n"NOR);


        if((string)obj->query("gender") == "無性")
          return notify_fail(CYN" 他是陰陽人,亂搞什麼嘛!\n"NOR);
        if( !living(obj) )
          return notify_fail("  \n");
        if( me->is_fighting() )
                return notify_fail(HIR"\n專心打架吧！！\n"NOR);

    if( userp(obj) && me->query_condition("pker"))
        return notify_fail("你已經被通輯了，不要再亂殺玩家了！\n");
    if( userp(obj) && obj->query("combat_exp") < me->query("combat_exp") && me->query_condition("pker"))
        return notify_fail("你已經被通輯了，不要再亂殺玩家了！\n");
 
        if (userp(me) && userp(obj)
         && obj->query_temp("nokill") )
        return notify_fail("那人啟用了免戰牌！\n");

        if (userp(me) && userp(obj)
         && me->query_temp("nokill") )
        return notify_fail("你啟用了免戰牌！\n");

    if( userp(me) && userp(obj) && obj->query_condition("nokill")
    && !obj->query_condition("pker"))
        return notify_fail("那個人剛被殺過，放過他吧！\n");

        if((int)obj->query("age") <= 1 && userp(obj))
                return notify_fail(CYN"她還是孩子，放過她吧！\n"NOR); 

        if( obj->query("env/no_fight") )
                return notify_fail(CYN"此人不允許下此指令！\n"NOR); 

        if(obj->query_temp("no_kill"))
                return notify_fail(CYN"此人不允許下此指令！\n"NOR); 


 else {             
                me->start_busy(2);
                obj->start_busy(2);
                message_vision(HIM"\n$N對著$n大叫一聲：寶貝兒，來給大爺我解解饞！\n說著便如狼似虎地向$n沖了過去！\n\n"NOR, me, obj);
                message_vision(HIC"$n對著$N大喝一聲："+RANK_D->query_rude(me)+"你休想，看招！\n"NOR, me, obj);
                me->fight_ob(obj);
                obj->fight_ob(me);
                   //設定兩者為敵對關系
                obj->remove_all_enemy(); //暫時停止，好讓下面程序運行
                for(n=0;n<=random(6)+1;n++)
               {
                if( obj && me && environment(me) && present(obj, environment(me)) )   COMBAT_D->do_attack(obj, me, obj->query_temp("weapon") );
                }
            if((int)me->query("kee") <= (int)me->query("max_kee")*3/4)
                call_out("do_leave",1,me,obj);
  else{        
                call_out("do_qiangjian", 2, me, obj); 
                call_out("do_look", 6, me, obj);
                call_out("do_look1", 8, me, obj);

       if((int)obj->query("per") > 22){                //考慮到差異，所以這裡要分支
                call_out("do_qiangjian1", 14, me, obj);
                call_out("do_qiangjian2", 18, me, obj);
                call_out("do_qiangjian3", 22, me, obj);
                call_out("do_qiangjian4", 26, me, obj); //懲罰函數調用
                call_out("do_qiangjian5", 32, me, obj);
                call_out("do_qiangjian6", 38, me, obj);  //倒
                call_out("do_qiangjian7", 49, me, obj);
                call_out("do_qiangjian8", 61, me, obj);
                call_out("do_qiangjian9", 62, me, obj);

                call_out("do_wakeup",70,me,obj);
                call_out("do_kill",71,me,obj);  
  }   else{
        if((int)obj->query("per") > 17){   
                call_out("do_qiangjian2", 14, me, obj);
                call_out("do_qiangjian4", 19, me, obj); 
                call_out("do_qiangjian6", 25, me, obj);                
                call_out("do_qiangjian7", 31, me, obj);
                call_out("do_qiangjian10", 45, me, obj);
                call_out("do_qiangjian9", 47, me, obj);
                call_out("do_wakeup",57,me,obj);
                call_out("do_kill",58,me,obj);
                                
   }else{
                call_out("do_puke",11,me,obj);      
         }   
      }
      }        
      }
        return 1;   
}

void do_leave(object me,object obj)
{
        
        if(objectp(present(obj,environment(me)))){
        tell_object(me,HIY"\n看來"+(string)obj->query("name")+"不好惹，你決定還是打消念頭，走開為好！\n"NOR, me, obj); 
        tell_object(obj,HIY"\n看來你的武功已讓"+(string)obj->query("name")+"心生怯意了.他邊打邊退，似乎想逃!"NOR);
        me->set("wimpy",90);
        me->start_busy(1);
        call_out("do_hit",0,me,obj);
        call_out("do_setwimpy",5,me,obj);
 }    return;
}

void do_hit(object me, object obj)
{
        if(objectp(present(obj,environment(me)))){
      message_vision(HIC"\n$n對著$N大喝一聲:"+RANK_D->query_rude(me)+"，想走? 沒門！嘗嘗本"+RANK_D->query_respect(obj)+"厲害再說！\n"NOR,me, obj);   
                COMBAT_D->do_attack(obj, me, obj->query_temp("weapon") );
                COMBAT_D->do_attack(obj, me, obj->query_temp("weapon") );
                me->fight_ob(obj);
                obj->fight_ob(me);
//                me->move(random(sizeof(keys(environment(me)->query("exits")))));
  }
        return;
}
void do_setwimpy(object me,object obj)
{
      

                me->set("wimpy",20);
        return;
}
           
void do_qiangjian(object me, object obj)
{
        mapping my_family;
        string my_fam;
        my_family = me->query("family"); 
        my_fam = my_family["family_name"];
        if(objectp(present(obj, environment(me)))) {
                me->start_busy(100);
                obj->start_busy(100);
        if( !living(obj) )
        message_vision(CYN"\n$N對著昏倒在地的$n笑道:昏了正好，昏了才是睡美人嘛!\n$N緩步來到$n身前，扶起$n的軀體。\n"NOR, me, obj); 
       else{
        message_vision(HIM"\n$N擋住了$n的拼命攻擊,並且抓住機會一把將$n緊緊抱住.\n\n"NOR, me, obj);
        tell_object(me,HIY"看來她被你緊緊抱住，沒了力氣，只有任你宰割了！\n"NOR);               

        tell_object(obj,HIY"\n你還想作拼死反抗。\n無奈被對方緊緊抱住,只覺渾身軟弱無力，什麼也作不了。\n\n"NOR);
               obj->set_temp("block_msg/all", 1);  
               environment(obj)->add_temp("no_fight",1);
               environment(obj)->add_temp("sleeping_person", 1);
               obj->set("hunmi",1);
           }  
	       CHANNEL_D->do_channel(this_object(), "rumor",
	       sprintf("我看見%s的%s正在幹壞事!!!!!!!", my_fam, me->name(1))); 
                                                  }     //為pksex埋下伏筆
           return;
}

void do_look(object me,object obj)
{     
        
        if(objectp(present(obj, environment(me)))) {
        message_vision("\n由于近在咫尺，$N又忍不住仔細端詳了$n一下\n", me, obj);
                                                   }
           return;
}
void do_look1(object me,object obj)
{     
    
        
        if(objectp(present(obj, environment(me)))) {
   tell_object(me,HIM"\n你望了望附近，看了看，沒人注意你，不由的.....\n"NOR);
                                                   }
           return;
}

void do_puke(object me, object obj)
{
     if(objectp(present(obj, environment(me)))) {
        message_vision(CYN"\n$N稀裡哇啦地吐了一地。\n"NOR, me,obj);
        tell_object(me,HIY"你不由得對自己說：天啦，這世上還有這麼醜的女人，我還是站遠些好！\n"NOR);    
        message_vision("\n$N遠遠地推開$n,苦笑著說："+RANK_D->query_respect(obj)+"，如此‘尊容’，在下實在無福消受\n剛才唐突，還望見諒，咋們後會無期！\n",me,obj); 
        message_vision(CYN"\n接著$N又是一陣狂吐。\n"NOR,me,obj);
        me->start_busy(1);
        obj->start_busy(1);
}
         return;
}

void do_qiangjian1(object me,object obj)  
{
     
      
        if(objectp(present(obj, environment(me)))) {
        message_vision("接著，$N的大手不顧$n的掙紮在$n的身上來回上下遊走.......\n", me, obj);   

}

        return;
}
void do_qiangjian2(object me,object obj)  
{
       
 
        if(objectp(present(obj, environment(me)))) {
        message_vision("\n好一會兒,$N再也按捺不住心中的欲火，將$n身上的衣物一件一件地扯下\n", me, obj);

}

        return;
}
void do_qiangjian3(object me,object obj)  
{
    
      
        if(objectp(present(obj, environment(me)))) {
        message_vision("\n經過一番撕扯，$n的衣物已經七零八落地散落地上，身上只剩\n", me, obj);
        message_vision("件肚兜遮羞，光滑柔嫩的肩背展現在$N的眼前！真是風景無限！\n", me, obj);
        if((int)obj->query("per") >= 30){
        message_vision("\n只見$n渾身肌膚雪白，晶瑩剔透,婉如玉人。\n",me,obj);}
 }
     return;
}

void do_qiangjian4(object me,object obj)       //為了增加隨機性,以年齡和容貌為指標
                                               //建立此函數,由于編者是站在正義這方的
                                               //所以此函數是用來懲罰命令使用者的
{      
       
       
         if(objectp(present(obj, environment(me)))) {

         if((int)obj->query("age") <= 18 ) {
        
         message_vision(HIM"\n這時$N瞥見了$n手臂上的'守宮砂',原來$n還是處女呢!\n"NOR, me, obj);
         if((int)obj->query("per") >= 30 )
         tell_object(me,HIY"\n這下可把你樂壞了，如此羞花閉月的處女還真是少見。\n"NOR);
         if((int)obj->query("combat_exp") <= 5000) {
           me->add("combat_exp", -(int)obj->query("combat_exp")/30);        
         }else{
           me->add("combat_exp", -(int)obj->query("combat_exp")/50);
              }
           me->add("gin",-random(200));   
                                                       
                                          }
                                          
else{
        if((int)obj->query("age") <= 30 ) {

         message_vision(HIM"\n雖說已不再是處女,但身為少婦的$n那豐滿的身體曲線也讓$N垂涎三尺!\n"NOR, me, obj);
           me->add("gin",-random(300));   
         if((int)obj->query("combat_exp") <= 5000) {
           me->add("combat_exp", -(int)obj->query("combat_exp")/30);
//           me->add("potential", -random((int)me->query("potential")/4));       
         }else{
           me->add("combat_exp", -(int)obj->query("combat_exp")/50);
              }

         }else{ 
           if((int)obj->query("age") >= 55 ) {
         message_vision(HIM"\n看來$N已經饑渴到饑不擇食的地步了,連$n這樣的老太太也不放過!\n"NOR, me, obj);
         message_vision(HIW"\n小心招天譴!!!\n"NOR, me, obj);
           me->add("gin",-random(500));   
         if((int)obj->query("combat_exp") <= 5000) {
           me->set("combat_exp",random((int)me->query("combat_exp")/4));    //懲罰亂用此命令者
         }else{
           me->add("combat_exp", -random((int)me->query("combat_exp")/15));
              }
         }else{
         message_vision(HIM"\n$n雖已是徐娘半老,但尤存之風韻仍讓$N大感刺激!\n"NOR, me, obj); 
           me->add("gin",-random(300));   
         if((int)obj->query("combat_exp") <= 5000) {
           me->add("combat_exp", -random((int)me->query("combat_exp")/10));
         }else{
           me->add("combat_exp", -random((int)me->query("combat_exp")/20));
                                                 
              }
              }
              }
     }
                                                   }
        return;
}
void do_qiangjian5(object me,object obj)  
{
        
        
        if(objectp(present(obj, environment(me)))) {
        message_vision("\n$N大手一揮，$n身上僅剩的肚兜也落下地了！這一下溫香滿懷，\n", me, obj);
        message_vision("舒服得$N只想喊娘！\n", me, obj);
}

        return;
}
void do_qiangjian6(object me,object obj)  
{
    
       

        if(objectp(present(obj, environment(me)))) {
        message_vision(HIM"\n接著$N一把將$n按倒在地上。。。。。\n"NOR, me, obj);

}

        return;
}
void do_qiangjian7(object me,object obj)  
{
       
        

        if(objectp(present(obj, environment(me)))) {
        message_vision("\n$N騎在$n身上，用手撫摸著$n的雙乳。\n"NOR, me, obj);
        message_vision("。。。四周充斥著$N那野獸般的吼叫聲和$n撕心裂肺的哭聲。。。\n", me, obj);
}

        return;
}
void do_qiangjian8(object me,object obj)  
{
        
     

        if(objectp(present(obj, environment(me)))) {
        message_vision(HIM"\n良久，風停雨歇。。。。\n"NOR, me, obj);
        message_vision("$N掙紮著爬了起來，對著昏睡在地的$n滿足地淫笑了一下。\n", me, obj);

}
        return;
}
void do_qiangjian9(object me,object obj)  
{	
        mapping my_family;
        string my_fam;
     
      
        my_family = me->query("family"); 
        my_fam = my_family["family_name"];	


        if(objectp(present(obj, environment(me)))) {
        message_vision(HIR"\n這時只見$N搖搖晃晃，立足不穩。\n"NOR, me,obj);
        tell_object(me,HIR"\n原來你發現自己全身乏力，看來是虛耗過度了！\n\n"NOR);
        me->set("kee",(int)obj->query("kee")/2);

					CHANNEL_D->do_channel(this_object(), "rumor",
					sprintf("%s被%s的%s強姦了。",obj->name(1), my_fam,me->name(1)));
					CHANNEL_D->do_channel(this_object(), "rumor",
					sprintf("%s被官府通緝了。", me->name(1)));

        me->start_busy(1);
        me->apply_condition("pker", 180 +
			me->query_condition("pker"));
        me->apply_condition("sexman", 180 +
			me->query_condition("sexman"));
        me->add("PKS",1);
        me->add("pker",1);
}
        return;
}

void do_qiangjian10(object me,object obj)  
{
      
     
        if(objectp(present(obj, environment(me)))) {
        message_vision(HIM"\n良久，風停雨歇。。。。\n"NOR, me, obj);
        message_vision("$N爬了起來，對著昏睡在地的$n失望地嘆了一下氣：真他媽的倒霉,讓老子遇到這種'水貨'。\n", me, obj);
}
        return;
}
void do_wakeup(object me,object obj)
{
        
        

               obj->set("hunmi",0);            
               obj->set_temp("block_msg/all", 0);
	   if (!environment(obj)->query("sleep_room") && !environment(obj)->query("hotel"))
	       environment(obj)->set("no_fight",0);
     	       environment(obj)->add_temp("sleeping_person", -1);
               obj->set("kee",(int)obj->query("max_kee"));
               obj->set("gen",(int)obj->query("max_gen"));
               tell_object(obj,HIC"\n看來你的力氣恢復得差不多了！\n"NOR);
               message_vision(HIY"\n$N慢慢地爬了起來！\n"NOR,obj);
               obj->start_busy(1);

        return;
}
void do_kill(object me,object obj)    
{
       
    

                if(objectp(present(obj, environment(me)))) {
         if((int)obj->query("age") <= 18)
     {
      message_vision(HIC"\n$n滿面淚痕地對著$N大喝一聲:"+RANK_D->query_rude(me)+"休逃，你毀我貞操，我和你拼了！\n\n"NOR,me, obj);
                me->kill_ob(obj);
                obj->kill_ob(me);
     }else{  
         if((int)obj->query("age") <= 30)
     {
      message_vision(HIC"\n$n滿面淚痕地對著$N大喝一聲:"+RANK_D->query_rude(me)+"休逃，你污我身體，讓我怎生作人,\n索性和你拼了！\n\n"NOR,me, obj);
                me->kill_ob(obj);
                obj->kill_ob(me);
     }else{         
         if((int)obj->query("age") <= 55){
           message_vision(HIW"\n$n對著$N大喝一聲:"+RANK_D->query_rude(me)+"休逃，你辱我清白，我和你拼了！\n\n"NOR,me, obj);
                me->kill_ob(obj);
                obj->kill_ob(me);
     }else{
           message_vision(HIW"\n$n對著$N大喝一聲:"+RANK_D->query_rude(me)+"休逃，你讓我晚節不保，我這條老命還留著作甚，\n索性和你拼了\n\n"NOR,me, obj);
                me->kill_ob(obj);
                obj->kill_ob(me);
     }
     }
     }
                                                         }
        return;
}

int help(object me)
{
  write(@HELP
指令格式 : qiangjian <人物>
   
   江湖中無風不起浪,武俠的世界裡總是少不了採花賊的，
象金庸先生筆下的田伯光等,這個命令正是留給他們的.
但當採花賊不僅對修為不利,而且還要面對滿街的討打聲，
沒有一點真本事,可有點受不了。
   有道是'多行不義必自斃'，用之者慎之！慎之！
當然正人君子莫為之！
HELP
    );
    return 1;
}
