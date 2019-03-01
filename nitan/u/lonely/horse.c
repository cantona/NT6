inherit ITEM;

#include <ansi.h>

#define LINE_COUNT 5
#define MEMBER_D "/adm/daemons/memberd"
#define LINE HIM "------------------------------------------------------------------------------------------" NOR

mapping trans = ([
// 城市
"beijing"   : "/d/beijing/majiu",
"luoyang"   : "/d/luoyang/majiu",
"yangzhou"  : "/d/city/majiu",
"dali"      : "/d/dali/majiu", 
"foshan"    : "/d/foshan/majiu", 
"fuzhou"    : "/d/fuzhou/majiu", 
"guanwai"   : "/d/guanwai/majiu", 
"hangzhou"  : "/d/hangzhou/majiu", 
"lanzhou"   : "/d/lanzhou/majiu", 
"lingzhou"  : "/d/lingzhou/majiu", 
"yongdeng"  : "/d/huanghe/majiu", 
"suzhou"    : "/d/suzhou/majiu",
"xiangyang" : "/d/xiangyang/majiu", 
"yili"      : "/d/xingxiu/majiu", 
"chengdu"   : "/d/city3/majiu", 
"emei"      : "/d/emei/majiu1", 
"emei2"     : "/d/emei/majiu2", 
"quanzhou"  : "/d/quanzhou/majiu1", 
"jiaxing"   : "/d/quanzhou/majiu2", 
"jingzhou"  : "/d/jingzhou/majiu", 
"nanyang"   : "/d/shaolin/majiu1", 
"changan"   : "/d/changan/majiu", 
"wugong"    : "/d/quanzhen/majiu", 
"hengyang"  : "/d/henshan/majiu", 
"kaifeng"   : "/d/kaifeng/majiu", 
"kunming"   : "/d/kunming/majiu", 
"zhongzhou" : "/d/zhongzhou/majiu",
// 門派
"family_1"    :  "/d/huashan/laojun",
"family_2"    :  "/d/songshan/dadian",
"family_3"    :  "/d/henshan/zhurongdian",
"family_4"    :  "/d/shaolin/guangchang1",
"family_5"    :  "/d/wudang/sanqingdian",
"family_6"    :  "/d/emei/huayanding",
"family_7"    :  "/d/xiaoyao/xiaodao4",
"family_8"    :  "/d/lingjiu/damen",
"family_9"    :  "/d/xingxiu/xxh1",
"family_10"   :  "/d/gumu/mumen", 
"family_11"   :  "/d/quanzhen/jiaobei",
"family_12"   :  "/d/kunlun/guangchang",
"family_13"   :  "/d/taohua/tao_in",
"family_15"   :  "/d/xuedao/shandong2",
"family_16"   :  "/d/xueshan/shanmen",
"family_17"   :  "/d/gaibang/inhole",
"family_18"   :  "/d/tiezhang/guangchang",
"family_19"   :  "/d/kaifeng/tieta",
"family_20"   :  "/d/wudu/neijin",
"family_21"   :  "/d/mingjiao/shanmen",
"family_22"   :  "/d/xuanminggu/zulin2",
"family_23"   :  "/d/meizhuang/keting",
"family_24"   :  "/d/lingxiao/gate",
"family_25"   :  "/d/beijing/gate",
"family_26"   :  "/d/jueqing/shanzhuang",
"family_27-1" : "/d/heimuya/pingdingzhou",
"family_27-2" : "/d/heimuya/shenggu",
"family_28"    :  "/d/city/beidajie1",
"family_29"    :  "/d/zhongzhou/miaojia_houting",
"family_30"    :  "/d/yanziwu/shuiyun",
"family_31"    :  "/d/shaolin/shang_men",
"family_32"    :  "/d/guanwai/xiaowu",
"family_33"    :  "/d/dali/neitang",
// 常用
"comm_1"  :  "/d/city/kedian",
"comm_2"  :  "/d/city/wumiao",
"comm_3"  :  "/d/city/zuixianlou",
"comm_4"  :  "/d/city/yh_cangku",
"comm_5"  :  "d/wuguan/guofu_gate",///
"comm_6"  :  "/d/item/xiaowu",
"comm_7"  :  "/d/item/road1",
"comm_8"  :  "/d/xiakedao/xkroad5",
"comm_9"  :  "/d/huashan/jianzhong",
"comm_10"  :  "/d/shaolin/hanshui1",
"comm_11"  :  "/d/huashan/shandong",
"comm_12"  :  "/d/dali/lushui",
"comm_13"  :  "/d/mingjiao/xuantianshi",
"comm_14"  :  "/d/beijing/shanlu3",
"comm_15"  :  "/d/xiakedao/haibin",
]);

