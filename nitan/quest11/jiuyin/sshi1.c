#include <ansi.h>
inherit ROOM;

void create()
{ 
       set("short",HIC"石室"NOR);
       set("long", @LONG
室中也無特異之處，你抬頭仰望，但見室頂密密麻麻的寫滿了字跡符號，
你看了一會，但覺奧妙難解。室頂西南角繪著一幅圖，似與武功無關，凝神細
看，倒像是幅地圖。石室右下方好象可以往下(down)走。
LONG
     );
        set("item_desc", ([
             "down": HIB"黑乎乎的，看不真切。\n"NOR,
        ]));
        set("exits", ([
              "up" : __DIR__"shiguan",                 
        ]));
        setup();
}

void init()
{
	object me = this_player();
	
	if(me)
	{
		if(!me->query("quest/jiuyin1/pass")
		&& !me->query("quest/jiuyingm/pass") )
		{
			me->delete_skill("jiuyin-shenfa");
			me->delete_skill("jiuyin-zhengong");
			me->delete_skill("jiuyin-shenzhua");
//                        me->delete_skill("yinlong-bian");
		}
	}
	
        add_action("do_look", "look"); 
        add_action("do_look", "kan");
        add_action("do_walk", "walk");
        add_action("do_walk", "leave");
        add_action("do_study", "yandu");
}

int do_look(string arg)
{
	object me=this_player();
	int i, time;
	if ( arg =="map") {
		write(HIY"你凝望著那幅圖，心中不由大喜，原來那繪的正是出墓的秘道。\n"NOR);
		me->set_temp("map", 1);
		me->start_busy(1);
		return 1;         
	}
	if ( arg =="ceiling") {
		write(HIY"你看著室頂，滿滿的都是密密麻麻的小字。\n"NOR);
		me->set_temp("ceiling", 1);
		me->start_busy(1);
		return 1;
	}
	if ( arg =="zi") {
		write(HIY"你望著那些小字，似乎都是一些武功要訣。\n"NOR);
		if( !me->query_temp("ceiling")
                 || me->query("combat_exp", 1) < 2000000 ){
			tell_object(me,HIY"不過上面寫的艱深難懂，你看了一會，覺得自己理解能力不足，只好放棄了。\n"NOR);
			return 1;
		}
                i = (me->query("combat_exp") - 1000000) / 500000;
		time = time() - me->query("quest/jiuyingm/time");
                if ( me->query("quest/jiuyingm/fail") >= i && me->query("registered") < 3 ){
			tell_object(me,HIY"不過上面寫的艱深難懂，你看了一會，覺得自己上次看過以後，增加的歷練還不足以理解其奧義。\n"NOR);
			return 1;
		}
                if ( time < 86400 ){
			tell_object(me,HIY"不過上面寫的艱深難懂，你自從上次看過後，思緒一直無法平靜下來，或許需要再過一點時間。\n"NOR);
			return 1;
		}

                if(( random(me->query("kar")) >= 28
                 && me->query("kar") <31
                 && random(20) == 10 
                 && me->query("int") > 30)
         || me->query("quest/jiuyingm/pass")){

			write(HIR"你陡然一瞥間，看到幾個小字“九陰真經內功要訣”，你興奮極了。\n"NOR);
			write(HIC"你研究了一下，發現應該能研讀(yandu)些道德經(daode-jing) \n"NOR);
			write(HIB"九陰真功(jiuyin-zhengong)以及九陰身法(jiuyin-shenfa)、\n"NOR);
                        write(HIM"九陰神爪(jiuyin-shenzhua)以及九陰銀龍鞭(yinlong-bian)的皮毛。\n"NOR);
			if( !me->query("quest/jiuyingm/pass"))
				log_file("quest/jiuyin",
					sprintf("%-18s失敗%s次後，在古墓石壁上得到九陰真經，福：%d，悟：%d。\n",
						me->name(1)+"("+capitalize(getuid(me))+")",
						chinese_number(me->query("quest/jiuyingm/fail")),
						me->query("kar"), 
						me->query("int") 
					), me
				);
			me->set("quest/jiuyingm/pass", 1);
		}
		else {
			me->add("quest/jiuyingm/fail", 1);
			me->set("quest/jiuyingm/time", time());
			log_file("quest/jiuyin",
				sprintf("%-18s錯過%s次，沒有發現古墓石壁上的九陰真經。\n",
                      			me->name(1)+"("+capitalize(getuid(me))+")", 
                      			chinese_number(me->query("quest/jiuyingm/fail"))
                      		), me
                      	);
			write(HIY"不過上面寫的艱深難懂，你看了一會就放棄了。\n"NOR);
		}
		me->delete_temp("ceiling");
		return 1;         
	}
	return notify_fail("你要看什麼？\n");
}

int do_walk(string arg)
{ 
        object me=this_player();
        if (me->is_busy() || me->is_fighting())
              return notify_fail("你正忙著哪！\n");
        if ( arg =="down"){ 
             if(!me->query_temp("map") || me->query_skill("yunu-xinjing")<120 )
//                   return notify_fail("你伸腳想往下走，但是猶豫再三，又伸回了腳。\n");      
           tell_object(me,HIM"\n你東轉西彎，越走越低。同時腳下漸漸潮濕，暗中隱約望去，到處都是岔道。\n"+
                             "再走一會，道路奇陡，竟是筆直向下。下降了約莫半個時辰，這路漸平，只是\n"+
                             "濕氣卻也漸重，到後來更聽到了淙淙水聲，路上水沒至踝。越走水越高，自腿\n"+
                             "而腹，漸與胸齊。\n"NOR);
           me->delete_temp("map");
           me->move(__DIR__"gmanhe1");
           tell_room(environment(me), me->name() + "從"HIC"石室"NOR"快步走了過來。\n", ({ me }));
           return 1;
        }
        return notify_fail("你在石室裡踱來踱去，不知如何是好？\n");
}

