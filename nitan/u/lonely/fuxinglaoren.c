// xiantong.c
#include <ansi.h>

inherit NPC;
inherit F_DTIME;

#define MEMBER_D              "/adm/daemons/memberd"
#define DB_D                  "/adm/daemons/dbd"

string gift_jingyan();
string gift_neigong();
string gift_ultra();
string gift_pthuiyuan();
string gift_zshuiyuan();


void create()
{
    	set_name(HIY "福星老人" NOR, ({ "fuxing laoren", "fuxing", "laoren" }));
	set("nickname", HIG "迎賓使者" NOR);
	set("title", "");
   	set("long", "他是笑傲漿糊開服迎賓使者，負責活動獎勵的發放。\n");
    	set("gender", "男性");
    	set("age", 999);
	set("max_qi", 99999);
	set("qi", 99999);
	set("max_jingli", 99999);
	set("max_jing", 99999);
	set("max_neili", 99999);
	set("jing", 99999);
	set("jingli", 99999);
	set("neili", 99999);

	set("per", 28);
	set("con", 88);
	set("int", 88);
	set("dex", 88);
	set("str", 88);

        set_disappear_msg("\n你只覺得眼前一閃，定睛一看，福星老人已經不見了。\n");
        set_appear_time(([
	        "2,7," : "3,7,",
        ]));
	
	set("inquiry", ([ 
		"笑傲江湖"      : "笑傲漿糊是泥潭系統終極版本，希望你玩得愉快。\n",
		"服務"          : "我是笑傲漿糊客服NPC，以後請多多指教！\n",
		"lonely"        : "Lonely你都不認識，還是回去多讀幾年書吧！\n",
		"福星老人"      : "別磨磨蹭蹭，找我有什麼事快説吧！\n",
                "每日獎勵"      : "每日獎勵到禮物天使那裏領取！\n",
                "經驗獎勵"      : (: gift_jingyan :),
                "內功獎勵"      : (: gift_neigong :),
                "宗師獎勵"      : (: gift_ultra :),
                "普通會員獎勵"  : (: gift_pthuiyuan :),
                "終身會員獎勵"  : (: gift_zshuiyuan :),
	]));

    	set("combat_exp", 10000000);
    	set("shen_type", 1);
    	setup();
}

string gift_jingyan()
{
	object me, ob;
	
	if (! objectp(me = this_player()))return "";
	
	if (query("kaifu_huodong/gift_jingyan", me))
		return me->name() + NOR "你已經領取過該獎勵了！";
	
	if (query("combat_exp", me) < 8880000)
	{
		return me->name() +  NOR "你經驗不足888萬，不能參與該活動！\n";
	}
	
	// 只允許前100名玩家領取
	if (DB_D->query_data("kaifu_huodong/gift_jingyan/count") < 100)
	{
		ob = new("/clone/armor/shuijing-guan");
		if (! objectp(ob))return "複製物品錯誤，請聯繫巫師！";
		
	        set("who_get/id", query("id", me), ob);
		set("who_get/time", time() + 30, ob); // 30秒內都不能撿取
		ob->move(me, 1);
		set("kaifu_huodong/gift_jingyan", 1, me);
		me->save();

		log_file("gift_jingyan", query("id", me) + " at " + ctime(time()) + "領取經驗獎勵，排名:" +
		         sprintf("%d", DB_D->query_data("kaifu_huodong/gift_jingyan/count")+1) + "\n");

		DB_D->set_data("kaifu_huodong/gift_jingyan/count", DB_D->query_data("kaifu_huodong/gift_jingyan/count") + 1);
		
		
		return me->name() + NOR "成功領取獎勵！";
	}
	else
	{
		return "對不起，前100名領獎名額已滿了！";
	}
	
	return "祝您遊戲愉快！";

}

