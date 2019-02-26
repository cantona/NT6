mapping menpai1=([
"玄慈大師":   "少林派",
"宋遠橋":     "武當派",
"滅絕師太":   "峨嵋派",
"洪七公":     "丐幫",
"嶽不羣":     "華山派",
"張無忌":     "明教",
"小龍女":     "古墓派",
"丘處機":     "全真教",
"陳近南":     "雲龍門",
]);

mapping menpai2=([
"丁春秋":     "星宿派",
"洪安通":     "神龍教",
"何鐵手":     "五毒教",
"歐陽峯":     "白駝山",
"慕容復":     "姑蘇慕容",
"邀月宮主":   "移花宮",  
"蘇星河":     "逍遙派",
"天山童姥":   "靈鷲宮",
"黃藥師":     "桃花島",   
]);

string *master1=({
"玄慈大師",
"宋遠橋",
"滅絕師太",
"洪七公",
"嶽不羣",
"張無忌",
"小龍女",
"丘處機",
"陳近南",
});

string *master2=({
"丁春秋",
"洪安通",
"何鐵手",
"歐陽峯",
"慕容復",
"邀月宮主", 
"蘇星河",
"天山童姥",
"黃藥師",   
});

private nosave string fam1;
private nosave string fam2;

int chousha_begin()
{
   int i,j,k;
   object *ulist;


   i=random(sizeof(master1));
   j=random(sizeof(master2));
   ulist=users();
   k=sizeof(ulist);

   fam1=menpai1[master1[i]];
   fam2=menpai2[master2[j]];

   message("channel:chat", HIB"【江湖仇殺】"+master1[i]+
   "："+fam1+"門下弟子聽令，命你們在一個時辰內將\n"
   +fam2+"徹底擊潰，以匡武林正義！\n"NOR,users());

   message("channel:chat", HIB"【江湖仇殺】"+master2[j]+
   "："+fam2+"弟子聽令，命你們在一個時辰內將\n"
   +fam1+"徹底蕩平，讓他們嚐嚐我們的厲害！\n"NOR,users());

   while (k-- )
   {
   if ( !environment(ulist[k]) ) continue;

   if (ulist[k]->query("family/family_name") == fam1)
      ulist[k]->set_temp("chousha/fam",fam2);
   else
   if (ulist[k]->query("family/family_name") == fam2)
      ulist[k]->set_temp("chousha/fam",fam1);
   else
   continue;
   }
   this_object()->set_temp("chousha/fam1",fam1); 
   this_object()->set_temp("chousha/fam2",fam2);
   write_file("/quest/chousha/fam1",fam1,1);
   write_file("/quest/chousha/fam2",fam2,1); 

   call_out("chousha_close",1800);
   return 1;
}


void chousha_close()
{
   object *ulist;
   int k;

   ulist=users();
   k=sizeof(ulist);

   while (k--)
   {
    if ( !environment(ulist[k]) ) continue;
    if (ulist[k]->query_temp("chousha"))
    {
    ulist[k]->delete_temp("chousha");
    tell_object(ulist[k], BLK"忽然你心中生起一股厭倦的感覺，"
    +"開始疑惑的這樣的江湖仇殺有何意義，\n"
    +"你看着自己沾滿鮮血的手，開始不斷地問自己為什麼？為什麼？.....\n"NOR);
    } else
    continue;
   }

   message("channel:rumor", HIB"【江湖仇殺】歷時半月的"+fam1+"與"+fam2
   +"之間的仇殺終於結束了，雙方皆死傷無數！\n"NOR,users());
   this_object()->delete("chousha");
   this_object()->delete_temp("chousha");

   return;
}
