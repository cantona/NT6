// /d/xingxiu/silk3.c
//tangfeng@SJ 2004

#include <ansi.h>
inherit ROOM;
#include <wanted.h>

#define QUESTDIR "quest/天龍八部/"
#define QUESTDIR3 "quest/天龍八部/蕭峯身世篇/"
#define QUESTDIR4 "quest/天龍八部/大遼救援篇/"

void create()
{
        set("short", HIM"頌摩崖"NOR);
        set("long", @LONG
頌摩崖又名黃龍碑。周圍山勢陡峭，兩山對峙，一泓中流，兩峽旁有潭，
淵深莫測。俗傳有黃龍自潭飛出，因名黃龍潭。潭左側摩崖成碑。漢隸真跡，
筆觸遒勁，刀刻有力，記敍了開天井道的過程。往東南是仇池山，往西則是
石門。
LONG);
        set("outdoors", "yili");
           set("quest",1);

        set("exits", ([
                "eastdown" : __DIR__"silk2",
                "westdown" : __DIR__"silk4",
                "north" : __DIR__"silk3a",
        ]));

        set("coor/x",-250);
  set("coor/y",90);
   set("coor/z",0);
   set("coor/x",-250);
  set("coor/y",90);
   set("coor/z",0);
   set("coor/x",-250);
 set("coor/y",90);
   set("coor/z",0);
   setup();
}

void init()
{
	object me = this_player();
	if (me->query(QUESTDIR3+"start")&&me->query_temp(QUESTDIR3+"askxiao") && !me->query_temp(QUESTDIR3+"lookcliff")&& !me->query(QUESTDIR3+"over")) {
		add_action("do_jump", ({"jump", "tiao"}));
		add_action("do_look", ({"look"}));
	}
        if ((me->query(QUESTDIR3+"good")&&me->query_temp(QUESTDIR4+"dagouzhen") &&me->query_temp(QUESTDIR4+"shaolinzhen")&&!me->query(QUESTDIR4+"over"))||(me->query(QUESTDIR4+"start")&&!me->query(QUESTDIR4+"over"))) {
		add_action("do_da", ({"da", "answer"}));
    if (localtime(TIME_TICK)[2] <= 2) tell_object(me,HIB"天黑了，這裏黑黝黝一片，伸手不見五指，正是夜襲大營的好時候，怎麼接應的人還沒來呢？\n"NOR); 
		add_action("do_han", ({"han", "yell"}));
	}
}
int do_look(string arg)
{
	object me = this_player();

	if (me->query(QUESTDIR3+"start")&&me->query_temp(QUESTDIR3+"askxiao") && !me->query_temp(QUESTDIR3+"lookcliff")&& !me->query(QUESTDIR3+"over")) {
	 if (!arg) {
		set("long", @LONG
頌摩崖又名黃龍碑。周圍山勢陡峭，兩山對峙，一泓中流，兩峽旁有潭，
淵深莫測。俗傳有黃龍自潭飛出，因名黃龍潭。潭左側摩崖成碑。漢隸真跡，
筆觸遒勁，刀刻有力，記敍了開天井道的過程。往東南是仇池山，往西則是
石門。山壁（cliff）上遠遠看去一塊地方光亮無比，似乎可以跳躍上去。
LONG
);
		me->look(arg);
	 }
	 else if (arg == "cliff") {
		tell_object(me,HIR"你仔細地觀察着峭壁，發現可以跳躍（jump）上去。\n"NOR);
		return 1;
	 }
	}
	else
	{
		set("long", @LONG
頌摩崖又名黃龍碑。周圍山勢陡峭，兩山對峙，一泓中流，兩峽旁有潭，
淵深莫測。俗傳有黃龍自潭飛出，因名黃龍潭。潭左側摩崖成碑。漢隸真跡，
筆觸遒勁，刀刻有力，記敍了開天井道的過程。往東南是仇池山，往西則是
石門。
LONG
);
		me->look(arg);
	}		
}

