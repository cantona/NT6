int ask_xingyue(object who)
{
	object me,ob;
	mapping myfam;

	me=this_player();

	myfam = me->query("family");
	if (!myfam || myfam["family_name"] != "天龍寺") {
		command("knock "+(string)me->query("id"));
		command("say 你非我派弟子，也敢來濫竽充數!\n");
		return 1;
	}
	if (me->query_skill("buddhism", 1) < 180){
		command("pat "+(string)me->query("id"));
		command("say 你的佛法還需精進，這星月菩提目前是不適合你的!\n");
		return 1;
	}
	command("nod "+(string)me->query("id"));
	ob=present("xingyue puti",this_object());
	if(ob){
		ob->move(me);
		command("say 你這麼勤奮修行，這佛門至寶就送你防身吧!\n");
	} else
		command("say 你這麼勤奮修行，不錯不錯，可惜我已經把它送給你的師兄弟了。\n");
	return 1;
}

void attempt_apprentice(object ob)
{
	string old_name,new_name;
	mapping myfam;

	myfam = (mapping)ob->query("family");
	if (!myfam) return;
	if (myfam["family_name"] != "天龍寺") {
		command ("say 你不是天龍寺弟子，這話從何説起！\n");
		return;
	}
	if((int)ob->query_skill("buddhism",1)<140){
		command("say 我段家武功與佛學息息相關，我看"+RANK_D->query_respect(ob)+"的禪宗修為似乎不夠？");
		return;
	}
	if((int)ob->query_skill("yiyang-zhi",1)<160){
		command("say 我天龍寺武功首推一陽指，我看"+RANK_D->query_respect(ob)+"似乎應在一陽指上多下點功夫。");
		return;
	}
	if((int)ob->query_skill("qiantian-yiyang",1)<160) {
		command("say 修練一陽指內功最為重要，我看"+RANK_D->query_respect(ob)+"似乎應在乾天一陽功上多下點功夫。");
		return;
	}
	if(!(ob->query("tls")) && !(ob->query_temp("tls_app"))){
		command("say 阿彌陀佛！請回吧，貧僧不輕易收出家弟子。");
		return;
	}
	if(ob->query("tls")&&((int)ob->query("shen") > 1000 || (int)ob->query("shen")+1000 <0 )){
		command("say 我天龍寺乃清修之地，依我看"+RANK_D->query_respect(ob)+"似乎紅塵未了,不宜繼續修行。");
		return;
	}

	command("smile");
	old_name = ob->query("name");
	if (ob->query("tls") && (string)ob->query("class") =="bonze"){
        	new_name="本"+old_name[2..3];
	}
	else{
		new_name="本"+old_name[0..1];
	}
	if (!ob->query("tls") || (string)ob->query("class")!="bonze"){
		command("say 貧僧只收出家弟子，今日老僧幫你剃度。");
		message_vision("$N雙手合什，喃喃念道: \n",ob);
		message_vision("我聞浮屠道  中有解脱門  置心如止水  視身等浮雲 \n",ob);
		message_vision("抖擻垢穢衣  度脱生死輪  胡為愛所苦  不去尚逡巡 \n",ob);
		message_vision("回念發弘願  願此見在身  只受過去報  不結未來恩 \n",ob);
		message_vision("誓以智慧水  永洗煩惱塵  不將恩愛子  再結煩憂根 \n",ob);
		message_vision("枯榮禪師伸出一隻皮包骨頭的瘦手在"+ob->query("name")+"的頭上一按，頓時頭髮盡落。\n",ob);
	}
	ob->set("name",new_name);
	ob->set("class","bonze");
	ob->set("tls",1);
	command("chat 入我門來法名"+new_name);
	command("recruit " + ob->query("id") );
	command("chat 哈哈哈哈!");
	command("chat 老衲終於找到一個可傳衣缽之人,真是可喜可賀!");
	return;
}

void recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
	ob->set("class", "bonze");
}

