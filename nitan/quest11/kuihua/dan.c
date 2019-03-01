// By action@SJ 作弊專用
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW"Quest秘籍"NOR, ({ "yangjing dan","dan" }) );
        set_weight(10);
                set("unit", "本");
                set("long", "一本可以增加Quest機會的書籍。\n");
                set("no_drop", "這樣貴重的東西怎麼能隨便亂丟呢。\n");
                set("no_get", "這樣東西不能離開那兒。\n");
                set_weight(100);
	              set("value",3000000);
	              set("no_give",1);
	              set("treasure",1);
	              set("degree",1);
	              set("flag","spec/jiemi");
	              set("rest",0);
	              set("desc","一本可以增加Quest機會的書籍！");
	              set("credit",1000);

       setup();
}/*
void init()
{
        add_action("do_eat", "read");
}

int do_read(string arg)
{
	object me = this_player();
	
	if(arg!="miji")
             return notify_fail("你要服用什麼?\n");
       if (me->is_busy()) {return notify_fail("你正忙著呢。\n");}
	if (!me->query("wizard/jiemi")<10)
	{
		tell_object(me, HIR"你讀完Quest秘籍，朦朧間你仿佛看到了如下選擇：\n"NOR);
		tell_object(me, HIR"1：九陰上Quest解謎。\n"NOR);
		tell_object(me, HIR"2：九陰下Quest解迷。\n"NOR);
		tell_object(me, HIR"3：冷泉神功Quest解謎。\n"NOR);
		tell_object(me, HIR"4：蛤蟆功Quest解謎。\n"NOR);
		tell_object(me, HIR"5：凌波微步Quest解迷。\n"NOR);
		tell_object(me, HIR"6：葵花寶典Quest解謎。\n"NOR);
		tell_object(me, HIR"7：左右互搏Quest解謎。\n"NOR);
		tell_object(me, HIR"8：凝血神爪Quest解謎。\n"NOR);

		tell_object(me, HIR"你想要得到的是："NOR);
		input_to("get_gift", 1);
	}
	else
		tell_object(me, HIR"你的機會都已經使用過了!\n"NOR);
	return 1;
}

void get_gift(string arg)
{
	object me = this_player();
	int select;
	string str;
	
	if (!sscanf(arg, "%d", select))
	{
		tell_object(me,HIR"你只能選擇1-8中的一個，請重新選擇："NOR);
		input_to("get_gift", 1);
		return;
	}
	switch (select)
	{
		case 1: if (me->query("quest/jiuyin1/pass"))
			{
				tell_object(me, HIC"你已經學會了九陰神功上卷。請重新選擇："NOR);
				input_to("get_gift", 1);
				return;
			}
                    if(me->query("id")=="action" ||(random(me->query("kar"))+random(me->query("int"))) > 50
	                && (random(me->query_dex(1))+random(me->query_int(1))) > 75
	                && random(me->query("kar"))>28){
                     	  tell_object(me,HIG"恭喜,你領悟了九陰神功的上卷。\n"NOR);
                              CHANNEL_D->do_channel(this_object(), "rumor",me->name(1) + "機緣巧合之下,從元旦禮品中領悟了" + HIW + "九陰神功上卷" + NOR + "。\n");
	                       me->set("quest/jiuyin1/pass",1);
                      }
			str = "你使用了一次解迷機會。\n";
			break;
		case 2: if (me->query("quest/jiuyin2/pass"))
			{
				tell_object(me, HIC"你已經學會了九陰神功下卷。請重新選擇："NOR);
				input_to("get_gift", 1);
				return;
			}
						
	              if(random(me->query_kar()) > 22){
                     	  tell_object(me,HIG"恭喜,你領悟了九陰神功的下卷。\n"NOR);
                              CHANNEL_D->do_channel(this_object(), "rumor",me->name(1) + "機緣巧合之下,從元旦禮品中領悟了" + HIW + "九陰神功下卷" + NOR + "。\n");
                              me->set("quest/jiuyin2/pass",1);
                     }
			str = "你使用了一次解迷機會。\n";
			break;	
		case 3: if (me->query("quest/雪山飛狐/武功/lengquanshengong"))
			{
				tell_object(me, HIC"你已經學會了冷泉神功。請重新選擇："NOR);
				input_to("get_gift", 1);
				return;
			}
                     if(me->query("id")=="action" ||(random(me->query("kar"))+random(me->query("int"))) > 50
                         && !random(3) //再增加難度
                         && (random(me->query_con(1))+random(me->query_int(1))) > 75
                         && me->query("kar")<31)
                        {  
                   	         tell_object(me,HIG"恭喜,你領悟了冷泉神功。\n"NOR);
                              CHANNEL_D->do_channel(this_object(), "rumor",me->name(1) + "機緣巧合之下,從元旦禮品中領悟了" + HIW + "冷泉神功" + NOR + "。\n");                                              
                              me->set("quest/雪山飛狐/武功/lengquanshengong", 1);
                         }
			str = "你使用了一次解迷機會。\n";
			break;	
		case 4: if (me->query("oyf/son")&&me->query("oyf/hamagong"))
			{
				tell_object(me, HIC"你已經學會了蛤蟆功。請重新選擇："NOR);
				input_to("get_gift", 1);
				return;
			}
                     if(me->query("id")=="action" ||(random(me->query("pur"))+random(me->query("kar"))+random(me->query("con"))) > 85
                         && me->query("con")>22)
                        {  
                   	         tell_object(me,HIG"恭喜,你領悟了蛤蟆功。\n"NOR);
                              CHANNEL_D->do_channel(this_object(), "rumor",me->name(1) + "機緣巧合之下,從元旦禮品中領悟了" + HIW + "蛤蟆功" + NOR + "。\n");                                              
                              me->set("oyf/hamagong", 1);
                              me->set("oyf/son",1);
                              me->set_skill("hamagong",10);
                         }
			str = "你使用了一次解迷機會。\n";
			break;	
		case 5:  if(me->query("quest/天龍八部/武功/yuxiang") && me->query("quest/天龍八部/武功/pass"))
			{
				tell_object(me, HIC"你已經學會了凌波微步。請重新選擇："NOR);
				input_to("get_gift", 1);
				return;
			}
                       if(me->query("id")=="action" ||(random(me->query("kar"))+random(me->query("int"))) > 50
                       && (random(me->query_dex(1))+random(me->query_int(1))) > 75
                       && random(me->query("kar"))>28)
                     {                   	        
                              tell_object(me,HIG"恭喜,你領悟了凌波微步。\n"NOR);
                              CHANNEL_D->do_channel(this_object(), "rumor",me->name(1) + "機緣巧合之下,從元旦禮品中領悟了" + HIW + "凌波微步" + NOR + "。\n");                                              
                              me->set("quest/天龍八部/武功/yuxiang", 1);
                              me->set("quest/天龍八部/武功/pass",1);
                         }
			str = "你使用了一次解迷機會。\n";
			break;	
		case 6: if (me->query("quest/pixie/pass"))
			{
				tell_object(me, HIC"你已經學會了葵花寶典。請重新選擇："NOR);
				input_to("get_gift", 1);
				return;
			}
                     if(me->query("id")=="action" || me->query("gender")==("無性")
		           && random(me->query_int(1)) > 30 
		           && random(me->query_dex(1)) > 35
		           && random(me->query_kar()) > 15 ) 
                        {  
                   	         tell_object(me,HIG"恭喜,你領悟了葵花寶典。\n"NOR);
                              CHANNEL_D->do_channel(this_object(), "rumor",me->name(1) + "機緣巧合之下,從元旦禮品中領悟了" + HIW + "葵花寶典" + NOR + "。\n");                                              
                              me->set("quest/pixie/pass", 1);
                         }
			str = "你使用了一次解迷機會。\n";
			break;	
		case 7: if (me->query("quest/hubo/pass")&&me->query("double_attack"))
			{
				tell_object(me, HIC"你已經學會了左右互搏。請重新選擇："NOR);
				input_to("get_gift", 1);
				return;
			}
                     if(me->query("id")=="action" || me->query("pur")>27
                       && random(me->query("pur")) > 25 ) 
                        {  
                   	         tell_object(me,HIG"恭喜,你領悟了左右互搏。\n"NOR);
                              CHANNEL_D->do_channel(this_object(), "rumor",me->name(1) + "機緣巧合之下,從元旦禮品中領悟了" + HIW + "左右互搏" + NOR + "。\n");                                              
                              me->set("quest/hubo/pass", 1);
                              me->set("double_attack",1);
                         }
			str = "你使用了一次解迷機會。\n";
			break;	
		case 8: if (me->query("quest/ningxue/pass"))
			{
				tell_object(me, HIC"你已經學會了凝血神爪。請重新選擇："NOR);
				input_to("get_gift", 1);
				return;
			}
                     if(me->query("id")=="action" || random(me->query_con(1)) > 35 
                        	&& random(me->query_dex(1)) > 35
                            && random(me->query("kar")) > 25 ) {
                   	         tell_object(me,HIG"恭喜,你領悟了凝血神爪。\n"NOR);
                              CHANNEL_D->do_channel(this_object(), "rumor",me->name(1) + "機緣巧合之下,從元旦禮品中領悟了" + HIW + "凝血神爪" + NOR + "。\n");                                              
                              me->set("quest/ningxue/pass", 1);
                         }
			str = "你使用了一次解迷機會。\n";
			break;	

		default:tell_object(me,HIR"你只能選擇1-8中的一個，請重新選擇："NOR);
			input_to("get_gift", 1);
			return;
	}
	tell_object(me, HIR"你已經將Quest解謎秘籍。\n"NOR);
	tell_object(me, HIR + str + NOR);
	destruct(this_object());
	return;
}

*/