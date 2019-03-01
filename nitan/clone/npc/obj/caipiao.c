//caipiao.c
//By haiyan

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "彩票" NOR, ({ "cai piao", "piao", "lottery" }));
        set_weight(10);
        set("long", @LONG
這是一張“泥潭博彩”有獎福利彩票，可以使用tianxie指令來填寫彩票。
LONG);

        set("unit", "張");
        set("value", 0);
        set("lottery", 1);

        setup();
}

void init()
{
        add_action("do_tianxie", "tianxie");
}

int do_tianxie(string arg)
{
        object me = this_player();
        string cost;
        string *numbers;

        if (! arg || ! sscanf(arg, "%s", cost))
                return notify_fail("指令格式：tianxie <五位號碼>。\n");

        if (strlen(cost) != 5 || cost[0..0] < "0" || cost[0..0] > "9" ||
            cost[1..1] < "0" || cost[1..1] > "9" ||
            cost[2..2] < "0" || cost[2..2] > "9" ||
            cost[3..3] < "0" || cost[3..3] > "9" ||
            cost[4..4] < "0" || cost[4..4] > "9")
                return notify_fail("你填的號碼有誤！\n");

        numbers = query("caipiao/numbers");
        if (! numbers)    numbers = ({});

        if (sizeof(numbers) >= 10)
                return notify_fail("這張彩票你已經填滿了。\n");

        numbers += ({ cost });
        tell_object(me, sprintf("你在彩票第%s欄填上了%s幾個數字。\n", 
                    chinese_number(sizeof(numbers)), cost));
        set("caipiao/numbers", numbers);
        return 1;
}