int do_jump(string arg)
{
	object room,me = this_player();
	object *player;
	int i;

	if(me->query_condition("killer")) return 0;//tjf不可以
   
	if (me->query(QUESTDIR3+"start")&&me->query_temp(QUESTDIR3+"askxiao") && !me->query_temp(QUESTDIR3+"lookcliff")&& !me->query(QUESTDIR3+"over")) {
		if( arg == "cliff" || arg == "峭壁" || arg == "峭崖")
		{
			if(me->query_skill("dodge")<200) 
			{
				message_vision(HIC"\n$N吸了一口氣，嘗試一躍峭壁，卻突然發現風大山高，卻有點力不從心。\n"NOR,me);
				return 1;
			}
			message_vision(HIC"\n$N吸了一口氣，一個縱身已經跳上峭壁。\n"NOR, this_player());
			if (!(room = find_object(__DIR__"cliff")))
				room = load_object(__DIR__"cliff");
			if(!room)
			{ 
				tell_object(me,HIR"\n你無論怎麼跳，發現都還在原地!\n");
				log_file("quest/TLBB", sprintf("%s(%s)缺少cliff.c文件。\n", me->name(1),me->query("id")) );	
			}
			else
			{
				player = all_inventory(room);
				for (i = 0; i < sizeof(player); i++) {
					if (player[i]->is_character()) return notify_fail(YEL"你突然發現這個落腳之處過於狹小，已經有"+player[i]->query("name")+"在上面，你更本無法站穩。\n你歎了口氣，只能左腳一點崖壁，又跳了下來。"NOR);
				}         	 
				tell_object(me,HIY"你沒有想到，這塊峭壁上竟然還有如此大的空間可以落腳，估計是當年中原高手埋伏的地點之一。\n"NOR);
				me->move(room);
			}
			return 1;
		}
	}
	return 0;
}
int do_han(string arg)
{
	object me, env;
	int count;

  me = this_player();
  
  //如果玩家進過大營，可以隨時返會大營
  
	if (localtime(TIME_TICK)[2] > 2 && !me->query(QUESTDIR4+"start"))  return 0;

	env = this_object();
	count = me->query_temp(QUESTDIR4+"count");
	if(!me->query(QUESTDIR3+"good") )return 0;
	if(!me->query(QUESTDIR4+"start")&&!me->query_temp(QUESTDIR4+"dagouzhen")) return 0;
	if(!me->query(QUESTDIR4+"start")&&!me->query_temp(QUESTDIR4+"shaolinzhen")) return 0;
	if(me->query_condition("killer")) return 0;//tjf不可以
	if (present("wu shi", env))
		return notify_fail(HIR"一品堂喝道：“深更半夜，鬼苦一樣大呼小叫什麼？”\n"NOR);
	if (me->is_busy())
		return notify_fail("你要喊什麼？先喘口氣吧。\n");

	if ( count > 3 ){
    message_vision(HIC"$N吸了口氣，道：“在下"+me->name()+HIC"，還請閣下現身！”聲音傳出去很遠。\n"NOR, me);
		me->start_busy(1);
		remove_call_out("happen");
		call_out("happen", 10, me);
		return 1;
	}
	else
	{
		if(random(2)) me->start_busy(1);
    me->add_temp(QUESTDIR4+"count",1);
    tell_object(me,HIY"你嘗試喊了一聲，可是似乎毫無反應。\n"NOR);
	}
	return 1;
}

void happen(object me)
{
	object ob, env;

	env = this_object();
	if (!me) return;
	if(!me->query(QUESTDIR3+"good") )return 0;
	if (me->query_temp(QUESTDIR4+"count")<3) return;
	
	if (!(ob = present("dizi", env))) {
                ob = new("/d/gb/npc/dizi");
                ob->set("party","gb");
		ob->move(env);
		tell_room(env, HIY"夜色中有人咳嗽了一聲，只見一個丐幫弟子疾步走了過來。\n"NOR, ({}));
	}
	if (!present(me, env)||(!me->query_temp(QUESTDIR4+"anhao")&&!me->query(QUESTDIR4+"start"))) {
		tell_room(env, CYN"丐幫四處看了看，皺了皺眉轉身走了。\n"NOR, ({}));
		destruct(ob);
		return;
	}
  message_vision(HIW"丐幫弟子向$N一拱手，道：“天王蓋地虎！”\n"NOR, me);
  me->start_busy(2);
}