mapping show_trans = ([
// 城市
"beijing"   : "北京",
"luoyang"   : "洛陽",
"yangzhou"  : "揚州",
"dali"      : "大理", 
"foshan"    : "佛山", 
"fuzhou"    : "福州", 
"guanwai"   : "關外", 
"hangzhou"  : "杭州", 
"lanzhou"   : "蘭州", 
"lingzhou"  : "靈州", 
"yongdeng"  : "永登", 
"suzhou"    : "蘇州",
"xiangyang" : "襄陽", 
"yili"      : "伊犁", 
"chengdu"   : "成都", 
"emei"      : "峨嵋山", 
"emei2"     : "峨嵋半山", 
"quanzhou"  : "泉州", 
"jiaxing"   : "嘉興", 
"jingzhou"  : "荊州", 
"nanyang"   : "南陽", 
"changan"   : "長安", 
"wugong"    : "武功鎮", 
"hengyang"  : "衡陽", 
"kaifeng"   : "開封", 
"kunming"   : "昆明", 
"zhongzhou" : "中州",

// 門派
"family_1":  "華山派",
"family_15": "血刀門",
"family_2":  "嵩山派",
"family_16": "大輪寺",
"family_3":  "衡山派",
"family_17": "丐幫",
"family_4":  "少林派", 
"family_18": "鐵掌幫",
"family_5":  "武當派", 
"family_19": "紅花會",
"family_6":  "峨嵋派",    
"family_20": "五毒教",
"family_7":  "逍遙派",   
"family_21": "明教",
"family_8":  "靈鷲宮", 
"family_22": "玄冥谷",
"family_9":  "星宿派",   
"family_23": "梅莊", 
"family_10": "古墓派",   
"family_24": "雪山派",
"family_11": "全真派",  
"family_25": "鎮遠鏢局",
"family_12": "昆侖派", 
"family_26": "絕情谷",
"family_13": "桃花島",   
"family_27-1": "日月神教（男）",
"family_27-2": "日月神教（女）",
"family_28":  "歐陽世家", 
"family_29":  "中原苗家",
"family_30":  "慕容世家",     
"family_31":  "八卦刀商家堡",
"family_32":  "關外胡家",
"family_33":  "大理段氏",
// 常用
"comm_1"  :  "揚州客店",
"comm_2"  :  "揚州武廟",
"comm_3"  :  "醉仙樓",
"comm_4"  :  "倉庫",
"comm_5"  :  "郭府外",///d/wuguan/guofu_gate
"comm_6"  :  "幹將莫邪",
"comm_7"  :  "張天師",
"comm_8"  :  "海龜",
"comm_9"  :  "神雕",
"comm_10"  :  "接引使",
"comm_11"  :  "宗師獨孤求敗",
"comm_12"  :  "宗師黃裳",
"comm_13"  :  "宗師霍山",
"comm_14"  :  "宗師葵花太監",
"comm_15"  : "南賢",

]);

mapping show_trans2;
string g_show_trans;

