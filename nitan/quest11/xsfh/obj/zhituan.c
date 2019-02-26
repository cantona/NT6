// by tangfeng 8/2004

#include <ansi.h>
inherit ITEM;

#define QUESTDIR5 "quest/雪山飛狐/寶藏/"
#define QUESTDIR4 "quest/雪山飛狐/武功/"

void create()
{
        set_name(HIW"紙團"NOR, ({ "zhi tuan", "zhituan", "paper"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "一個奇怪的紙團，展開之後似乎紀錄一些內功的運行方法。\n");
                set("unique", 1);
                set("treasure", 1);
                set("material", "silk");
                set("no_give", "這樣東西不能離開你。\n");
                set("no_get", "這樣東西不能離開那兒。\n");
        }
}
void init()
{
          if(!this_object()->query("owner")) return;
     	  add_action("do_yanjiu", "yanjiu");
     	  add_action("do_yanjiu", "find");
}

int do_yanjiu(string arg)
{
	object obj,me = this_player();
	if (!(arg=="zhi tuan" || arg == "zhituan" || arg == "paper")) return 0;
	if ( me->is_busy())
		return notify_fail("你現在正忙着呢。\n");
	if( me->is_fighting() )
		return notify_fail("你無法在戰鬥中做這個事情。\n");
	if (!id(arg))
		return notify_fail("你要翻什麼？\n");
        if( !me->query(QUESTDIR5+"shuku")||me->query(QUESTDIR5+"shuku")<3)
		return notify_fail("你哪裏來的奇怪紙團啊。\n");
	if(this_object()->query("owner")!=me->query("id"))
		return notify_fail("你哪裏來的奇怪紙團啊。\n");
	if (me->query(QUESTDIR4+"lengquanshengong"))
		return notify_fail("你已經明瞭冷泉神功的修煉方法。\n");
  if(!present("tishi ka",me))
  {
  	message_vision(HIY"突然一個人影出現在$N面前，遞給$N一張卡片。\n"NOR, me);
  	tell_object(me,YEL"你低頭一看，是一張提示卡，回頭再一看，人影已經不見——好帥哦~~~~~。\n"NOR);
  	obj=new(__DIR__"tishika");
  	obj->move(me);
	me->start_busy(2);
    tell_object(me,YEL"你還是認真看一下提示卡的內容，不要過於衝動。\n"NOR);
  	return 1;
  }
  //只能一次機會
  //難度係數與原來的凌波微步難度相同
  //降低難度，以前是random(kar)+random(int)>50,現在修改成1個random(kar+int)>50 by lsxk 2007/9/12
  //增加5點難度,畢竟是調用一個random總合來判斷 random (30+30) > 50 這個判斷有點過低 by server 2007/9/14
  //改為54, 1/10概率
  if((random((int)me->query("kar")+(int)me->query("int"))) > 54
      && !random(3) //再增加難度
  //降低難度，以前是random(query_con)+random(query_int)>50,現在修改成1個random(query_con+query_int)>50 by lsxk 2007/9/12
       && (random((int)me->query_con(1)+(int)me->query_int(1))) > 75
	   && me->query("kar")<31)
  {
	  tell_object(me,HIG"你突然發現這線線代表的不是武功祕籍，卻是一個藏寶的地點。\n"NOR);
	  tell_object(me,HIG"你仔細研究紙團的內容，地點應該就在剛才經過的書房裏。\n"NOR);
	  me->set(QUESTDIR4+"lengquanshengong", 1);
	  me->start_busy(2);
	  log_file("quest/FEIHU", sprintf(HIR"%s(%s) 解開冷泉神功。富源：%d；經驗：%d。\n"NOR, me->name(1),me->query("id"), me->query("kar"),me->query("combat_exp")) );
  }
  else
  {
	  tell_object(me,HIY"\n你按照紙團上的這些線線運行全身經脈，發現全無用處，更別説提高武功了。\n"NOR);
	  log_file("quest/FEIHU", sprintf("%s(%s) 試圖解開冷泉神功失敗。經驗：%d。富源：%d。\n", me->name(1),me->query("id"), me->query("combat_exp"),me->query("kar")) );
	  tell_room(environment(me),HIY""+me->name()+"順手丟掉一個紙團。\n"NOR, ({}));
	  if(me->query(QUESTDIR5+"shuku")==2 && me->query("registered")>=3)
	  {
		  tell_object(me,HIR"\n因為VIP身份，你可以繼續使用搜索命令找到另外一張紙團。這也是最後一次機會。\n"NOR);
		  tell_object(me,HIR"但如果你認為目前屬性不好或運氣不佳，可以以後再來這裏搜索，避免機會浪費。\n"NOR);
	  }
	  me->start_busy(2);
	  destruct(this_object());
  }
	return 1;
}
