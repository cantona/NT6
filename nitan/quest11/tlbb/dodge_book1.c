#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC"帛卷"NOR, ({ "bo juan", "bojuan", "book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "一本帛制長卷，質地柔軟堅韌，不知道什麼材質織成，正是逍遙派無崖子所藏祕籍。\n"); 
                set("unique", 1);
                set("treasure", 1);
                set("material", "silk");
                set("no_give", "這樣東西不能離開你。\n");
                set("no_get", "這樣東西不能離開那兒。\n");
        }
}


void init()
{
             add_action("do_du", "read");
     	      add_action("do_fan", "fan");	
      	      add_action("do_fan", "find");
}

int do_fan(string arg)
{
	object obj,me = this_player();    
    		       
	if (!(arg=="bo juan" || arg == "bojuan" || arg == "book")) return 0;
	if ( me->is_busy()) 
		return notify_fail("你現在正忙着呢。\n");
	if( me->is_fighting() ) 
		return notify_fail("你無法在戰鬥中做這個事情。\n");
	if (!id(arg))
		return notify_fail("你要翻什麼？\n");

	if(this_object()->query("owner")!=me->query("id"))
		return notify_fail("你哪裏來的這個東西啊。\n");

	if (me->query("quest/天龍八部/武功/pass") && me->query("quest/天龍八部/北冥神功/pass") )
		return notify_fail("帛卷中所記載的內容對你來説已經瞭然於胸了。\n");

       if (me->query_temp("find") < 8 ){
              write("你緩緩展開帛卷，只見裏面密密麻麻的都是一些圖形和文字，正是逍遙無崖子所藏的武功祕籍。\n");
              me->add_temp("find", 1);         
              return 1;
         }
  
write("你仔細翻看着帛卷裏所記的逍遙派武學，武學修為大有進展。\n");

   if(   (random(me->query("kar"))+random(me->query("int"))) > 30
           && (random(me->query("dex"))+random(me->query("int"))) > 30
           && random(me->query("kar")) <31
           && random(me->query("kar"))> 20 )
  {
	  tell_object(me,HIG"你翻到最後，不由得大為狂喜，這部分並沒有被撕爛，題着“凌波微步”四字。\n"NOR);
	  tell_object(me,HIG"其後繪的是無數足印，註明“婦妹”、“無妄”等等字樣，盡是易經中的方位。\n"NOR);
         tell_object(me,HIG"只見足印密密麻麻，不知有幾千百個，自一個足印至另一個足印均有綠線貫串。\n"NOR);
	  tell_object(me,HIG"線上繪有箭頭，料是一套繁複的步法。最後寫着一行字道：“猝遇強敵，以此。\n"NOR);
	  tell_object(me,HIG"保身，更積內力，再取敵命。\n"NOR);
	  me->set("quest/天龍八部/武功/pass",1);
         me->set("quest/天龍八部/武功/read", 1);
         me->delete_temp("find");
	  me->start_busy(2);
         me->set_skill("lingbo-weibu",1);
	  log_file("quest/lbwb", sprintf(HIR"%s(%s) 通過無崖子祕籍學會凌波微步。富源：%d；經驗：%d。\n"NOR, me->name(1),me->query("id"), me->query("kar"),me->query("combat_exp")) );
  }

 if(   random(me->query("kar"))>20
        && me->query("kar") <31 
        && random(me->query("pur") )>20
        && me->query("pur") <31
      && ( random(5) ==1 ||( me->query("buyvip")&& random(3)==1 ) )
 ) { 
       tell_object(me,HIC"你戰戰兢兢的打開綢包，裏面是個捲成一卷的帛卷展將開來，\n"+
                        "第一行寫着“北冥神功”。字跡娟秀而有力，便與綢包外所書\n"+
                        "的筆致相同。其後寫道：“莊子‘逍遙遊’有云：‘窮髮之北\n"+
                        "有冥海者，天池也。有魚焉，其廣數千裏，未有知其修也。’\n"+
                        "又云：‘且夫水之積也不厚，則其負大舟也無力。覆杯水於坳\n"+
                        "堂之上，則芥為之舟；置杯焉則膠，水淺而舟大也。’是故本\n"+
                        "派武功，以積蓄內力為第一要義。內力既厚，天下武功無不為\n"+
                        "我所用，猶之北冥，大舟小舟無不載，大魚小魚無不容。是故\n"+
                        "內力為本，招數為末。以下諸圖，務須用心修習。”\n\n"NOR);

       me->set("quest/天龍八部/北冥神功/pass",1);
      if(!me->query_skill("beiming-shengong")) 
                 me->set_skill("beiming-shengong",1);
          
          message_vision(HIC"\n你的「北冥神功」進步了！”\n"NOR,me); 
          message_vision(HIC"\n你儼然已參透了帛卷中的武功絕學，以後就要靠你自己練習了！”\n"NOR,me); 
      me->start_busy(2);
      me->set("quest/天龍八部/北冥神功/time", time());
      me->set("quest/天龍八部/北冥神功/combat_exp",me->query("combat_exp"));
     if(!me->query_skill("beiming-shengong"))  me->set_skill("beiming-shengong",1);
     log_file("quest/bmsg", sprintf(HIR"%s(%s) 通過無崖子祕籍學會北冥神功。富源：%d；經驗：%d。\n"NOR, me->name(1),me->query("id"), me->query("kar"),me->query("combat_exp")) );
    }

  else
  {
	  tell_object(me,HIY"\n你翻到最後發現帛卷已經過於陳舊，什麼都看不清了，只得作罷。無法從裏面學到東西。\n"NOR);
	  log_file("quest/lbwb", sprintf("%s(%s) 試圖閲讀無崖子祕籍失敗。經驗：%d。富源：%d。\n", me->name(1),me->query("id"), me->query("combat_exp"),me->query("kar")) );
	  tell_room(environment(me),HIY""+me->name()+"懊惱之下,順手將帛卷扔到了地下。\n"NOR, ({}));
	  me->start_busy(2);

  }
message_vision(HIC"\n你還待翻閲，卻發現帛卷因為過於陳舊，已經化為飛灰，不復辨識了。！”\n"NOR,me); 
       destruct(this_object()); 
	return 1;	    

}


