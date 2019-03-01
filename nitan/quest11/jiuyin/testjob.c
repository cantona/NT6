// houdian.c 後殿

inherit ROOM;
void create()
{
	set("short", "後殿");
	set("long",@long
這是峨嵋山華藏庵的後殿。是峨嵋派掌門人傳教弟子功夫的地方。這裡供
有一尊普賢菩薩像。兩旁靠牆放著幾張太師椅，地上放著幾個蒲團。掌門人正
在向幾個女弟子傳授武功。
long);
	set("exits",([
		"north" : __DIR__"daxiong",
	]));
        set("objects",([
//                CLASS_D("emei") + "/mie-jue" : 1,
	]));
//	create_door("north", "小門", "south", DOOR_CLOSED);
        setup();
}

void reset()
{
	object here=this_object();
	if (here->query("fighting") != 1) {
		if (here->query("count") != 1)
			here->set("count", random(4) );
		if ((int)here->query("count") == 1){
			remove_call_out("test");
			call_out("test", 5, here);
		}
	}
	::reset();
}

int sort(object obj1, object obj2)
{
	int temp1,temp2;
	temp1 = obj1->query("em_job1");
	temp2 = obj2->query("em_job1");
	if (temp1 > temp2) return 1;
	else if (temp1 < temp2) return -1;
	else return 0;
}

void test(object here)
{
	string s;
	object ob, ling, where;
	object *list, *selected, *sorted;
	int num0, num1, num2, num3;
	int i, cnt = 0;
	string* tgt= ({ "/d/emei/houshanty", "/d/emei/baoguosi", "/d/emei/sheshenya",
                        "/d/emei/zhongfengsi", "/d/emei/qianfoan", "/d/emei/chunyangdian",
                        "/d/emei/guanyinqiao", "/d/emei/jietuopo", "/d/emei/xianfengsi" });
	string* tgtname= ({ "炭窯", "報國寺", "舍身崖", "中峰寺", "千佛庵",
                            "純陽殿", "觀音橋", "解脫坡", "仙峰寺"});
	num0 = -1;
	num2 = -1;
	num3 = -1;
	num1 = -1;
	num0 = random(sizeof(tgt));
	num1 = random(sizeof(tgt));
	while (num0 == num1) {
		num1 = random(sizeof(tgt));
	}
	num2 = random(sizeof(tgt));
	while (num0 == num2 || num1 == num2) {
		num2 = random(sizeof(tgt));
	}
	num3 = random(sizeof(tgt));
	while (num0 == num3 || num1 == num3 || num2 == num3) {
		num3 = random(sizeof(tgt));
	}
	if (!(ob = present("miejue shitai", here))) return;
	list = filter_array(users(), (: $1->query_temp("emhsjob"):));
	sorted = sort_array(list, (: sort :));
	i = sizeof( sorted );
	while( i-- ) {
		if (!environment(list[i]) ) continue;
		if (wizardp(list[i]) || list[i]->query("env/invisibility")) continue;
		if ( !interactive(list[i]) ) continue;
		if (query_idle(list[i]) > 2000) continue;
		cnt++;
		list[i]->set_temp("selected", 1);
	}
	if ( cnt < 2 ) {
		here->set("count", random(2));
		return;
	}
	selected = filter_array(list, (: $1->query_temp("selected") == 1 :));
	i = 1;
	if (!(where = find_object("fang ping")))
		ling = new("/d/emei/npc/fang");
	else ling = present("fang ping", where);
	ling->move("/d/city/yltw");
	ling->set("pl", selected[0]);
	s = selected[0]->query("name")+"趕緊到揚州月老亭把方老前輩請來助陣，";
	while( i < 5 ) { ling->set("pl"+i, ling); i++; }
	ling->set("pl1",selected[1]);
	ling->set("st1",tgt[num0]);
	s = s + selected[1]->query("name")+"守住"+tgtname[num0]+"，";
	if( cnt > 2 ) {
		ling->set("pl2",selected[2]);
		ling->set("st2",tgt[num1]);
		s = s + selected[2]->query("name")+"守住"+tgtname[num1]+"，";
	}
	if( cnt > 3 ) {
		ling->set("pl3",selected[3]);
		ling->set("st3",tgt[num2]);
		s = s + selected[3]->query("name")+"守住"+tgtname[num2]+"，";
	}
	if( cnt > 4 ) {
		ling->set("pl4",selected[4]);
		ling->set("st4",tgt[num3]);
		s = s + selected[4]->query("name")+"守住"+tgtname[num3]+"，";
	}
	CHANNEL_D->do_channel(ob, "chat", "元兵攻山，" + s + "等待援兵，殺退敵人！\n");
	ling->apply_condition("em_job1", 30);
	ling->apply_condition("job_busy", 30);
	here->set("fighting", 1);
	return;
}

void init()
{
	add_action("do_swear",  ({ "qishi", "fashi" }));
	add_action("do_huzhuo",  ({ "huzhuo" }));
	add_action("do_nod",  ({ "nod" }));
}

