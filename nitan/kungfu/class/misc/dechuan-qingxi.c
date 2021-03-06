#include <ansi.h>

#define MAX_POINT     300
#define MEMBER_D      "/adm/daemons/memberd"

// X小時後更新
#define UPDATE_TIME          48 * 3600
// 出現地點
#define UPDATE_PLACE         "/d/quanzhou/nanmen"
// BOSS文件
#define BOSS_FILE            "/kungfu/class/misc/dechuan-qingxi"

// 經驗過高後無任何獎勵
#define MAX_EXP              200000000

inherit NPC;

void create()
{
        set_name(HIG "德川慶喜" NOR, ({ "dechuan qingxi boss",}));
        set("title", HIR "德川幕府的將軍" NOR);
        set("gender", "男性");
        set("age", 42);
        set("long", @LONG
來自德川幕府的將軍，據説身手一流。
LONG);
        set("attitude", "friendly");
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("per", 20);
        set("shen_type", 0);

	set("no_nuoyi", 1); // 不被挪移影響
	
        set("qi", 36000000);
        set("max_qi", 36000000);

        set("jing", 4000000);
        set("max_jing", 4000000);
        set("jingli", 4000000); 
        set("max_jingli", 4000000); 

        set("neili", 65000); 
        set("max_neili", 65000); 
        set("jiali", 2000); 
        set("combat_exp", 60000000);

	set("scborn/ok", 1);
	set("special_skill/guimai", 1);
	
        set_skill("force", 1400);
        set_skill("pixie-jian", 1400);
        set_skill("surge-force", 1400);
        set_skill("liumai-shenjian", 1400);
        set_skill("sword", 1400);
        set_skill("finger", 1400);
        set_skill("whip", 1400);
        set_skill("dodge", 1400);
        set_skill("parry", 1400);
        set_skill("unarmed", 1400);
        set_skill("strike", 1400);
        set_skill("zuoyou-hubo", 500);
        set_skill("literate", 1000);
        set_skill("throwing", 1400);
        set_skill("jueqing-quyu", 500);
        set_skill("jingluo-xue", 500);
        set_skill("martial-cognize", 1400);

        map_skill("force", "surge-force");
        map_skill("sword", "pixie-jian");
        map_skill("dodge", "pixie-jian");
        map_skill("parry", "pixie-jian");
        map_skill("unarmed", "pixie-jian");
        map_skill("finger", "liumai-shenjian");

        prepare_skill("finger", "liumai-shenjian");

        set_temp("apply/attack",16000);
        set_temp("apply/defense", 16000);
        set_temp("apply/damage", 10000);
        set_temp("apply/unarmed_damage", 10000);
        set_temp("apply/armor", 10000);
        set_temp("apply/fy", 10);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform sword.duo and sword.gui") :),
                (: command("perform sword.pi and sword.po") :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: perform_action, "sword.jian twice" :),
                (: perform_action, "finger.tian twice" :),
        }) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/baipao")->wear();
}

int accept_fight(object ob)
{
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        kill_ob(ob);
        return -1;	
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
	ob->start_busy(5 + random(6));
	me->receive_wound("qi", 8500 + random(5600), ob);
        return HIY "$N" HIY "怒喝一聲，奮力反抗，竟逼得$n" HIY "手忙腳亂。\n" NOR;
}

void heart_beat()
{
	if (query("neili") < 1 && random(50) == 1)						
		set("neili", query("max_neili"));

	return ::heart_beat();
}

void unconcious()
{
	// 防止直接call_die()
	if (query("qi") > 500000)
	{
		revive();
		return;
	}
        die(query_last_damage_from());
}

