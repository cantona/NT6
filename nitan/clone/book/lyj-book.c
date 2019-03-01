// lyj-book.c

inherit ITEM;

string* titles = ({
        "兩儀劍心得",
});

void create()
{
        set_name(titles[random(sizeof(titles))], ({ "shu", "book" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是昆侖派前人所總結的正兩儀劍法的秘籍。\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name": "liangyi-sword",     // name of the skill
                        "exp_required": 100000,      // minimum combat experience required
                        "jing_cost":    40,     // jing cost every time study this
                        "difficulty":   30,     // the base int to learn this skill
                        "max_skill":    180      // the maximum level you can learn
                ]) );
        }
}

void init()
{
        if(this_player()==environment() )
        {
                add_action("do_study", "study");
        }
}

int do_study(string arg)
{
        object me=this_player();

        if (arg != "shu" && arg!="book" && arg != "xinde" )
                return notify_fail("你要學什麼？\n");
        if (!present(this_object(), this_player()))
                return 0;
        if( query("jing", me)<30 )
                return notify_fail("你太累了，還是歇會再研究吧！\n");

        if ((int)me->query_skill("liangyi-sword", 1) > 100
                && (int)me->query_skill("liangyi-sword", 1) <= 180)
        {
                me->receive_damage("jing", 40);
                me->improve_skill("liangyi-sword", (query("int", me))/2+(me->query_skill("literate", 1))/5,1 );
                message_vision("$N苦心研究「兩儀劍心得」，思索良久，似乎有所領悟。\n",me);
                return 1;
        }

        return 1;
}
