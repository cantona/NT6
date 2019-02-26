
// 定心術 Create by Rcwiz for yhonline 04/21 2010

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIG "定心術" NOR; }

int perform(object me, string skill)
{
	// 2轉後使用可立即獲得180級左右互搏
	// 如果當前等級超過180則顯示説明
	if (me->query("thborn/ok") && me->query_skill("zuoyou-hubo",1) < 180)
	{
		me->set_skill("zuoyou-hubo", 180);
		me->save();
                return notify_fail("你獲得了左右互搏180級。\n");
	}
        else
        {
      		return notify_fail("定心術可攝定心神,令施展左右互搏不受牽制。\n"
          	   		   "使用後可獲得左右互搏180級,同時可自行\n"
          	   		   "研究到380級.如絕情去欲技能達到三百級\n"
                                   "可研究左右互搏到400級。\n");
       }
}