mapping get_trans2()
{
	mapping m;
	string *keys_show_trans;
	int i;
	
	m = ([]);
	keys_show_trans = keys(show_trans);
	
	for (i = 0; i < sizeof(keys_show_trans); i ++)
	{
		m += ([ show_trans[keys_show_trans[i]] : keys_show_trans[i] ]);
	}
	
	return m;
}

string get_trans_path(string s)
{
	string st;
	
	// 同時兼容中文和英文
	if (member_array(s, keys(trans)) == -1)
	{
		s = show_trans2[s];
	}
	
	return trans[s];
}

int is_horse()
{
	return 1;
}

void setup()
{
        set("ridable", 1);
	set("no_give", 1);
	set("value", 1);
	set("unit", "匹");
	set("base_unit", "匹");
	set_weight(1);

	show_trans2 = get_trans2();
	set_heart_beat(2);
	/*
	remove_call_out("start_heart_beat");
	call_out("start_heart_beat", 2);
	*/
	::setup();
}

int show_trans(object me)
{
	mapping self_flag;
        int i;
	string *places, show_places;
	string show_city, show_family, show_comm;
	int ncity, nfamily, ncomm;

	show_places = "";
	show_city = "";
	show_family = "";
	show_comm = "";
	if (sizeof(g_show_trans))
	{
		show_places += g_show_trans;
	}
	else
	{
		
		show_places += HIY "【你可以騎馬到以下地方】\n" + LINE + "\n"NOR;
	
		places = keys(show_trans2); 
		
	        for (i = 0; i < sizeof(places); i ++)
	        {
			if (strsrch(show_trans2[places[i]], "comm_") != -1)
			{
				show_comm += sprintf("%-18s", places[i]);
				ncomm ++;
				if (ncomm % LINE_COUNT == 0)show_comm += "\n";
			}
			else if (strsrch(show_trans2[places[i]], "family_") != -1)
			{
				show_family += sprintf("%-18s", places[i]);
				nfamily ++;
				if (nfamily % LINE_COUNT == 0)show_family += "\n";
			}
			else
			{
				show_city += sprintf("%-18s", places[i]);
				ncity ++;
				if (ncity % LINE_COUNT == 0)show_city += "\n";
			}
		}
	        show_places += HIG + "<城市>\n" NOR;
	        show_places += show_city;
	        show_places += HIY + "\n<門派>\n" NOR;
	        show_places += show_family;
	        show_places += HIC + "\n<常用>\n" NOR;
	        show_places += show_comm;
	        	
	        g_show_trans = show_places; // 全局記錄，不需要每次都計算
	}

		// 自己記錄的地點
		self_flag=query("horse/flags", me);

		if (mapp(self_flag))
		{
			show_places += HIR "\n<用戶記錄地點>\n" NOR;
			if (sizeof(self_flag))
			{
				places = ({});
				places = keys(self_flag);
				for (i = 0; i < sizeof(places); i ++)
				{
					show_places += sprintf("%-18s", places[i]);
					if ((i+1) % LINE_COUNT == 0)show_places += "\n";
				}
				if (sizeof(places) % LINE_COUNT != 0)show_places += "\n";
			}
		}
		else
		{
			show_places += "\n";
		}

		show_places += LINE + HIY "\n請使用 rideto <目的地> 騎馬到指定地方，例如：rideto 客店\n" NOR;
		

	write(show_places);
	return 1;
}

