#include <ansi.h>; 
inherit ITEM;

void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
}

int query_autoload() { return 1; }
void create()
{
        set_name(CYN"武穆遺書"NOR, ({ "wumu yishu", "book", "yishu"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", "這樣東西不能賣。\n");
                set("long", "一本薄薄的絹帛，乃抗金大將岳飛灌注畢生心血所編撰而成。\n", );
        }
        setup();
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        mapping skill;
        int pxlevel, arlevel; 

        if (!(arg=="wumu yishu" || arg == "book" || arg == "yishu" ))
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
        message("vision", me->name() + "正專心地研讀武穆遺書。\n", environment(me), me);
        if( query("jing", me)<80){
                write("你現在過于疲倦，無法專心下來研讀新知。\n");
                return 1;
        }
        if( query("qi", me)<80){
                write("你現在過于疲倦，無法專心下來研讀新知。\n");
                return 1;
        }
        pxlevel = me->query_skill("craft-cognize", 1);
        arlevel = me->query_skill("array-cognize", 1);
        if( query("combat_exp", me)<100000){
                write("你的實戰經驗不足，無法看懂武穆遺書中的內容。\n");
                return 1;
        }
        if( query("combat_exp", me)<pxlevel*pxlevel/10*pxlevel){
                write("你的實戰經驗不足，無法看懂武穆遺書中的內容。\n");
                return 1;
        }
        if( me->query_skill("craft-cognize", 1) > 399 &&
            me->query_skill("array-cognize", 1) > 399){
                write("你發現對于武穆遺書上的兵法和陣法要詣已經了然于胸，完全掌握了。\n");
                return 1;
        }
        me->receive_damage("qi", 50);
        me->receive_damage("jing", 50);
        if( pxlevel < 400 )
                me->improve_skill("craft-cognize", (int)me->query_skill("literate", 1)/5+1);
        if( arlevel < 400 )
                me->improve_skill("array-cognize", (int)me->query_skill("literate", 1)/5+1);
        write("你仔細研讀武穆遺書中兵法和陣法，頗有心得。\n");
        return 1;
}
