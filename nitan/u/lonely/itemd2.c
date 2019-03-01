// itemd.c
// updated by Rcwiz 2006.03.14

#pragma optimize

#pragma save_binary


#include <ansi.h>
#include <command.h>

#define GIFT_POINT   1

void create() { seteuid(getuid()); }
void reduce_consistence(object item, object me, object victim, int damage);

// 返回爆物品幾率
// 1 為正常，2 為雙倍
int gift_point(){ return GIFT_POINT; }

// 返回項鏈內功加成點及內力加成點
// 1 為內功加成 ， 2為內力加成
int neck_add_damage(object me, int k)
{
		mapping neck_enlist = ([
			"藍寶石"     :     ({ 5, 10 }),
			"紅寶石"     :     ({ 10, 5 }),
			"聖龍之眼"   :     ({ 50, 10 }),
			"聖龍之魂"   :     ({ 15, 40 }),
			"神龍夢幻"   :     ({ 50, 30 }),
			"神龍無邊"   :     ({ 40, 40 }),
			"妖靈﹒魂"    :     ({ 50, 60 }),
			"妖靈﹒魄"    :     ({ 60, 50 }),	
		]);

		object ob; // 項鏈
		int total_force, total_neili, i, count;
		string *key_enchase, *key_neck_point;
		mapping enchase;

		total_force = 0;
		total_neili = 0;

		if (! objectp(me))return 0;

		if (! objectp( ob = me->query_temp("armor/neck")))return 0;
				
		if (! ob->is_item_make())return 0;
		
		if (ob->query("enchase_all") < 1)return 0;
		
		enchase = ob->query("enchase");

		if (! sizeof(enchase))return 0;

		key_enchase = keys(enchase);
		count = sizeof(key_enchase);
		if (! count)return 0;
		
		
		for (i = 0; i < count; i ++ )
		{
			// 找到對應的鑲嵌物品
			key_neck_point = neck_enlist[enchase[key_enchase[i]]["name"]];
			if (sizeof(key_neck_point))
			{
					total_force += key_neck_point[0];
					total_neili += key_neck_point[1];
			} 
		}

		if (k == 1)return total_force;
		if (k == 2)return total_neili;
		
		return 0;
						
}

// 檢查項鏈中是否鑲嵌著某兩種物品
// 用于檢測是否出特效
// 返回0則沒有鑲嵌，返回正整數為計算出特效的幾率
int neck_enchase_item(object me, string item1, string item2)
{
		object ob; // 項鏈
		string *key_enchase;
		mapping enchase;
		int count, i, i1, i2, result;
		int have10kOB = 0; // 是否有10孔鑲嵌物

		if (! objectp(me))return 0;

		if (! objectp( ob = me->query_temp("armor/neck")))return 0;
				
		if (! ob->is_item_make())return 0;
		
		if (ob->query("enchase_all") < 1)return 0;
		
		enchase = ob->query("enchase");

		if (! sizeof(enchase))return 0;

		key_enchase = keys(enchase);
		count = sizeof(key_enchase);
		if (! count)return 0;
		
		i1 = 0;
		i2 = 0;
		for (i = 0; i < count; i ++ )
		{
			// 找到對應的鑲嵌物品
			if (enchase[key_enchase[i]]["name"] == item1)i1 ++;
			if (enchase[key_enchase[i]]["name"] == item2)i2 ++;	
			
			// 是否鑲嵌10孔寶石
			if (enchase[key_enchase[i]]["spe_data"]["luhua-zhijing"])have10kOB = 1;
		}

		if (i1 == 0 || i2 == 0)return 0;
		
		// 計算幾率
		result = i1 < i2 ? i1 : i2;

		if (COMBAT_D->enchased_neck_item(me, "七彩神珠"))result += 2;
		
		if (COMBAT_D->enchased_neck_item(me, "聖石") &&
			item1 == "藍寶石" || item1 == "紅寶石")result += 6;

		if (COMBAT_D->enchased_neck_item(me, "水靈") &&
			item1 == "聖龍之眼" || item1 == "聖龍之魂")result += 5;

		if (COMBAT_D->enchased_neck_item(me, "百煉寒精") &&
			item1 == "神龍夢幻" || item1 == "神龍無邊")result += 5;
		
		if (COMBAT_D->enchased_neck_item(me, "妖靈之翼") &&
			item1 == "妖靈﹒魂" || item1 == "妖靈﹒魄")result += 5;
		
		if (have10kOB)result += 5;
		
		return result;

}

// 發揮項鏈特殊攻擊
int do_neck_attack(object me, object target)
{
		mapping special_attack = ([
			"無雙合擊"    :  ({"藍寶石", "紅寶石"}),
			"聖龍之怒"    :  ({"聖龍之眼", "聖龍之魂"}),
			"龍咆哮"      :  ({"神龍夢幻", "神龍無邊"}),
			"妖靈合擊"    :  ({"妖靈﹒魂", "妖靈﹒魄"}),
		]);

		string *key_special_attack, *need_item, msg;
		string skill; // 最終選定的技能
		int count, point;

		key_special_attack = keys(special_attack);

		count = sizeof(key_special_attack);

		skill = key_special_attack[random(count)];

		// 該技能出現幾率
		need_item = special_attack[skill];
		point = neck_enchase_item(me, need_item[0], need_item[1]);

		if (point > 2 && userp(target))point /= 2;
				
		if (! point)return 0;
		
		if (! objectp(me) || ! objectp(target))return 0;		

		// 滿足幾率
		if (1 + random(100) <= point)
		{
			if (skill == "無雙合擊")
			{
				msg = HIY "$N胸前數道光芒閃過，猛然間猶如著魔一般，竟然施展出「無雙合擊」，連連攻向$n" HIY "。\n" NOR;
				message_combatd(msg, me, target);
				COMBAT_D->do_attack(me, target, 0, 0);
				COMBAT_D->do_attack(me, target, 0, 0);
			}
			if (skill == "聖龍之怒")
			{
				msg = HIC "剎那間，$N胸前項鏈發出刺眼的藍光，並不停的顫抖，神技「聖龍之怒」已然發出，頃刻間，一道藍芒已射向$n" HIC "！\n" NOR;
				message_combatd(msg, me, target);
				if (target->query("neili") > 0)								
					target->add("neili", -1 * target->query("neili") / 10 );
				if (target->query("qi") > 0)								
					target->add("qi", -1 * target->query("qi") / 10 );
				if (target->query("eff_qi") > 0)								
					target->add("eff_qi", -1 * target->query("eff_qi") / 20 );
				
				if (userp(target))target->start_busy(5 + random(5));
				else target->start_busy(8 + random(8));
				
			}
			if (skill == "龍咆哮")
			{
				msg = HIM "突然，$N胸前項鏈發出震天巨響，猶如千萬條巨龍咆哮，「龍咆哮」已奔嘯而出，響徹天地！\n" NOR;
				message_combatd(msg, me, target);
				if (userp(target))
					target->receive_wound("qi", me->query("jiali") * 2 + random(me->query("jiali") * 3));

				else
					target->receive_wound("qi", me->query("jiali") * 3 + random(me->query("jiali") * 6));

			}
			if (skill == "妖靈合擊")
			{
				msg = HIG "陰風狂起，兩道寒光自$N胸前瀑出，湧向四周，絕技「妖靈合擊」卻已發出，將$n" HIG "籠罩！\n" NOR;
				COMBAT_D->do_attack(me, target, 0, 0);
				COMBAT_D->do_attack(me, target, 0, 0);
				message_combatd(msg, me, target);
				if (userp(target))
					target->receive_wound("qi", me->query_skill("force") * 2 + random(me->query_skill("force") * 3));
				
				else
					target->receive_wound("qi", me->query_skill("force") * 3 + random(me->query_skill("force") * 6));
			}

			// 降低耐久度
			if (objectp(me->query_temp("armor/neck")))
			{
				reduce_consistence(me->query_temp("armor/neck"), me, target, 0);
				reduce_consistence(me->query_temp("armor/neck"), me, target, 0);
				reduce_consistence(me->query_temp("armor/neck"), me, target, 0);
				reduce_consistence(me->query_temp("armor/neck"), me, target, 0);
				reduce_consistence(me->query_temp("armor/neck"), me, target, 0);
				reduce_consistence(me->query_temp("armor/neck"), me, target, 0);
			}
		}
		
		return point;
		
}


// huya
void huya_remove_effect(object me, int ef_point, int en_heishuijing)
{
		me->delete_temp("enchase/special/huya", 1); // 取消標志
		me->add_temp("apply/damage", -1 * (ef_point + ef_point / 2 * en_heishuijing));
		me->add_temp("apply/str", -1 * (ef_point / 20 + ef_point / 40 *  en_heishuijing));
		me->add_temp("apply/force", -1 * (ef_point / 20 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/blade", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/staff", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/whip", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/club", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));	
		
		tell_object(me, HIG "「虎嘯」的效果消失了。\n" NOR);
}

