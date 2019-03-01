// enterworld.c

#include <ansi.h>
#include <net/messaged.h>

inherit F_CLEAN_UP;

string *valid_entry = ({ "/d/city/kedian" });

int main(object me, mapping info)
{
        object env;
        string startroom;

        if (objectp(env = environment(me)) &&
            env != find_object(VOID_OB))
                return MESSAGE_D->error_msg("你現在已經進入到世界中了。\n");

        startroom = info[ARG];
        if (! stringp(startroom) || member_array(startroom, valid_entry) == -1)
                startroom = "/d/city/kedian";

        if (! me->move(startroom))
                return MESSAGE_D->error_msg("系統出現故障，無法讓你進入世界。\n");

        message("vision", HIC "空氣中悄然彌漫出一股青煙，漸漸的凝成了" +
               me->name() + HIC "的樣子。\n" NOR, environment(me), ({ me }));

        return 1;
}
