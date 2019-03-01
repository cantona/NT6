  
mapping city_area=([
 "揚州城" : ({"/d/city/","beidajie1","beidajie2","beimen","guangchang",
              "nandajie1","nandajie2","nanmen","qianzhuang","shuyuan",
              "xidajie1","xidajie2","ximen",
            }),
 "泉州城" : ({"/d/quanzhou/","beimen","haigang","jiaxing","jxnanmen",
              "nanhu","nanhu1","nanmen","qzroad1","qzroad2","qzroad3",
              "qzroad4","qzroad5","tieqiang","yanyu","zahuopu","zhongxin",
            }),
 "襄陽城" : ({"/d/xiangyang/","guangchang","eastjie1","eastjie2","eastroad1",
              "eastroad2","jiekou2","northroad2","dingzi","northroad1",
              "jiekou1","westroad2","westroad1","westjie2","westjie1",
            }), 
         ]);

string *city_name=({"揚州城","泉州城","襄陽城"});
string site_name;
int haojie_times;

int place_killer(string site,object ob)
{
     string *location, site_file;
     int size;

     location=city_area[site];
     size=sizeof(location);

     site_file=location[0]+location[random(size-1)+1];
     ob->set("area",site);
     ob->set("place_name",site_file);
     ob->move(site_file);
     return 1;
}

void haojie_begin(int num)
{
     object killer;
     string site_name;
     int n;

     if( haojie_times < 1 )
     {
        remove_call_out("haojie_begin");
        return;
     }

     if( haojie_times >= 4  )
     {
        remove_call_out("haojie_begin");
        remove_call_out("haojie_new");
        call_out("haojie_new",600,num);
        return;
     }

     haojie_times++;

     site_name=city_name[random(sizeof(city_name))];
     message("channel:rumor", HIR"【江湖浩劫】"HIW"江湖英雄令"
            +HIR"重現江湖，號召各路豪傑齊赴"+HIY+site_name+HIR"抵御"
             +HIB"神秘殺手組織"+HIR"之入侵！\n"NOR,users());
     for(n=0;n<num;n++)
     {
          killer=new("/quest/chousha/killer");
          killer->start_escape(600);
          place_killer(site_name,killer);
     }

     remove_call_out("haojie_begin");
     call_out("haojie_begin",60,num);
     return;
}
              
void haojie_new(int num) 
{
     if( haojie_times >= 4 )
     {
          haojie_times=1;
          message("channel:rumor", HIR"【江湖浩劫】經過一段時間的殊死"
            +HIR"搏鬥，雙方皆有傷亡，進入了短暫的休整！\n"NOR,users()); 

          remove_call_out("haojie_begin");
          call_out("haojie_begin",120,num);
     }  

     remove_call_out("haojie_new");
     return;
}

void haojie_close()
{
   string temp;
   int killer_rate,chousha_count;
   object *ulist;
   int k;

   ulist=users();
   k=sizeof(ulist);
   while (k--)
   {
      if( !environment(ulist[k]) || !ulist[k]->query_temp("haojie")) continue;
      ulist[k]->delete_temp("haojie");
      ulist[k]->delte_temp("apply/short");
   }

   message("channel:rumor", HIR"【江湖浩劫】經過各路武林豪傑的殊死抗爭，"
   +HIY"神秘殺手組織"+HIR"稱霸中原武林的陰謀終于暫時宣告破滅，\n江湖中又似乎恢復"
   +"了以往的片刻安平！\n"NOR,users());

   haojie_times=0;
   killer_rate=6;
   temp=sprintf("%d",killer_rate);
   write_file("/quest/chousha/killer_rate",temp,1);
   chousha_count=0;
   temp=sprintf("%d",chousha_count);
   write_file("/quest/chousha/chousha_count",temp,1);

   remove_call_out("haojie_begin");
   remove_call_out("haojie_close");
   return;
}

