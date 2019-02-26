#include <ansi.h>

mixed names = ({
        ({
        "朱雀外門","青龍外門","白虎外門","玄武外門","天安門",
        "揚州武館","福威鏢局","玄妙觀","靈隱寺","泉州南門",
        "靈州南門","諸葛亮殿","煙雨樓","南陽城","佛山南門",                
        "蛇骨塔","長安樂坊","衡陽西街","喜州城","葛魯城", 
        "北疆小鎮","山海關","老龍頭","長白天池","天山腳下",
        "麗春院","湧泉寺","聽雨軒","五老峯","紫金城",
        "松風觀","終南山腳","抱子巖","白馬潭","昇仙坊",                
        "嘉應門","懸空寺","峻極禪院","俠義廳","蕭家橋", 
        }),
        ({
         "宋兵","流氓","偏將","裨將","佐將","小販","男孩","郭芙","老先生",
                 "小孩","書店老闆","武三通","窮漢","鐵匠","朱子柳","店小二","宋兵",
                 "靜玄師太","靜照師太","宋遠橋","莫聲谷","陸乘風","韓寶駒","黃藥師","餘滄海",
                 "殷野王","鄧百川","尹志平","小龍女","劉承風","歐陽鋒","白衣少女","九翼道人",
                 "阿紫","玉磬子","玉音子","嶽夫人","嶽不羣","令狐沖","玄苦大師","清善比丘",
                 "獨臂神尼","莊夫人","雙兒","吳六奇","木婉清","蕭遠山","李沅芷","向問天",
                 "曲洋","黑白子","程瑤迦","程瑤迦","沐劍屏","天柏道人","本塵","本觀",
                 "天山童姥","韋一笑","謝遜","澄堅","陸乘風","張翠山","宋青書","玄貞道長",
                 "石破天","蘇星河","慕容復","朱丹臣","簡長老","封不平",

        }),
        });

// names need modify
string ask_job()
{ 
  object  ob, me,gift,*team;
  int exp,position;
  string target,myfam,obfam,job_type;
  ob=this_player();
  me=this_object();
  exp=query("combat_exp", ob);
 /*myfam=query("family/family_name", me);//同一門派的才給他job,把這四行去
  obfam=query("family/family_name", ob);//掉後就沒有門派限制
  if(!myfam ||!obfam||myfam != obfam) 
  return "你不是本門弟子,我不能給你工作!";
  */
  if( interactive(ob) && query_temp("zzz_job_target", ob )
      && (int)ob->query_condition("zzz_mission"))  
       return "你上一次的任務還沒完成!";
  if( interactive(ob) && !query_temp("zzz_job_target", ob )
      && (int)ob->query_condition("zzz_mission"))  
       return "你辦事不力，先等會吧。";
   
    if (interactive(ob) &&
       (int)ob->query_condition("zzz_busy"))  
       return "現在我可沒有給你的任務，等會再來吧。\n";
     
        
        if(exp<=100000)     
    return "你的武功太差了,等練強了再來吧。\n";
    job_type="保護";
           set_temp("zzz_job_type", job_type, ob);
        
        if(job_type=="保護")
        {target = names[1][random(sizeof(names[1]))];
    ob->apply_condition("zzz_mission",30);    
        set_temp("zzz_job_target", target, ob);
    message_vision(CYN"$N點了點頭，對$n説道:蒙古人收買了一批武林敗類,好像要暗殺"+target+"，你去保護他一下。\n"NOR , me,ob);
    call_out("begin_kill",30,ob,target);
        return "多加小心。";
        }
}

int accept_object(object who, object ob,object me)
{
        if( query("id", ob) != "corpse"){
                command("say 你給我這個幹嗎?");
                return 0;
        }
        if( !query_temp("zzz_job_target", who)){
                command("say 好啊！不過你得先申請任務。");
                return 0;
        }

/*if( query_temp("zzz_job_type", who) == "殺" )
                if( query("victim_name", ob) != query_temp("zzz_job_target", who )
                         || query("victim_user", ob) || query_temp("zzz_given", who) )
                {       command("shake");
                command("say 你殺錯人了。");
                return 0;
        }*/
        if( query_temp("zzz_job_type", who) == "保護" )
                if( query_temp("must_killby", ob) != query("id", who )
                         || query("victim_user", ob) || query_temp("zzz_given", who) )
                {       command("shake");
                command("say 你殺錯人了。");
                return 0;
        } 

  /*if( query("kill_by", ob) != who){
                command("say 這個任務似乎不是你自己完成的吧？");
                return 0;
        }
set_temp("zzz_given", 1, who); */
        call_out("destroying", 1, ob);
        call_out("ok", 1, who);
        return 1;
}