int do_da(string arg)
{
	object me, ob,room,*obj;
	int i;
	me = this_player();
	if (!me) return 0;
  if (me->query_temp(QUESTDIR4+"count")<3) return 0;

	if (me->is_busy() || !arg )
		return notify_fail("你要説什麼？先喘口氣吧。\n");

  if (!present("gaibang dizi", this_object())){
		message_vision(CYN"丐幫弟子在遠處喊道：“"+me->name()+""CYN"，我先走了！”\n"NOR, me);
		me->delete_temp("quest/天龍八部");
		me->delete_temp("quest/busy");//任務衝突標誌取消 
		me->start_busy(1);
		return 1;
	}
  ob = present("gaibang dizi", this_object());
  obj = deep_inventory(me);
  i = sizeof(obj);
  while (i--)
    if (obj[i]->is_character())
       me->set_temp("out",1);
  if (me->query_temp("out")){
		message_vision(HIY"$N皺了皺眉頭道："+me->name()+HIY"，你身上這位是......！我先走了！”\n"NOR,ob,me);
		me->delete_temp("quest/天龍八部");
		me->delete_temp("quest/busy");//任務衝突標誌取消 
		me->delete_temp("out");
		me->start_busy(1);
		destruct(ob);
		return 1;
	}
	
    if (arg==me->query_temp(QUESTDIR4+"anhao")||me->query(QUESTDIR4+"start")) {
	  me->start_busy(1);
	  message_vision(HIC"$N對$n點了點頭。\n"NOR, ob,me);
	  //只能一個人做
	  obj = users();
	  i = sizeof(obj);
	  while(i--) {
		  if ( obj[i]->query_temp(QUESTDIR4+"godaliao") && obj[i]!=me) 
		  {
			  message_vision(HIY"$N微笑着道：不用擔心了，已經有"+obj[i]->query("name")+RANK_D->query_respect(obj[i]) +"前往大遼營救去了！\n"NOR,ob,me);
			  message_vision(HIY"$N晃了晃頭道："+obj[i]->query("name")+RANK_D->query_respect(obj[i]) +"武功高牆，料想沒什麼問題！這樣的話，我先走了！\n"NOR,ob,me);
			  message_vision(HIY"$N聳了聳肩，做了個揖，轉身離開了。\n"NOR,ob,me);
			  me->delete_temp("quest/天龍八部");
			  me->delete_temp("quest/busy");//任務衝突標誌取消 
			  log_file("quest/TLBB", sprintf("%s(%s)開始解救蕭峯，但和%s(%s)衝突失敗。經驗：%d。\n", me->name(1),me->query("id"), obj[i]->name(1),obj[i]->query("id"), me->query("combat_exp")) ); 
			  destruct(ob);
			  return 1;
		  }
	  }
      
	  message_vision(HIC"$N説道：「"+me->name()+"，我們這就出發，且隨我來。」\n"NOR, ob,me);
	  if (!(room = find_object(__DIR__"daliao/shulin")))
		  room = load_object(__DIR__"daliao/shulin");
	  if(!room)
	  { 
		  tell_object(me,HIR"\n你發現你們竟然還在原地!\n");
		  log_file("quest/TLBB", sprintf("%s(%s)缺少文件..daliao/shulin.c。\n", me->name(1),me->query("id")) ); 
	  	  return 1;
	  }

	  tell_object(me,HIY"你跟着丐幫弟子疾步向北走去，你突然發現這丐幫弟子輕功確實不錯，丐幫不愧為天下第一幫。\n"NOR);
	  message_vision(YEL"$N急急忙忙離開頌摩崖。\n"NOR,me);
	  message_vision(YEL"$N急急忙忙離開頌摩崖。\n"NOR,ob);
	  me->move(room);
	  ob->move(room);
	  message_vision(YEL"$N急急忙忙來到"+room->query("short")+YEL"。\n"NOR,me);
	  message_vision(YEL"$N急急忙忙來到"+room->query("short")+YEL"。\n"NOR,ob);
	  message_vision(HIC"\n$N對$n點了點頭。\n"NOR, ob,me);
	  message_vision(CYN"$N説道：「一直北行就是遼兵大營。我先行告退，還有幾批武林人士需要接應。"+me->name()+CYN"還請小心，這一路恐怕不免一路廝殺。」\n"NOR, ob,me);
	  message_vision(CYN"$N説道：「"+RANK_D->query_respect(me) +"最好先去糧倉所在，可以點火（dianhuo），引起混亂，之後伺機營救蕭大俠。蕭大俠據説在遼營左堂附近。」\n"NOR, ob,me);
	  message_vision(HIC"$N對着$n揮了揮手。\n"NOR, ob,me);
	  message_vision(YEL"$N急急忙忙離開"+room->query("short")+YEL"。\n"NOR,ob);
	  log_file("quest/TLBB", sprintf("%s(%s)已經深入大遼，開始解救蕭峯。經驗：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) ); 
	  me->set_temp(QUESTDIR4+"godaliao",1);
	  me->set(QUESTDIR4+"start",1);
	  destruct(ob);
	  return 1;
	}
	message_vision(HIY"$N抓耳撓腮，想了半天説道：“"+arg+"”。\n"NOR, me);
	message_vision(HIY"$N皺了皺眉頭道："+me->query("name")+HIY"，你的意思是......"+arg+"”\n"NOR,ob,me);
	message_vision(HIY"$N皺了皺眉頭。\n"NOR,ob);
	me->start_busy(1);
	return 1;
} 
 int valid_leave(object me, string dir)
 {
        object ob;
        if (base_name(this_object())==__DIR__"silk8" && dir == "south" && (is_wanted(me) || !userp(me)))
                return 0;
 
        if(me->query_temp("wait_target") && objectp(present("anran zi", environment(me))))
                return notify_fail("黯然子閃身攔在你面前，喝道：臨陣想溜？給我滾回來！\n");
 
        if(me->query_temp("xx_rob") 
        && objectp(ob = present("hubiao biaoshi", environment(me)))
        && ob->query("target") == me)
                return notify_fail("護鏢鏢師閃身攔住你的去路，看來是想把你給廢了！\n");  
 
        if(me->query_temp("xx_rob") && objectp(present("shangdui", environment(me))))
                return notify_fail("商隊在這裏呢，快搶(qiang)啊！\n");  
 
        return ::valid_leave(me, dir);
 }