// yingyan
void yingyan_remove_effect(object me, int ef_point, int en_heishuijing)
{
		me->delete_temp("enchase/special/yingyan", 1); // 取消標志
		me->add_temp("apply/damage", -1 * (ef_point + ef_point / 2 * en_heishuijing));
		me->add_temp("apply/dex", -1 * (ef_point / 20 + ef_point / 40 *  en_heishuijing));
		me->add_temp("apply/finger", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/strike", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/unarmed", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/cuff", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/hand", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/claw", -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));

		tell_object(me, HIG "「鷹之歌」的效果消失了。\n" NOR);
}

// xuejingling
void xuejingling_remove_effect(object me, int ef_point, int en_heishuijing)
{
		me->delete_temp("enchase/special/xuejingling", 1); // 取消標志
		me->add_temp("apply/con",  -1 * (ef_point / 20 + ef_point / 40 *  en_heishuijing));
		me->add_temp("apply/dex",  -1 * (ef_point / 20 + ef_point / 40 *  en_heishuijing));
		me->add_temp("apply/str",  -1 * (ef_point / 20 + ef_point / 40 *  en_heishuijing));
		me->add_temp("apply/dodge",  -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/parry",  -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));
		me->add_temp("apply/force",  -1 * (ef_point / 10 + ef_point / 20 * en_heishuijing));

		tell_object(me, HIG "「雪地聖音」的效果消失了。\n" NOR);
}

// xuejingling 分身消除
void fenshen_remove_effect(object me)
{
		me->delete_temp("hiding_kuihua");	    
		tell_object(me, HIG "「雪地聖音」﹒分身的效果消失了。\n" NOR);
}

// 發揮護腕特殊攻擊
int do_wrists_attack(object me, object victim, string en9)
{
	mapping enchase;
	int i_en, i, i_temp, j;
	string item_type, ran_item_enchase, s_temp;
	string ran_enchase_affect;

	string *k_enchase, *k_affect_list;
	mapping affect_list;
	string ran_affect;
	int en_zipili = 0; // 是否鑲嵌九孔紫霹靂
	int en_heishuijing = 0; // 是否鑲嵌九孔黑水晶
	int i_ef;

	object item;

	int ef_point, ef_ran, n_ef;
	int ran_result;
	string msg;

	mapping list = ([
		"鷹眼"   :  ([
					"yingyan" : ([   "ran"    :  1 + random(2),
                                     "point"  :  500 + random(501)]),
		]),
		"虎牙"   :  ([
					"huya" : (["ran"    :  1 + random(2),
                               "point"  :  500 + random(501)]),
		]),
		"雪精靈"   :  ([
					"xuejingling"    : (["ran"    :  1 + random(2),
                                         "point"  :  500 + random(501)]),
		]),
		"碧水融華"   :  ([
					"bishuironghua"  : (["ran"    :  1 + random(2),
                                         "point"  :  300 + random(201)]),
		]),
	]);

	if (! objectp( item = me->query_temp("armor/wrists")))return 0;

    // 不是自造兵器則返回
	if (! item->is_item_make())return 0;

	// 沒有鑲嵌則返回
	enchase = item->query("enchase");
	
	if (! mapp(enchase))return 0;
	i_en = sizeof(enchase);
	if (! i_en)return 0;

	// 幾率計算 平均?% + 幾個累加%
	// 同一時間隨機選取一種特效
	k_enchase = keys(enchase);

    // 從已鑲嵌的物品中隨機選擇一個
	ran_item_enchase = enchase[k_enchase[random(i_en)]]["name"];

	// 從選取的物品中隨機選擇一種特效
	affect_list = list[ran_item_enchase];
	if (! affect_list)return 0;

	k_affect_list = keys(affect_list);

	i_ef = sizeof(k_affect_list);
	if (! i_ef)return 0;

	ran_affect = k_affect_list[random(i_ef)];

	// 特效選取好後則計算特效幾率及威力（時間等）
	// 幾率計算 平均?% + 幾個累加%
	// 威力計算，當前獲取的隨機鑲嵌物品的該特效威力
	
	// 先計算威力
	ef_point = list[ran_item_enchase][ran_affect]["point"];

	// 計算幾率
	// 先計算幾率總和及該特效個數
	n_ef = 0;
	ef_ran = 0;
	for (i = 0; i < i_en; i ++)
	{
		// 分別依次獲得已鑲嵌的物品
		s_temp = enchase[k_enchase[i]]["name"];

		// 如果效果定義中無該鑲嵌物品則跳過
		if (member_array(s_temp,keys(list)) == -1)continue;

		// 如果該鑲嵌物品存在此特效
		if (mapp(list[s_temp][ran_affect]))
		{
			n_ef += 1;
			ef_ran += list[s_temp][ran_affect]["ran"];
		}
	}

	// 得到最後計算的幾率
	if (n_ef <= 0)ran_result = 2;  //以防萬一
	else
		ran_result = ef_ran / n_ef + n_ef - 1;


	// 是否鑲嵌紫霹靂和黑水井
	for (j = 0; j < sizeof(k_enchase); j ++ )
	{
		if (enchase[k_enchase[j]]["name"] == "黑水晶")
		{
			en_heishuijing = 1;
		}
		if (enchase[k_enchase[j]]["name"] == "紫霹靂")
		{
			en_zipili = 1;
		}
	}

    // 外部調用，返回是否鑲嵌某種物品
	if (stringp(en9))
	{
		if (en9 == "heishuijing")
			return en_heishuijing;

		if (en9 == "zipili")
			return en_heishuijing;
	}

	// 隨機判斷是否發出該特效
	if (1 + random(100) > ran_result)return 0;
	
	// 發出特效
	switch(ran_affect)
	{
		case "yingyan":

			if (me->query_temp("enchase/special/yingyan"))return 0;

			message_combatd(HIG + "$N" HIG "的「" + ran_item_enchase + "」發出一道奇異的光芒！\n" NOR, me);

			msg = HIR "烏雲散去，一聲尖厲的嘯叫自天空傳來，" + me->name() + HIR "指手向天，數到奇光劃過將" + me->name() +
				  HIR "\n包圍，然後漸漸侵入其體內，令人匪夷所思。\n" NOR;
			tell_object(me, msg);
			
			me->set_temp("enchase/special/yingyan", 1); // 設置標志，以免重復累加效果
			me->add_temp("apply/damage", ef_point + ef_point / 2 * en_heishuijing);
			me->add_temp("apply/dex", ef_point / 20 + ef_point / 40 *  en_heishuijing);
			me->add_temp("apply/finger", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/strike", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/unarmed", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/cuff", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/hand", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/claw", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->start_call_out((: call_other, __FILE__, "yingyan_remove_effect",
				                  me, ef_point, en_heishuijing :), 180 + 180 / 2 * en_zipili);
			return 0;

		case "huya":

			if (me->query_temp("enchase/special/huya"))return 0;

			message_combatd(HIG + "$N" HIG "的「" + ran_item_enchase + "」發出一道奇異的光芒！\n" NOR, me);

			msg = HIY "猛然間，一聲凄厲的嚎叫由" + item->name() + HIY "震天般傳出，攝人心魄，但見" + me->name() + HIY
				  "\n仰天望月，一道金黃色的光芒將其全身籠罩，剎那間威風無比，猶如猛虎。\n" NOR;
			tell_object(me, msg);

			me->set_temp("enchase/special/huya", 1); // 設置標志，以免重復累加效果
			me->add_temp("apply/damage", ef_point + ef_point / 2 * en_heishuijing);
			me->add_temp("apply/str", ef_point / 20 + ef_point / 40 *  en_heishuijing);
			me->add_temp("apply/force", ef_point / 20 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/blade", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/staff", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/whip", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/club", ef_point / 10 + ef_point / 20 * en_heishuijing);

			me->start_call_out((: call_other, __FILE__, "huya_remove_effect",
				                  me, ef_point, en_heishuijing :), 180 + 180 / 2 * en_zipili);

			return 0;

		case "xuejingling":

			if (me->query_temp("enchase/special/xuejingling"))return 0;

			message_combatd(HIG + "$N" HIG "的「" + ran_item_enchase + "」發出一道奇異的光芒！\n" NOR, me);

			msg = HIW "天色突變，漫天飛雪狂舞，無數雪精自天而下，紛紛落向" + me->name() + HIW +"，然後侵入" + me->name() +
				  HIW "\n四肢，慢慢消失。\n" NOR;
			tell_object(me, msg);

			me->set_temp("enchase/special/xuejingling", 1); // 設置標志，以免重復累加效果
			me->add_temp("apply/con", ef_point / 20 + ef_point / 40 *  en_heishuijing);
			me->add_temp("apply/dex", ef_point / 20 + ef_point / 40 *  en_heishuijing);
			me->add_temp("apply/str", ef_point / 20 + ef_point / 40 *  en_heishuijing);
			me->add_temp("apply/dodge", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/parry", ef_point / 10 + ef_point / 20 * en_heishuijing);
			me->add_temp("apply/force", ef_point / 10 + ef_point / 20 * en_heishuijing);
			
			me->set_temp("hiding_kuihua", 1); // 分身化影

			me->start_call_out((: call_other, __FILE__, "xuejingling_remove_effect",
				                  me, ef_point, en_heishuijing :), 180 + 180 / 2 * en_zipili);

			me->start_call_out((: call_other, __FILE__, "fenshen_remove_effect",
				                  me :), 45 + 22 / 2 * en_zipili);

			return 0;

		case "bishuironghua":

			if (time() - victim->query_temp("enchase/special/bishuironghua") < 180)return 0;			

			message_combatd(HIG + "$N" HIG "的「" + ran_item_enchase + "」發出一道奇異的光芒！\n" NOR, me);

			msg = HIG "一道綠光閃過，" + victim->name() + HIG "似乎中了邪一般，痴痴地望著前方，綠光卻毫無忌憚地穿過" + 
				  victim->name() + HIG "身體，令其苦不堪言。\n" NOR;
			tell_object(me, msg);

			victim->set_temp("enchase/special/bishuironghua", time());
			victim->start_busy(2 + random(2));
			victim->affect_by("bishuihan_poison",
                              ([ "level" : 300 + 300 / 2 * en_heishuijing,
                                 "id"    : me->query("id"),
                                 "duration" : 100 + 100 / 2 * en_zipili ]));

			return 0;
	}

	return 0;
		
}

// 可以用來浸透的物品列表：必須是物品的base_name
string *imbue_list = ({
        "/clone/fam/gift/int3",
        "/clone/fam/gift/con3",
        "/clone/fam/gift/str3",
        "/clone/fam/gift/dex3",
        "/clone/fam/item/bless_water",
        "/clone/fam/etc/lv7d",
        "/clone/fam/etc/lv7c",
});

// 浸入的次數的隨機界限：如果每次IMBUE以後取0-IMBUE次數的隨機
// 數大于這個數值，則IMBUE最終成功。
#define RANDOM_IMBUE_OK         105

// 每次浸入需要聖化的次數
#define SAN_PER_IMBUE           5

// 殺了人以後的獎勵
void killer_reward(object me, object victim, object item)
{
        int exp;
        mapping o;
        string my_id;

        if (! me || ! victim)
                return;

        if (! victim->query("can_speak"))
                // only human does effect
                return;

        // record for this weapon
	if (victim->is_not_bad())  item->add("combat/WPK_NOTBAD", 1);
	if (victim->is_not_good()) item->add("combat/WPK_NOTGOOD", 1);
	if (victim->is_good())     item->add("combat/WPK_GOOD", 1);
	if (victim->is_bad())      item->add("combat/WPK_BAD", 1);

        if (userp(victim))
                item->add("combat/PKS", 1);
        else
                item->add("combat/MKS", 1);

        exp = victim->query("combat_exp");
        if (exp < 10000 || me->query("combat_exp") < exp * 4 / 5)
                return;

        exp /= 10000;
        if (exp > 250) exp = 100 + (exp - 250) / 16; else
        if (exp > 50) exp = 50 + (exp - 50) / 4;
        my_id = me->query("id");
        o = item->query("owner");
        if (! o) o = ([ ]);
        if (! undefinedp(o[my_id]) || sizeof(o) < 12)
                o[my_id] += exp;
        else
        {
                // Too much owner, I must remove one owner
                int i;
                int lowest;
                string *ks;

                lowest = 0;
                ks = keys(o);
                for (i = 1; i < sizeof(ks); i++)
                        if (o[ks[lowest]] > o[ks[i]])
                                lowest = i;
                map_delete(o, ks[lowest]);
                o += ([ my_id : exp ]);
        }
        item->set("owner", o);
}

// 召喚物品
int receive_summon(object me, object item)
{
        object env;
        object temp;
        int type;
        
/* 在/adm/daemons/biwud.c 做設置
	// 特殊：針對挑戰系統，非我的兵器不能召喚 
	if (! playerp(me) && item->item_owner() != me->query("id"))return 1;
*/	
        if ((env = environment(item)) && env == me)
        {
                tell_object(me, item->name() + "不就在你身上"
                            "嘛？你召喚個什麼勁？\n");
                return 1;
        }

        if (me->query("jingli") < 200)
        {
                tell_object(me, "你試圖呼喚" + item->name() +
                            "，可是難以進入境界，看來是精力不濟。\n");
                return 0;
        }
        me->add("jingli", -200);

        if (item->query("id") == "qingtian")
        {
              message_sort(HIM "\n只見四周金光散布，祥雲朵朵，遠處有鳳凰盤繞，麒麟逐戲。耳邊"
                           "傳來陣陣梵音。$N" HIM "一聲長嘯，" + item->query("name") + HIM
                           "破空而來 ……。\n\n" NOR, me); 
        }
        else

              message_vision(HIW "$N" HIW "突然大喝一聲，伸出右手凌空"
                             "一抓，忽然烏雲密布，雷聲隱隱。\n\n" NOR, me);

        if (env == environment(me))
        {
                message_vision(HIW "只見地上的" + item->name() +
                               HIW "應聲而起，飛躍至$N" HIW
                               "的掌中！\n\n" NOR, me);
        } else
        {
                type = random(3);
                if (env)
                {
                        if (env->is_character() && environment(env))
                                        env = environment(env);

                        switch (type)
                        {
                        case 0:
                                message("vision", HIW "天空中傳來隱隱的雷聲"
                                        "，忽然電閃雷鳴，" + item->name() +
					HIW "騰空而起，"
                                        "消失不見！\n\n" NOR, env);
                                break;
                        case 1:
                                message("vision", HIC "一道神光從天而降"
                                        "，罩定了" + item->name() + HIC "，只見" +
					item->name() + HIC "化作長虹破空而"
					"走。\n\n" NOR, env);
                                break;
                        default:
                                message("vision", HIY "忽然間麝香遍地，氤氳彌漫，" +
                                        item->name() + HIY "叮呤呤的抖動數下，化作一"
					"道金光轉瞬不見！\n\n" NOR, env);
                                break;
                        }

                        if (interactive(env = environment(item)))
                        {
                                tell_object(env, HIM + item->name() +
                                                 HIM "忽然離你而去了！\n" NOR);
                        }
                }

                switch (type)
                {
                case 0:
                        message_vision(HIW "一聲" HIR "霹靂" HIW "，"
                                       "閃電劃破長空，" + item->name() + HIW
                                       "從天而降，飛入$N" HIW "的手中！\n\n" NOR, me);
                        break;
                case 1:
                        if (item->query("id") == "qingtian")break;

                        message_vision(HIW "一道" HIY "長虹" HIW "掃過"
                                       "天空，只見" + item->name() + HIW
					"落入了$N" HIW "的掌中！\n\n" NOR, me);
                        break;
                default:
                        message_vision(HIW "只見" + item->name() + HIW "呤呤作響，大"
                                       "放異彩，挾雲帶霧，突現在$N"
                                       HIW "的掌中！\n\n" NOR, me);
                        break;
                }
        }

        // 取消no_get屬性
        item->delete_temp("stab_by");
        item->delete("no_get");

        item->move(me, 1);
        if (environment(item) != me)
                return 1;

        if (item->query("armor_type"))
        {
                // is armor
                temp = me->query_temp("armor/" + item->query("armor_type"));
                if (temp) temp->unequip();
                WEAR_CMD->do_wear(me, item);
        } else
        if (item->query("skill_type"))
        {
                if (temp = me->query_temp("weapon"))
                        temp->unequip();
                if (temp = me->query_temp("secondary_weapon"))
                        temp->unequip();
                WIELD_CMD->do_wield(me, item);
        }

        return 1;
}

// 隱藏物品
int hide_anywhere(object me, object item)
{
        if (item->item_owner() != me->query("id"))
                return 0;

        if (me->query("jingli") < 100)
        {
                tell_object(me, "你試圖令" + item->name() +
                            "遁去，可是精力不濟，難以發揮它的能力。\n");
                return 0;
        }
        me->add("jingli", -100);

        message_vision(HIM "$N" HIM "輕輕一旋" + item->name() +
                       HIM "，已然了無蹤跡。\n", me);
        destruct(item);
        return 1;
}

// 追尋物品
int receive_miss(object me, object item)
{
        object env, me_env;
	string bn, bn2;

        env = environment(item);

        if (env == environment(me))
        {
                write("你瞪著" + item->name() + "，看啥？\n");
                return 0;
        }

        if (env == me)
        {
                write("你摸著" + item->name() + "，發了半天的呆。\n");
                return 0;
        }

        if (! objectp(env) || userp(env) || environment(env))
        {
                write("你試圖感應" + item->name() + "，但是感覺非常的渺茫。\n");
                return 0;
        }

        if (! wizardp(me) && ! env->query("outdoors"))
        {
                write("冥冥中你感應到" + item->name() + "，但是似乎難以到達那裡。\n");
                return 0;
        }

        message("vision", me->name() + "在凝神思索，不知道要做些什麼。\n",
                environment(me), ({ me }));
        if (me->query("jingli") < 400)
        {
                write("你覺得" + item->name() + "的感覺相當"
                      "飄忽，看來精力不濟，難以感應。\n");
                return 0;
        }

	bn = base_name(env);
	me_env = environment(me);
	if (sscanf(bn, "/kungfu/class/sky%s", bn2) == 1)
	{
		write("你感覺 " + item->name() + NOR " 似乎不存在于人界！\n" NOR);
		return 0;
	}
	if (sscanf(bn, "/d/newbie/%s", bn2) == 1)	
	{
		log_file("horse", me->query("id") + "于" + ctime(time()) + " 試圖利用兵器回到新手村。\n");
		return notify_fail("你感覺 " + item->name() + NOR " 似乎不能感應到你的呼喚！\n" NOR);
	}
	if (bn->query("no_flyto"))
	{
		write("你無法追尋到你兵器的所在地。\n");
		return 0;
	}
	
	// 蓬萊島上不能MISS
	if (sscanf(base_name(me_env), "/d/penglai/%s", bn2) == 1)
	{
		write("無法感應到你的兵器所在！\n" NOR);
		return 0;
	}
		
	// 神龍島上不能MISS
	if (sscanf(bn, "/d/shenlong/%s", bn2) == 1)
	{
		write("無法感應到你的兵器所在！\n" NOR);
		return 0;
	}

	if (sscanf(base_name(me_env), "/d/shenlong/%s", bn2) == 1)
	{
		write("此處無法感應到你的兵器。\n");
		return 0;
	}

        // 消耗精力
        me->add("jingli", -300 - random(100));
        message_vision(HIM "$N" HIM "口中念念有詞，轉瞬天際一道長虹劃"
                       "過，$N" HIM "駕彩虹而走。\n" NOR, me);
        tell_object(me, "你追尋" + item->name() + "而去。\n");
        me->move(environment(item));
        message("vision", HIM "一道彩虹劃過天際，" + me->name() +
                HIM "飄然落下，有若神仙。\n" NOR, environment(me), ({ me }));
        tell_object(me, HIM "你追尋到了" + item->name() +
                    HIM "，落下遁光。\n" NOR);
        return 1;
}

// 插在地上
int do_stab(object me, object item)
{
        if (! item->is_weapon() && item->query("armor_type") != "hands")
                return notify_fail(item->name() + "也能插在地上？\n");

        if (! environment(me)->query("outdoors") &&
            ! wizardp(me))
                return notify_fail("在這裡亂弄什麼！\n");

        item->set("no_get", bind((: call_other, __FILE__, "do_get_item", item :), item));
        item->set_temp("stab_by", me->query("id"));

        message_vision(WHT "\n$N" WHT "隨手將" + item->name() + NOR +
                       WHT "往地上一插，發出「嚓愣」一聲脆響。\n\n" NOR, me);
        item->move(environment(me));
        return 1;
}

// 把取物品時檢查
mixed do_get_item(object item)
{
        object me;

        if (! objectp(me = this_player()))
                return 1;

        if (me->query("id") != item->query_temp("stab_by") &&
            me->query("id") != item->item_owner())
                return "你試圖將" + item->name() + "拔起，卻"
                       "發現它仿佛是生長在這裡一般，無法撼動。\n";

        message_vision(HIW "\n$N" HIW "隨手拂過" + item->name() +
                       HIW "脊處，頓時只聽「嗤」的一聲，揚起一陣"
                       "塵土。\n\n" NOR, me);
        item->delete_temp("stab_by");
        item->delete("no_get");
        item->move(me, 1);
        return "";
}

// 發揮特殊功能
mixed do_touch(object me, object item)
{
        string msg;
        object ob;
        object *obs;
        mapping my;
        int ran_n; 

        if (me->query("id") != item->item_owner())
        {
                message_vision(HIR "\n$N輕輕觸碰" + item->name() +
                               HIR "，突然間全身一震，連退數步，如"
                               "遭受電擊。\n" NOR, me);
                me->receive_damage("qi", 50 + random(50));
                return 1;
        }

		

        if (me->query("jingli") < 160)
        {
                me->set("jingli", 1);
                return notify_fail(CYN "\n你凝視" + item->name() +
                                   CYN "許久，悠悠一聲長嘆。\n" NOR);
        }
		else
                me->add("jingli", -150);

        switch (random(3))
        {
        case 0:
                msg = CYN "\n$N" CYN "輕輕一彈$n" CYN "，長吟"
                      "道：「別來無恙乎？」\n" NOR;
                break;
        case 1:
                msg = CYN "\n$N" CYN "輕輕撫過$n" CYN "，作古"
                      "風一首，$n" CYN "鈴鈴作響，似以和之。\n" NOR;
                break;
        default:
                msg = CYN "\n$N" CYN "悠然一聲長嘆，輕撫$n"
                      CYN "，沉思良久，不禁感慨萬千。\n" NOR;
                break;
        }

        switch (random(3))
        {
        case 0:
                msg += HIM "忽然只見$n" HIM "閃過一道光華，"
                       "飛躍而起，散作千百流離。\n" NOR;
                break;
        case 1:
                msg += HIM "頓聽$n" HIM "一聲龍吟，悠悠不絕"
                       "，直沁入到你的心肺中去。\n" NOR;
                break;
        default:
                msg += HIM "霎時間$n" HIM "光芒四射，如蘊琉"
                       "璃異彩，逼得你難以目視。\n" NOR;
                break;
        }

        msg = replace_string(msg, "$n", item->name());
        message_vision(msg, me);

	ran_n = 1000;
	if (me->is_fighting())ran_n = 3000;
	
        if (random(ran_n) == 1 || wizardp(me))
        {
                obs = filter_array(all_inventory(environment(me)), (: userp :));
                foreach (ob in obs)
                {
                        my = ob->query_entire_dbase();
                        my["jing"]   = my["eff_jing"] = my["max_jing"];
                        my["qi"]     = my["eff_qi"]   = my["max_qi"];
                        my["neili"]  = my["max_neili"];
                        my["jingli"] = my["max_jingli"];
                        ob->set_temp("nopoison", 1);
                }
                tell_object(obs, HIC "你感到一股溫和的熱浪襲來，便似"
                                "獲得重生一般。\n" NOR);
        } else
        if (me->query("neili") < me->query("max_neili") || item->query("enchase_all") >= 9 )
        {
			    // 九孔兵器特效
			    if (item->query("enchase_all") >= 9 
					&& me->query("qi") > 500 
					&& time() - me->query_temp("last_touch_jl") > 180)
			    {
						me->set("eff_jingli", me->query("max_jingli"));
						me->set("jingli", me->query("max_jingli"));

						me->receive_damage("qi", 400);
						me->set_temp("last_touch_jl", time());
			    }

                me->set("neili", me->query("max_neili"));
                tell_object(me, HIC "你只覺一股熱氣至丹田冉冉升起，"
                                "說不出的舒服。\n" NOR);
        }
        return 1;
}

// 聖化物品
int do_san(object me, object item)
{
        string my_id;
        int count;
        int san;

        if (! item->query("skill_type") && item->query("armor_type") != "hands")
        {
                // 是裝備類？
                return notify_fail("裝備現在還無法聖化。\n");
        }

        // 武器類的聖化
        if (item->query("magic/power") > 0)
                return notify_fail("現在" + item->name() + "的威力"
                                   "已經得到了充分的發揮了。\n");

        if (item->query("magic/imbue_ok"))
                return notify_fail("現在" + item->name() + "的潛力"
                                   "已經充分挖掘了，現在只是需要最"
                                   "後一步融合。\n");

        my_id = me->query("id");

        count = sizeof(item->query("magic/do_san"));
        if (item->query("magic/imbue_ob"))
                return notify_fail("現在" + item->name() + "已經被充分的聖"
                                   "化了，需要浸入神物以進一步磨練。\n");

        if (item->query("magic/do_san/" + my_id))
                return notify_fail("你已經為" + item->name() + "聖化過了，"
                                   "非凡的能力還無法被它完全吸收。\n你"
                                   "有必要尋求他人幫助以繼續聖化。\n");

        if (item->item_owner() == my_id)
        {
                if (! count)
                        return notify_fail("你應該先尋求四位高手協助你先行聖化" +
                                           item->name() + "。\n");

                if (count < SAN_PER_IMBUE - 1)
                        return notify_fail("你應該再尋求" +
                                           chinese_number(SAN_PER_IMBUE - 1 - count) +
                                           "位高手先行聖化" + item->name() + "。\n");
        } else
        {
                if (count >= SAN_PER_IMBUE - 1)
                        return notify_fail("最後需要劍的主人為它聖化，不勞你費心了。\n");
        }

        if (me->query("neili") < me->query("max_neili") * 9 / 10)
                return notify_fail("你現在內力並不充沛，怎敢貿然運用？\n");

        if (me->query("jingli") < me->query("max_jingli") * 9 / 10)
                return notify_fail("你現在精力不濟，怎敢貿然運用？\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的內功根基不夠紮實，不能貿然聖化。\n");

        if (me->query("max_neili") < 8000)
                return notify_fail("你嘗試運了一下內力，無法順"
                                   "利運足一個周天，難以施展你的能力。\n");

        if (me->query("max_jingli") < 1000)
                return notify_fail("你試圖凝神運用精力，但是感覺尚有欠缺。\n");

        message_sort(HIM "\n$N" HIM "輕輕撫過$n" HIM "，兩指點于其上，同"
                     "時運轉丹田內力，經由奇經八脈源源由體內流出，注"
                     "入$n" HIM "。忽的只見氤氳紫氣從$n" HIM
                     "上騰然升起，彌漫在四周。\n" NOR, me, item);

        if (me->query("max_neili") < me->query_neili_limit() - 400)
        {
                if (random(2) == 1)
                {
                        // 內力未滿警告
                        message_vision(HIR "$N" HIR "臉色忽然變了變。\n" NOR,
                                       me);
                        tell_object(me, HIC "你忽然覺得丹田氣息有些錯亂。\n" NOR);
                } else
                {
                        message_vision(HIR "$N" HIR "忽然悶哼一聲，臉"
                                       "上剎時大汗淋漓！\n" NOR, me);
                        tell_object(me, HIC "你感到可能是你的內力尚未鍛煉"
                                    "到極至，結果損傷了你的內功根基。\n" NOR);
                        tell_object(me, HIC "你的基本內功下降了。\n");
                        me->set_skill("force", me->query_skill("force", 1) - 10 - random(5));
                        return 1;
                }
        }

        // 統計IMBUE過的次數，並用來計算本次MAX_NEILI/JINGLI的消耗
        san = item->query("magic/imbue");

        me->add("max_neili", -(san + 5));
        me->add("neili", -(san * 10 + 100));
        me->add("max_jingli", -(san * 5 + 50));
        me->add("jingli", -(san * 5 + 50));
        item->set("magic/do_san/" + my_id, me->name(1));
        me->start_busy(1);

        if (item->item_owner() == my_id)
        {
                tell_object(me, HIW "你凝神片刻，覺得" + item->name() +
                            HIW "似乎有了靈性，跳躍不休，不禁微微一笑。\n" NOR);
                message("vision", HIW + me->name() + HIW "忽然"
                        "微微一笑。\n" HIW, environment(me), ({ me }));

                // 選定一個需要imbue的物品
                item->set("magic/imbue_ob", imbue_list[random(sizeof(imbue_list))]);
        }
        return 1;
}

// 浸透物品
int do_imbue(object me, object item, object imbue)
{
        if (item->query("magic/power") > 0)
                return notify_fail("現在" + item->name() + "的威力"
                                   "已經得到了充分的發揮了。\n");

        if (item->query("magic/imbue_ok"))
                return notify_fail("現在" + item->name() + "的潛力"
                                   "已經充分挖掘了，現在只是需要最"
                                   "後一步融合。\n");

        if (sizeof(item->query("magic/do_san")) < SAN_PER_IMBUE)
                return notify_fail("你必須先對" + item->name() +
                                   "進行充分的聖化才行。\n");

        if (base_name(imbue) != item->query("magic/imbue_ob"))
                return notify_fail(item->name() + "現在不需要用" +
                                   imbue->name() + "來浸入。\n");

        message_sort(HIM "$N" HIM "深吸一口氣，面上籠罩了一層白霜，只手握住$n" +
                     imbue->name() +
                     HIM "，忽然間融化在掌心，晶瑩欲透！$N"
                     HIM "隨手一揮，將一汪清液洒在$n" HIM
                     "上，登時化做霧氣，須臾成五彩，奇光閃爍。\n" NOR,
                     me, item);

        tell_object(me, "你將" + imbue->name() + "的效力浸入了" +
                    item->name() + "。\n");
        item->delete("magic/do_san");
        item->delete("magic/imbue_ob");
        imbue->add_amount(-1);
        if (imbue->query_amount() < 1)
                destruct(imbue);

        me->start_busy(1);

        item->add("magic/imbue", 1);
        if (random(item->query("magic/imbue")) >= RANDOM_IMBUE_OK)
        {
                // 浸透完成
                tell_object(me, HIG "你忽然發現手中的" + item->name() +
                            HIG "有一種躍躍欲試的感覺，似乎期待著什麼。\n" NOR);
                item->set("magic/imbue_ok", 1);
        }

        return 1;
}

// 鑲嵌物品
int do_enchase(object me, object item, object tessera)
{
        if (item->query("magic/power") > 0)
                return notify_fail("現在" + item->name() + "的威力"
                                   "已經得到了充分的發揮了。\n");

        if (! item->query("magic/imbue_ok"))
                return notify_fail("現在" + item->name() + "的潛力"
                                   "還沒有充分的激發，未到鑲嵌的時候。\n");

        if (! tessera->query("can_be_enchased"))
                return notify_fail(tessera->name() + "好象沒"
                                   "法用來鑲嵌吧。\n");

        if (! mapp(tessera->query("magic")))
                return notify_fail(tessera->name() + "不能發揮魔力，"
                                   "沒有必要鑲嵌在" + item->name() + "上面。\n");

        if (me->query_skill("certosina", 1) < 100)
                return notify_fail("你覺得你的鑲嵌技藝還不夠"
                                   "嫻熟，不敢貿然動手。\n");

        message_sort(HIM "“喀啦”一聲，$N" HIM "將" + tessera->name() +
                     HIM "鑲嵌到了$n" HIM "上面，只見$n" HIM
                     "上面隱隱的顯過了一道奇異的光芒，隨"
                     "即變得平靜，說不出的平凡。\n" NOR, me, item);
        tell_object(me, HIC "你感受" + item->name() + HIC "發生了"
                    "不可言喻的變化。\n" NOR);
        item->set("magic/power", tessera->query("magic/power"));
       	item->set("magic/type", tessera->query("magic/type"));
        item->set("magic/tessera", tessera->name());
        item->save();
        destruct(tessera);

        // 發布消息
        CHANNEL_D->do_channel(this_object(), "rumor",
                              "聽說神品" + item->name() + HIM +
                              "來到了人間。");

        me->start_busy(1);
        return 1;
}

string get_random_key(string key_id)
{
	key_id += sprintf("%d", random(20));
	return key_id;
}
// 擴展鑲嵌
int do_enchase2(object me, object item, object tessera)
{
		string key_id;
		mapping enchases;
		string *k_enchases;
		int i;
	
        if (! tessera->query("enchase/point"))
                return notify_fail(tessera->name() + "好象沒"
                                   "法用來鑲嵌吧。\n");

        if (me->query_skill("certosina", 1) < 100)
                return notify_fail("你覺得你的鑲嵌技藝還不夠"
                                   "嫻熟，不敢貿然動手。\n");

        if (item->query("enchase_all") - sizeof(item->query("enchase")) <= 0)
		return notify_fail("你的 " + item->name() + NOR " 上已沒有足夠的槽位。\n" );

		// 九孔鑲嵌物品只能鑲嵌到第九孔上，且每把兵器只能鑲嵌一個
		if (tessera->query("nine_object"))
		{
			enchases = item->query("enchase");
			if (mapp(enchases))
			{
				k_enchases = keys(enchases);
			}

			if (item->query("enchase_all") < 9)
			{
				return notify_fail("這塊寶石只能鑲嵌到第九孔上。\n");
			}

			for (i = 0; i < sizeof(k_enchases); i ++ )
			{
				if (enchases[k_enchases[i]]["name"] == "海藍石" ||
					enchases[k_enchases[i]]["name"] == "紅眼惡魔")
				{
					return notify_fail("不能在一把兵器上同時鑲嵌兩個九孔寶石。\n");
				}
				if (enchases[k_enchases[i]]["name"] == "古鬆殘□" ||
					enchases[k_enchases[i]]["name"] == "龍凰紫珠")
				{
					return notify_fail("不能在一把兵器上同時鑲嵌兩個九孔寶石。\n");
				}
				if (enchases[k_enchases[i]]["name"] == "流星趕月" ||
					enchases[k_enchases[i]]["name"] == "九天玲瓏珠")
				{
					return notify_fail("不能在一把兵器上同時鑲嵌兩個九孔寶石。\n");
				}	
				if (enchases[k_enchases[i]]["name"] == "黑水晶" ||
					enchases[k_enchases[i]]["name"] == "紫霹靂")
				{
					return notify_fail("不能在一把兵器上同時鑲嵌兩個九孔寶石。\n");
				}							
			}
		}

	log_file("beset", me->query("id") + " beset " + tessera->name() + NOR " to " + base_name(item) + "(" + 
	                  item->name() + NOR + ") at " + ctime(time()) + "\n");
        message_sort(HIG "“喀啦”一聲，$N" HIG "將" + tessera->name() +
                     HIG "鑲嵌到了$n" HIG "上面，只見$n" HIG
                     "上面隱隱的顯過了一道奇異的光芒，隨"
                     "即變得平靜，說不出的平凡。\n" NOR, me, item);
        tell_object(me, HIC "你感受" + item->name() + HIC "發生了"
                    "不可言喻的變化。\n" NOR);

        key_id = tessera->query("id");
	if (item->query("enchase/" + key_id))
	{
		while (1)
		{			
			key_id = get_random_key(tessera->query("id"));
			if (! item->query("enchase/" + key_id))break;
		}
	}

        item->set("enchase/" + key_id + "/name", tessera->query("enchase/name"));
       	item->set("enchase/" + key_id + "/point", tessera->query("enchase/point"));
       	item->set("enchase/" + key_id + "/fy", tessera->query("enchase/fy"));
       	item->set("enchase/" + key_id + "/qy", tessera->query("enchase/qy"));
       	item->set("enchase/" + key_id + "/type", tessera->query("enchase/type"));
       	item->set("enchase/" + key_id + "/cur_firm", tessera->query("enchase/cur_firm"));
       	item->set("enchase/" + key_id + "/spe_data", tessera->query("enchase/spe_data"));

	// 武器鑲嵌提高傷害50點
	if (item->query("skill_type") || item->query("armor_type") == "hands")
	{
		if (tessera->query("enchase/spe_data/luhua-zhijing"))
			item->set("enchase/" + key_id + "/point", 2500); //itemmake.c point * 2
	}
	
	// 護身符
	if (item->query("armor_type") == "myheart" || item->query("armor_type") == "myheart2" )
	{
		if (tessera->query("enchase/spe_data/luhua-zhijing"))
		{
			item->set("enchase/" + key_id + "/fy", 3);
       			item->set("enchase/" + key_id + "/qy", 3);
		}
	}
	// 護腕鑲嵌提高傷害40點 itemmake.c
	if (item->query("armor_type") == "wrists")
	{
		if (tessera->query("enchase/spe_data/luhua-zhijing"))
			item->set("enchase/" + key_id + "/point", 1);
	}
	// 披風鑲嵌提高傷害40點 itemmake.c
	if (item->query("armor_type") == "surcoat")
	{
		if (tessera->query("enchase/spe_data/luhua-zhijing"))
			item->set("enchase/" + key_id + "/point", 1);
	}
	// 轉世勛章鑲嵌提高point 21點
	if (item->query("armor_type") == "medal2")
	{
		if (tessera->query("enchase/spe_data/luhua-zhijing"))
			item->set("enchase/" + key_id + "/point", 21);
	}
	// 防具鑲嵌提高防護+50
	if (item->query("armor_type") == "armor")
	{
		if (tessera->query("enchase/spe_data/luhua-zhijing"))
			item->set("enchase/" + key_id + "/point", 2500); // 2500*2.4
	}
	
        item->save();
	tell_object(me, HIM + item->name() + HIM " 突然離你而去 ……\n" NOR);
	destruct(item);
        destruct(tessera);

        me->start_busy(1);

        return 1;
}

// 10級兵器攻擊對手
mixed weapon10lv_hit_ob(object me, object victim, object weapon, int damage_bonus)
{
        mapping magic;
        int jingjia;
        int power, resistance;
        int damage;
        string msg;

		int point;

        // 計算魔法效果
        magic = weapon->query("magic");
        power = magic["power"];
        damage = 0;
        resistance = 0;
        //jingjia = me->query("jiajing");
        jingjia = me->query("jiali") / 3;
      
        switch (magic["type"])
        {
        case "lighting":
                // 閃電攻擊：傷害內力++和氣+
                resistance = victim->query_temp("apply/resistance/lighting");
                damage = (power + jingjia) * 200 / (100 + resistance);
                switch (random(3))
                {
                case 0:
                        msg = HIY + weapon->name() + HIY "迸發出幾道明亮的閃光，茲茲作響，讓$n"
                              HIY "不由為之酥麻。\n" NOR;
                        break;
                case 1:
                        msg = HIY "一道電光閃過，" + weapon->name() + HIY
                              "變得耀眼奪目，令$n" HIY "無法正視，心神俱廢。\n" NOR;
                        break;
                default:
                        msg = HIY "天際隱隱響起幾聲悶雷，緊接著一道霹靂直下，" +
                              weapon->name() + HIY "忽明忽暗，五彩繽紛，震得$n"
                              HIY "酸軟無力。\n" NOR;
                        break;
                }

                if (victim->query("neili") > damage)
                        victim->add("neili", -damage);
                else
                        victim->set("neili", 0);

                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 4);
                break;

        case "cold":
                // 冷凍攻擊：傷害精++和氣+
                resistance = victim->query_temp("apply/resistance/cold");
                damage = (power + jingjia) * 200 / (100 + resistance);
                victim->receive_damage("jing", damage / 3);
                victim->receive_wound("jing", damage / 6);
                victim->receive_damage("qi", damage / 2);
                victim->receive_wound("qi", damage / 5);
                switch (random(3))
                {
                case 0:
                        msg = HIB + weapon->name() + HIB "閃過一道冷澀的藍光，讓$n"
                              HIB "不寒而栗。\n" NOR;
                        break;
                case 1:
                        msg = HIB "忽然間" + weapon->name() + HIB
                              "變得透體通藍，一道道冰冷的寒光迸發出來，$n"
                              HIB "渾身只是一冷。\n" NOR;
                        break;
                default:
                        msg = HIB "一道光圈由" + weapon->name() + HIB "射出，"
                              "森然盤旋在$n" HIB "四周，悄然無息。\n" NOR;
                        break;
                }
                break;

        case "fire":
                // 火燄攻擊：傷害精+和氣++
                resistance = victim->query_temp("apply/resistance/fire");
                damage = (power + jingjia) * 300 / (100 + resistance);
                victim->receive_damage("jing", damage / 5);
                victim->receive_wound("jing", damage / 8);
                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 2);
                switch (random(3))
                {
                case 0:
                        msg = HIR + weapon->name() + HIR "驀的騰起一串火燄，將$n"
                              HIR "接連逼退了數步，慘叫連連。\n" NOR;
                        break;
                case 1:
                        msg = HIR "一道火光從" + weapon->name() + HIR
                              "上迸出，迅捷無倫的擊中$n" HIR "，令人避無可避！\n" NOR;
                        break;
                default:
                        msg = HIR "一串串火燄從" + weapon->name() + HIR "上飛濺射出，"
                              "四下散開，接連擊中$n" HIR "！\n" NOR;
                        break;
                }
                break;

        case "magic":
                // 魔法攻擊：吸取氣+
                resistance = victim->query_temp("apply/resistance/magic");
                damage = (power + jingjia) * 200 / (100 + resistance);
                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 4);
                switch (random(3))
                {
                case 0:
                        msg = HIM + weapon->name() + HIM "響起一陣奇異的聲音，猶如龍吟，令$n"
                              HIM "心神不定，神情恍惚。\n" NOR;
                        break;
                case 1:
                        msg = HIM "“啵”的一聲，" + weapon->name() + HIM
                              "如擊敗革，卻見$n" HIM "悶哼一聲，搖晃不定！\n" NOR;
                        break;
                default:
                        msg = HIM + weapon->name() + HIM "上旋出一道道五彩繽紛的"
                              "光圈，籠罩了$n" HIM "，四下飛舞。\n" NOR;
                        break;
                }
                break;

        default:
                msg = "";
                break;
        }

        // 使用perform
        if (random(2)) return msg;
        damage = 200 + random(400);


		if (do_wrists_attack(me, victim, "zipili"))		
			point = 6;		
		else
			point = 8;
		
        switch (random(point))
        {
        case 0:
                victim->receive_wound("jing", damage / 6 + random(damage / 6), me);
                return msg + HIM "$N" HIM "嘿然冷笑，抖動" + weapon->name() +
                       HIM "，數道光華一起射出，將$n" HIM "困在當中，無法自拔。\n" NOR;

        case 1:
                victim->receive_wound("jing", damage / 5 + random(damage / 5), me);
                return msg + HIC "$N" HIC "手中的" + weapon->name() + HIC "射出各種光芒，"
                       "眩目奪人，一道道神採映射得天地盡情失色，讓$n"
                       HIC "目瞪口呆！\n" NOR;
        case 2:
                victim->receive_wound("qi", damage / 4 + random(damage / 4), me);
                return msg + HIY "$N" HIY "舉起" + weapon->name() +
                       HIY "，只見天空一道亮光閃過，$n" HIY "連吐幾口鮮血！\n" NOR;

        case 3:
                victim->receive_wound("qi", damage / 3 + random(damage / 3), me);
                return msg + HIG "$N" HIG "隨手劃動" + weapon->name() + HIG "，一圈圈碧芒"
                       "圍向$n" HIG "，震得$n吐血連連！\n" NOR;

        case 4:
                victim->receive_wound("qi", damage / 2 + random(damage / 2), me);
                return msg + HIW "$N" HIW "一聲長嘆，" + weapon->name() + HIW "輕輕遞出，"
                       "霎時萬籟俱靜，$n" HIW "只覺得整個人都跌進了地獄中去！\n" NOR;

        default:
                if (me->query_temp("weapon_performing"))
                        break;
                me->start_call_out(bind((: call_other, __FILE__, "continue_attack",
                                           me, victim, weapon, 10 + random(4) :), me), 0);
        }
}

