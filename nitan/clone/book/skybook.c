// skybook.c

#include <ansi.h>
inherit ITEM;
inherit F_AUTOLOAD;
void create()
{
        set_name(HIB"無字天書"NOR, ({"skybook","book"}) );
        set_weight(10);
        set("no_steal", 1);
        set("no_beg", 1);
//        set("no_get", 1);
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
        if (!present(this_object(), this_player())) return 0;

        tell_object(me,
    "法訣                    功能
筋斗雲(cloud)         到想去的地方\n");
        return 1;
}
// 筋斗雲

int cloud_goto(string arg)
{
        object obj,mme=this_player();
        object* ob;
        int i;
        ob = users();

        if (!present(this_object(), this_player()))
                return 0;

        for ( i=sizeof(ob); i>0; i-- )
        {
                if ((query("id", ob[i-1])==arg) && ( !wizardp(ob[i-1])))
                {
                        obj = environment(ob[i-1]);
                        this_player()->move(obj);
                        tell_object(mme,HIM"你一個筋斗竄向空中,只見眼前紅雲飛過,耳邊風呼呼作響 ..\n\n"NOR);
                        tell_object(mme,"哇喔,好痛快,好爽,爽歪歪!\n\n");
                        mme->move(obj);
                        tell_object(mme,"你駕着雲緩緩下降,叭嘰一聲,嘿!安全着陸...\n");
                        return 1;
                }
        }
        return 0;
}

void owner_is_killed()
{
        write(HIY"只見眼前金光一閃...好像是.....\n"NOR);
        destruct(this_object());
}