int do_swear()
{
	object ob, me = this_player();
	object where = environment(me);
	if( !(ob = present("miejue shitai", where) ) )
		return 0;
	if( me->query_temp("jiuyin140") < 5 )
		return 0;
	if( me->query("gender") == "女性" )
		message_vision("$N說道：小女子" + me->query("name") + "對天盟誓，日後我若對魔教教主張無忌這淫徒心存愛慕，\n"+
			"倘若和他結成夫婦，我親身父母死在地下，屍骨不得安穩；我師父滅絕師太必成厲鬼，\n"+
			"令我一生日夜不安，我若和他生下兒女，男子代代為奴，女子世世為娼。\n", me);
	else
		tell_room(where, me->query("name")+"說道：不才" + me->query("name") + "一定要實現師太的兩大願望，逐走韃子，\n"+
			"光復漢家山河；率領峨嵋派領袖群倫，蓋過少林、武當，成為中原武林中的第一門派。\n"+
			"有違誓言者天打雷劈，萬劍穿身，死無葬身之地。\n");
	tell_room(where, "滅絕師太臉上露出一絲笑容。\n");
	me->set_temp("jiuyin140", 6);
	tell_room(where, "滅絕師太說道：黃女俠在鑄刀鑄劍之前，和郭大俠兩人窮一月心力，繕寫了兵法和武功的\n"+
			"精要，分別藏在刀劍之中。屠龍刀中藏的乃是兵法，此刀名為‘屠龍’，意為日後有人得\n"+
			"到刀中兵書，當可驅除韃子，殺了韃子皇帝。倚天劍中藏的則是武學秘笈，其中最為寶貴\n"+
			"的，乃是一部‘九陰真經’，一部‘降龍十八掌掌法精義’，盼望後人習得劍中武功，替\n"+
			"天行道，為民除害。\n");
	tell_room(where, "滅絕師太說道：你取到屠龍刀和倚天劍後，來到我這裡，一手執刀，一手持劍，運起內力，\n"+
			"以刀劍互斫(huzhuo)，寶刀寶劍便即同時斷折，即可取出藏在刀身和劍刃中的秘笈。這是\n"+
			"取出秘笈的唯一法門，那寶刀寶劍可也從此毀了。你記住了麼？\n");
	return 1;
}

int do_nod()
{
	object me=this_player();
	if( me->query_temp("jiuyin140") != 6 ) return 0;
	me->set_temp("jiuyin140", 7);
	message_vision("$N只聽得渾身熱血沸騰，一股浩然的正氣充滿胸襟。\n", me);
	me->add("shen", me->query("combat_exp")/3);
	return 0;
}

int do_huzhuo()
{
	object ob, me=this_player();
	object ob1, ob2, where = environment(me);
	if( me->query_temp("jiuyin140") < 6 ) return 0;
	if( !(ob1 = present("yitian jian", me)) ) return 0;
	if( !(ob2 = present("tulong dao", me)) ) return 0;
	if( me->query_temp("jiuyin140") != 7 )
		return notify_fail("你答應了滅絕師太的要求了嗎？\n");
	if ( !me->query("jiuyin/emeipass") || !me->query("jiuyin/emeijump"))
		return notify_fail("嘿嘿！想作弊麼？\n");
	if( !(ob = present("miejue shitai", where) ) )
		return notify_fail("滅絕師太不在這裡，你最好先別這樣做。\n");
	message_vision("只見$N一手執刀，一手持劍，運起內力，刀劍互斫。\n"+
			"只聽見‘哧’的一聲輕響，這兩把舉世無雙的屠龍刀和倚天劍就此消失了。\n", me);
	destruct(ob1);
	destruct(ob2);
	message_vision("滅絕師太從斷刀斷劍中取出了幾張帛卷，看了幾眼，拿出一張帛卷交給了$N。\n", me);
	if( me->query_skill("xianglong-zhang", 1) > 0)
	        tell_room(where, "滅絕師太說道：降龍十八掌你已經學了，這張九陰白骨爪精解你就拿去學吧。\n");
	else
		tell_room(where, "滅絕師太說道：你的武學路子與降龍十八掌的剛陽勁力不符，這張九陰白骨爪精解你就拿去學吧。\n");
	tell_room(where, "滅絕師太說道：待我覓得一個心地仁善、赤誠為國的志士，將兵書傳授于他，要他立誓驅除胡虜。\n");
	tell_room(where, "滅絕師太又說道：我看這還是我先保管，你如果需要隨時來跟我要吧。\n");
	me->set("jiuyin/emei",1);
	log_file("quest/jiuyin",sprintf("%-18s在娥眉九陰部分失敗%s次後成功從滅絕師太處得到娥眉九陰。\n",
		me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(me->query("jiuyin/emeifail"))), me);
	me->delete_temp("jiuyin140");
	return 1;
}