// 9級兵器攻擊對手
mixed weapon_hit_ob(object me, object victim, object weapon, int damage_bonus)
{
        int ap;
        int dp;
        int damage;
		int point;

        if (random(2)) return;

        // 計算damage：不論是空手武器還是普通兵器，統一計算
        if (weapon->is_weapon())
                damage = me->query_temp("apply/damage");
        else
                damage = me->query_temp("apply/unarmed_damage");

		if (do_wrists_attack(me, victim, "zipili"))		
			point = 5;		
		else
			point = 8;

        switch (random(point))
        {
        case 0:
                victim->receive_wound("jing", damage / 5 + random(damage / 5), me);
                return HIY "$N" HIY "抖動手中的" + weapon->name() + HIY
                       "，幻化成夜空流星，數道" HIM "紫芒" HIY "劃破星"
                       "空襲向$n" HIY "。\n" NOR;
        case 1:
                victim->receive_wound("qi", damage / 3 + random(damage / 3), me);
                return HIR "$N" HIR "大喝一聲，手中" + weapon->name() +
                       HIR "遙指$n" HIR "，一道殺氣登時將$n" HIR "震退"
                       "數步。\n" NOR;
        case 2:
                victim->receive_wound("qi", damage / 6 + random(damage / 6), me);
                victim->receive_wound("jing", damage / 10 + random(damage / 10), me);
                return HIG "$N" HIG "驀地回轉" + weapon->name() + HIG
                       "，漾起層層碧波，宛若" NOR + HIB "星河" HIG "氣"
                       "旋，將$n" HIG "圈裹其中。\n" NOR;
        case 3:
				if (do_wrists_attack(me, victim, "zipili"))
				{
					 if (me->query_temp("weapon_performing"))
			                break;
					 me->start_call_out(bind((: call_other, __FILE__, "continue_attack",
                                           me, victim, weapon, 5 + random(4) :), me), 0);					
				}
				break;
        case 4:
        case 5:
        case 6:
                break;

        default:
                if (me->query_temp("weapon_performing"))
                        break;
                me->start_call_out(bind((: call_other, __FILE__, "continue_attack",
                                           me, victim, weapon, 5 + random(4) :), me), 0);
        }
}

