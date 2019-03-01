// xiakedao 石室

int do_study(string arg)
{
        object me;
        int lvl;

        if (arg != "wall")
                return notify_fail("你想研究什麼？\n");

        me = this_player();
        if( query("combat_exp", me)<500000 )
        {
                write("你看了半天，只恨自己實戰經驗太淺薄，無法領悟上面的高深知識。\n");
                return 1;
        }

        if (me->is_busy())
        {
                write("你現在正忙，沒空研究上面的詩句。\n");
                return 1;
        }

        me->receive_damage("jing", 15);
        me->start_busy(1);

        lvl = me->query_skill("literate", 1);
        if (lvl >= 200)
                write("你看了半天，覺得這首詩寫的很好，不過似乎沒什麼特別之處。\n");
        else
        if (lvl >= 100)
                write("你覺得這上面的詩大有寓意，不由的盡心苦思。\n");
        else
        if (lvl >= 1)
                write("你心中暗想：這定是前輩高手留下的秘籍，這些詞句可要好好分析。\n");
        else
        if (random(2))
        {
                write("你望著上面的筆劃，想起所修習的武功來，不禁漸漸有所體會。\n");
                if( query("experience", me)<me->query_experience_limit() )
                        addn("experience", 1, me);
        } else
                write("你潛心琢磨上面的筆劃，全然沒有想它是什麼含義。\n");

        return 1;
}

void init()
{
        add_action("do_study", "think");
        add_action("do_study", "study");
}
