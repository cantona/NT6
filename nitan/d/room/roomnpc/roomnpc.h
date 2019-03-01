// major function of room's npc

#define GOLDS  10000
#include <ansi.h>

int is_owner(object ob)
{
        if( query("id", ob) == query("room_owner_id", environment()) || 
            query("couple/couple_id", ob) == query("room_owner_id", environment()) )
                return 1;

        return 0;
}

int is_owner_permit(object ob)
{
        string *vip;

        if (query_temp("permit_enter/" + query("room_owner_id",environment()),ob)) 
                return 1;

        if (objectp(present(query("room_owner_id",environment()) + " pass", ob))) 
                return 1;

        vip=query("vip", this_object());
        if (vip && sizeof(vip) && member_array(query("id",ob),vip) != -1) 
                return 1;

        return 0;
}

int owner_is_present()
{
        string id;

        if( present(id=query("room_owner_id", environment())) )
                return 1;

        return 0;
}

int do_invite(string arg)
{
        object ob;
        object me;

        me = this_player();

        if (!is_owner(me))
                return notify_fail("老僕奇怪的問：你是誰？憑什麼對我指手畫腳的？\n");

        if (! arg || ! objectp(ob = present(arg, environment())))
                return notify_fail("你要邀請誰？\n");

        if (! ob->is_character())
                return notify_fail("你向邀請它，可是它不會走路啊！\n");

        if( !query("can_speak", ob) )
                return notify_fail("有意思，不過你最好還是邀請一個“人”。\n");

        if (ob == me)
                return notify_fail("你要邀請你自己？想法不錯，可惜沒有用。\n");

        if (is_owner(ob))
                return notify_fail("這人也算是這兒的主人，有什麼好邀請的？\n");

        if (! userp(ob))
                return notify_fail("這人你還是別邀請了。\n");

        me = this_player();
        message_vision("$N指著" + ob->name() + "對$n道：“這是我請來的"
                       "客人，你可不要怠慢了！”\n$n連忙點頭哈腰道：“"
                       "知道了！知道了！這位" + RANK_D->query_respect(ob) +
                       "，小的哪有不周盡管提！”\n", me, this_object());
        set_temp("permit_enter/"+query("id", me), 1, ob);
        return 1;
}

int do_show(string arg)
{
        object ob;
        object me;
        string msg;

        if (! arg)
                return notify_fail("你要亮出什麼東西？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上沒有這種東西。\n");
 
        msg="$N亮出一"+query("unit", ob)+ob->name()+"\n";
       if (! ob->id(query("room_owner_id",environment()) + " pass")) 
                msg += "不過$n理都沒有理$n。\n";
        else
                if (is_owner_permit(me))
                        msg += "$n滿臉堆笑，對$N道：“失敬！失敬！”\n";
                else
                {
                        msg += "$n一看，滿臉堆笑，對$N道：“原來是" +
                               environment(query("room_owner", ))+
                               "的朋友，失敬！失敬！”\n";
                        me->set_temp("permit_enter/"+
                                     environment(query("room_ownerid", )),1);
                }
        message_vision(msg, me, this_object());
        return 1;
}

int list_vip()
{
        object ob;
        int i;
        string msg,*vip;

        if (!is_owner(this_player()))
                return notify_fail("老僕奇怪的問：你是誰？憑什麼對我指手畫腳的？\n");

        ob = this_object();

        vip=query("vip", ob);
        if (!vip || sizeof(vip) < 1)
        {
                msg = "您並沒有定義任何的貴賓。\n";
                msg += "您可以通過vip <id>來添加貴賓，通過vip <id> -c來清除貴賓。\n";
                return notify_fail(msg);
        }
        msg = HIY "您所定義的貴賓有如下玩家：\n" NOR;
        msg += "------------------------------\n";
        for (i = 0;i < sizeof(vip);i++)
        {
                msg += sprintf(HIY"%s\n"NOR, vip[i]);
        }
        msg += "------------------------------\n";

        msg += HIY "總共" + sizeof(vip) + "個貴賓。\n" NOR;
        msg += HIY "您可以通過vip <id>來添加貴賓，通過vip <id> -c來清除貴賓。\n" NOR;
        write(msg);
        return 1;
}

int do_vip(string arg)
{
        string *vip;
        object ob,me;
        int num;
        
        ob = this_object();
        me = this_player();

        if (!is_owner(me))
                return notify_fail("老僕奇怪的問：你是誰？憑什麼對我指手畫腳的？\n");

        if (!arg)
                return notify_fail("您可以通過vip <id>來添加貴賓，通過vip <id> -c來清除貴賓。\n");

        vip=query("vip", ob);
        if (!vip) vip = ({});

        if (sscanf(arg,"%s -c",arg) == 1)
        {
                if (member_array(arg,vip) == -1)
                        return notify_fail(ob->name(1) + "賠著笑臉說：" + arg + "本來就不是您的貴賓啊！\n");
                vip -= ({arg});
                set("vip", vip, ob);
                ob->save();
                write(ob->name(1) + "點頭哈腰對你說：收到！收到！！以後" + arg + "不是您的貴賓了。\n");
                return 1;
        }

        if( sizeof(vip) >= query("max_vip", ob) )
                return notify_fail(ob->name(1) + "苦著臉說：您定的貴賓太多了，老奴我實在是記不住啊！\n");

        if( arg == query("id", me) )
                return notify_fail(ob->name(1) + "一個哆嗦，戰戰兢兢的說：您是主人啊，老奴不敢當您是客人！\n");

        if (member_array(arg,vip) != -1)
                return notify_fail(ob->name(1) + "賠著笑臉說：" + arg + "本來就已經是您的貴賓啦！\n");

        vip += ({ arg });
        set("vip", vip, ob);
        ob->save();
        write(ob->name(1) + "滿臉堆笑，點頭哈腰到：" + arg + "既然是您貴賓，以後一定放行！\n");
        return 1;
}