string gift_neigong()
{
	object me, ob1,ob2;
	
	if (! objectp(me = this_player()))return "";
	
	if (query("kaifu_huodong/gift_neigong", me))
		return me->name() + NOR "你已經領取過該獎勵了！";	
	
	if (me->query_skill("force", 1) < 500)
	{
		return me->name() +  NOR "你基本內功不足500級，不能參與該活動！\n";
	}
	
	// 只允許前100名玩家領取
	if (DB_D->query_data("kaifu_huodong/gift_neigong/count") < 100)
	{
		ob1 = new("/clone/fam/item/wuming-tongren");
		if (! objectp(ob1))return "複製物品錯誤，請聯繫巫師！";
		ob2 = new("/clone/fam/item/wuming-tongren");
		if (! objectp(ob2))return "複製物品錯誤，請聯繫巫師！";
				
	        set("who_get/id", query("id", me), ob1);
		set("who_get/time", time() + 30, ob1); // 30秒內都不能撿取
		ob1->move(me, 1);
	        set("who_get/id", query("id", me), ob2);
		set("who_get/time", time() + 30, ob2); // 30秒內都不能撿取
		ob2->move(me, 1);
		set("kaifu_huodong/gift_neigong", 1, me);		
		me->save();

		log_file("gift_neigong", query("id", me) + " at " + ctime(time()) + "領取內功獎勵，排名:" +
		         sprintf("%d", DB_D->query_data("kaifu_huodong/gift_neigong/count")+1) + "\n");

		DB_D->set_data("kaifu_huodong/gift_neigong/count", DB_D->query_data("kaifu_huodong/gift_neigong/count") + 1);
		return me->name() + NOR "成功領取獎勵！";	
	}
	else
	{
		return "對不起，前100名領獎名額已滿了！";
	}
	
	return "祝您遊戲愉快！";
}

string gift_ultra()
{
	object me,ob1,ob2;
	
	if (! objectp(me = this_player()))return "";

	if (query("kaifu_huodong/gift_ultra", me))
		return me->name() + NOR "你已經領取過該獎勵了！";
		
	if (! ultrap(me))
	{
		return me->name() +  NOR "你還沒有獲得宗師稱號，不能參與該活動！\n";
	}
	
	// 只允許前100名玩家領取
	if (DB_D->query_data("kaifu_huodong/gift_rendu/count") < 100)
	{
		ob1 = new("/clone/tongren/tongren1");
		if (! objectp(ob1))return "複製物品錯誤，請聯繫巫師！";
		ob2 = new("/clone/tongren/tongren2");
		if (! objectp(ob2))return "複製物品錯誤，請聯繫巫師！";

	        set("who_get/id", query("id", me), ob1);
		set("who_get/time", time() + 30, ob1); // 30秒內都不能撿取
		ob1->move(me, 1);
	        set("who_get/id", query("id", me), ob2);
		set("who_get/time", time() + 30, ob2); // 30秒內都不能撿取
		ob2->move(me, 1);
		set("kaifu_huodong/gift_ultra", 1, me);		
		me->save();

		log_file("gift_ultra", query("id", me) + " at " + ctime(time()) + "領取宗師獎勵，排名:" +
		         sprintf("%d", DB_D->query_data("kaifu_huodong/gift_rendu/count")+1) + "\n");

		DB_D->set_data("kaifu_huodong/gift_rendu/count", DB_D->query_data("kaifu_huodong/gift_rendu/count") + 1);
		return me->name() + NOR "成功領取獎勵！";	
	}
	else
	{
		return "對不起，前100名領獎名額已滿了！";
	}
	
	return "祝您遊戲愉快！";

}

string gift_pthuiyuan()
{
	object me, ob;
	

	if (! objectp(me = this_player()))return "";
	
	if (query("kaifu_huodong/gift_pthuiyuan", me))
		return me->name() + NOR "你已經領取過該獎勵了！";
			
	if (! MEMBER_D->is_valid_member(query("id",me)))
	{
		return me->name() +  NOR "你不是有效會員，不能參與該活動！\n";
	}
	
	// 只允許前100名玩家領取
	if (DB_D->query_data("kaifu_huodong/gift_pthuiyuan/count") < 100)
	{
		ob = new("/clone/armor/yecha2");
		if (! objectp(ob))return "複製物品錯誤，請聯繫巫師！";
		
	        set("who_get/id", query("id", me), ob);
		set("who_get/time", time() + 30, ob); // 30秒內都不能撿取
		ob->move(me, 1);
		set("kaifu_huodong/gift_pthuiyuan", 1, me);
		me->save();

		log_file("gift_pthuiyuan", me->query("id") + " at " + ctime(time()) + "領取經驗獎勵，排名:" +
		         sprintf("%d", DB_D->query_data("kaifu_huodong/gift_pthuiyuan/count")+1) + "\n");

		DB_D->set_data("kaifu_huodong/gift_pthuiyuan/count", DB_D->query_data("kaifu_huodong/gift_pthuiyuan/count") + 1);
		
		return me->name() + NOR "成功領取獎勵！";
	}
	else
	{
		return "對不起，前100名領獎名額已滿了！";
	}
	
	return "祝您遊戲愉快！";
}

