// id.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object obj, *inv;
        string *id;
        string cname;
        string name;
        int i, j;
        int l = 20;

        if (! arg)
        {
                inv = all_inventory(me);
                if (! sizeof(inv))
                        return notify_fail("你身上沒有任何東西。\n");
                write("你身上攜帶物品的別稱如下(右方)：\n");
                for(i = 0; i < sizeof(inv); i++)
                {
                        if (! me->visible(inv[i])) continue;
                        name = inv[i]->name();
#ifndef LONELY_IMPROVED
                        l = 20 + strlen(name) - strlen(filter_color(name));
#endif
                        write(sprintf("%-" + sprintf("%d", l) + "s = %s\n", name,
                                implode(inv[i]->parse_command_id_list(), "、")));
                }
                return 1;
        }

        if (arg == "here" || sscanf(arg, "here for %s", cname))
        {
                inv = all_inventory(environment(me));

                if (cname)
                        inv = filter_array(inv, (: $1->name() == $(cname) :));

                if (! sizeof(inv))
                        return notify_fail("這裏沒有任何東西。\n");

                write("在這個房間中, 生物及物品的(英文)名稱如下：\n");
                for(i = 0; i < sizeof(inv); i++)
                {
                        if (! me->visible(inv[i])) continue;
                        name = inv[i]->name();
#ifndef LONELY_IMPROVED
                        l = 20 + strlen(name) - strlen(filter_color(name));
#endif
                        write(sprintf("%-" + sprintf("%d", l) + "s = %s\n", name,
                                implode(inv[i]->parse_command_id_list(), "、")));
                }
                return 1;
        }
}

int help(object me)
{
        write(@HELP
指令格式 : id [here [for <中文名字>]]
 
這個指令可以讓你知道物品的英文名稱及名字. 只打 id 會顯示
你身上所攜帶物品的名稱. 'id here' 則顯示所有跟你在同一個
環境裏的物件名稱.
 
HELP );
        return 1;
}