int add_force()
{
        object ob, me;

        ob = this_object();
        me = this_player();

        if (!is_owner(me))
                return notify_fail("老僕奇怪的問：你是誰？憑什麼對我指手畫腳的？\n");

        if( query("max_jing", ob) >= 1000000 || query("max_qi", ob) >= 1000000
             || query("max_neili", ob) >= 1000000 )
                return notify_fail("老僕的精、氣、內力已經不能再升了。\n");

#ifdef LONELY_IMPROVED 
        if( count_lt(query("balance", me),100000000) )
#else
        if( query("balance", me)<100000000 )
#endif
                return notify_fail("你的存款不足。\n");

        addn("balance", -10000*GOLDS, me);
        addn("max_qi", 2000, ob);
        addn("max_jing", 2000, ob);
        addn("max_jingli", 2000, ob);
        addn("max_neili", 2000, ob);
        addn("qi", 2000, ob);
        addn("jing", 2000, ob);
        addn("jingli", 2000, ob);
        addn("neili", 2000, ob);

        ob->save();
        message_vision("只見$N臉上紅光忽隱忽現，" +
                "瞬間又恢復平靜。\n", ob);
        tell_object(me, "老僕的精、氣、內力升級成功！\n");
        return 1;
}

int add_skill()
{
        object ob, me;
        int oldlvl;

        ob = this_object();
        me = this_player();

        if (!is_owner(me))
                return notify_fail("老僕奇怪的問：你是誰？憑什麼對我指手畫腳的？\n");

        oldlvl = ob->query_skill("force", 1);

#ifdef LONELY_IMPROVED
        if( count_lt(query("balance", me),count_mul(oldlvl,200000)) )
#else
        if( query("balance", me)<oldlvl*200000 )
#endif
                return notify_fail("你的存款不足。\n");

        addn("balance", -oldlvl*20*GOLDS, me);
        ob->set_skill("force", oldlvl + 100);
        ob->set_skill("parry", oldlvl + 100);
        ob->set_skill("dodge", oldlvl + 100);
        ob->set_skill("strike", oldlvl + 100);
        ob->set_skill("claw", oldlvl + 100);
        ob->set_skill("jiuyang-shengong", oldlvl + 100);
        ob->set_skill("lingbo-weibu", oldlvl + 100);
        ob->set_skill("qiankun-danuoyi", oldlvl + 100);
        ob->set_skill("jiuyin-baiguzhao", oldlvl + 100);
        ob->set_skill("cuixin-zhang", oldlvl + 100);
        ob->set_skill("martial-cognize", oldlvl + 100);
        ob->set_skill("count", oldlvl + 100);

        ob->save();
        message_vision("忽然間聽到$N全身的骨骼“嘩啦啦”一陣暴響，" +
                "瞬間又恢復平靜。\n", ob);
        tell_object(me, "老僕的武功升級成功！\n");
        return 1;
}

int buy_vip()
{
        object ob, me;

        ob = this_object();
        me = this_player();

        if (!is_owner(me))
                return notify_fail("老僕奇怪的問：你是誰？憑什麼對我指手畫腳的？\n");

#ifdef LONELY_IMPROVED 
        if( count_lt(query("balance", me),2000*GOLDS) )
#else
        if( query("balance", me)<2000*GOLDS )
#endif
                return notify_fail("你的存款不足。\n");

        addn("balance", -2000*GOLDS, me);
        addn("max_vip", 1, ob);

        ob->save();
        tell_object(me, "成功增加一個VIP名額！\n");
        tell_object(me,sprintf("現共有%d個VIP名額。\n",query("max_vip", ob)));
        return 1;
}

int add_hujiu()
{
        object ob, me;

        ob = this_object();
        me = this_player();

        if (!is_owner(me))
                return notify_fail("老僕奇怪的問：你是誰？憑什麼對我指手畫腳的？\n");

        if( query("can_hujiu", ob) )
                return notify_fail("主人已經吩咐過了，老奴不敢忘記。\n");

#ifdef LONELY_IMPROVED 
        if( count_lt(query("balance", me),3000*GOLDS) )
#else
        if( query("balance", me)<30000*GOLDS )
#endif
                return notify_fail("你的存款不足。\n");

        addn("balance", -30000*GOLDS, me);
        set("can_hujiu", 1, ob);

        ob->save();
        tell_object(me, "主人放心，老奴記住了！\n");
        return 1;
}