// 絕招：12連環攻擊
void continue_attack(object me, object victim, object weapon, int times)
{
        int i;
        string msg;
        int ap, dp;

        if (! me || ! victim || ! weapon || ! me->is_fighting(victim))
                return;

        msg  = HIW "霎時只聽$N" HIW "縱聲長嘯，人與" + weapon->name() +
               HIW "融為一體，霎時間寒芒飛散，向$n" HIW "射去。\n" NOR;

        ap = me->query_skill("martial-cognize");
        dp = victim->query_skill("parry");

        if (ap / 2 + random(ap) > dp * 2 / 3)
                msg += HIR "$n" HIR "大駭之下連忙後退，可已然不及閃避，慌亂"
                       "中不禁破綻迭出。\n" HIW "$N" HIW "盯住$n" HIW "招中"
                       "破綻，疾速旋轉手中" + weapon->name() + HIW "，電光火"
                       "石間已朝$n" HIW "攻出" + chinese_number(times) + HIW
                       "招！\n" NOR;
        else
        {
                msg += CYN "可是$n" CYN "冥神抵擋，將$N"
                       CYN "此招的所有變化全然封住。\n" NOR;
                message_combatd(msg, me, victim);
                return;
        }
        message_combatd(msg, me, victim);

        me->set_temp("weapon_performing", 1);
        i = times;
        while (i--)
        {
                if (! me->is_fighting(victim))
                        break;

                if (! victim->is_busy() && random(2))
                        victim->start_busy(1);

                COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 0);
        }
        me->delete_temp("weapon_performing");
}

