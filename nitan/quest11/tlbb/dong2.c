// dong2.c
// bbb 1997/07/16
//COOL@SJ,9808
//tangfeng@SJ,2004

#include <ansi.h>
inherit ROOM;

#define QUESTDIR "quest/天龍八部/"
#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龍八部/天龍營救篇/"
#define QUESTDIR3 "quest/天龍八部/蕭峯身世篇/"
#define QUESTDIR4 "quest/天龍八部/大遼救援篇/"
#define QUESTDIR5 "quest/天龍八部/復興天下篇/"
#define QUESTDIR6 "quest/天龍八部/武功/"

string look_yuxiang();
string look_zi();
string look_shoe();
string look_left();
string look_right();
string look_picture();
void dy(object me);

void create()
{
    set("short", "內室");
	set("long", @LONG
眼前突然一亮，一個宮裝美女，手持長劍，劍尖對準了你的胸膛。細看之
下，原來是一座玉像(yuxiang)。東壁寫了許多字(zi)，筆法飄逸，似以極強
腕力以利器寫成，西壁鑲了六塊大水晶，水晶外綠水隱隱，映得石室中比第一
間石室亮了數倍。
LONG
	);

	set("exits", ([
		"out" : __DIR__"dong1",
	]));

	set("valid_startroom",1);
	
	set("item_desc",([
		"left"		:	(: look_left :),
		"right"	:		(: look_right :),
		"zi"		:	(: look_zi :),
		"yuxiang"	:	(: look_yuxiang :),
		"picture"	:	(: look_picture :),

	]));

	setup();
}


