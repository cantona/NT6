// fake-tao.c 獼猴桃幹

#include <ansi.h>

inherit ITEM;
void init()
{
        object me = this_object();
        object who = this_player();
        object where = environment();
        if (!wizardp(this_player())) 
        {
        set("no_get","你手裡一鬆"+query("name", this_object())+"從指間滑落！\n");
        set("no_give","這麼珍貴的藥，哪能隨便給人？\n");
        set("no_drop","這麼寶貴的藥，扔了多可惜呀！\n");
        set("no_sell","凡人哪裡知道"+query("name", this_object())+"的價值？還是自己留著吧。\n");
        if( !query("my_owner", me) && interactive(who) )
        set("my_owner",query("id",  who), me);
   
        if (userp(where))
        {
                if( query("owned", me) )
                {
                        if( query("owned", me) != query("id", where) )
                        {
                                call_out("destruct_me",1,where,me);
                        }
                }
        else
        {
        set("owned",query("id",  where), me);
        }
        }
        call_out("destroy_me",120,where,me);
        }                                                            

}

void destruct_me(object where, object me)
{
        message_vision("千面怪鬼鬼祟祟地拿起$n撒腳就跑,快追!\n",where,me);
        destruct (me);
}
void create()
{
        set_name(HIY"珍貴藥材"NOR, ({"zhengui yaocai","yaocai"}));
        set_weight(20);
        if (clonep())
        set_default_object(__FILE__);
        else {
                set("unit", "株");
                set("long", "一株珍貴藥材，如果煉成丹藥有強身健體延年益壽的功效。\n");
                set("canoe",1); // 身份鑒定,防止假藥材
                set("value", 0);
                set("drug_type", "補品");
        } 
        setup();
}