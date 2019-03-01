// cook.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string  skill;
        string *menu_list;
        mapping menu;
        string  msg;
        object  cailiao;
        object  ob;

        skill = me->query_skill_mapped("cooking");
        if (! skill)
                return notify_fail("請先激發你要使用的菜藝。\n");

        menu = SKILL_D(skill)->query_menu(me);
        if (! arg)
        {
                if (! menu || sizeof(menu) < 1)
                {
                        write("你不會利用" + to_chinese(skill) +
                        "做任何菜肴。\n");
                        return 1;
                }

                msg = "你現在使用" + to_chinese(skill) + "會做" +
                      implode(keys(menu), "、") + "這些菜肴。";
                write(sort_string(msg, 64));
                return 1;
        }

        if (! objectp(cailiao = present("cai liao", me)) ||
            cailiao->query_amount() < 1)
        {
                write("你現在手頭沒有菜料，沒法做菜。\n");
                return 1;
        }

        menu_list = 0;
        if (undefinedp(menu[arg]) &&
            ! sizeof(menu_list = filter_array(keys(menu),
                                        (: member_array($(arg), $(menu)[$1]) != -1 :))))
        {
                write("你現在還不知道怎麼做『" HIG + arg + NOR
                      "』這味菜。\n");
                return 1;
        }
        if (menu_list) arg = menu_list[0];

        if ((int)me->query_skill(skill, 1) < 50)
        {
                write("你這點" + to_chinese(skill) + "還是不要浪費菜料了。\n");
                return 1;
        }

        message_vision("$N卷起袖子，運用鍋鏟瓢盆、醬油茶"
                       "醋，精心調制出一份" + arg + "來。\n", me);
        cailiao->add_amount(-1);
        ob = new("/clone/food/dish");
        ob->set_name(arg, menu[arg] + ({ "dish" }));
        ob->set("long","一份由"+me->name(1)+"精心烹制的"+
                        ob->name() + "。\n");
        set("skill", skill, ob);
        set("level", me->query_skill(skill,1), ob);
        set("by",query("id",  me), ob);
        ob->move(me, 1);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : cook [<菜肴名稱>]

HELP );
        return 1;
}