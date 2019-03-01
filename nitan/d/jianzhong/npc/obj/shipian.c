#include <ansi.h>
inherit ITEM;
int do_study(string arg);
void init()
{
        add_action("do_study","yanxi");
}
void create()
{
        set_name(HIC"長石片"NOR, ({ "chang shipian", "stone", "shipian" }) );
        set_weight(5000);
        set("unit", "塊");
        set("long",HIC@LONG
一塊普普通通的長條石片，上面有些細細的紋路，看不出什麼特別之處。
LONG
NOR
);
        set("value", 1);
        set("material", "stone");
        setup();
}
int do_study(string arg)
{
        object me = this_player();
        int dugulevel = me->query_skill("dugu-jiujian-sword",1);
        if ( (arg != "stone") && (arg != "shipian") && (arg != "chang shipian") )
                return notify_fail("你要學什麼？\n");
        if ((dugulevel >= 150) && (dugulevel <= 250) )
        {
               if( query("combat_exp", me)<dugulevel*dugulevel*dugulevel/10 )
                        return notify_fail("你只覺得石頭的紋理暗合「獨孤九劍」的劍意，可是就是理不出\n頭緒，看來是實戰經驗不夠。\n");
               if( query("jing", me)<25 )
                        return notify_fail("你現在過于疲倦，無法專心下來研讀新知。\n");
                me->receive_damage("jing", 25);
                me->improve_skill("dugu-jiujian-sword",(query("int", me))*(query("combat_exp", me)/20000));
                message("vision","你拿出長石條仔細研究，竟從石條的紋理上領悟出「獨孤九劍」\n的劍意，「獨孤九劍」大有長進。\n",me);
                message("vision",query("name", me)+"仔細研讀一塊石片。\n",environment(me),me);
                return 1;
        }
        return notify_fail("你對著石頭看來看去，沒看出什麼道理出來。\n");
}