// sanshi.c
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR"三屍腦神丹"NOR, ({"sanshinao shendan", "sanshi dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", 
"一粒火紅色的丹藥，看樣子不是尋常物品。你只可以乘別人人事不知時
喂(wei)給人家吃。\n");
                set("unit", "粒");
                set("value", 20000);
        }
        set("pour_type", "1");
        setup();
}

int init()
{
        add_action("do_wei", "wei");
}

int do_wei(string arg)
{
        object me = this_player(), ob = this_object(), who;

        if (!present(ob, me)) return 0;
        if( query("id", me) != query("owner", ob) )
                return notify_fail("這不是你練的丹，你喂也沒用。\n");
        if(!arg) return notify_fail("你要給誰喂三屍腦神丹？\n");
        if(!objectp(who = present(arg, environment(me))))
                return notify_fail("這裡沒有這個人。\n");
        if( living(who) && !query_temp("noliving", who) )
                return notify_fail("人家有知有覺的，誰肯吃你的臭藥？\n");
        message_vision("$N撬開$n的嘴，將"+query("name", ob)+"塞進$n嘴裡。\n",me,who);
        set("sanshi",query("id",  me), who);
        destruct(this_object());
        return 1;
}
