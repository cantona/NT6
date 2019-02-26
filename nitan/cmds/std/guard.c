// guard.c

inherit F_CLEAN_UP;

mapping default_dirs = ([
        "north":        "北",
        "south":        "南",
        "east":         "東",
        "west":         "西",
        "northup":      "北邊",
        "southup":      "南邊",
        "eastup":       "東邊",
        "westup":       "西邊",
        "northdown":    "北邊",
        "southdown":    "南邊",
        "eastdown":     "東邊",
        "westdown":     "西邊",
        "northeast":    "東北",
        "northwest":    "西北",
        "southeast":    "東南",
        "southwest":    "西南",
        "up":           "上",
        "down":         "下",
        "out":          "外",
        "in" :          "裏",
        "enter" :       "裏面",
]);

int main(object me, string arg)
{
        string dir;
        object ob, *guards;
        object env;
        mixed old_target;

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你現在沒有辦法分心去做這類事！\n");

        old_target=query_temp("guardfor", me);

        if (! arg || arg == "")
        {
                if (objectp(old_target))
                        if (living(old_target))
                                write("你正在守護著" + old_target->name() +
                                      "。\n");
                        else
                                write("你正守在" + old_target->name() +
                                      "一旁，防止別人拿走。\n");
                else
                if (stringp(old_target))
                        write("你正守住往" + default_dirs[old_target] +
                              "的方向，不準任何人離開。\n");
                else
                             return notify_fail("指令格式：guard <生物> | "
                                           "<物品> | <方向>\n");

                return 1;
        }

        env = environment(me);
        ob = present(arg, env);

        if (ob)
        {
                if (ob == me)
                        return notify_fail("守衞自己？不用説你也會"
                                           "做，對吧。\n");
                if( query("jing", me)*100/query("max_jing", me)<60 )
                        return notify_fail("你現在無法集中精神守衞" + ob->name() + "。\n");
                set_temp("guardfor", ob, me);
        } else
        if( query("exits/"+arg, env) )
        {
                if ((base_name(env))[0..10]=="/data/room/")
                        return notify_fail("這裏是別人家裏，不准你撒野！\n");
                if( query("no_fight", env) )
                        return notify_fail("這裏不準戰鬥——也不準堵住別人去路！\n");
                if( query("max_room", env) )
                        return notify_fail("這裏是住宅區，不準堵住別人去路！\n");
                if( query("jing", me)*100/query("max_jing", me)<75 )
                        return notify_fail("你現在無法集中精神守衞這個方向。\n");
                set_temp("guardfor", arg, me);
        } else
        if (arg != "cancel")
                return notify_fail("你要守衞誰，什麼，或是哪個方向？\n");

        if (objectp(old_target))
        {
                if( arrayp(guards=query_temp("guarded", old_target)) )
                {
                        guards -= ({ me, 0 });
                        if (! sizeof(guards))
                        {
                                delete_temp("guarded", old_target);
                        } else
                                set_temp("guarded", guards, old_target);
                }
                if (interactive(old_target))
                        tell_object(old_target, me->name() +
                                    "不再保護你了。\n");
        } else
        if (stringp(old_target))
        {
                guards=query_temp("guarded/"+old_target, env);
                if (arrayp(guards))
                {
                        guards -= ({ me, 0 });
                        if (! sizeof(guards))
                        {
                                delete_temp("guarded/"+old_target, env);
                        } else
                                set_temp("guarded/"+old_target, guards, env);
                }
        }
        delete_temp("guardfor", me);

        if (arg=="cancel")
        {
                write("什麼也不用守了，真是好輕鬆。\n");
                return 1;
        }

        if (objectp(ob))
        {
                guards=query_temp("guarded", ob);
                if (! arrayp(guards))
                        guards = ({ me });
                else
                {
                        guards -= ({ 0 });
                        guards += ({ me });
                }
                set_temp("guarded", guards, ob);
                if (living(ob))
                        message_vision("$N開始保護$n。\n", me, ob);
                else
                        message_vision("$N站到地上的$n一旁守著，以"
                                       "免別人取走。\n", me, ob);
                set_temp("guardfor", ob, me);
        } else
        {
                guards=query_temp("guarded/"+arg, env);
                if (! arrayp(guards))
                        guards = ({ me });
                else
                {
                        guards -= ({ 0 });
                        guards += ({ me });
                }
                set_temp("guarded/"+arg, guards, env);
                message("vision", me->name() + "鬼鬼祟祟的望了望四周，"
                                  "不知道要幹什麼。\n", env, ({ me }));
                tell_object(me, "你開始守住往" + default_dirs[arg] +
                               "的方向不讓任何人通行。\n", me);
                set_temp("guardfor", arg, me);
        }

        return 1;
}

int help(object me)
{
        write(@TEXT
指令格式：guard [<某人>|<地上某物>|<某個出口>|cancel]

這個指令有三種作用方式，分別如後：

guard <某人>      保護<某人>，當他／她受到攻擊時，保護者會自
                  動加入戰鬥。

guard <地上某物>  守住放在地上的某件東西，防止別人來拿，只要
                  你還在這個房間，而且沒有忙著其他事，別人就
                  無法拿走這件東西。

guard <某個出口>  守住某個出口防止所有人從這個出口離開，可以
                  用來阻攔善於逃跑的敵人或攔路打劫做壞事，如
                  果你當時正忙，則不能阻擋別人。

guard cancel      取消先前的 guard 對象。

注意，只要你一移動，對物品和出口的守衞狀態就會解除，但是對人
物的保護狀態仍然有效，只要你到了保護對象的身邊仍然發揮作用。
另外，當你在守衞狀態的時候，會消耗精，如果精不夠了，則會自動
解除守衞狀態。
TEXT );
        return 1;
}