void ok(object who)
{
        int exp,pot,i;
        if (!who) return;
        command("pat"+query("id", who));
        command("say 乾的好，你辦事幹淨利落,將來必成大器!");
        if( !query("zzz_job_count", who) )
                set("zzz_job_count", 1, who);
        else
                addn("zzz_job_count", 1, who);
                i=query("zzz_job_count", who);
                i/=30;
             exp=800+random(200)+i;
        if( query_temp("zzz_job_super", who) )
        {exp+=100;
                 delete_temp("zzz_job_super", who);
                }
                pot=exp/3+random(10);
                //i=3+random(3)+exp/200;
                
                addn("potential", pot, who);
        addn("combat_exp", exp, who);
        delete_temp("zzz_job_target", who);
        delete_temp("zzz_given", who);
                delete_temp("zzz_job_type", who);
                who->clear_condition("zzz_mission");
          who->apply_condition("zzz_busy",1);  
                                tell_object(who,HIW"你被獎勵了：\n" + 
                       chinese_number(exp) + "點實戰經驗\n" +
                       chinese_number(pot) + "點潛能\n"+
                       NOR);
                return;
}


void destroying(object obj)
{
        destruct(obj);
        return;
}

string ask_fangqi()
{
         object me;
         me = this_player();
         if(me->query_condition("zzz_mission")<=1)
         return "你沒有領任務,跑這裏瞎嚷嚷什麼?";
         me->clear_condition("zzz_mission");
         addn("combat_exp", -100+random(20), me);
          me->apply_condition("zzz_busy",4+random(10));
         delete_temp("zzz_job_target", me);
                 delete_temp("zzz_job_type", me);
         return "沒關係,下次繼續努力 。";
}


void begin_kill(object me,string target)
{  object obj,*ob;
   int i,flag=0;
   if(!me->query_condition("zzz_mission"))
   return;
   if( query_temp("zzz_job_type", me) != "保護" || query_temp("zzz_job_target", me) != target )
   return;
   ob = all_inventory(environment(me));
   for(i=0; i<sizeof(ob); i++)
   {
   if( !living(ob[i])||userp(ob[i])||ob[i]==me ) continue;
   if( query("name", ob[i]) == target )
   {flag=1;
        break;
   }
   }
   if (flag==0)
   { call_out("begin_kill",30,me,target);
     return;           
   } 
        obj=new(__DIR__"killer");
        obj->move(environment(me));
    if( random(10)>7 || query("id", me) == "zzz" )
        {obj->do_copy(me,1);
         set("title", HIR"武林敗類"NOR, obj);
         set_temp("zzz_job_super", 1, me);
        }
        else
        obj->do_copy(me,0);
        set_temp("must_killby",query("id",  me), obj);
        message_vision(GRN"\n$N對着"+target+"發出一陣陰笑聲，令"+target+"全身上下的寒毛根根豎起，不寒而慄。\n"NOR,obj); 
        message_vision(HIY"$N對$n喝道:大膽狂徒,竟敢在這撒野！！\n"NOR,me,obj);    
    message_vision(HIY"$N陰陰一笑:要你多管閒事,去死吧！！\n"NOR,obj);
    obj->kill_ob(me);
}

string ask_gonglao(object who)
{
  object me;
  int i;
           
  me = this_player();
  if( !query("zzz_job_count", me) )
  i=0;
  else 
  i=query("zzz_job_count", me);
  message_vision(CYN"$N對$n説道:你已經完成了" + chinese_number(i) + "次任務。\n"NOR,who,me);
  return "繼續努力吧！";
}