// 計算穿透特效點
public int chuantou_point(object me, object item)
{	
		int total;
		mapping enchase;
		string *k_enchase, *k_chuantou_item;
		int i;
		string name;

		mapping chuantou_item = ([
			"炎黃之星"       : 100,
			"炎黃﹒戰神"      : 100,
			"炎黃﹒君臨天下"  : 100,
			"龍女﹒曙光"      : 100,
			"龍女﹒蝕"        : 200,
		]);

		total = 0;

		total = me->query_temp("apply/chuantou");

		enchase = item->query("enchase");
		if (! mapp(enchase))return total;

		k_enchase = keys(enchase);

		if (! sizeof(k_enchase))return total;

		k_chuantou_item = keys(chuantou_item);

		for (i = 0; i < sizeof(k_enchase); i ++ )
		{
			name = enchase[k_enchase[i]]["name"];
			if (member_array(name, k_chuantou_item) != -1)
			{	
				  total = total + chuantou_item[name];	
			}
		}
		
		return total;
}

// 發揮鑲嵌物品的特效
public void do_enchase_attack(object item, object me, object victim, int damage)
{
	mapping enchase;
	int i_en, i, i_temp, j;
	string item_type, ran_item_enchase, s_temp;
	string ran_enchase_affect;

	string *k_enchase, *k_affect_list;
	mapping affect_list;
	string ran_affect;
	int i_ef;

	int ef_point, ef_ran, n_ef;
	int ran_result;
	string msg;

	object shenlong; // 碧海神龍

	mapping list = ([
		"天魔﹒幽靈"   :  ([
					"suck_neili" : (["ran"    :  1 + random(3),
                                     "point"  :  30 + random(21)]),
		]),
		"天魔﹒夢幻"   :  ([
					"add_damage" : (["ran"    :  1 + random(3),
                                     "point"  :  30 + random(21)]),
		]),
		"天魔﹒鬼煞"   :  ([
					"suck_qi"    : (["ran"    :  1 + random(3),
                                     "point"  :  10 + random(21)]),
		]),
		"天魔﹒妖晶"   :  ([
					"add_wound"  : (["ran"    :  1 + random(3),
                                     "point"  :  30 + random(21)]),
		]),
		"陰月﹒亂世"   :  ([
					"busy"  :      (["ran"    :  2 + random(2),
                                     "point"  :  2 + random(2)]),
		]),
		"陰月﹒沖天"   :  ([
					"add_damage"  : (["ran"   :  2 + random(2),
                                      "point" :  30 + random(21)]),
		]),
		"陰月﹒落霞"   :  ([
					"jing_wound"  : (["ran"   :  1 + random(3),
                                      "point" :  10 + random(11)]),
		]),
		"陰月﹒聖光"   :  ([
					"suck_neili"  : (["ran"   :  2 + random(2),
                                      "point" :  50]),
		]),
		"天嬌﹒伏魔"   :  ([
					"add_wound"  : (["ran"    :  2 + random(2),
                                     "point"  :  50]),
		]),
		"天嬌﹒沉淪"   :  ([
					"add_damage"  : (["ran"   :  3 + random(3),
                                      "point" :  50]),
		]),
		"天嬌﹒神泣"   :  ([
					"jing_wound"  : (["ran"   :  2 + random(2),
                                      "point" :  15 + random(6)]),
		]),
		"天轎﹒覺醒"   :  ([
					"suck_qi"    : (["ran"    :  2 + random(2),
                                     "point"  :  30]),
		]),
		"輪回﹒煉獄"   :  ([
					"poison_lianyu"    : ([ "ran"    :  2 + random(2),
                                            "point"  :  me->query_temp("apply/damage")]),
		]),
		"輪回﹒餓鬼"   :  ([
					"suck_neili" : (["ran"    :  3 + random(3),
                                     "point"  :  50 + random(31)]),
		]),
		"輪回﹒修羅"   :  ([
					"add_wound"  : (["ran"    :  3 + random(3),
                                     "point"  :  50 + random(31)]),
		]),
		"輪回﹒烈火"   :  ([
					"no_exert"   : (["ran"    :  2 + random(2),
                                     "point"  :  10 + random(6)]),
		]),
		"輪回﹒裁決"   :  ([
					"no_perform"   : (["ran"    :  2 + random(2),
                                       "point"  :  10 + random(6)]),
		]),
		"輪回﹒重生"   :  ([ // 特別地
					"lunhui-chongsheng" : (["ran"    :  3 + random(3),
                                            "point"  :  0]),
		]),
		"輪回﹒滅世"   :  ([ // 特別地 ：致命攻擊
					"unconcious" : (["ran"    :  1,
                                     "point"  :  0]),
		]),
		
		"炎黃之星"   :   ([ // 多種復合特效
					"suck_neili" : (["ran"    :  5,
                                     "point"  :  150]),
					"suck_qi"    : (["ran"    :  5,
                                     "point"  :  150]),
		]),
		"龍女之淚"   :   ([ // 多種復合特效
					"suck_neili" : (["ran"    :  5,
                                     "point"  :  100]),
					"suck_qi"    : (["ran"    :  5,
                                     "point"  :  100]),
					"reduce_def" :(["ran"   :  5, // 化解對方防御等級1
						            "point" :  100]),
					"reduce_dam" :(["ran"   :  5, // 化解對方傷害等級1
						            "point" :  100]),
		]),
		"炎黃﹒君臨天下":  ([
					"jing_wound"  : (["ran"   :  3 + random(3),
                                      "point" :  50 + random(31)]),
					"busy"  :       (["ran"    :  5,
                                      "point"  :  5]),
		]),		
		"炎黃﹒國色天香":   ([ // 多種復合特效
					"suck_neili" : (["ran"    :  5,
                                     "point"  :  100]),
					"suck_qi"    : (["ran"    :  5,
                                     "point"  :  100]),
					"busy"  :       (["ran"    :  5,
                                      "point"  :  5]),
					"no_exert"   : (["ran"    :  3,
                                     "point"  :  15]),
					"no_perform"   : (["ran"    :  3,
                                       "point"  :  15]),
		]),		
		"炎黃﹒戰神":  ([ // 特別地 ：致命攻擊
					"unconcious" : (["ran"    :  2,
                                     "point"  :  0]),
					"add_damage"  : (["ran"   :  5,
                                      "point" :  200]),
		]),		
		"龍女﹒碧海神龍":  ([ // 特別地 ：召喚神龍
					"summon_shenlong": (["ran"   :  5,
                                         "point" :  0]),
					"add_damage"  : (["ran"   :  5,
                                      "point" :  200]),					
		]),
		"龍女﹒曙光"   :  ([
					"add_wound"  : (["ran"   :  3 + random(3),
                                      "point" :  100 + random(101)]),
					"jing_wound" : (["ran"   :  3 + random(3),
                                      "point" :  35 + random(26)]),
		]),
		"龍女﹒蝕":       ([
					"add_damage"  : (["ran"   :  3,
                                      "point" :  300]),					
		]),
	]);


    // 發揮項鏈的特殊攻擊技能
	do_neck_attack(me, victim);

	// 發揮護腕特殊攻擊效果
	do_wrists_attack(me, victim, "");

    // 不是自造兵器則返回
	if (! item->is_item_make())return;

	if (item->query("skill_type"))item_type = "weapon";
	if (item->query("armor_type") == "hands")item_type = "weapon";

    // 不是兵器則返回
	if (item_type != "weapon")return;

	// 沒有鑲嵌則返回
	enchase = item->query("enchase");
	
	if (! mapp(enchase))return;
	i_en = sizeof(enchase);
	if (! i_en)return;

	// 幾率計算 平均?% + 幾個累加%
	// 同一時間隨機選取一種特效
	k_enchase = keys(enchase);

	// 發揮穿透特效
	victim->receive_wound("qi", chuantou_point(me, item), me);	

    // 從已鑲嵌的物品中隨機選擇一個
	ran_item_enchase = enchase[k_enchase[random(i_en)]]["name"];

	// 從選取的物品中隨機選擇一種特效
	affect_list = list[ran_item_enchase];
	if (! affect_list)return;

	k_affect_list = keys(affect_list);

	i_ef = sizeof(k_affect_list);
	if (! i_ef)return;

	ran_affect = k_affect_list[random(i_ef)];

	// 特效選取好後則計算特效幾率及威力（時間等）
	// 幾率計算 平均?% + 幾個累加%
	// 威力計算，當前獲取的隨機鑲嵌物品的該特效威力
	
	// 先計算威力
	ef_point = list[ran_item_enchase][ran_affect]["point"];

	// 計算幾率
	// 先計算幾率總和及該特效個數
	n_ef = 0;
	ef_ran = 0;
	for (i = 0; i < i_en; i ++)
	{
		// 分別依次獲得已鑲嵌的物品
		s_temp = enchase[k_enchase[i]]["name"];

		// 如果效果定義中無該鑲嵌物品則跳過
		if (member_array(s_temp,keys(list)) == -1)continue;

		// 如果該鑲嵌物品存在此特效
		if (mapp(list[s_temp][ran_affect]))
		{
			n_ef += 1;
			ef_ran += list[s_temp][ran_affect]["ran"];
		}
	}

	// 得到最後計算的幾率
	if (n_ef <= 0)ran_result = 3;  //以防萬一
	else
		ran_result = ef_ran / n_ef + n_ef - 1;

	// 如果鑲嵌了寶石--紅眼惡魔則提高1%～2%的幾率
	for (j = 0; j < sizeof(k_enchase); j ++ )
	{
		if (enchase[k_enchase[j]]["name"] == "紅眼惡魔")
		{
			ran_result = ran_result + 1 + random(2);
		}
	}

	// 隨機判斷是否發出該特效
	if (1 + random(100) > ran_result)return;
	
	message_combatd(HIG + "$N" HIG "的「" + ran_item_enchase + "」發出一道奇異的光芒！\n" NOR, me);

	// 發出特效
	switch(ran_affect)
	{
		case "suck_neili":
			if (victim->query("neili") < ef_point)return;

			msg = HIY "「" + ran_item_enchase + "」吸取「" + victim->name() + HIY +
                              "」內力：" + sprintf("%d", ef_point) + "點\n" NOR;
			tell_object(me, msg);			
			victim->add("neili", -1 * ef_point);
			if (victim->query("neili") < 0)victim->set("neili", 0);
			me->add("neili", ef_point);
			if (me->query("neili") > me->query("max_neili"))
				me->set("neili", me->query("max_neili"));

			return;

		case "suck_qi":
			if (victim->query("qi") < ef_point)return;

			msg = HIY "「" + ran_item_enchase + "」吸取「" + victim->name() + HIY +
                              "」氣血：" + sprintf("%d", ef_point) + "點\n" NOR;
			tell_object(me, msg);
			victim->receive_damage("qi", ef_point, me);
			if (victim->query("qi") < 0)victim->set("qi", 0);
			me->add("qi", ef_point);
			if (me->query("qi") > me->query("eff_qi"))
				me->set("qi", me->query("eff_qi"));

			return;

		case "add_damage":
			msg = HIR "「" + ran_item_enchase + "」追加「" + victim->name() + HIY +
                              "」傷害：" + sprintf("%d", ef_point) + "點\n" NOR;
			tell_object(me, msg);
			victim->receive_damage("qi", ef_point, me);

			return;

		case "add_wound":
			msg = HIR "「" + ran_item_enchase + "」追加「" + victim->name() + HIY +
                              "」傷害上限：" + sprintf("%d", ef_point) + "點\n" NOR;
			tell_object(me, msg);
			victim->receive_wound("qi", ef_point, me);

			return;
		
		case "busy":
			msg = HIR "「" + ran_item_enchase + "」追加「" + victim->name() + HIY +
                              "」忙亂效果：" + sprintf("%d", ef_point) + "秒\n" NOR;
			tell_object(me, msg);
			if (! victim->is_busy())victim->start_busy(ef_point);

			return;

		case "no_exert":
			msg = HIR "「" + ran_item_enchase + "」追加「" + victim->name() + HIY +
                              "」內息紊亂：" + sprintf("%d", ef_point) + "秒\n" NOR;
			tell_object(me, msg);
			if (! victim->query_temp("no_exert"))victim->set_temp("no_exert", 1);
			tell_object(victim, HIM "你被" + me->name() + "的" + HIY + ran_item_enchase + HIM "打中，頓覺內息紊亂！\n" NOR);

			// 消除效果
			call_out("remove_effect", ef_point, victim, "內息紊亂");
			return;

		case "no_perform":
			msg = HIR "「" + ran_item_enchase + "」追加「" + victim->name() + HIY +
                              "」力道渙散：" + sprintf("%d", ef_point) + "秒\n" NOR;
			tell_object(me, msg);
			if (! victim->query_temp("no_perform"))victim->set_temp("no_perform", 1);
			tell_object(victim, HIM "你被" + me->name() + "的" + HIY + ran_item_enchase + HIM "打中，頓覺力道渙散！\n" NOR);

			// 消除效果
			call_out("remove_effect", ef_point, victim, "力道渙散");
			return;		

        // 輪回﹒重生的特殊效果
		// 削弱戰力
		case "lunhui-chongsheng":
			if (victim->query_temp("lunhui-chongsheng/xueruo"))return;

			msg = HIR "「" + ran_item_enchase + "」追加「" + victim->name() + HIY +
                              "」削弱戰力：削弱攻、防、回避、命中各30%。\n" NOR;
			
			tell_object(me, msg);
			
			victim->set_temp("lunhui-chongsheng/xueruo", 1);
			victim->set_temp("apply/damage", victim->query_temp("apply/damage") / 10 * 7);
			victim->set_temp("apply/unarmed_damage", victim->query_temp("apply/unarmed_damage") / 10 * 7);
			victim->set_temp("apply/defense", victim->query_temp("apply/defense") / 10 * 7);
			victim->set_temp("apply/attack", victim->query_temp("apply/attack") / 10 * 7);

			return;

        // 致命一擊
		case "unconcious":
			if (userp(victim))return;
						
			msg = HIR "「" + ran_item_enchase + "」追加「" + victim->name() + HIY +
                              "」致命一擊！\n" NOR;
			
			tell_object(me, msg);

			victim->receive_wound("qi", 1, me);
			victim->unconcious(me);

			return;
		
		// 化解防護
		case "reduce_def":
			if (userp(victim))return;
			
			if (victim->query_temp("apply/defense") <= 0)return;
						
			msg = HIR "「" + ran_item_enchase + "」追加「" + victim->name() + HIY +
                              "」化解防護：" + sprintf("%d", ef_point) + "點\n" NOR;
			tell_object(me, msg);

			if (victim->query_temp("apply/defense") < ef_point)
					victim->set_temp("apply/defense", 0);
			else
					victim->add_temp("apply/defense", -1 * ef_point);

			return;
			
		// 化解傷害
		case "reduce_dam":
			if (userp(victim))return;
						
			msg = HIR "「" + ran_item_enchase + "」追加「" + victim->name() + HIY +
                              "」化解傷害：" + sprintf("%d", ef_point) + "點\n" NOR;
			tell_object(me, msg);

			if (victim->query_temp("apply/damage") < ef_point)
					victim->set_temp("apply/damage", 0);
			else
					victim->add_temp("apply/damage", -1 * ef_point);

			if (victim->query_temp("apply/unarmed_damage") < ef_point)
					victim->set_temp("apply/unarmed_damage", 0);
			else
					victim->add_temp("apply/unarmed_damage", -1 * ef_point);

			return;

        // 召喚神龍
		case "summon_shenlong":

			if (time() - me->query_temp("last_summon_shenlong") < 180)return;

			if (! victim)return;

			msg = HIG "「" + ran_item_enchase + "」光芒萬丈，一條神龍伴隨著光芒從天而降。\n" NOR;
			message_combatd(msg, me);
			
			shenlong = new("/kungfu/class/misc/shenlong");
			
			if (! objectp(shenlong))return;
						
			me->set_temp("last_summon_shenlong", time());

			shenlong->move(environment(me));
			shenlong->set("long", HIC + me->name() + "的寶物龍女﹒碧海神龍的力量所召喚的神龍，威風無比。\n" NOR);
			shenlong->kill_ob(victim);
			shenlong->force_me("guard " + me->query("id") );

			return;

	}

	return;
}

