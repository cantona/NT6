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
        set_name(CYN "降龍十八掌秘笈" NOR, ({ "xianglong miji", "book", "miji"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", 1);
                set("long",
        "乃大俠郭靖所編寫，記載了丐幫的絕學降龍十八掌。\n"
        "為武林至高無上的武學。\n", );
        }
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        mapping skill;
        int pxlevel; 

        if (!(arg=="xianglong miji" || arg == "book" || arg == "miji" ))
        return 0;
        if (me->is_busy()) {
                write("你現在正忙著呢。\n");
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

        message("vision", me->name() + "正專心地研讀降龍十八掌秘笈。\n", environment(me), me);
        if( query("jing", me)<80){
                write("你現在過于疲倦，無法專心下來研讀新知。\n");
                return 1;
        }
        if( query("qi", me)<80){
                write("你現在過于疲倦，無法專心下來研讀新知。\n");
                return 1;
        }
        pxlevel = me->query_skill("dragon-strike", 1);
        if( query("combat_exp", me)<100000){
                write("你的實戰經驗不足，無法看懂降龍十八掌秘笈中的內容。\n");
                return 1;
        }
        if( query("combat_exp", me)<pxlevel*pxlevel/10*pxlevel){
                write("你的實戰經驗不足，無法看懂降龍十八掌秘笈中的內容。\n");
                return 1;
        }
        if( me->query_skill("dragon-strike", 1) > 249){
                write("你研讀了一會兒，但是發現秘笈中的內容對你而言都太淺了，沒有學到任何東西。\n");
                return 1;
        }
        if( me->query_skill("dragon-strike", 1) < 80){
                write("你研讀了一會兒，但是發現秘笈中的內容深奧無比，沒有學到任何東西。\n");
                return 1;
        }
        me->receive_damage("qi", 50);
        me->receive_damage("jing", 50);
        me->improve_skill("dragon-strike", (int)me->query_skill("literate", 1)/5+1);
        write("你仔細研讀降龍十八掌秘笈，頗有心得。\n");
        return 1;
}