// 騎馬到指定地點
int move_to(object me, string place)
{
	object running, horse, follower;
        string trans_path;
	int trans_times, sk_riding, horse_level, horse_tili, cost_tili, level;
	string temp,temp2;
	object trans_target, me_env;
	

	// 檢查是否騎馬
        if( !objectp(horse=query_temp("is_riding", me)) )
	{
		write("你並沒有騎馬啊。\n" );
		return 1;
	}
	if( query_temp("running", horse) )
	{
		write(this_object()->name() + NOR "正在奔跑呢！\n" NOR);
		return 1;
	}
	if( query_temp("running", me) )
	{
		write("你正在奔跑中呢。\n");
		return 1;
	}
	if (me->is_busy() || me->is_fighting())
	{
		write("你正忙呢！\n");
		return 1;
	}
	sk_riding = me->query_skill("riding", 1);
        if (sk_riding < 30)
	{
		write("你騎術不夠，無法騎馬到指定地點。\n");
		return 1;
	}

        // 檢查是否有該地方可去
        if (! stringp(trans_path = get_trans_path(place)))
	{
			if( stringp(trans_path=query("horse/flags/"+place, me)) )
			{
				if (! find_object(trans_path) && ! load_object(trans_path))
				{
					write("你無法騎馬達到這個地方。\n");
					return 1;
				}
				
			}
			if( !stringp(trans_path=query("horse/flags/"+place, me)) )
			{
				write("你無法騎馬達到這個地方。\n");
				return 1;
			}		
			else
			{
				if( !MEMBER_D->is_valib_member(query("id", me)) && !query("horse/stone", me) )
				{
					write("你無法騎馬達到這個地方。\n");
					return 1;
				}
			}
	}

	// 某些地方無法騎馬到達
	trans_target = find_object(trans_path);
	if (! objectp(trans_target))trans_target = load_object(trans_path);

	if (! objectp(trans_target))
	{
		write("你無法騎馬達到這個地方。\n");
		return 1;
	}
	
	if( query("no_flyto", trans_target) )
	{
		write("你無法騎馬達到這個地方。\n");
		return 1;
	}

        // 在天界也無法到達
	if (sscanf(trans_path, "/kungfu/class/sky%s", temp) == 1)
	{
		write("你無法騎馬達到這個地方。\n");
		return 1;
	}

	if (sscanf(trans_path, "/d/newbie/%s", temp) == 1)
	{
		write("你無法騎馬達到這個地方。\n");
		log_file("horse",query("id", me)+"于"+ctime(time())+"試圖利用記錄點回到新手村。\n");
		return 1;
	}	
	// 神龍島上不能到達(超影馬除外)
	me_env = environment(me);
	
	if( query("no_rideto", me_env) )
	{
		write("此處不能騎馬。\n");
		return 1;		
	}
	if( sscanf(base_name(me_env),"/d/shenlong/%s",temp) == 1 && query("id", this_object()) != "chaoying" )
	{
		write("此處無法騎馬。\n");
		return 1;
	}
	if( sscanf(trans_path,"/d/shenlong/%s",temp) == 1 && query("id", this_object()) != "chaoying" )
	{
		write("你無法騎馬達到這個地方。\n");
		return 1;
	}
	
	if (trans_path == "/d/shenlong/shejingdong")
	{
		write("你的坐騎無法感應蛇精洞內的情況，無法騎馬達到這個地方。\n");
		return 1;
	}
	
        // dream_boat上無法騎馬
	if (sscanf(base_name(me_env), "/clone/misc/dream_%s", temp) == 1)
	{
		write("此處無法騎馬。\n");
		return 1;
	}
	
	// 玩家房間無法到達，自己的房間可以
	if (sscanf(trans_path, "/data/room/%s/%s", temp, temp2) == 2)
	{
		// 自己房間可以進入
		if( query("id", me) != temp )
		{
			write("你無法騎馬進入私人住宅。\n");
			return 1;
		}
	}

	if (sscanf(trans_path, "/clone/misc/dream_%s", temp) == 1)
	{
		write("你無法騎馬達到這個地方。\n");
		return 1;
	}
	if (sscanf(trans_path, "/d/xiangyang/%s", temp) == 1 && XYWAR_D->now_status() == 2)
	{
		write("現在襄陽城全面戒備，你還是坐馬車比較安全！\n");
		return 1;
	}

	if (sscanf(base_name(environment(me)),"/d/xiangyang/%s", temp) == 1  && XYWAR_D->now_status() == 2)
	{
		write("現在襄陽城全面戒備，你還是坐馬車比較安全！\n");
		return 1;
	}

	// 根據馬的好壞及騎馬者的騎術來判斷達到目的地時間
	level=query("level", horse);
	if (sk_riding >= 300)sk_riding = 300;
	trans_times = 2 + random(1 + 300 / sk_riding) + random(22 - level*4);

	if (trans_times <= 0)
		log_file("horse_time", trans_times + "\n");

        // 判斷騎馬到指定地點馬所消耗的體力
	horse_tili=query("tili", horse);
	cost_tili = 10 + random(trans_times * 25);

	if (horse_tili <= cost_tili)
	{
		write(horse->name() + NOR "體力不足，還是讓它休息會兒吧。\n");
		return 1;
	}

	running = new("/clone/misc/running");

        if( objectp(follower=query_temp("is_rided_follow", horse)) )
	{
		if (environment(follower) && (interactive(follower) || ! userp(follower)))
			follower->move(running);
	}
	me->move(running);
        addn("tili", -1*cost_tili, horse);
set_temp("running", 1, 	horse);
set_temp("running", 1, 	me);

	message("vision",  "\n" + this_object() ->name() + HIW "一聲長"
                  "嘶，箭一般地沖出 ……\n" NOR, environment(me), ({horse}));

	call_out("arrived_dest", trans_times, me, follower, running, horse, trans_path);

	return 1;
}

