inherit ROOM;

protected int nut = 3;
protected string ll = "這裏是一片低矮的灌木叢，空氣中有一種淡淡的幽香，身臨
空谷，聞着淡淡的芬芳之氣，讓人心曠神怡。";

string query_long();
string query_item_desc();

string query_long()
{
        if(nut <= 0)
                return ll+"\n";
        return ll+"叢中還結着幾顆棕\n色的[小果子]。\n";
}

string query_item_desc()
{
        if(nut > 0)
                return "這是一顆小指甲蓋大的棕色果子，可愛
的樣子只想讓人摘(pick)下來看看。\n";

        return 0;
}

void reset()
{
        if(nut < 3)
                nut = 3;
        ::reset();
}

void init()
{
        add_action("do_pick", "pick");
}

int do_pick(string arg)
{
        object ob, me = this_player();
        mapping q;

        if(arg != "果子" && arg != "小果子")
                return notify_fail("你要摘什麼？\n");

        if(nut <= 0)
                return notify_fail(sprintf("這裏沒有%s。\n", arg));

        if( !mapp(q=query("quest/yaowang_quest", me)) || (q["name"] != "海松子") || q["get_nut"] )
                return notify_fail("你沒小心被灌木上的小刺紮了一下，疼得趕緊縮回了手。\n");

        nut--;
        message_vision("$N小心翼翼的摘下了一顆小果子。\n", me);

        ob = new(__DIR__"obj/nut");

        if(!ob->move(me) && !ob->move(this_object()))
                destruct(ob);

        q["get_nut"] = 1;
        return 1;
}
