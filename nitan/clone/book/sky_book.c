// skybook.c

#include <ansi.h>

inherit ITEM;
inherit F_AUTOLOAD;


void create()
{
        set_name(HIY"無字天書"NOR, ({"skybook","book"}) );
        set_weight(10);
        set("no_steal", 1);
        set("no_beg", 1);
        set("no_get", 1);
        set("no_drop","哇？天書都想丟掉,小心遭天譴。\n\n");
        set("long",@LONG
此乃當年仙人贈於"蛋生"的寶物,因為蛋生不識字,仙人施了法,
把天書變成了無字天書,呵呵!就是文盲也能讀懂,快看看(kan)吧！
LONG );
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "本");
                set("material", "unknow");
        }
}

void init()
{
        add_action( "kan_book", "kanbook" );
        add_action( "bigu_eat", "bigu" );
        add_action( "cloud_goto", "cloud");
}

int query_autoload()
{
        return 1;
}

//介紹
int kan_book()
{
        object me;
        me=this_player();
        if (!present(this_object(), this_player()))
                return 0;

        tell_object(me,
    "法訣                    功能

辟穀(bigu)        三天三夜不吃不喝\n

康復(body)        立馬恢復精神體力\n

筋斗雲(cloud)     到想去的地方\n");
        return 1;
}

// 辟穀

int bigu_eat()
{
        object  ob, me;
        int             fw;

        ob = this_object();
        me = this_player();

        if (!present(this_object(), this_player()))
                return 0;

        if( !me->query_condition("f_condi") )
        {
                write(HIY"你口中唸唸有詞,那咦咪哞嘻...\n"NOR);
                tell_object(me, "你只覺神清氣爽,可以不吃飯了...\n" );

                fw = (int)me->max_food_capacity();
                set("food", fw, me);
                fw = (int)me->max_water_capacity();
                set("water", fw, me);

                write("三天三夜也不會餓了！\n\n");
                me->apply_condition("f_condi", 5);
                set("eated", "xixi", ob);
        }
        else
        {

                tell_object(me, "Ou。。你打了個飽嗝。。。Ou...Ou...\n" );

                fw = (int)me->max_food_capacity();
                set("food", fw, me);
                fw = (int)me->max_water_capacity();
                set("water", fw, me);
        }

        return 1;
}
// 筋斗雲

int cloud_goto(string arg)
{
        string home;
        object mme;
        int goto_inventory = 0;
        object obj;
        string msg;
        mme=this_player();
        if (!present(this_object(), this_player()))
                return 0;

        if( !arg ) return notify_fail("你要去哪裏？\n");

        if( sscanf(arg, "-i %s", arg) ) goto_inventory = 1;

        if( !arg ) return notify_fail("你要去哪裏？\n");

        obj = find_player(arg);
        if(!obj) obj = find_living(arg);
        if(!obj || !mme->visible(obj)) {
                arg=resolve_path(query("cwd", mme),arg);
                if( !sscanf(arg, "%*s.c") ) arg += ".c";
                if( !(obj = find_object(arg)) ) {
                        if( file_size(arg)>=0 )
                                return mme->move(arg);
                        return notify_fail("沒有這個玩家、生物、或地方。\n");
                }
        }

        if(!goto_inventory && environment(obj))
                obj = environment(obj);

        if( !obj ) return notify_fail("這個物件沒有環境可以 goto。\n");
        tell_object(mme,HIM"你一個筋斗竄向空中,只見眼前紅雲飛過,耳邊風呼呼作響 .
.\n\n"NOR);
        tell_object(mme,"哇喔,好痛快,好爽,爽歪歪!\n\n");
        mme->move(obj);

        tell_object(mme,"你駕着雲緩緩下降,叭嘰一聲,嘿!安全着陸...\n");
        return 1;
}
// 恢復
int body_recover()
{
    object mme;
    mme=this_player();
    set("jing",query("max_jing",  mme), mme);
    set("eff_jing",query("max_jing",  mme), mme);
    set("qi",query("max_qi",  mme), mme);
    set("eff_qi",query("max_qi",  mme), mme);
    set("neili",query("max_neili",  mme), mme);
    tell_object(mme,"哇喔,太好了,你覺得全身都是力量!\n");
    return 1;
}
void owner_is_killed() {

        write(HIY"只見眼前金光一閃...好像是.....\n"NOR);
        destruct(this_object());
}