// 消除特效
void remove_effect(object victim, string eff)
{

	if (! objectp(victim))return;
	
	switch(eff)
	{
		case "內息紊亂":
			victim->delete_temp("no_exert");			
			return;

		case "力道渙散":
			victim->delete_temp("no_perform");
		    return;
	}
	return;
}

// 降低耐久度
void reduce_consistence(object item, object me, object victim, int damage)
{
        int st;
        int con;
		int i, en_num, flag, cur_firm;
		mapping enchases;
		string* en_keys;

        // 調用鑲嵌物品攻擊特效	
		if (! objectp(item))return;
		if (item->query("armor_type") != "neck" && item->query("armor_type") != "armor")
			do_enchase_attack(item, me, victim, damage);

        st = item->query("stable");

        if (st < 2)
                return;

        con = item->query("consistence");

		// 降低鑲嵌物品的耐久度
		flag = 0;
        enchases = item->query("enchase");
        en_num = sizeof(enchases);
        if (en_num && mapp(enchases))
		{
		en_keys = keys(enchases);
		for (i = 0; i < en_num; i ++)
		{
			cur_firm = item->query("enchase/" + en_keys[i] + "/cur_firm");
			if (enchases[en_keys[i]]["cur_firm"] == 100)continue;
			if (random(100) >= 20)/*random(st) > ((100 - cur_firm / 2) / 10) )*/continue;
			if (item->add("enchase/" + en_keys[i] + "/cur_firm", -1) > 0)
				continue;
			flag = 1;
        	if (environment(item))
			{
             			tell_object(environment(item), HIG "你的" +
                         	            item->query("enchase/" + en_keys[i] + "/name") + HIG "已經徹底損壞了。\n" NOR);

			}
			item->set("enchase/" + en_keys[i] + "/cur_firm", 0);
                        item->delete("enchase/" + en_keys[i]);
			item->save();

		}
		if (flag)
		{
			tell_object(environment(item), HIM "突然間，" + item->name() + HIM "離你而去！\n" NOR);
			destruct(item);
			return;
		}
	}

        // 寰宇天晶煉制的武器永不磨損
        if (item->query("material") == "tian jing")
                return;

        if (random(st) > (100 - con) / 13 || random(2))
                return;

        if (item->add("consistence", -1) > 0)
                return;

        item->set("consistence", 0);

        if (environment(item))
                tell_object(environment(item), HIG "你的" +
                            item->name() + HIG "已經徹底損壞了。\n" NOR);

        item->unequip();
}

