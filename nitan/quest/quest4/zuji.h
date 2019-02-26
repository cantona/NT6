// Modified by lonely@NT
int zuji_times; 
void zuji_begin(int num)
{
     object killer;
     object killer1;
     int n;

/*
     if( zuji_times < 1 )
     {
        remove_call_out("zuji_begin");
        return;
     }
*/

     if( zuji_times >= 8  )
     {
        remove_call_out("zuji_begin");
        remove_call_out("zuji_new");
        call_out("zuji_new",60,num);
        return;
     }

     zuji_times++;

     message("channel:rumor", MAG"【故事傳聞】只聽得的的馬蹄之聲，一隊契丹武士揮舞着長矛，身背弓箭，指指點點，來到了雁門關外。\n"
        "帶頭大哥道：雖然這些契丹人看似來狩獵的，但不能馬虎，一個也留不得！\n"
        "眾人的暗器便射了出去，鋼鏢、袖箭、飛刀、鐵錐……每件都餵了劇毒。\n"
        "只聽得眾遼人啊啊呼叫，亂成一團，一大半都摔下馬來。\n"
        "眾人一擁而上。刀劍齊施！\n"NOR,users());
     for(n=0;n<num;n++)
     {
          killer=new("/quest/zuji/qidanb");
          killer->move("/d/yanmen/road");
          killer->change_ob();
/*
          killer1=new("/quest/zuji/songb");
          killer1->move("/d/yanmen/shance");
          killer1->change_ob();
*/
     }

     remove_call_out("zuji_begin");
     call_out("zuji_begin",30,num);
     return;
}
              
void zuji_new(int num) 
{
     object killer;
     int n;
/*
     if( zuji_times >= 4 )
     {
*/
          zuji_times=1;
   message("channel:rumor",MAG"【故事傳聞】雁門關外，只見這時，馬蹄聲又響起來，遼人當先的馬匹奔近。\n"
       "只見這些契丹武士身上都披皮裘，或拿長矛，或提彎刀，或彎弓搭箭，或停獵鷹，高歌而來。\n"
       "帶頭大哥一聲長嘯，就是他們了！眾人的暗器便射了出去，鋼鏢、袖箭、飛刀、鐵錐……每件都餵了劇毒。\n"
       "只聽得眾遼人啊啊呼叫，亂成一團，一大半都摔下馬來。\n"
       "眾人一擁而上。刀劍齊施！\n"NOR,users());

     for(n=0;n<num;n++)
     {
          killer=new("/quest/zuji/qidanb");
          killer->move("/d/yanmen/road");
          killer->change_ob();
     }
          remove_call_out("zuji_continue");
          call_out("zuji_continue",60,num);
     return;
}


void zuji_continue(int num)
{
          message("channel:rumor", HIR"【故事傳聞】經過一段時間的殊死"
            +HIR"搏鬥，將這剩下幾人盡數殺了，沒一個活口逃走。！\n"NOR,users()); 
          remove_call_out("zuji_over");
          call_out("zuji_over",30,num);
}
void zuji_over(int num)
{
     object killer,killer1;
     int n;
   message("channel:rumor",MAG"【故事傳聞】只聽得馬蹄聲音，西北角又有兩騎馬馳來，馬上是男女二人。\n"
        "這兩人見到那一十九名武士死在地下，那男子立時神色十分兇猛，向眾人大聲喝問。\n"
        "遼人：$*@!@#$%^&*！\n"
        "鐵塔方大雄舉起一條鑌鐵棍，喝道：兀那遼狗，納下命來！揮棍便向那契丹男子打了過去。\n"
        "那遼人右臂伸出，折斷方大雄右臂關節，將他的身子挑了起來，連人帶棍，一起摔在道旁。\n"
        "遼人：#$%^&*$*@!@！\n"
        "當下六七人一擁而上，向那遼人攻了過去。另外四五人則向那少婦攻擊。\n"
        "那少婦被人一劍便斬斷一條手臂，抱着的嬰兒跌下地來，跟着便被一刀砍去了半邊腦袋。\n"
        "只聽得那遼人眼睛登時紅了，臉上神色可怖之極，暴喝一聲，衝向敵陣。\n"
        ".........\n"
        NOR+HIY"夕陽如血，雁關門外朔風呼號.........\n"NOR,users());
/*
     for(n=0;n<num;n++)
     {
          killer=new("/quest/zuji/qidanb");
          killer->move("/d/yanmen/road");
          killer->change_ob();
     }
*/
          killer1=new("/quest/zuji/xiao");
          killer1->move("/d/yanmen/road");
          killer1->change_ob();
     return;
}
void zuji_close()
{
   string temp;
   int killer_rate,chousha_count;
   object *ulist;
   int k;

   ulist=users();
   k=sizeof(ulist);
   while (k--)
   {
      if( !environment(ulist[k]) || !ulist[k]->query_temp("zuji")) continue;
      ulist[k]->delete_temp("zuji");
      ulist[k]->delte_temp("apply/short");
      ulist[k]->add("combat_exp",20000);
      ulist[k]->add("potential",5000);
      ulist[k]->add("weiwang",20);
           tell_object(ulist[k],HIW"你獲得了"+HIR+chinese_number(20000) 
           +HIW"點經驗和"+HIR+chinese_number(5000)+HIW"點潛能獎勵和"+HIR+chinese_number(20)+HIW"點威望！！\n"NOR);   
   }

  message("channel:rumor",MAG"【故事傳聞】只聽得當的一聲，那遼人擲下短刀，俯身抱起他妻子的屍身和兒子，走到崖邊，\n"
       "湧身便往深谷中跳了下去。忽然間“哇哇”兩聲嬰兒的啼哭，從亂石谷中傳了上來，跟着黑黝黝一件物事從\n"
       "谷中飛上，拍的一聲輕音，正好跌在汪幫主身上。嬰兒啼哭之聲一直不止，正是那個嬰兒。\n"NOR,users());

   zuji_times=0;
   killer_rate=6;
   temp=sprintf("%d",killer_rate);
   write_file("/quest/chousha/killer_rate",temp,1);
   chousha_count=0;
   temp=sprintf("%d",chousha_count);
   write_file("/quest/chousha/chousha_count",temp,1);

   return;
}

void zuji_fail()
{
     remove_call_out("zuji_begin");
     remove_call_out("zuji_new");
     remove_call_out("zuji_continue");
     remove_call_out("zuji_over");
     remove_call_out("zuji_close");
     remove_call_out("remove_enemy");
     call_out("remove_enemy",1);
     return;
}
void remove_enemy()
{
   string temp;
        object *enemys;
        int i, chousha_count;
        mapping my = query_entire_dbase();

   chousha_count=0;
   temp=sprintf("%d",chousha_count);
   write_file("/quest/chousha/chousha_count",temp,1);
        if (arrayp(enemys = children("/quest/zuji/qidanb")))
        {
                for (i = 0; i < sizeof(enemys); i++)
                {
                        if (enemys[i]->is_fighting())
                        {
                                enemys[i]->remove_all_killer();
                                tell_room(environment(enemys[i]), HIW "只見" + enemys[i]->name()
                                        + "突然面色一變，迅速攻出幾招，跳出戰圈轉身逃了。\n");
                        }
                        else {
                                tell_room(environment(enemys[i]), HIW "只見" + enemys[i]->name()
                                        + "掐值一算，突然臉色大變，急急忙忙地逃走了。\n");
                        }
                        destruct(enemys[i]);
                }
        }
        return; 
}