void init()
{
	object me;
    me = this_player();
    
    //通緝犯不可逗留；不過通緝犯能來這裏，肯定是巫師幫忙
    if(me->query_condition("killer"))
    {
       message_vision(HIC"\n突然，不知道從哪裏傳來一個聲音道：這裏不歡迎$N。\n"NOR,me); 
       tell_object(me,HIR"跟着，不知道哪裏來的一隻神腳飛起一腳，將你一腳踢飛出去！\n"NOR);
       tell_room(environment(me),HIR"\n不知道哪裏來的一隻神腳飛起一腳，將"+ me->name()+ "踢飛出去！\n"NOR, ({ me }));
       if(random(2)) me->move("/d/dali/wuliang/xiaoxi");
       else me->move("/d/xiangyang/conglin3");
       tell_room(environment(me), HIR"\n只見"+ me->name()+ "大叫一聲飛過來，摔了個狗吃屎！好帥哦~~~~~~~~\n"NOR, ({ me }));
       me->start_busy(1);
       return;
    }
	if (me->query(QUESTDIR1+"start") 
	      && !me->query(QUESTDIR1+"wuliangover")
	      && me->query_temp(QUESTDIR1+"jianying")
	      && !me->query_temp(QUESTDIR1+"see_duanyu1"))
    {      
  	  me->start_busy(2);
  	  remove_call_out("dy");
  	  call_out("dy",1,me);
  	}
  	add_action("do_ketou", "ketou");
  	add_action("do_ketou", "kneel");
  	add_action("do_yanjiu", "yanjiu");
}
void dy(object me)
{
	object obj;
  if(!me) return;
  if(!present(me,this_object())) return;
  if(present("duan yu",this_object()))
  {
  	obj=present("duan yu",this_object());
  	destruct(obj); 
  }
  if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& me->query_temp(QUESTDIR1+"jianying") && !me->query_temp(QUESTDIR1+"see_duanyu1"))
  {
      tell_object(me,HIG"\n你伸手推門，眼前陡然一亮，失聲驚呼：“啊喲！”眼前一個宮裝美女，手持長劍，劍尖對準了他胸膛。你定睛看時，見這女子雖\n"
                          "是儀態萬方，卻似並非活人，大着膽子再行細看，才瞧出乃是一座白玉雕成的玉像。這玉像與生人一般大小，身上一件淡黃色綢衫\n"
                          "微微顫動；更奇的是一對眸子瑩然有光，神彩飛揚。更奇怪的是一對眼珠乃以黑寶石雕成，只覺越看越深，眼裏隱隱有光彩流轉。\n"
                          "這玉像所以似極了活人，主因當在眼光靈動之故。 \n"NOR);
     obj=new(__DIR__"npc/dy");
     if(!present("qingnian nanzi",this_object()) && !present("duan yu",this_object()))
            obj->move(environment(me)); 
  }  
}
int do_ketou(string arg)
{      
       int time;
	object me,obj;
	me=this_player();
  if(present("duan yu",this_object())) return 0;

	if( !arg || arg != "yuxiang" ) return 0;
	
	if( arg=="yuxiang" ) {
		message_vision("$N口中數着，恭恭敬敬的向玉像磕起頭來。\n", this_player());
		if (!me->query_temp(QUESTDIR1+"lbwb/left")|| !me->query_temp(QUESTDIR1+"lbwb/right"))
		{
			tell_object(me,"你對着玉像一個頭磕下去，似乎發現玉像的左腳(left)、右腳(right)繡得有字。 \n");
			return 1; 
		}
		me->add_temp(QUESTDIR1+"ketou_trigger", 1);
	}
	if( me->query_temp(QUESTDIR1+"ketou_trigger")==16 ) {
		me->delete_temp(QUESTDIR1+"lbwb1");
		me->delete_temp(QUESTDIR1+"ketou_trigger");
		if(me->query(QUESTDIR1+"start")
		   &&me->query_temp(QUESTDIR1+"see_duanyu1")
		   &&!me->query(QUESTDIR1+"wuliangover"))
		{
		   message_vision("$N看見蒲團上的薄草早已破裂，不由伸手進去，裏面什麼也沒有，好像已經被取走了。\n", me);
                  if(!me->query(QUESTDIR6+"yuxiang"))  log_file("quest/TLBB", sprintf("%s(%s) 玉像處磕頭獲得武功標誌1。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
           me->set(QUESTDIR6+"yuxiang",1);
           return 1;	
	     }
		if(me->query(QUESTDIR1+"start")
		   &&me->query(QUESTDIR1+"wuliangover")
		   &&!me->query(QUESTDIR1+"over"))
		{
		   message_vision("$N看見蒲團上的薄草早已破裂，不由伸手進去，裏面什麼也沒有，好像已經被取走了。\n", me);
		   tell_object(me,HIG"雖然什麼都沒有，你忍不住不住地磕頭，看來你已經形似痴狂。\n"NOR);
		   return 1;
		}
		if(me->query(QUESTDIR1+"start")
		   &&me->query(QUESTDIR6+"yuxiang")
		   &&me->query(QUESTDIR1+"over"))
		{
			if(me->query(QUESTDIR6+"pass"))
			{
				message_vision("$N看見蒲團上的薄草早已破裂，不由伸手進去，裏面什麼也沒有，好像已經被取走了。\n", me);
				tell_object(me,HIG"你雖然已經領悟到了凌波微步，還是忍不住回到這裏，看來你已經形似痴狂。\n"NOR);
				return 1;
			}

       //增加時間間隔一天
	     if(me->query(QUESTDIR6+"time")&& time()-me->query(QUESTDIR6+"time")<86400)
	     {
		       message_vision("$N看見蒲團上的薄草早已破裂，不由伸手進去，裏面什麼也沒有，好像已經被取走了。\n", me);
	         return 1;
		 }
       //by Spiderii@ty 加入新標記,只為防止以前開lbwb的玩家可以連續fan bojuan
       time = time() - me->query("quest/天龍八部/武功/time");
       if ( me->query("quest/天龍八部/武功/time") && time < 86400 ) 
          {
		       message_vision("$N看見蒲團上的薄草早已破裂，不由伸手進去，裏面什麼也沒有，好像已經被取走了。\n", me);
	         return 1;
		 }


       if(present("bo juan",me))
	     {
		       message_vision("$N看見蒲團上的薄草早已破裂，不由伸手進去，裏面什麼也沒有，好像已經被取走了。\n", me);
	         return 1;	
		 }
       //任何人都可以拿到凌波微步祕籍，但是能不能領悟卻只有三次機會（非VIP）
       
       obj=unew("/d/dali/obj/dodge_book");
         if(!clonep(obj)){
		       message_vision("$N看見蒲團上的薄草早已破裂，不由伸手進去，裏面什麼也沒有，好像已經被取走了。\n", me);
              return 1;
         }
         if(clonep(obj) && obj->violate_unique()){
            destruct(obj);
		       message_vision("$N看見蒲團上的薄草早已破裂，不由伸手進去，裏面什麼也沒有，好像已經被取走了。\n", me);
            return 1;
         } 

	   message_vision(HIR"$N看見蒲團上的薄草早已破裂，不由伸手進去，裏面好像什麼也沒有，$N不甘心又摸索一會，果然找出一個帛卷。\n"NOR, me);
	   log_file("quest/TLBB", sprintf("%s(%s) 玉像處磕頭獲得帛卷。\n", me->name(1),me->query("id")) );
          obj->set("owner", me->query("id"));//By Spiderii@ty 加個標記,防止BUG
	   obj->move(me);	
          me->set("quest/天龍八部/武功/time", time()); //加個限制。禁止連續翻,只為防備以前開lbwb的玩家 By Spiderii@ty
	   return 1;
	  }	  
	}
	return 1;
}


string look_left()
{ 
     object me;  
     me=this_player();
     me->set_temp(QUESTDIR1+"lbwb/left",1);
	return
	 HIC"磕首百遍，供我驅策。\n"NOR;
}

string look_right()
{ 
     object me;  
     me=this_player();
    me->set_temp(QUESTDIR1+"lbwb/right",1);
	return
	HIY"遵行我命，百死無悔。 \n"NOR;
}

string look_zi()
{
	return
	HIW"洞中無日月，人間至樂也 -- 逍遙子為秋水妹書。\n"NOR;
}

string look_yuxiang()
{    
     object me;  
     me=this_player();
     me->set_temp(QUESTDIR1+"lbwb/yuxiang",1); 
  	return
	HIR"那是一座白玉雕成的玉像，與真人一般大小，身上淡黃綢衫微微顫動，更奇的是一對眸子瑩然有光，神采飛揚。\n"NOR;
}

string look_picture()
{    
     object me;  
     me=this_player();
  	return
	HIR"畫卷上赫然出現一個橫卧的裸女畫像，全身一絲不掛，面貌竟與那玉像一般無異。\n"NOR;
}

int do_yanjiu(string arg)
{
	object me = this_player();  
	int time;
	      		       
	if (!(arg=="picture")) return 0;
		
	if ( me->is_busy()) 
		return notify_fail("你現在正忙着呢。\n");
		
	if( me->is_fighting() ) 
		return notify_fail("你無法在戰鬥中做這個事情。\n");
		

	if (me->query("quest/天龍八部/北冥神功/pass"))
		return notify_fail("你已經完全參透了北冥神功絕學。\n");
		
	if (me->query("quest/天龍八部/北冥神功/fail") >=3 && me->query("registered") < 3)
		return notify_fail("就你現在的情況，恐怕沒有機會領悟無量山中的武功了。\n");
		
		time = time() - me->query("quest/天龍八部/北冥神功/time");
       if ( me->query("quest/天龍八部/北冥神功/time") && time < 86400 ) 
		       return notify_fail("你來的也太勤快了些吧。\n");
/*
if(me->query("quest/天龍八部/北冥神功/combat_exp") && me->query("combat_exp")-me->query("quest/天龍八部/北冥神功/combat_exp")<100000)
	return notify_fail("以你當前的經驗恐怕還是難以領悟，還是抓緊去練功去吧。\n");
*/
 if((int)me->query("combat_exp")< 2000000)
    return notify_fail("你的實戰經驗不夠，無法鑽研這麼高深的武功。\n"); 
              
  if(  random(me->query("kar"))>26
       && me->query("kar") <31 
       && random(me->query("pur") )>25
       && me->query("pur") <31
       && ( (!me->query("buyvip")&& random(15) ==1) ||( me->query("buyvip")&& random(12)==1 ) )
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
     remove_call_out("beiming1");
     call_out("beiming1", 5, me); 
     me->start_busy(10);
   
}
else
{
		  tell_object(me,HIR"但見帛捲上赫然出現一個橫卧的裸女畫像，全身一絲不掛，面貌竟與那玉像一般無異。\n"+
		                    "你只覺多瞧一眼也是褻瀆了神仙姊姊，急忙掩卷不看。然而你卻發現畫卷已不知所踵。\n"NOR);
	  me->add("quest/天龍八部/北冥神功/fail",1);
	  log_file("quest/bmsg", sprintf("%s(%s) 試圖解開北冥神功失敗。經驗：%d。富源：%d。\n", me->name(1),me->query("id"), me->query("combat_exp"),me->query("kar")) );
	  me->start_busy(2);
	  me->set("quest/天龍八部/北冥神功/time", time());
	  me->set("quest/天龍八部/北冥神功/combat_exp",me->query("combat_exp"));
}
	return 1;	
}
void beiming1(object me)
{
  if(!me) return;
     tell_object(me,HIY"你讚道：“神仙姊姊這段話説得再也明白不過了。”再想：“\n"+
                       "這北冥神功是修積內力的功夫，學了自然絲毫無礙。”左手慢\n"+
                       "慢展開帛卷，突然間“啊”的一聲，心中怦怦亂跳，霎時間面\n"+
                       "紅耳赤，全身發燒。但見帛捲上赫然出現一個橫卧的裸女畫像\n"+
                       "，全身一絲不掛，面貌竟與那玉像一般無異。你只覺多瞧一眼\n"+
                       "也是褻瀆了神仙姊姊，急忙掩卷不看。過了良久，心想：“神\n"+
                       "仙姊姊吩咐：‘以下諸圖，務須用心修習。’我不過遵命而行\n"+
                       "，不算不敬。”\n\n"NOR);
     remove_call_out("beiming2");
     call_out("beiming2", 1, me);  
}

void beiming2(object me)
{
  if(!me) return;
     tell_object(me,HIM"於是顫抖着手翻過帛卷，但見畫中裸女嫣然微笑，眉梢眼角，\n"+
                       "脣邊頰上，盡是妖媚，比之那玉像的莊嚴寶相，容貌雖似，神\n"+
                       "情卻是大異。你似乎聽到自己一顆心撲通、撲通的跳動之聲，\n"+
                       "斜眼偷看那裸女身子時，只見有一條綠色細線起自左肩，橫至\n"+
                       "頸下，斜行而至右乳。你看到畫中裸女椒乳墳起，心中大動，\n"+
                       "急忙閉眼，過了良久才睜眼再看，見綠線通至腋下，延至右臂\n"+
                       "，經手腕至右手大拇指而止。你越看越寬心，心想看看神仙姊\n"+
                       "姊的手臂，手指是不打緊的，但藕臂葱指，畢竟也不能不為之\n"+
                       "心動。\n\n"NOR);
     remove_call_out("beiming3");
     call_out("beiming3", 1, me);  
}

void beiming3(object me)
{
  if(!me) return;
     tell_object(me,HIC"另一條綠線卻是至頸口向下延伸，經肚腹不住向下，至離肚臍\n"+
                       "數分處而止。你對這條綠線不敢多看，凝目看手臂上那條綠線\n"+
                       "時，見線旁以細字注滿了“雲門”、“中府”、“天府”、“\n"+
                       "俠白”、“尺澤”、“孔最”、“列缺”、“經渠”、“大淵\n"+
                       "”、“魚際”等字樣，至拇指的“少商”而止。你平時常聽師\n"+
                       "父談論武功，雖不留意，但聽得多了，知道“雲門”、“中府\n"+
                       "”等等都是人身的穴道名稱。\n\n"NOR);
     remove_call_out("beiming4");
     call_out("beiming4", 1, me);  
}

void beiming4(object me)
{
  if(!me) return;
     tell_object(me,HIB"當下將帛卷又展開少些，見下面的字是：“北冥神功系引世人\n"+
                       "之內力而為我有。北冥大水，非由自生。語云：百川匯海，大\n"+
                       "海之水以容百川而得。汪洋巨浸，端在積聚。此‘手太陰肺經\n"+
                       "’為北冥神功之第一課。”\n\n"NOR);
     remove_call_out("beiming5");
     call_out("beiming5", 1, me);  
}

void beiming5(object me)
{
  if(!me) return;
     tell_object(me,HIR"          下面寫的是這門功夫的詳細練法。\n\n"+
                       HIG"最後寫道：“世人練功，皆自雲門而至少商，我逍遙派則反其\n"+
                       "道而行之，自少商而至雲門，拇指與人相接，彼之內力即入我\n"+
                       "身，貯於雲門等諸穴。然敵之內力若勝於我，則海水倒灌而入\n"+
                       "江河，兇險莫甚，慎之，慎之。本派旁支，未窺要道，惟能消\n"+
                       "敵內力，不能引而為我用，猶日取千金而復棄之於地，暴殄珍\n"+
                       "物，殊可哂也。”\n\n"NOR);
         me->set("quest/天龍八部/北冥神功/pass",1);
         
     if(!me->query_skill("beiming-shengong")) 
{
me->set_skill("beiming-shengong",251);
         
tell_object(me,HIC"你的「北冥神功」進步了！”\n"NOR);
tell_object(me,HIC"你儼然已學會畫卷中的武功絕學，以後就要靠你自己練習了！”\n"NOR);
	  me->start_busy(2);
	  me->set("quest/天龍八部/北冥神功/time", time());
	  me->set("quest/天龍八部/北冥神功/combat_exp",me->query("combat_exp"));
	  log_file("quest/bmsg", sprintf(HIR"%s(%s) 學會北冥神功。富源：%d；經驗：%d。\n"NOR, me->name(1),me->query("id"), me->query("kar"),me->query("combat_exp")) );
}
else
{
tell_object(me,HIR"你儼然已學會畫卷中的武功絕學，以後就要靠你自己練習了！”\n"NOR);
 me->start_busy(2);
me->set("quest/天龍八部/北冥神功/time", time());
me->set("quest/天龍八部/北冥神功/combat_exp",me->query("combat_exp"));
log_file("quest/bmsg", sprintf(HIR"%s(%s) 學會北冥神功。富源：%d；經驗：%d。\n"NOR, me->name(1),me->query("id"), me->query("kar"),me->query("combat_exp")) );
}
}
