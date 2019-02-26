#include <ansi.h>; 
inherit ITEM;

void create()
{
        set_name(HIW "「九陰真經」" NOR, ({ "jiuyin zhenjing", "jiuyin", "zhenjing", "jing"}));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", 1);
                set("long", HIW "\n這是一本用薄紙寫成的書，封皮上寫有「九陰真"
                            "經」四\n字。書皮泛黃，看來已經保存很久了。真經中"
                            "記載有催\n心掌、九陰白骨爪、大伏魔拳、銀龍鞭法、"
                            "易筋鍛骨和\n蛇行狸翻等絕技，你可以試着讀讀(read)"
                            "看。\n\n" NOR, );
        }
}

void init()
{
        add_action("do_du", "read");
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;

        string skill, book;
        int lv;

        if (! arg)
        {
                write("研讀九陰真經指令格式：read <技能> from <九陰真經>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", skill, book) != 2)
        {
                write("研讀九陰真經指令格式：read <技能> from <九陰真經>\n");
                return 1;
        }

        if (me->is_busy())
        {
                write("你現在正忙着呢。\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("你無法在戰鬥中專心下來研讀新知！\n");
                return 1;
        }

        if( query("no_fight", where )
            && query("doing", me) != "scheme" )
        {
                write("你無法在這裏靜下心來研讀真經。\n");
                return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }

        if (! id(book))
        {
                write("這裏沒有這本書。\n");
                return 1;
        }

        if (skill != "yijin-duangu" && skill != "易筋鍛骨"
           && skill != "shexing-lifan" && skill != "蛇行狸翻"
           && skill != "cuixin-zhang" && skill != "催心掌"
           && skill != "jiuyin-baiguzhao" && skill != "九陰白骨爪"
           && skill != "dafumo-quan" && skill != "大伏魔拳"
           && skill != "yinlong-bian" && skill != "銀龍鞭法")
        {
                write("真經上並沒有記載你打算研究的內容。\n" NOR);
                return 1;
        }

        if (me->query_skill("sanscrit", 1) < 200)
        {
                write("你的梵文水平太低，無法看懂真經裏所記載的內容。\n");        
                return 1;
        }

        if( count_lt(query("combat_exp", me),1000000) )
        {
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }

        if( query("jing", me)<100
            || query("qi", me)<100
            || query("neili", me)<200 )
        {
                write("你現在過於疲倦，無法專心下來研讀新知。\n");
                return 1;
        }

        if (skill == "yijin-duangu" || skill == "易筋鍛骨")
                skill = "yijin-duangu";
        else

        if (skill == "shexing-lifan" || skill == "蛇行狸翻")
                skill = "shexing-lifan";
        else

        if (skill == "cuixin-zhang" || skill == "催心掌")
                skill = "cuixin-zhang";
        else

        if (skill == "jiuyin-baiguzhao" || skill == "九陰白骨爪")
                skill = "jiuyin-baiguzhao";
        else

        if (skill == "dafumo-quan" || skill == "大伏魔拳")
                skill = "dafumo-quan";
        else

        if (skill == "yinlong-bian" || skill == "銀龍鞭法")
                skill = "yinlong-bian";

        if (! SKILL_D(skill)->valid_learn(me))
                       return 0;

        if (! me->can_improve_skill(skill))
               {
                       write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                       return 1;
               }

        lv = me->query_skill(skill, 1);

        if (lv >= 180)
        {
                write("你研讀了一會兒，但是發現上面所説的對你而言都太淺了。\n");
                return 1;
        }

        // 天賦聰穎增加研讀速度
        if( query("special_skill/clever", me) )
                me->improve_skill(skill,query("int", me)+5);
        else
                me->improve_skill(skill,query("int", me)+1);

        me->receive_damage("qi", random(50) + 30);
        me->receive_damage("jing", random(50) + 30);
        addn("neili", -lv, me);
        message("vision", me->name() + "正專心地研讀九陰真經。\n",
                          environment(me), me);
        write("你仔細研讀九陰真經，頗有心得。\n");
        return 1;
}