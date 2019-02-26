// goto.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int goto_inventory = 0;
        object obj;
        object env;
        string msg;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! arg) return notify_fail("你要去什麼地方？\n");

        if (sscanf(arg, "-i %s", arg)) goto_inventory = 1;

        if (! arg) return notify_fail("你要去哪裏？\n");

        obj = find_player(arg);
        if (! obj) obj = MESSAGE_D->find_user(arg);
        if (! obj) obj = find_living(arg);
        if (! obj || ! me->visible(obj))
        {
                arg = resolve_path(query("cwd", me), arg);
                if (! sscanf(arg, "%*s.c") ) arg += ".c";
                if (! (obj = find_object(arg)))
                {
                        if (file_size(arg)>=0)
                                return me->move(arg);
                        return notify_fail("沒有這個玩家、生物、或地方。\n");
                }
        }

        if (! goto_inventory)
        {
                if (environment(obj))
                        obj = environment(obj);
                else
                {
                        if (obj->is_character())
                                // unless you goto a inventory, or you
                                // can not enter a character
                                obj = 0;
                }
        }

        if (! obj) return notify_fail("這個物件沒有環境可以 goto。\n");

        /*
        if (wiz_level(obj) > wiz_level(me))
                return notify_fail("你找死啊。\n");
        */

        if ((env = environment(me)) == obj)
                return notify_fail("你在原地亂蹦什麼？\n");

        if (obj == me)
                return notify_fail("好厲害！你想鑽到自己身體裏面？\n");

        if( query("gender", me) == "女性" )
                tell_object(me, HIG "你化作清風而去。\n" NOR);
        else
                tell_object(me, HIY "你化作長虹而去。\n" NOR);

        if( env && !query("env/invisible", me) )
        {
                if( !stringp(msg=query("env/msg_out", me)) )
                        msg = "只見一陣煙霧過後，$N的身影已經不見了。";

                msg = replace_string(msg, "$N", me->name() + HIM);
                       message("vision", HIM + msg + "\n" NOR, env, ({ me, env }));
        }

        me->set_magic_move();
        if (! me->move(obj))
        {
                msg = HIM "你的遁術失敗了。\n" NOR;
                tell_object(me, msg);
                message("vision", HIM "突然" + me->name() + "一個跟頭"
                                  "摔倒在地上。\n" NOR, obj, ({ me }));
                return 1;
        }
        else
                msg = HIM "你到了地方，落下遁光，收住身形。\n" NOR;

        if (environment(me) != obj)
                return 1;

        tell_object(me, msg);

        if( !query("env/invisible", me) )
        {
                if( !stringp(msg=query("env/msg_in", me)) )
                        msg = "$N的身影突然出現在一陣煙霧之中。";
                msg = replace_string(msg, "$N", me->name());
                       message("vision", HIM + msg + "\n" NOR, obj, ({ me, obj }));
        }

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : goto [-i] <目標>

這個指令會將你傳送到指定的目標. 目標可以是一個living 或房間
的檔名. 如果目標是living , 你會被移到跟那個人同樣的環境.
如果有加上 -i 參數且目標是 living, 則你會被移到該 living 的
的 inventory 中.

HELP );
        return 1;
}