void die(object killer)
{
        object dob;             // 打暈這個NPC的人
        int n;                  // 可以獎勵的人的數目
        int exp;                // 需要瓜分的經驗
        int pot;                // 需要瓜分的潛能
        int weiwang;            // 需要瓜分的威望
        int gongxian;           // 貢獻
        int tihui;              // 體會
        int score;              // 需要瓜分的閲歷
        object *t;              // 殺死我的人的隊伍列表
        object tob;
        int ysg;
        int i;

        // 定義獎勵物品列表
	// 機率  MAX_POINT 分之 X
	mixed oblist = ([
			"/clone/misc/boss_item/jiaozi"               :         240,			
			"/clone/armor/mingwang-xiang"                :         100,
			"/clone/armor/sanye-cao"                     :         100,
			"/clone/fam/enchase/guxuan-yu2"              :          80,
			"/clone/armor/fusang/jianghu-zhanyi"         :         200,
		]);

		object gift_ob;
		string s_gift, *key_s_gift;
		int gift_point;

	        // 防止直接call_die()
		if (query("qi") > 500000)
		{
			revive();
			return;
		}

                // 找到殺了我(NPC)或是打暈我的人
                if (! objectp(dob = killer))
                dob = query_last_damage_from();

		if (! dob)
		{
			//MAP_D->update_boss(BOSS_FILE,UPDATE_PLACE,UPDATE_TIME);
			destruct(this_object());
			return;
		}

                t = dob->query_team();

	        if (objectp(dob) && environment(dob) == environment(this_object()))
	        {
	                exp = 200000 + random(290000);
	                pot = 300000 + random(400000);
	                gongxian = 4400 + random(8200);
	                tihui = 30000 + random(35000);
			n = 0;
	                n = sizeof(t);

	                if (! n || n < 3)
	                {
	                       exp /= 3;
	                       pot /= 3;
	                       weiwang /= 3;
	                       score /= 3;
	                       tihui = 0;	                       
	                }

			if (n >= 3)
			{
				exp /= n;
				pot /= n;			
			}
	
			if (n)
			{				
				foreach(tob in t)
				{
					
					if (objectp(tob) && living(tob))
					{
						if (tob->query("combat_exp") >= MAX_EXP)continue;
						if (environment(tob) == environment(dob))
							GIFT_D->delay_bonus(tob,
								([ "exp"      : exp + ((tob == dob) ? 30000 : 0),
								   "pot"      : pot + ((tob == dob) ? 30000 : 0),
								   "mar"      : tihui + ((tob == dob) ? 3000 : 0),
								   //"gongxian" : tob->query("family/family_name") == "崑崙派" ? gongxian : 0,
								   "prompt"   : "你的隊伍打敗" + name() + "之後"]), 999);
	
					}
				}
			}
			else
			{
				if (dob->query("combat_exp") < MAX_EXP)
					GIFT_D->delay_bonus(dob,
						 ([ "exp"      : exp,
					    	    "pot"      : pot,
					    	    "prompt"   : "你在打敗" + name() + "之後"]), 999);
			}
	
	        }
		
	        // 一定機率掉物品在殺我的人身上dob
		if (objectp(dob) && environment(dob) == environment(this_object()) && 
		    dob->query("combat_exp") < MAX_EXP)
		{
			key_s_gift = keys(oblist);
			s_gift = key_s_gift[random(sizeof(key_s_gift))];
			gift_point = oblist[s_gift];

			// 判斷機率
			if (MEMBER_D->is_valib_member(dob->query("id")) 
			    && random(MAX_POINT / ITEM_D->gift_point()) < gift_point)
			{
				// 獲得物品--爆出物品直接放在dob身上
				gift_ob = new(s_gift);
				if (objectp(gift_ob))
				{
					message_vision(HIR "叮~~一聲，從$N" HIR "掉出一樣東西，$n" HIR 
						       "趕緊揀了起來。\n" NOR, this_object(), dob);
					tell_object(dob, BLINK + HIG "你得到了" + gift_ob->name() + BLINK + HIG "。\n" NOR);
					gift_ob->move(dob, 1);
				}
				else // 紀錄之 
				{
					log_file("killed-gift-none", s_gift + "\n");
				}
			}
		}

	        // 消失
	        if (0)
	        {
	        	command("chat* heng");
		}/*
		else
		{
			message_vision(HIG "猛然間，$N " HIG " 向後一跳，隨手仍出一顆黑色小丸，頓時騰起一片煙霧 ...\n" NOR, 
			               this_object());
			command("chat 哼，雕蟲小技，不陪你們玩了，告辭！");
			CHANNEL_D->do_channel(this_object(), "rumor", "聽説" + name() + HIM "從古墓中盜得珍寶後，奪路而逃。" NOR);
		}
*/
		// 設置更新
		//MAP_D->update_boss(BOSS_FILE,UPDATE_PLACE,UPDATE_TIME);
		
		// 1/200機率掉出無名銅人
		if (random(200) < 1)
		{
			object ob_tongren;
			ob_tongren = new("/clone/fam/item/wuming-tongren");			
			message_vision(HIR "當~~一聲，從$N" HIR "身上掉出" + ob_tongren->name() + HIR "，落在地上。\n" NOR, this_object());
			ob_tongren->set("who_get/id", "NONE");
			ob_tongren->set("who_get/time", time() + 30); // 30秒內都不能撿取		
			ob_tongren->move(environment(this_object()));
		}	
		
		// 特殊活動爆物品，統一調用giftd接口
		GIFT_D->fuben_boss_gift(this_object());	
					
		destruct(this_object());
	
	        return;
}

void remove()
{
	MAP_D->update_boss(BOSS_FILE,UPDATE_PLACE,UPDATE_TIME);
	return;
}
