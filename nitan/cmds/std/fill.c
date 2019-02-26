// drink.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        mapping my;
        object ob;
        function f;

        if (! arg)
                return notify_fail("你要往什麼東西里面灌？\n");

        if( !query("resource/water", environment(me)) )
                return notify_fail("這裏沒有地方可以裝水。\n");

        if (me->is_busy())
                return notify_fail("你上一個動作還沒有完成。\n");

        if (me->is_fighting())
                return notify_fail("你正忙着打架，沒工夫裝水！\n");

        if (! objectp(ob = present(arg, me)))
                return notify_fail("你身上沒有這樣東西。\n");

        if( !mapp(my=query("liquid", ob)) )
                return notify_fail("這個容器裝不了水。\n");

        if (my["remaining"] && my["name"] != "清水")
                message_vision("$N將" + ob->name() + "裏剩下的" +
                               my["name"] + "倒掉。\n", me);

        message_vision("$N將" + ob->name() + "裝滿清水。\n", me);

        my["type"] = "water";
        my["name"] = "清水";
        my["remaining"]=query("max_liquid", ob);
        my["drink_func"] = 0;

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : fill <容器>
 
這個指令可以讓有水的地方把容器灌滿清水。
 
HELP
    );
    return 1;
}
 