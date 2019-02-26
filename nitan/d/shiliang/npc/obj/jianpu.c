// Feb. 6, 1999 by Winder
inherit ITEM;
void setup()
{}
void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
}
void create()
{
        set_name("金蛇劍譜", ({ "jinshe jianpu", "jianpu"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這就是記載着金蛇郎君一生心血的金蛇劍譜。\n");
                set("value", 50000);
                set("material", "paper");
                set("no_drop", "這樣東西不能離開你。\n");
                set("no_get", "這樣東西不能離開那兒。\n");
                set("no_put", "這本劍譜不能放進去。\n");
        }
}
int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        mapping skill;
        int jslevel; 
        int neili_lost;
        if (!(arg=="jinshe jianpu" || arg == "jianpu" ))
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
/*        if(!arg || !objectp(ob = present(arg, me)) ){
                write("你要讀什麼？\n");
                return 1;
        }
*/
        if (!id(arg)) { 
                write("你要讀什麼？\n");
                return 1;
        }
        if( !me->query_skill("literate", 1) ){
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }
        switch(random(3)) {
          case 0:
        message("vision", me->name() + "專心地研讀金蛇劍譜。\n", environment(me), me);
              break;
          case 1:
        message("vision", me->name() + "看着金蛇劍譜，眼中好像發着陣陣金光。\n", environment(me), me);
              break;
          case 2:
        message("vision", me->name() + "突然放下劍譜，站起身來比劃了幾下。\n", environment(me), me);
              break;
        }
        if( query("jing", me)<15){
                write("你現在過於疲倦，無法專心下來研讀新知。\n");
                return 1;
        }
        if ( me->query_skill("jinshe-jian", 1) > 84) neili_lost = 55;
        else
        if ( me->query_skill("jinshe-jian", 1) > 74) neili_lost = 40;
        else neili_lost = 5;
        if( query("neili", me)<neili_lost){
                write("你內力不夠，無法鑽研這麼高深的武功。\n");
                return 1;
        }
        jslevel = me->query_skill("jinshe-jian", 1);
        if( query("combat_exp", me)<jslevel*jslevel*jslevel/10){
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        } 
        if( me->query_skill("jinshe-jian", 1) > 200){
                write("你研讀了一會兒，但是發現上面所説的對你而言都太淺了，沒有學到任何東西。\n");
                return 1;
        }
        me->receive_damage("jing", 45);
        set("neili",query("neili",  me)-neili_lost, me);
        me->improve_skill("jinshe-jian", (int)me->query_skill("literate", 1)/3+1);
        write("你研讀《金蛇劍譜》的祕訣，眼中發出陣陣金光，頗有心得。\n");
        return 1;
}