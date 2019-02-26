// xisuijing.c 洗髓經

inherit ITEM;
#include <ansi.h>
int do_study(string);
string* skill = ({
        "whip",
        "finger",
        "hand",
        "cuff",
        "claw",
        "strike",
});
void create()
{
        set_name(YEL"洗髓經"NOR, ({ "xisuijing" }));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "卷");
                set("long","這本破紙筒就是少林最高武學典籍，是達摩老祖面壁九年與易筋經一起\n參悟出來的絕世典籍。\n");
                set("value", 5000);
                set("material", "paper");
        }
}

void init()
{
        add_action("do_study","canwu");
}

int do_study(string arg)
{
        object where;
        object ob = this_object();
        object me = this_player();
        int myskill, cost, i, exp;

        cost=50;
        where = environment(me);
        if (!arg || !objectp(ob = present(arg, me)))
                return notify_fail("你要參悟什麼？\n");
        if( query("jing", me)<25 )
        {
                write("你現在過於疲倦，無法專心下來研讀新知。\n");
                return 1;
        }
        if( query("short", where) != "達摩院二樓" )
                return notify_fail("洗髓經只能在達摩院裏參悟！\n");
        if (!me->query_skill("literate",1)||me->query_skill("literate",1)<100)
        {
                write("你把紙筒翻來翻去，就是什麼都讀不懂。\n");                
                return 1;
        }
        if (!me->query_skill("yijinjing",1)||me->query_skill("yijinjing",1)<100)
        {
                write("也許是沒有融會貫通易筋經，你覺得這洗髓經莫名其妙。\n");
                return 1;
        }
        if( query("kar", me)<25 )
        {
                write("你把紙筒翻來翻去，看來你與這絕世典籍無緣。\n");                
                return 1;
        }  
        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");
        if (me->is_fighting() )
                return notify_fail("你無法在戰鬥中專心下來研讀新知！\n");
        exp=query("combat_exp", me);
        if (exp < 300000)
        {
                write("你的實戰經驗不足，不能參悟洗髓經。\n");
                return 1;
        }
        if( query("jing", me)>cost )
        {
                for ( i=sizeof(skill); i>0; i-- )
                {
                        myskill=me->query_skill(skill[i-1], 1);
                        if ( myskill<180 && myskill>1 && myskill*myskill*myskill/10<exp)
                        {
me->improve_skill(skill[i-1],(me->query_skill("literate",1)+query("int", me))/2);
                        }
                }
                printf("你參悟洗髓經上的經文，似乎有點心得。\n");
                me->receive_damage("jing", cost );
        }
        else
        {
                cost=query("jing", me);
                write("你現在過於疲倦，無法專心下來參悟洗髓經。\n");
        }
        return 1;
}