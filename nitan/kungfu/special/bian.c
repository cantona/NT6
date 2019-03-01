// bian.c 詭辯奇學
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIC "詭辯奇學" NOR; }

int perform(object me, string skill, string arg)
{
        int i;
      
        object ob;

        if (time() - me->query("special2/bian") < 600)
                return notify_fail("你剛施展完詭辯奇學，等下再說吧！\n");

        if (me->is_busy())return notify_fail("等你忙完再說吧！\n");

        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("這裡沒有這個人！可能是你的格式有錯誤！\n"
                                   "格式 ： special bian <對象id> \n");


        if (! playerp(ob))return notify_fail("詭辯奇學只能對同門玩家使用！\n");

        if (ob->query("family/family_name") != me->query("family/family_name"))
                return notify_fail("詭辯奇學只能對同門玩家使用！\n");

        message_vision(HIM "$N" HIM "施展出詭辯奇學，詭辯之聲不絕于耳 ……\n" NOR, me);

        if (me->query("gongxian") > 100000000)
        {
                tell_object(me, HIG "你的門派貢已經超過極限！\n");
                return 1;
        }
        
        me->add("gongxian", 1000 + random(101));
        me->start_busy(2);

        tell_object(me, HIG "你的門派貢獻提高了！\n");

        me->set("special2/bian", time());

        return 1;
}
