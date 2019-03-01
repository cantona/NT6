// By Spiderii fix bug
// chen.c
inherit NPC;
#include <ansi.h>;

void init()
{
        object me = this_player();
        if (me->query_temp("thd/onquest")==2) { 
           message_vision(HIY"$N見到黑風雙煞來勢猛惡，頓時想起靴旁的匕首(bishou)。\n"NOR,me);
           add_action("do_chou","chou");
        }
}

void create()
{
        set_name( "陳玄風" ,({ "chen xuanfeng", "chen" }));
        set("title", "黑風雙煞");
        set("nickname", HIY"銅屍"NOR);
        set("gender", "男性");
        set("age", 35);
        set("long",
            "此人是黃藥師的二弟子，他濃眉大眼，背厚膀寬，軀體甚是壯健，只是\n"
            "面色微微泛黃。\n");
        set("attitude", "aggressive");
        set("str", 37);
        set("int", 32);
        set("con", 35);

        set("unique", 1);
        set("no_quest", 1);
        set("max_qi",3500);
        set("qi",3500);
        set("max_jing",1000);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 100);
        set("shen",-50000);

        set("combat_exp", 800000);

        set_skill("claw", 200);
        set_skill("force", 200);
        set_skill("parry", 200);
        set_skill("dodge", 200);
        set_skill("leg", 200);
        set_skill("jiuyin-baiguzhua", 200);
        set_skill("bihai-chaosheng", 200);
        set_skill("suibo-zhuliu", 200);
        set_skill("xuanfeng-tui", 200);

        map_skill("force", "bihai-chaosheng");
        map_skill("parry", "jiuyin-baiguzhua");
        map_skill("dodge", "suibo-zhuliu");
        map_skill("claw", "jiuyin-baiguzhua");
        map_skill("leg", "xuanfeng-tui");
        prepare_skill("claw", "jiuyin-baiguzhua");

        create_family("桃花島", 2, "被逐弟子");
        set("inquiry", ([
           "銅屍":     "江湖上的人都這麼叫我的，你怕不怕？哈哈哈哈。",
           "東邪":     "那是我師父的綽號。",
           "西毒":     "那是與家師齊名的高手之一，是個老毒物，住在白駝山。",
           "南帝":     "段王爺已出家當和尚去了，法名叫一燈。",
           "北丐":     "北丐統領中原的丐幫，勢力頗為強大。",
           "洪七公":   "洪七公武功高強，而且教會郭靖那小兒降龍十八掌，可恨！",
           "黃蓉":     "她是我師父的獨女，最是刁蠻任性。",
           "梅超風":   "她是我的師妹，也是我的內室。",
           "陳玄風":   "不就是我麼？你是白痴啊？",
           "黃藥師":   "他是我師父。"]) );
        setup();
        carry_object(ARMOR_D("cloth"))->wear();
}

void kill_ob(object me)
{
        object ob=this_object();
        command("say 想搶我的九陰真經？沒那麼容易！");
        message_vision(HIY"陳玄風向$N急攻數招，奪路向外跑去。\n\n"NOR,me);
        COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 3);
        COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 3);
        COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 3);
        command("out");
        ::kill_ob(me);
}

void do_dest(object ob)
{
	::die();
}

int do_chou(string arg)
{
        object me = this_player();
        object ob = this_object();
        object obj;
        string msg;
        if (!arg||arg!="bishou")
                return notify_fail("什麼？\n");
        if (me->query_temp("thd/onquest")!=2)
                return notify_fail("什麼？\n");         
        if(arg=="bishou"&&me->query_temp("thd/onquest")==2)
        {
                msg = HIR"$N見到黑風雙剎襲來，心中一驚，抽出匕首胡亂揮舞起來。\n";
                msg+= HIR"陳玄風冷笑一聲，在$N肩頭青門穴一彈，$N手一沉，竟然正好插在\n";
                msg+= HIR"他的肚臍上！\n\n"NOR;
                msg+= HIY"陳玄風瞪著$N，身子慢慢的軟倒。\n\n"NOR;
                msg+= HIC"梅超風慘叫一聲，不故性命的向你攻來！\n"NOR;
                        if (!objectp(obj = present("mei chaofeng",environment(me)))) {
                                call_out("do_dest",1,ob);
                                return 1;
                        }
                obj->set_temp("target",me->query("id"));
                message_vision(msg, me);
                me->set_temp("thd/onquest",3);
                ob->die();
                return 1;
         }
}

void die()
{
	object me = query_temp("last_damage_from");
	object skin;
	int i, time;
	if (!objectp(me)) return;

        i = me->query("combat_exp") - 1000000;
        i /= 1000000;
	time = time() - me->query("quest/jiuyin2/time");

	if ((me->query("quest/jiuyin2/fail") >= 3 && me->query("registered") < 3)
//        || me->query("quest/jiuyin2/fail") >= i
	|| time < 86400 ) {
		::die();
		return;
	}

	if(
             ( 
                random(me->query("kar")) >= 26
              && me->query("combat_exp", 1) > 1000000 
             && me->query("kar",1)< 31 
             &&(random(5)==2||(me->query("buyvip")&& random(4)==3 ))
)
         || me->query("quest/jiuyin2/pass")
                                                      )
           {
            skin = unew(__DIR__"../obj/jiuyin-book2");
		if(!clonep(skin)){
			::die();
			return;
		}
		message_vision(HIY"\n$N看到陳玄風身上有一片皮革，順手拿了起來。\n"NOR,me);
		skin->set("owner", me->query("id"));
		skin->move(me);
		if(! me->query("quest/jiuyin2/pass"))
			log_file("quest/jiuyin",sprintf("%-18s失敗%s次後，從陳玄風處得到九陰真經下卷，福：%d。\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("quest/jiuyin2/fail")),
              			me->query("kar")), me);
		me->set("quest/jiuyin2/pass", 1);
		::die();
		return;
	}
	me->add("quest/jiuyin2/fail", 1);
        me->set("quest/jiuyin2/time", time());
        me->set("quest/jiuyin2/combat_exp", me->query("combat_exp"));
	log_file("quest/jiuyin",
		sprintf("%-18s想從陳玄風處得到九陰真經下卷，失敗%s次。\n",
			me->name(1)+"("+capitalize(getuid(me))+")",
                        chinese_number(me->query("quest/jiuyin2/fail"))
		), me
	);
	::die();
	return;
}
