// ride.c

#include <ansi.h>

#define MEMBER_D        "/adm/daemons/memberd"

void create() { seteuid(getuid()); }

int no_clean_up() { return 1; }

int main(object me, string arg)
{
        object ob, env;

	if (! arg)
                return notify_fail("指令格式： lured <誘餌> \n");

	if (! objectp(ob = present(arg, me)))
		return notify_fail("你身上沒有這樣東西。\n");

	if( !query("lure", ob) )
		return notify_fail("這東西好象不是誘餌吧！\n");

	if (me->is_busy())
		return notify_fail("等你忙完了再說吧！\n");

	if( query_temp("hunting", me) )
		return notify_fail("別著急，再等等！\n");

	message_vision(HIG "$N將" + ob->name() + "放在地上，躲在一旁靜靜守侯著 ……\n" NOR, me);

	me->start_busy(3 + random(5));
set_temp("hunting", 1, 	me);

	env = environment(me);

        call_out("do_hunt", 5 + random(5), me, env, ob);

	return 1;
}

void do_hunt(object me, object env, object ob)
{
	object obq;
	string* temp;
	string str;
	mapping quarry;
	int i, point;

	if (! objectp(me))return;
	if (! objectp(env))return;
	if (! objectp(ob))return;

	if( !query("can_hunting", env) )
		return;

	quarry=query("quarry", env);
	temp = keys(quarry);
	i = random(sizeof(temp));

delete_temp("hunting", 	me);

        // 獲得幾率判斷是否動物出現
	point = quarry[temp[i]];
	if( MEMBER_D->is_valid_member(query("id", me)) )
		point += 3;

	if( query("level", ob)>1 )
		point=query("level", ob);

        if (random(100) >= point)
	{
		if (base_name(environment(me)) == base_name(env))
		{
			write(HIY "等了半天卻不見獵物出現，你只好把" + ob->name() + HIY "收了起來。\n");
		}
		else
		{
			destruct(ob);
		}
		return;
	}	
	
	obq = new("/clone/quarry/" + temp[i]);
	obq->move(env);
set("owner",query("id",  me), 	obq);
        set("name", HIR+me->name()+"("+query("id", me)+")獵出的"+obq->name()+NOR, obq);
  
	if (environment(me) == env)
	{
		switch(random(4))
		{
			case 0:
			message_vision(HIG "不一會兒，一只" + obq->name() + HIG "竄了出來，將" + 
                                       ob->name() + HIG "一口咬在嘴裡。\n" NOR, me);
			break;

			case 1:
			message_vision(HIM "轉眼間，一只" + obq->name() + HIG "突然出現，將" + 
                                       ob->name() + HIG "吞進嘴裡。\n" NOR, me);
			break;

			case 2:
			message_vision(HIW "良久，一只" + obq->name() + HIG "大搖大擺地走了出來，仔細地打量著" + 
                                       ob->name() + HIG "。\n" NOR, me);
			break;

			default:
			message_vision(HIC "少時，一只" + obq->name() + HIG "竄了過來，一口將" + 
                                       ob->name() + HIG "叼在了嘴上，相貌貪婪之極。\n" NOR, me);
			break;
		}
	}
	destruct(ob);
	return;
	
}


int help(object me)
{
	write(@HELP
指令格式 :

        lured <誘餌>：在當前地點放置誘餌等待獵物出現。
                     注：一次只能放一個誘餌。
                     
HELP
    );
    return 1;
}