int arrived_dest(object me, mixed follower, object running, object horse, string trans_path)
{
	object ob, ob2;
	
	if (objectp(me))
	{
		me->move(trans_path);
delete_temp("running", 		me);
		if (random(2))me->improve_skill("riding", 1);
	}
	if (objectp(follower))follower->move(trans_path);
	if( objectp(horse))delete_temp("running", horse);
	// 如果有同伴則同伴自動移動到面前
	ob=query("me_mater", me);
	if (objectp(ob))
		ob->move(environment(me));
		
	if (objectp(follower))
	{
		ob2=query("me_mater", follower);
		if (objectp(ob2))
			ob2->move(environment(follower));	
	}
		 		 	
        if(objectp(running))destruct(running);

	if (objectp(horse))
		message("vision",  "\n" + this_object()->name() + HIW "到了目的地，猛然長嘶，前"
                          "踢高揚，頓時塵土四散……\n" NOR, environment(horse), ({horse}));

	return 1;
}

// 強行上馬
int force_me_ride(object me)
{
        object owner;

    if (! objectp(me))
    {
		write("物件出錯。\n");
		return 0;
    }

	if( query_temp("is_rided_follow", this_object()) )
		return 0;

	owner=query_temp("is_rided_by", this_object());

  set_temp("is_rided_follow", me, 	this_object());
set_temp("is_riding_follow", this_object(), 	me);

    message_vision("$N躍上$n" NOR "，坐在" + owner->name() + "的身後。\n", me, this_object());

	return 1;
}

// 心跳
void heart_beat()
{
     int level;
     object follower;
/*
     remove_call_out("start_heart_beat");
     call_out("start_heart_beat", 2);
*/
     level=query("level", this_object());

     if( !query_temp("running", this_object()) )
     {
	if( query("tili", this_object())+1<query("max_tili", this_object()))		
       addn("tili", level+random(level), 		this_object());
		
	if( query("tili", this_object())>query("max_tili", this_object()) )
set("tili",query("max_tili",  this_object()), 		this_object());
     }

     follower=query_temp("is_rided_follow", this_object());
     if (! objectp(follower))return;

     if (! objectp(environment(follower)) || 
         (objectp(follower) && (userp(follower) && ! interactive(follower))) ||
          (objectp(follower) && environment(follower) != query_temp("is_rided_by", environment(this_object()))) )
     {
delete_temp("is_rided_follow", 	this_object());
     }

     return;
}

int query_autoload()
{
     return 1;
}