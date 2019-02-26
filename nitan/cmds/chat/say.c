// chat command: say.c

#include <ansi.h>
#include <net/messaged.h>

inherit F_CLEAN_UP;

int main(object me, mapping info)
{
        object env;
        string msg;

        if (! objectp(env = environment(me)) || env == find_object(VOID_OB))
                return MESSAGE_D->error_msg("你現在在縹緲的虛空中，沒"
                                            "有人聽得到你説的話。\n");

        if (! stringp(msg = info[MESSAGE]))
                return MESSAGE_D->error_msg("你要説什麼話？\n");

        message_vision(CYN "$N" CYN "説道：" + msg + "\n" NOR, me);
        return 1;
}
