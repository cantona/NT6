// underlt.c
// 擂台下面

inherit ROOM;

#define LEITAI          __DIR__ "leitai"

void init()
{
        add_action("do_pass", "pass");
}

void init_here()
{
}

int valid_leave(object me, string dir)
{
        object ob;
        string dest;

        dest = query("exits/" + dir);
        if (! stringp(dest))
                return ::valid_leave(me, dir);

        ob = find_object(dest);
        if (! objectp(ob) || wizardp(me))
                return ::valid_leave(me, dir);

        if (ob->refuse(me))
                return notify_fail("你湊什麼熱鬧，現在不是你上去的時候。\n");

        return ::valid_leave(me, dir);
}

int do_pass(string arg)
{
        object me;
        object ob;
        object ob_leitai;

        me = this_player();
        if (! wizardp(me))
                return notify_fail("你不是巫師，沒有資格讓人家上去。\n");

        if (! arg ||
            ! objectp(ob = present(arg, this_object())))
                return notify_fail("你想讓誰上去？\n");

        if (ob == me)
                return notify_fail("你就不會自己走上去？\n");

        if (wizardp(ob))
                return notify_fail("人家自己想上去自己會上去，不勞你費心。\n");

        if (! ob->is_character())
                return notify_fail("你是不是大腦進了水？\n");

        if (! userp(ob))
                return notify_fail("你捅了捅了" + ob->name() + "，不過人家沒動。\n");

        if (! living(ob))
                return notify_fail("好歹你得弄醒人家吧？\n");

        ob_leitai = find_object(LEITAI);
        if (! objectp(ob_leitai))
                ob_leitai = load_object(LEITAI);
        if (! objectp(ob_leitai))
                return notify_fail("擂台在哪裡？\n");

        message_vision("$N點點頭，對$n道：“你上去吧。”\n"
                       "只見$n摩拳擦掌，踴躍奔上台去。\n",
                       me, ob);
        message("vision", "只見" + ob->name() + "躍上台來，矯健之極。\n",
                ob_leitai);
        ob->move(ob_leitai);
        return 1;
}