int do_study(string arg)
{
	int cost, my_skill;
 	object me=this_player();

	if (!arg) return 0;

	if( ! me->query("quest/jiuyingm/pass"))
		return 0;

	if(me->is_busy())
		return notify_fail("你現在正忙著呢。\n");

	if( me->is_fighting() )
		return notify_fail("你無法在戰鬥中專心下來研讀新知！\n");

	if( !me->query_skill("literate", 1) )
		return notify_fail("你是個文盲，先學點文化(literate)吧。\n");

	if((int)me->query("potential") < 1 )
		return notify_fail("你的潛能已經用完了，再怎麼讀也沒用。\n");

	if((int)me->query("combat_exp") < 1000000 )
		return notify_fail("你的實戰經驗不足，再怎麼讀也沒用。\n");

	if( me->query_int() < 40 )
		return notify_fail("以你目前的領悟能力，還沒有辦法學這個技能。\n");

	cost = 40 * ( 1 + ( 35 - (int)me->query("int"))/20 );
	if (cost < 20) cost = 20;
	if( me->query("neili") < cost * 2 + 300)
		return notify_fail("你的內力不夠，無法領會這個技能。\n");
	me->set_temp("last_damage_from", "研讀高深武功，熬盡心機累");

	switch (arg) {
		case "jiuyin-zhengong":
			my_skill = me->query_skill("jiuyin-zhengong", 1);
			if( my_skill >= 201)
				return notify_fail("你覺得這洞壁上所刻已經太淺了，不能學到什麼東西。\n");
			if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
				return notify_fail("也許是缺乏實戰經驗，你對洞壁上所刻總是無法領會。\n");
			else
				write("你研讀著有關九陰真功的技巧，似乎有些心得。\n");
			me->improve_skill("jiuyin-zhengong", ((int)me->query_skill("literate", 1)/5 + 1));
			me->receive_damage("jing", cost );
			me->add("neili", -cost * 2);
			me->add("potential", - random(2));
		break;      
                case "daode-jing":
			my_skill = me->query_skill("daode-jing", 1);
			if( my_skill >= 220)
				return notify_fail("你覺得洞壁所刻已經盡藏胸中，沒有什麼可學的了。\n");
			if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
				return notify_fail("也許是缺乏實戰經驗，你對洞壁上所刻總是無法領會。\n");
			else
				write("你研讀著道德經，覺得心性修為大有長進。\n");
			me->improve_skill("daode-jing", ((int)me->query_skill("literate", 1)/5 + 1));
			me->receive_damage("jing", cost );
			me->add("neili", -cost * 2);
			me->add("potential", - random(2));
		break;             
		case "jiuyin-shenfa":
			my_skill = me->query_skill("jiuyin-shenfa", 1);
			if( my_skill >= 201)
				return notify_fail("你覺得這洞壁上所刻已經太淺了，不能學到什麼東西。\n");
			if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
				return notify_fail("也許是缺乏實戰經驗，你對洞壁上所刻總是無法領會。\n");
			else
				write("你研讀著有關九陰身法的技巧，似乎有些心得。\n");
			me->improve_skill("jiuyin-shenfa", ((int)me->query_skill("literate", 1)/5+1));
			me->receive_damage("jing", cost );
			me->add("neili", -cost * 2);
			me->add("potential", - random(2));
		break;
                case "yinlong-bian":
			my_skill = me->query_skill("yinlong-bian", 1);
			if( my_skill >= 201)
				return notify_fail("你覺得這洞壁上所刻已經太淺了，不能學到什麼東西。\n");
			if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
				return notify_fail("也許是缺乏實戰經驗，你對洞壁上所刻總是無法領會。\n");
			else
				write("你研讀著有關九陰銀龍鞭的技巧，似乎有些心得。\n");
			me->improve_skill("yinlong-bian", ((int)me->query_skill("literate", 1)/5+1));
			me->receive_damage("jing", cost );
			me->add("neili", -cost * 2);
			me->add("potential", - random(2));
		break;
		case "jiuyin-shenzhua":
			my_skill = me->query_skill("jiuyin-shenzhua", 1);
			if( my_skill >= 201)
				return notify_fail("你覺得這洞壁上所刻已經太淺了，不能學到什麼東西。\n");
			if( my_skill * my_skill * my_skill / 10 > (int)me->query("combat_exp") ) 
				return notify_fail("也許是缺乏實戰經驗，你對洞壁上所刻總是無法領會。\n");
			else
				write("你研讀著有關九陰神爪的技巧，似乎有些心得。\n");
			me->improve_skill("jiuyin-shenzhua", ((int)me->query_skill("literate", 1)/5+1));
			me->receive_damage("jing", cost );
			me->add("neili", -cost * 2);
			me->add("potential", - random(2));
		break;
	}
	return 1;
}
