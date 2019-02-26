//ryu, 11/17/96. 
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
        set_name("持世陀羅尼經", ({ "shu", "book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("value", 400);
                set("material", "paper");

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

        if (!(arg== "book" || arg== "shu"))
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

        if( query("family/family_name", me) != "雪山寺"
         && query("family/family_name", me) != "血刀門"
         || query("class", me) != "bonze" )
                return notify_fail("你未入佛門，塵緣不斷，無法繼續修持密宗神法。\n");

        if( !me->query_skill("literate", 1) ){
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }

        message("vision", me->name() + "仔細地研讀《持世陀羅尼經》。\n", environment(me), me);
        if( query("jing", me)<15){
                write("你現在過於疲倦，無法專心下來研讀新知。\n");
                return 1;
        }

        if ( me->query_skill("lamaism", 1) > 300) neili_lost = 10;
             else if ( me->query_skill("lamaism", 1) > 200) neili_lost = 8;
             else if ( me->query_skill("lamaism", 1) > 100) neili_lost = 5;
             else neili_lost = 5;


        if( query("neili", me)<neili_lost){
                write("你內力不夠。\n");
                return 1;
        }

            if ((!objectp(ob = present("kulou guan", me)) ) ||
               (!query("equipped", ob))){
                write("你覺得頭上彷彿少了點什麼，讀得頭昏眼花。\n");
                return 1;
        }
            if ((!objectp(ob = present("rentou lian", me)) ) ||
               (!query("equipped", ob))){
                write("你覺得身上彷彿少了點什麼，讀得頭昏眼花。\n");
                return 1;
        }
            if ((!objectp(ob = present("lubo", me)) ) ||
               (!query("equipped", ob))){
                write("你覺得手中彷彿少了點什麼，讀得頭昏眼花。\n");
                return 1;
        }

        // keep some kinda of limit on it to provent newbie with 400 level lamaism
        if( me->query_skill("lamaism", 1) > 
            (me->query_skill("longxiang", 1))*1.5 ){
                write("你研讀了一會兒，但是發現上面所説的對你而言都太深奧了，沒有學到任何東西。\n");
                return 1;
        }

        if( me->query_skill("lamaism", 1) > 400){
                write("你研讀了一會兒，但是發現上面所説的對你而言都太淺了，沒有學到任何東西。\n");
                return 1;
        }

        me->receive_damage("jing", 40);
        set("neili",query("neili",  me)-neili_lost, me);
        if( !me->query_skill("lamaism", 1) ) {
                me->set_skill("lamaism", 0);
        }
        me->improve_skill("lamaism", (int)me->query_skill("literate", 1)/3+1);
        write("你研讀《持世陀羅尼經》，頗有心得。\n");
        return 1;
}
