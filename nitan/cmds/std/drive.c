// drive.c

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

mapping dirs = ([
        "n":    "north",
        "s":    "south",
        "e":    "east",
        "w":    "west",
        "nu":   "northup",
        "su":   "southup",
        "eu":   "eastup",
        "wu":   "westup",
        "nd":   "northdown",
        "sd":   "southdown",
        "ed":   "eastdown",
        "wd":   "westdown",
        "ne":   "northeast",
        "nw":   "northwest",
        "se":   "southeast",
        "sw":   "southwest",
        "u" :   "up",
        "d" :   "down",
        "enter" :   "enter",
        "out" :   "out",
]);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob;
        string cdir, rdir;
        string dir;
        object env;
        string msg_leave, msg_arrival;
        int lvl;
        int result;

        if (! arg)
                return notify_fail("你要趕什麼？\n");

        if (sscanf(arg, "%s %s", arg, dir) != 2)
                return notify_fail("你要往哪個方向趕？\n");

        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("這裏沒有這樣東西讓你趕啊！\n");

        notify_fail("你看清楚了，這不是能驅使的車輛！\n");
        if (! ob->can_drive_by(me))
                return 0;

        if (! undefinedp(dirs[dir]))
                dir = dirs[dir];
        else
        if (member_array(dir, values(dirs)) == -1)
                return notify_fail("你不能往這個方向趕車。\n");

        if (me->is_fighting())
                return notify_fail("你現在正在和人家動手，沒空趕車。\n");

        if (me->is_busy())
                return notify_fail("你上一個動作還沒有完成，先等等吧。\n");

        // 查看駕車技術
        lvl = me->query_skill("driving");
        if (random(lvl + 100) < 50)
        {
                message_vision("$N手忙腳亂的折騰了半天，可是" +
                               ob->name() + "一動不動。\n", me);
                me->start_busy(1);
                return 1;
        }

        env = environment(me);

        notify_fail("");
        result = GO_CMD->main(me, dir);
        if (environment(me) == env)
        {
                string fail;

                if (! result)
                {
                        fail = query_fail_msg();
                } else
                        fail = "";
                write(fail + "你現在沒法趕着" + ob->name() + "前進。\n");
                return 1;
        }
        ob->move(environment(me));

        if (random(lvl + 100) < 30)
                me->start_busy(1);

        if (me->can_improve_skill("driving"))
                me->improve_skill("driving", 1);

        cdir = GO_CMD->query_chinese_dir(dir);
        dir  = GO_CMD->query_reverse(dir);
        rdir = GO_CMD->query_chinese_dir(dir);
        switch (random(5))
        {
        case 0:
                msg_leave   = "$N一聲吆喝，趕着$n向" + cdir + "駛去。\n";
                msg_arrival = "只聽一聲吆喝，$N趕着$n從" + rdir + "駛來。\n";
                break;
        case 1:
                msg_leave   = "$N一言不發，只是趕着$n向" + cdir + "駛去。\n";
                msg_arrival = "只見$N悶頭悶腦的趕着$n從" + rdir + "駛了過來。\n";
                break;
        case 2:
                msg_leave   = "$N喝道：“讓開了！讓開了”，只見人和$n已經滾滾朝着" +
                              rdir + "去了。\n";
                msg_arrival = "遠遠的只聽一陣喝聲，緊接着就見$N趕着$n滾滾的從" +
                              rdir + "駛了過來。\n";
                break;
        case 3:
                msg_leave   = "$N抹了抹汗，繼續趕着$n往" + rdir + "去了。\n";
                msg_arrival = "只見$N一邊抹汗，一邊趕着$n從" +
                              rdir + "駛了過來。\n";
                break;
        default:
                msg_leave   = "只聽隆隆聲響，就見$N急衝衝的趕着$n奔" +
                              rdir + "去了。\n";
                msg_arrival = "只聽隆隆聲響，就見$N急衝衝的趕着$n從" +
                              rdir + "駛來。\n";
                break;
        }

        msg_leave = replace_string(msg_leave, "$N", me->name());
        msg_leave = replace_string(msg_leave, "$n", ob->name());
        msg_arrival = replace_string(msg_arrival, "$N", me->name());
        msg_arrival = replace_string(msg_arrival, "$n", ob->name());

        message("vision", msg_leave, env);
        message("vision", msg_arrival, environment(me), ({ me }));
        tell_object(me, "你趕着" + ob->name() +
                        "到了" + environment(me)->short() + "。\n");
        ob->set_owner(me);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : drive <車輛> <方向>

這個指令可以讓你向某個方向趕車，當然，這得是你的車才行。如果
你的駕車技術不是非常嫻熟，那麼可能不能自由的驅使，而且有可能
會帶來不必要的延遲。怎麼鍛鍊自己的駕車技術？熟能生巧嘛！

HELP );
    return 1;
}
