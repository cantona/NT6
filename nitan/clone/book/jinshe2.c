// jinshe2.c 

inherit ITEM;
inherit F_UNIQUE;
#include <ansi.h>; 
void setup()
{}
void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
}
void create()
{
        set_name(YEL"「金蛇祕芨」"NOR"中冊", ({ "jinshe book2","book2", }));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_drop", "這樣東西不能離開你。\n");
                set("no_get", "這樣東西不能離開那兒。\n");
                set("no_put", "這樣東西不能放在那兒。\n");
                set("long",
        "這是一本用薄紙寫成的書。上書：「金蛇祕芨」。\n"
        "書皮泛黃，看來已經保存很久了。\n", );
        }
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        mapping skill;
        int pxlevel; 
        int neili_lost;

        if (!(arg=="jinshe book2" || arg == "book2"))
        return 0;
        if (!present(this_object(), this_player()))
                return 0;
        if( query("pigging", where)){
                write("你還是專心拱豬吧！\n");
                return 1;
        }
        if (me->is_busy()) {
                write("你現在正忙着呢。\n");
                return 1;
        }
        if( me->is_fighting() ) {
                write("你無法在戰鬥中專心下來研讀新知！\n");
                return 1;
        }
        if (!id(arg)) {        
                write("你要讀什麼？\n");
                return 1;
        }
        if( !me->query_skill("literate", 1) ){
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }
        message("vision", me->name() + "正專心地研讀金蛇密芨。\n", environment(me), me);
        if( query("jing", me)<25){
                write("你現在過於疲倦，無法專心下來研讀新知。\n");
                return 1;
        }
        neili_lost = 5;
        if( query("neili", me)<neili_lost){
                write("你內力不夠，無法鑽研這麼高深的武功。\n");
                return 1;
        }
        pxlevel = me->query_skill("jinshe-zhui", 1);
        if( query("combat_exp", me)<pxlevel*pxlevel*pxlevel/10){
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }
        if( me->query_skill("jinshe-zhui", 1) > 199){
                write("你研讀了一會兒，但是發現上面所説的對你而言都太淺了，沒有學到任何東西。\n");
                return 1;
        }
        me->receive_damage("jing", 15);
        set("neili",query("neili",  me)-neili_lost, me);
        me->improve_skill("jinshe-zhui", (int)me->query_skill("literate", 1)/3+1);
        write("你研讀金蛇密芨，頗有心得。\n");
        return 1;
}