int ask_dudan(object who)
{
	object me,ob_dan;
	mapping myfam;
	me=this_player();
	myfam = (mapping)me->query("family");
	if (!myfam || myfam["family_name"] != "天龍寺") {
		command("slap "+(string)me->query("id"));
		command("say 你非我派弟子，也敢來濫竽充數!\n");
		return 1;
	}
        if (me->query_skill("kurong-changong", 1) < 200){
		command("pat "+(string)me->query("id"));
		command("say 你的枯榮禪功根基不夠，這毒丹我是不能給你吃的!\n");
		return 1;
	}
	if((int)me->query("dudan_given") < (int)(me->query_skill("kurong-changong", 1)/10)) {
		command("nod "+(string)me->query("id"));
		me->add("dudan_given",1);
		ob_dan = new("/d/tls/npc/obj/dudan");
		ob_dan->move(me);
		message_vision("$N獲得一顆毒丹。\n",this_player());
		command("say 這是一顆毒丹，可是對於修煉枯榮禪功，極為有益，你這麼勤奮練功就贈給你吧!\n");
		return 1;
	}
	else  {
		command("say 你現在還是好好修煉枯榮禪功，老想靠藥物來增漲可是不行! \n");
		return 1;
	}
}

string ask_liumai2()
{
        object me,ob,*thing;
	mapping myfam;
	int i;
	ob=this_player();
	me=this_object();

	myfam = (mapping)ob->query("family");

	if (myfam["family_name"] != "天龍寺"||!ob->query("tls")||ob->query("class") != "bonze"){
		return "對不起，我不知道！\n";

	}
   if (ob->query("liumai_pass") && (ob->query_skill("liumai-shenjian",1) < 181)) {
		command ("nod "+ ob->query("id"));
		message_vision("枯榮長老一掌向地拍去，身後轟然移開一扇石門，$N看也不看，走了過去。\n", ob);
		thing = deep_inventory(ob);
		i = sizeof(thing);
		while (i--)
		if (thing[i]->is_character()) {
			message_vision("枯榮長老突然伸手一攔，道；你怎麼帶外人進洞？。\n", ob);
			me->set_leader(ob);
			remove_call_out("kill_ob");
			call_out("kill_ob", 0, me);
			return " ";
		}
		ob->move("/d/tls/pyd");
		return "";
	}
	if( ob->query_skill("yiyang-zhi",1) < 180 )
		return "你的一陽指修煉的這麼差，還不回去好好練功!!\n";
	if (ob->query("max_neili") < 4500)
		return "你的內力修煉的這麼差，還不回去好好練功!!\n";
	if (ob->query_skill("force", 1) < 200)
		return "你的內功修煉的這麼差，還不回去好好練功!!\n";
	if (ob->query_temp("try_fight"))
		return "你不是正在接我的招嗎？!\n";
	if (ob->query_temp("try"))
		return "如果你準備好了，請確定(try)。 \n";
	if (me->query_temp("try"))
		return "對不起，現在正有人在準備過招. \n";
	if (me->query_temp("try_fight"))
		return "對不起，現在我正忙着，你有什麼要求一會兒再説. \n";
        if (ob->query_skill("liumai-shenjian",1) > 180){
		ob->set("quest/天龍八部/武功/liumai_update",1);
		return "你的六脈神劍修為已經登峯造級，老衲這裏也不能給你什麼幫助了，\n"+
			"你去找鎮南王世子段譽吧，也許他能給你些幫助。";
	}
	else {
		command("say 依照天龍寺祖上傳下規矩，" + RANK_D->query_respect(ob) + "你必須接下我十招不死不昏，才夠資格進普雲洞修習六脈神劍。");
		ob->set_temp("try",1);
		me->set_temp("try",1);
		call_out("wait", 1, me, 0);
		return "如果你準備好了接招，請確定（try)。\n";
	}
}

void init()
{
	object me;
	me = this_player();
	::init();
	if (interactive(me) && living(me)) {
	 	if(me->query(QUESTDIR2+"start")&& !me->query(QUESTDIR2+"over"))
    {
    	command("look "+me->query("id"));
    	command("touch "+me->query("id"));
    	command("say 有這位大俠幫忙，本寺當可高枕無憂了。"); 
    }
	} 
	add_action("do_yes", "try");
	add_action("do_kill", "kill");
	add_action("do_kill", "tk");
	add_action("do_kill", "teamkill");
	add_action("do_kill", "hit");
}

