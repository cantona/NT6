//獨孤九劍劍譜(Lonely_sword_book)
// ls_book.c
// Date: Oct.6 1997 by That

#include <ansi.h>
inherit ITEM;
inherit F_AUTOLOAD;
int do_study(string);
int study(object me, string arg)
{
    object where = environment(me);
    object ob;
    int myskill, cost;

    cost=20;                                            //每讀一次耗20精
    myskill=me->query_skill("lonely-sword", 1);
    if (!arg || !objectp(ob = present(arg, me)))
        return notify_fail("你要讀什麼？\n");
    if (!me->query_skill("literate", 1)||me->query_skill("literate",1) < 100)
        return notify_fail("對照劍譜，你什麼都讀不懂。\n");
    if (me->is_busy())
        return notify_fail("你現在正忙着呢。\n");
    if (me->is_fighting() )
        return notify_fail("你無法在戰鬥中專心下來研讀新知！\n");
    if( query("combat_exp", me)<50000 )
        return notify_fail("你的實戰經驗不足，不能學獨孤九劍。\n");
    if (myskill>299)
        return notify_fail("你研讀了一會兒，發現上面所説的對你而言都太淺了。\n");
    if (myskill<75)
        return notify_fail("你讀了一會書,可是卻毫無收穫。\n");
    if( query("jing", me)>cost )
    {
       if( myskill*myskill*myskill/10>query("combat_exp", me) )
       {
          printf("也許是缺乏實戰經驗，你對獨孤九劍劍譜面所説的東西總是無法領會。\n");
       }
       else
       {
          printf("你研讀有關獨孤九劍劍譜上的技巧，似乎有點心得。\n");
          me->improve_skill("lonely-sword",me->query_skill("literate",1)+query("int", me));
       }
    }
    else
    {
       cost=query("jing", me);
       write("你現在過於疲倦，無法專心下來研讀新知。\n");
    }
    me->receive_damage("jing", cost );
    return 1;
}
void create()
{
        set_name(HIG"獨孤九劍劍譜"NOR, ({ "lonely_sword_book","ls_book" }));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "本");
                set("no_drop","這是當世孤本啊。如何能丟失？");
                set("no_put","這是當世孤本啊。如何能丟失？");
                set("no_get",1);
                set("no_steal",1);
                set("long","獨孤九劍劍法。你只能研習(yanxi)。\n");
                set("value", 1000);
                set("material", "paper");
                set("master_id","npc");
        }
}

void init()
{
        add_action("do_study","yanxi");
}

int do_study(string arg)
{
        object me,ob;
        me=this_player();
        ob=this_object();

        write("哇，真是千古獨步的劍法！");
        study(me,arg);
        return 1;
}

string query_autoload()
{
        object me;
        me = this_object();
        return query("master_id", me);
}
void autoload(string arg)
{
        set("master_id",arg);
}
void owner_is_killed()
{
        write(HIY"只見眼前金光一閃...好像是.....\n"NOR);
        destruct(this_object());
}