// 構造物品缺省的耐久度信息
void equip_setup(object item)
{
        int stable;
        mapping dbase;

        dbase = item->query_entire_dbase();
        if (undefinedp(dbase["consistence"]))
                dbase["consistence"] = 100;

        if (undefinedp(item->query("stable")))
        {
                switch (item->query("material"))
                {
                case "cloth":
                        // 永遠不會損壞
                        stable = 0;
                        break;
                case "paper":
                        stable = 3;
                        item->set("no_repair", "這東西我可沒法修理。\n");
                        break;
                case "bone":
                        stable = 8;
                        item->set("no_repear", "修理這個？可別拿我尋開心。\n");
                        break;
                case "bamboo":
                case "wood":
                        stable = 10;
                        item->set("no_repair", "這東西我咋修理？\n");
                        break;
                case "copper":
                        stable = 40;
                        break;
                case "silver":
                        stable = 40;
                        break;
                case "iron":
                        stable = 45;
                        break;
                case "gold":
                        stable = 50;
                        break;
                case "steel":
                        stable = 75;
                        break;
                case "stone":
                        stable = 80;
                        break;
                default:
                        stable = 100;
                        break;
                }

                if (! item->is_item_make())
                        stable /= 2;

                item->set("stable", stable);
        }
}


// 外部調用來自 /clone/fam/item/moye-shengfu.c
// 寫入文件
public int extern_write_file(string str_file, string msg, int flag)
{
	if (! write_file(str_file, msg, flag))return 0;

	return 1;
}
2371    // 來自/feature/itemmake.c的調用，強化等級增加相應的鑲嵌效果 
2372    //public int qianghua_enchase_points("WEAPON", enchase_points, query("qh_level")) 
2373    public int qianghua_enchase_points(string stype, int points, int qh_level) 
2374    { 
2375            int i; 
2376            if (points <= 0)return points; 
2377            if (qh_level < 1)return points; 
2378             
2379            switch(stype) 
2380            { 
2381            case "weapon": // 武器每級強化遞增x% 
2382                    for (i = 0; i < qh_level; i ++) 
2383                            points = points + points / 10; 
2384                    return points; 
2385            break; 
2386     
2387            case "wrists": // 護腕每級增加x% 
2388                    points *= 300; // 護腕傳入的是sizeof(鑲嵌) 
2389                    for (i = 0; i < qh_level; i ++) 
2390                            points = points + points * 3 / 50; 
2391                    return points; 
2392            break; 
2393     
2394            case "surcoat": // 披風每級增加x%，基礎為鑲嵌總數*300 
2395                    points *= 300; // 披風傳入的是sizeof(鑲嵌） 
2396                    for (i = 0; i < qh_level; i ++) 
2397                            points = points + points / 10; 
2398                    return points; 
2399            break; 
2400     
2401            default: 
2402                    return points; 
2403            break; 
2404            } 
2405     
2406            return points; 
2407    } 
2408     
2409    // 來自外部調用，強化裝備等級 
2410    public int qianghua_object(object me, object obj) 
2411    { 
2412            string *can_qianghua, str_log; 
2413            int qh_level, qhobj_count, suc_points; 
2414            object qhobj; 
2415            mapping suc_points_list; 
2416             
2417            // 開放強化的道具 
2418            can_qianghua = ({ 
2419                    "hands", "surcoat", "wrists", "head", 
2420            }); 
2421    /* 
2422            suc_points_list = ([ 
2423                    "0" :  80,  // 代表0->1 
2424                    "1" :  70, 
2425                    "2" :  50, 
2426                    "3" :  30, 
2427                    "4" :  10, 
2428                    "5" :  5,   // 5升6的時候失敗就會降到4級，後面都是降到4級 
2429                    "6" :  4,   
2430                    "7" :  3, 
2431                    "8" :  2, 
2432                    "9" :  1, 
2433            ]); 
2434    */ 
2435            suc_points_list = ([ 
2436                    "0" :  80,  // 代表0->1 
2437                    "1" :  70, 
2438                    "2" :  60, 
2439                    "3" :  50, 
2440                    "4" :  45, 
2441                    "5" :  40,   // 5升6的時候失敗就會降到4級，後面都是降到4級 
2442                    "6" :  35,   
2443                    "7" :  20, 
2444                    "8" :  22, 
2445                    "9" :  12, 
2446            ]); 
2447                     
2448            str_log = ctime(time()); // 記錄LOG 
2449             
2450            if (! objectp(me) || ! objectp(obj)) 
2451                    return notify_fail("遇到問題，暫時不能強化！\n"); 
2452             
2453            // 非自造兵器不能強化 
2454            if (! obj->is_item_make()) 
2455                    return notify_fail("只有自造物品才能強化！\n"); 
2456             
2457            // 不是自己的道具不能強化 
2458            if (obj->item_owner() != me->query("id")) 
2459                    return notify_fail("這個好像不是你的裝備吧，不能強化！\n"); 
2460     
2461            // 只開放的強化類型 
2462            if (! obj->query("skill_type") && // 武器 
2463                  member_array(obj->query("armor_type"), can_qianghua) == -1) 
2464                    return notify_fail("該類型的裝備暫時還未開放強化，詳見幫助文件！\n"); 
2465     
2466            // 沒有鑲嵌信息不能強化 
2467            if (! sizeof(obj->query("enchase"))) 
2468                    return notify_fail("這件裝備似乎還沒有鑲嵌過任何東西，暫時不能強化！\n"); 
2469             
2470            qh_level = obj->query("qh_level"); 
2471            // 強化等級滿了不能強化 
2472            if (qh_level >= 10) 
2473                    return notify_fail("該裝備強化等級已滿！\n"); 
2474     
2475            // 需要消耗強化物品 
2476            if (! objectp(qhobj = present("tie ying", me))) 
2477                    return notify_fail("你身上沒有鐵英石，不能強化裝備!\n"); 
2478             
2479            // 強化物品是否正確 
2480            if (! qhobj->query("qhobj")) 
2481                    return notify_fail("你身上沒有鐵英石，不能強化裝備。\n"); 
2482     
2483            qhobj_count = qh_level - 3; 
2484            if (qhobj_count < 1)qhobj_count = 1; 
2485            // 數量是否足夠 
2486            if (qhobj->query_amount() < qhobj_count) 
2487                    return notify_fail("你身上沒有足夠的鐵英石，當前強化需要" +  
2488                                       sprintf("%d", qhobj_count) + "個。\n"); 
2489     
2490            // 開始強化 
2491            str_log += " " + obj->name() + "(" + obj->query("id") + ") of " + obj->item_owner() + NOR " 強化："; 
2492            // 計算成功幾率suc_points 
2493            suc_points = suc_points_list[sprintf("%d", qh_level)]; 
2494            str_log += sprintf("基礎成功率：%d，", suc_points); 
2495            // 如果裝備有成功率加成則增加 
2496            if (obj->query("suc_points_add")) 
2497                    suc_points += obj->query("suc_points_add"); 
2498            str_log += sprintf("加成後成功率：%d，", suc_points); 
2499            // 扣掉物品 
2500            qhobj->add_amount(-1*qhobj_count); 
2501            if (qhobj->query_amount() < 1)destruct(qhobj); 
2502     
2503            // 清除增加成功率 
2504            if (obj->query("suc_points_add")) 
2505            { 
2506                    obj->delete("suc_points_add"); 
2507                    obj->save(); 
2508            } 
2509             
2510            // 等級大于6時，成功率降低5% 
2511            if (qh_level > 6)suc_points -= 5; 
2512            // 9級時候再減2% 
2513            if (qh_level == 9)suc_points -= 2; 
2514             
2515            // 是否失敗 
2516            if (random(100) >= suc_points) // 失敗 
2517            { 
2518                    // 當前等級不超過4級則失敗提示返回即可 
2519                    if (qh_level <= 4) 
2520                    { 
2521                            str_log += sprintf("強化失敗等級為：%d。\n", qh_level); 
2522                            log_file("0裝備強化", str_log); 
2523                            return notify_fail("很遺憾，強化失敗了！\n"); 
2524                    } 
2525                    else // 超過4級，失敗就會倒退到4級 
2526                    { 
2527                            // 如果有防止失敗掉級 
2528                            if (obj->query("no_reduce_level")) 
2529                            { 
2530                                    obj->delete("no_reduce_level"); 
2531                                    obj->save(); 
2532                                    str_log += sprintf("強化失敗等級為：%d(強化等級未損失）。\n", qh_level); 
2533                                    log_file("0裝備強化", str_log); 
2534                                    return notify_fail("很遺憾，強化失敗了(強化等級未損失）！\n"); 
2535                            } 
2536                            else 
2537                            { 
2538                                    obj->set("qh_level", 4); 
2539                                    obj->save(); 
2540                                    str_log += sprintf("強化失敗等級為：%d(強化等級降為4級）。\n", qh_level); 
2541                                    log_file("0裝備強化", str_log); 
2542                                    write(HIG "你感覺" + obj->name() + HIG "突然離你而去，似乎發生了不可言喻的變化！\n" NOR); 
2543                                    //destruct(obj); 
2544                                     
2545                                    return notify_fail(HIR "很遺憾，強化失敗了(強化等級降為4級）！\n" NOR); 
2546                            } 
2547                    } 
2548            } 
2549            else // 成功！！！ 
2550            { 
2551                    obj->set("qh_level", qh_level+1); 
2552                    obj->save(); 
2553                    write(HIG "強化成功！" + obj->name() + HIG "強化等升至" + 
2554                          sprintf(HIY "%d" HIG, obj->query("qh_level")) + "級。\n" NOR); 
2555                    str_log += sprintf("強化成功！等級從%d升級到%d\n", qh_level, obj->query("qh_level")); 
2556                    log_file("0裝備強化", str_log); 
2557                     
2558                    // 全屏通告 
2559                    if (obj->query("qh_level") >= 6) 
2560                    { 
2561                            CHANNEL_D->do_channel(this_object(), "chat",  
2562                                                  "聽說" + HIY + me->name() + HIM "的" + obj->name() +  
2563                                                  HIM "強化至" HIR + sprintf("%d", obj->query("qh_level")) +  
2564                                                  HIM "級。\n" NOR); 
2565     
2566                    } 
2567                    if (obj->query("qh_level") == 10) 
2568                    { 
2569                            CHANNEL_D->do_channel(this_object(), "chat",  
2570                                                  HIR "恭喜" + HIY + me->name() + HIR "的" + obj->name() +  
2571                                                  HIR "強化為曠世神兵！\n" NOR); 
2572                    } 
2573                    write(HIG "你感覺" + obj->name() + HIG "突然離你而去，似乎發生了不可言喻的變化！\n" NOR); 
2574                    //destruct(obj); 
2575                    return 1; 
2576            } 
2577    } 
2578     
2579    // 來自/inherit/char/dream_npc調用 
2580    // 判斷是否掉出鐵英石，外部控制幾率，方便隨時調整 
2581    public int drop_tieyingshi(object me) 
2582    { 
2583            int ran; 
2584             
2585            if (! objectp(me))return 0; 
2586     
2587            if (me->query("service/jiutoushe")) 
2588            { 
2589                    ran = 20000; 
2590            } 
2591            else 
2592            { 
2593                    if (! MEMBER_D->is_valib_member(me->query("id")))ran = 1200000; // 非會員爆率極低 
2594                    else 
2595                            ran = 150000; 
2596            } 
2597            /* 
2598            if (random(ran) == 1) 
2599            { 
2600                    // 記錄每日鐵英掉落總量 
2601                    total_tieying += 1; 
2602                    if (total_tieying % 100 == 0) 
2603                    { 
2604                            DB_D->set_data("tieying_drop/" + sprintf("%d", time() / 86400), total_tieying); 
2605                    } 
2606                     
2607                    // 返回1則掉落 
2608                    return 1; 
2609            } 
2610            */ 
2611            return 0; 
2612    } 