string gift_zshuiyuan()
{
	object me, ob1, ob2, ob3, ob4, ob5, ob6, ob7;

	if (! objectp(me = this_player()))return "";

	if (query("kaifu_huodong/gift_zshuiyuan", me))
		return me->name() + NOR "你已經領取過該獎勵了！";

	if (MEMBER_D->db_query_member(me, "endtime") < 1888888888)
	{
		return me->name() +  NOR "你不是終身會員，不能參與該活動！\n";
	}

	// 只允許前20名玩家領取
	if (DB_D->query_data("kaifu_huodong/gift_zshuiyuan/count") < 20)
	{
		ob1 = new("/clone/goods/wisdom_armor");
		if (! objectp(ob1))return "複製物品1錯誤，請聯繫巫師！";
		ob2 = new("/clone/goods/wisdom_cloth");
		if (! objectp(ob2))return "複製物品2錯誤，請聯繫巫師！";
		ob3 = new("/clone/goods/wisdom_head");
		if (! objectp(ob3))return "複製物品3錯誤，請聯繫巫師！";
		ob4 = new("/clone/goods/wisdom_boots");
		if (! objectp(ob4))return "複製物品4錯誤，請聯繫巫師！";	
		ob5 = new("/clone/goods/wisdom_wrists");
		if (! objectp(ob5))return "複製物品5錯誤，請聯繫巫師！";
		ob6 = new("/clone/goods/wisdom_waist");
		if (! objectp(ob6))return "複製物品6錯誤，請聯繫巫師！";	
		ob7 = new("/clone/goods/wisdom_surcoat");
		if (! objectp(ob7))return "複製物品7錯誤，請聯繫巫師！";	
									
	        set("who_get/id", query("id", me), ob1);
		set("who_get/time", time() + 30, ob1); // 30秒內都不能撿取
		ob1->move(me, 1);
	        set("who_get/id", query("id", me), ob2);
		set("who_get/time", time() + 30, ob2); // 30秒內都不能撿取
		ob2->move(me, 1);
	        set("who_get/id", query("id", me), ob3);
		set("who_get/time", time() + 30, ob3); // 30秒內都不能撿取
		ob3->move(me, 1);
	        set("who_get/id", query("id", me), ob4);
		set("who_get/time", time() + 30, ob4); // 30秒內都不能撿取
		ob4->move(me, 1);
	        set("who_get/id", query("id", me), ob5);
		set("who_get/time", time() + 30, ob5); // 30秒內都不能撿取
		ob5->move(me, 1);
	        set("who_get/id", query("id", me), ob6);
		set("who_get/time", time() + 30, ob6); // 30秒內都不能撿取
		ob6->move(me, 1);
	        set("who_get/id", query("id", me), ob7);
		set("who_get/time", time() + 30, ob7); // 30秒內都不能撿取
		ob7->move(me, 1);
														
		set("kaifu_huodong/gift_zshuiyuan", 1, me);
		me->save();

		log_file("gift_zshuiyuan", query("id", me) + " at " + ctime(time()) + "領取終身會員獎勵，排名:" +
		         sprintf("%d", DB_D->query_data("kaifu_huodong/gift_zshuiyuan/count")+1) + "\n");

		DB_D->set_data("kaifu_huodong/gift_zshuiyuan/count", DB_D->query_data("kaifu_huodong/gift_zshuiyuan/count") + 1);

		
		return me->name() + NOR "成功領取獎勵！";
	}
	else
	{
		return "對不起，前20名領獎名額已滿了！";
	}

	return "祝您遊戲愉快！";

}
