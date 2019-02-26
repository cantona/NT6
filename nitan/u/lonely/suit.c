// special

#include <ansi.h>

#define TAOZHUANG_D   "/adm/daemons/taozhuangd"

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string tzx, result, *keys_tzlist;
	object ob;
	int i;
	mapping tz;
	string *keys_tz, str_color;

	mapping tzlist = ([
		"head"       :  "頭飾",
		"waist"      :  "腰帶",
		"boots"      :  "靴子",
		"surcoat"    :  "披風",//
		"armor"      :  "戰甲",
		"cloth"      :  "戰衣",
		"wrists"     :  "護腕",
		"neck"       :  "項鍊",
		"rings"      :  "戒指",
		"myheart"    :  "左符",
		"myheart2"   :  "右符",
	]);

	if (! objectp(me))return 0;

	if (! arg)arg = "show";

	keys_tzlist = keys(tzlist);

	// 一次性穿上一套
	if (arg == "wear")
	{
		tz = me->query("tzlist");

		if (! sizeof(tz))
			return notify_fail("你還沒有自定義套裝列表，詳情見 help taozhuang 説明。\n");
		/*
		if (sizeof(tz) < 12 && ! wizardp(me)) // 巫師測試的時候可不用穿12件
			return notify_fail("你還未完成12件套裝部件的定義，請使用 suit show 查看！\n");
*/
		keys_tz = keys(tz);
		for (i = 0; i < sizeof(keys_tz); i ++)
		{
			if (! objectp(ob = present(tz[keys_tz[i]], me)))
			{
				// 未在身上，嘗試召喚
				__DIR__"summon"->main(me, tz[keys_tz[i]]);
				// 召喚後如果還沒有則終止
				if (! objectp(ob = present(tz[keys_tz[i]], me)))
					return notify_fail("未找到裝備 " + tz[keys_tz[i]] + "，操作終止！\n");
			}

			if (ob->query("equipped"))continue;


			// 裝備特殊處理
			if (ob->query("skill_type"))
			{
				"/cmds/std/wield"->do_wield(me, ob);
			}
			else
			{
				"/cmds/std/wear"->do_wear(me, ob);
			}
		}

		return notify_fail("OK.\n");
	}


	// 顯示已加入的套裝列表
	if (arg == "show")
	{
		result = HIG "-----------自定義套裝列表-------------\n" NOR;

		if (! sizeof(me->query("tzlist")))
			return notify_fail("你還沒有自定義套裝列表，詳情見 help taozhuang 説明。\n");

		if (sizeof(me->query("tzlist/weapon")))
		{
			ob = present(me->query("tzlist/weapon"), me);
			if (objectp(ob))
			{
				str_color = ob->query("equipped") ? HIM : HIC;
				result += str_color + "武器： " + HIC + ob->name() + HIC + "（" +
		                 	  TAOZHUANG_D->taozhuang_name(ob->query("taozhuang")) + HIC "）\n" NOR;
		        }
		        else
		        	result += HIC "武器： " NOR + WHT + me->query("tzlist/weapon") + "\n" NOR;
		}
		else
		{
			result += HIC "武器： " + NOR + WHT "----\n" NOR;
		}

		for (i = 0; i < sizeof(keys_tzlist); i ++)
		{
			if (sizeof(me->query("tzlist/" + keys_tzlist[i])))
			{
				ob = present(me->query("tzlist/" + keys_tzlist[i]), me);
				if (objectp(ob))
				{
					str_color = ob->query("equipped") ? HIM : HIC;
					result += str_color + tzlist[keys_tzlist[i]] + "： " + HIC + ob->name() + HIC + "（" +
		                          	  TAOZHUANG_D->taozhuang_name(ob->query("taozhuang")) + HIC "）\n" NOR;
		                }
		                else
		                	result += HIC + tzlist[keys_tzlist[i]] + "： " NOR + WHT +
		                	          me->query("tzlist/" + keys_tzlist[i]) + "\n" NOR;
			}
			else
			{
				result += HIC + tzlist[keys_tzlist[i]] + "： " NOR + WHT + "----\n" NOR;
			}
		}
		result += HIG "-------------------------------------\n" NOR;
		result += HIW "裝備類型名為" HIM "紫紅色" HIW "的表示已裝備，" HIC "天青色" HIW "為未裝備。\n" NOR;
		result += HIY "使用指令 suit add 裝備id 添加自定義套裝列表。\n" NOR;
		result += HIR "使用指令 suit wear 可將自定義套裝列表內的套件批量裝備。\n" NOR;
		//result += HIY "使用指令 suit remove 裝備id 從自定義套裝列表中移出該裝備。\n" NOR;
		write(result);
		return 1;
	}


	// 將指定裝備加入套裝列表
	if (sscanf(arg, "add %s", tzx))
	{
		if (! objectp(ob = present(tzx, me)))
			return notify_fail("你身上沒有這件裝備！\n");

		// 判斷裝備是否屬於自己
		if (ob->item_owner() != me->query("id"))
			return notify_fail("這個，這個……，好像不屬於你吧！\n");

		// 判斷是否為12件裝備中的類型
		if (ob->query("skill_type") || ob->query("armor_type") == "hands") // 武器
		{
			me->set("tzlist/weapon", tzx);
			return notify_fail("添加自定義套裝成功，可使用 suit show 查看。\n");
		}
		if (! ob->query("armor_type"))
			return notify_fail("這件物品不屬於裝備類型！\n");

		if (member_array(ob->query("armor_type"), keys_tzlist) == -1)
			return notify_fail("這件物品不屬於套裝部件！\n");

		me->set("tzlist/" + ob->query("armor_type"), tzx);
		return notify_fail("添加自定義套裝成功，可使用 suit show 查看。\n");
	}

	return TAOZHUANG_D->suit_special(me, arg);

}