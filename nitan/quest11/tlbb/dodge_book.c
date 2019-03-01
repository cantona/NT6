//By Spiderii@ty 從新編寫,徹底完善
// By Spiderii@ty 加入天賦系統

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW"帛卷"NOR, ({ "bo juan", "bojuan", "book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "一本爛的不成樣子的帛制長卷。\n"); 
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
		return notify_fail("你現在正忙著呢。\n");
	if( me->is_fighting() ) 
		return notify_fail("你無法在戰鬥中做這個事情。\n");
	if (!id(arg))
		return notify_fail("你要翻什麼？\n");
	if(this_object()->query("owner")!=me->query("id"))
		return notify_fail("你哪裡來的這個東西啊。\n");
	if (me->query("quest/天龍八部/武功/pass"))
		return notify_fail("帛卷中所記載的內容對你來說已經了然于胸了。\n");
              
       if (me->query_temp("find") < 8 ){
              write("你仔細翻看著被撕的破爛的帛卷，希望能從中找出點什麼。\n");
              me->add_temp("find", 1);         
              return 1;
         }
  //難度系數加大,畢竟是sj第一dodge
  if((random(me->query("kar"))+random(me->query("int"))) > 38
           && (random(me->query_dex(1))+random(me->query_int(1))) > 60
         && random(me->query("kar")) <31
           && random(me->query("kar"))>25
           && ((!me->query("buyvip")&&random(5)==1)||(me->query("buyvip")&&random(4)==1)))
  {
	  tell_object(me,HIG"你翻到最後，不由得大為狂喜，這部分並沒有被撕爛，題著“凌波微步”四字。\n"NOR);
	  tell_object(me,HIG"其後繪的是無數足印，注明“婦妹”、“無妄”等等字樣，盡是易經中的方位。\n"NOR);
         tell_object(me,HIG"只見足印密密麻麻，不知有幾千百個，自一個足印至另一個足印均有綠線貫串。\n"NOR);
	  tell_object(me,HIG"線上繪有箭頭，料是一套繁復的步法。最後寫著一行字道：“猝遇強敵，以此。\n"NOR);
	  tell_object(me,HIG"保身，更積內力，再取敵命。\n"NOR);
	  me->set("quest/天龍八部/武功/pass",1);
         me->set("quest/天龍八部/武功/read", 1);
         me->delete_temp("find");
	  me->start_busy(2);
	  log_file("quest/lbwb", sprintf(HIR"%s(%s) 學會凌波微步。富源：%d；經驗：%d。\n"NOR, me->name(1),me->query("id"), me->query("kar"),me->query("combat_exp")) );
  }
  else
  {
	  tell_object(me,HIY"\n你翻到最後發現帛卷撕的亂七八糟，什麼都看不清，根本無法從裡面學到東西。\n"NOR);
	  log_file("quest/lbwb", sprintf("%s(%s) 試圖解開凌波微步失敗。經驗：%d。富源：%d。\n", me->name(1),me->query("id"), me->query("combat_exp"),me->query("kar")) );
	  tell_room(environment(me),HIY""+me->name()+"懊惱之下,順手將帛卷扔到了地下。\n"NOR, ({}));
	  me->start_busy(2);
	  destruct(this_object()); 
  }
	return 1;	    
}
int do_du(string arg)
{
        object me = this_player();
        if (!(arg=="bo juan" || arg == "bojuan" || arg == "book"))
        return 0;
        if( me->is_busy()) 
            return notify_fail("你現在正忙著呢。\n");
        if( me->is_fighting() ) 
            return notify_fail("你無法在戰鬥中專心下來研讀新知！\n");
        if(!id(arg))
             return notify_fail("你要讀什麼？\n");
	 if (!me->query("quest/天龍八部/武功/pass"))
             return notify_fail("帛卷撕的亂七八糟，什麼都看不清，你無法從裡面學到東西。\n");
        if (!me->query("quest/天龍八部/武功/read"))
             return notify_fail("帛卷撕的亂七八糟，什麼都看不清，你無法從裡面學到東西。\n");
	 if((int)me->query("jing") < 25 )
             return notify_fail("你現在過于疲倦，無法專心下來研讀新知。\n");        
	 if((int)me->query("neili") < 35 )
             return notify_fail("你內力不夠，無法專心下來研讀新知。\n");        
        if((int)me->query_int() < 34)
             return notify_fail("你的悟性不足鑽研這麼高深的武功。\n");
        if((int)me->query_skill("literate", 1) < 100)
             return notify_fail("你看不懂這上面所寫的文字。\n"); 
        if((int)me->query("max_neili") < 1200 )
             return notify_fail("你內力修為不夠，無法鑽研這麼高深的武功。\n");
        if((int)me->query("combat_exp")< 200000)
             return notify_fail("你的實戰經驗不夠，無法鑽研這麼高深的武功。\n"); 
        if( me->query_skill("lingbo-weibu", 1) > 180)
	     return notify_fail("你研讀了一會兒，覺得書上講的步法，如果不身體力行的練習是無法領會的。\n");
        //天賦“領悟大師”影響效果：  by spiderii@ty ..lsxk想法太過變態了
        if(me->query("relife/quest/lwds")){
         if(random(100) > me->query("relife/quest/lwds")*10)
            write(HIC"你經過轉世重修後，領悟到了武技萬變不離其宗的道理，瞬間領悟到了凌波微步的精華所在。\n"NOR);
            me->set_skill("lingbo-weibu",180);
            }

          me->receive_damage("jing", 15);
          me->add("neili",-(int)me->query_skill("lingbo-weibu", 1)/2);  
          me->improve_skill("lingbo-weibu", (int)me->query_skill("literate", 1)/3+1);
          write("你仔細研讀著帛卷上的步法。\n");
        
         return 1;
}