int do_kill(string arg)
{
	object ob,ob2;
	object me = this_player();
	ob2 = this_object();

	if (!arg) return 0;
	ob = present(arg, environment(me));

	if (ob == this_object() || ob == me) return 0;
	if (!ob || !ob->is_character()) return 0;

	if (ob->query("family/family_name") == "天龍寺") {
		if (me->query("family/family_name") == "天龍寺") {
			message_vision(ob2->name()+"向$N沉聲喝道：出家人戒殺生，怎麼連自己的同門都殺？！\n", me);
		}
		else {
			message_vision(ob2->name()+"向$N沉聲喝道：大膽狂徒，居然來天龍寺行兇！\n", me);
			kill_ob(me);
		}
		me->set("vendetta/天龍寺", 1);
		return 1;
	}
	return 0;
}

int do_yes()
{
	object me,ob,room;
	ob = this_player();
	me = this_object();

	if( !ob->query_temp("try")) return 0;

	message_vision("$N單掌一立，沉聲説道：“請”。\n",ob );
	set("max_jing",3000);
	set("jing",3000);
	set("eff_jingli",3000);
	set("max_qi",5000);
	set("qi",5000);
	set("jiali",100);
	set("neili",8000);
	set("max_neili",8000);
	command("yun rong");
	if(!( room = find_object("/d/tls/lsy" )) )
		room = load_object("/d/tls/lsy");
	room->delete("exits");
	ob->delete_temp("try");
	me->delete_temp("try");
	me->set_temp("try_fight",1);
	ob->set_temp("try_fight",1);
	call_out("fighting",  3, me, ob, 0);
	message_vision("枯榮大師雙掌合什，躬身一揖，恭恭敬敬的道：“請指教。”\n",ob);
	return 1;
}

void waiting(object me, int wait_time)
{
	object fighter;

	if( wait_time >= 150 ) {
		say( "枯榮大師説道：看來你不打算接我十招了！\n\n");
		call_out("do_recover", 0, me);
		return;
	}
	if( !objectp( fighter = present( me->query_temp("fight"), environment(me) ) ) ){
		call_out("waiting", 1, me, wait_time + 1);
		return;
	}
}

void fighting(object me, object fighter, int count)
{
	object room;

	if (!fighter || !living(fighter) || environment(fighter)!=environment(me)) {
		if(!( room = find_object("/d/tls/lsy" )) )
                room = load_object("/d/tls/lsy");
		if( objectp(fighter)) {
			fighter->delete_temp("try_fight");
			fighter->delete_temp("beat_count");
		}
		me->delete_temp("try_fight");
		room->set("exits/out","/d/tls/songlin-1");
                command("chat* 搖了搖頭，説道：想不到... 唉！");
		command("sigh");
		return;
	}
	else if (count <10) {
		if (interactive(fighter) && fighter->query_temp("try_fight") && living(fighter))
	 		COMBAT_D->do_attack(this_object(), fighter, query_temp("weapon"), random(2)?1:2);
	 	count++;
		call_out("fighting", 2, me, fighter, count);
	}
	else call_out("do_congra", 3, me, fighter);
}

void do_congra(object me, object fighter)
{
	int i;
	object room,*thing;

	if(!( room = find_object("/d/tls/lsy" )) )
		room = load_object("/d/tls/lsy");
	fighter->delete_temp("try_fight");
	fighter->set("liumai_pass",1);
	me->delete_temp("try_fight");
	command("smile");
        command("say 恭喜，恭喜，你技藝青出於藍勝於藍，可以修習本寺神功六脈神劍,你去吧。\n");
	room->set("exits/out","/d/tls/songlin-1");
	message_vision(HIY"\n枯榮長老一掌向地拍去，身後轟然移開一扇石門，$N看也不看，走了過去。\n"NOR,fighter);

        thing = deep_inventory(fighter);
	i = sizeof(thing);
	while (i--)
	if (thing[i]->is_character()) {
		message_vision("枯榮長老突然伸手一攔，道；你怎麼帶外人進洞？。\n", fighter);
		me->set_leader(fighter);
		remove_call_out("kill_ob");
		call_out("kill_ob", 0, me);
		return;
	}
	fighter->move("/d/tls/pyd");
	return;
}
