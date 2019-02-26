// kuihua.c 葵花寶典
// Jay 4/5/96

inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
        add_action("do_join", "join");
}

void create()
{
        set_name("葵花寶典", ({ "kuihua baodian", "baodian", "book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這就是武林第一祕籍《葵花寶典》，相傳是一位宮中太監所作。\n");
                set("value", 50000);
                set("material", "paper");
                set("no_drop", "這樣東西不能離開你。\n");
                set("no_get", "這樣東西不能離開那兒。\n");

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

        if (!(arg=="kuihua baodian" || arg == "baodian" || arg == "book"))
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
        if( query("gender", me) == "女性"){
                write("自古沒有女人可以讀《葵花寶典》的。\n");
                return 1;
        }
        if( query("gender", me) == "男性"){
               write("《葵花寶典》的第一頁寫着：欲練神功，必先自宮。\n");
               return 1;
        }
        if( !me->query_skill("literate", 1) ){
                write("你是個文盲，先學點文化(literate)吧。\n");
                return 1;
        }

        switch(random(3)) {
          case 0:
        message("vision", me->name() + "偷偷摸摸翻出一本書在讀。\n", environment(me), me);
              break;
          case 1:
        message("vision", me->name() + "邊讀書邊騷首弄姿，好像在模仿女人。\n", environment(me), me);
              break;
          case 2:
        message("vision", me->name() + "邊讀書邊把腰身扭來扭去。\n", environment(me), me);
              break;
        }
        if( query("jing", me)<15){
                write("你現在過於疲倦，無法專心下來研讀新知。\n");
                return 1;
        }

        if ( me->query_skill("bixie-jian", 1) > 84) neili_lost = 15;
        else
        if ( me->query_skill("bixie-jian", 1) > 74) neili_lost = 10;
        else neili_lost = 5;


        if( query("neili", me)<neili_lost){
                write("你內力不夠，無法鑽研這麼高深的武功。\n");
                return 1;
        }

        pxlevel = me->query_skill("bixie-jian", 1);
        if( query("combat_exp", me)<pxlevel*pxlevel*pxlevel/10){
                write("你的實戰經驗不足，再怎麼讀也沒用。\n");
                return 1;
        }

        if( me->query_skill("bixie-jian", 1) > 9)
            if ((!objectp(ob = present("golden ring", me)) ) ||
               (!query("equipped", ob))){
                write("你沒戴戒指，感到很難理解陰柔的指法。\n");
                return 1;
        }
        if( me->query_skill("bixie-jian", 1) > 19)
            if ((!objectp(ob = present("flower shoes", me)) ) ||
               (!query("equipped", ob))){
                write("你沒穿繡花鞋，感到很難理解陰柔的步法。\n");
                return 1;
        }
        if( me->query_skill("bixie-jian", 1) > 29)
            if ((!objectp(ob = present("xiuhua zhen", me)) ) ||
               (!query("equipped", ob))){
                write("你沒用繡花針，感到無法理解這種陰柔靈活的武功。\n");
                return 1;
        }
        if( me->query_skill("bixie-jian", 1) > 39)
            if ((!objectp(ob = present("pink cloth", me)) ) ||
               (!query("equipped", ob))){
                write("你沒穿女人的衣衫，感到很難理解陰柔的身法。\n");
                return 1;
        }
        if( me->query_skill("bixie-jian", 1) > 49)
            if ((!objectp(ob = present("golden necklace", me)) ) ||
               (!query("equipped", ob))){
                write("你沒戴項鍊，覺得練這種陰柔的功夫缺乏自信。\n");
                return 1;
        }

        if( me->query_skill("bixie-jian", 1) > 59)
            if( query("rank_info/respect", me) != "公公"){
                write("你現在需要正式加入(join)東廠才能繼續深造辟邪劍法。\n");
                write("鍵入join你便成為東廠的一位太監。這將不影響你的師承，\n");
                write("而且大家都將尊稱你為公公。\n");
                set_temp("pending/join", 1, me);
                return 1;
        }


        if( me->query_skill("bixie-jian", 1) > 199){
                write("你研讀了一會兒，但是發現上面所説的對你而言都太淺了，沒有學到任何東西。\n");
                return 1;
        }

        me->receive_damage("jing", 15);
        set("neili",query("neili",  me)-neili_lost, me);
        if( !me->query_skill("bixie-jian", 1) ) {
                me->set_skill("bixie-jian", 0);
write("                   《葵花寶典》閲讀指南\n"
"\n    恭喜你開始研習武林第一功夫－－－－辟邪劍法！\n"
"注意事項：\n"
"一．研習辟邪劍法必先自宮，如你不想讓別人發現這個天大的祕密，你必須\n"
"    找一無人所在之處閲讀，且當有別的玩家在場時不要使用辟邪劍法戰鬥，\n"
"    因為當你閲讀或使用辟邪劍法時會出現一些陰柔的舉動，使別人產生懷\n"
"    疑。切記不可收徒或拜別的玩家為師，以免被人檢查你的技能。\n\n"
"二．辟邪劍法功力極強，既可作劍法，又可作騰挪之法。\n\n"
"三．《葵花寶典》不可送人，出售，丟棄，撿拾，唯一的獲取方法是你使用\n"
"    你得到的密碼去密室尋找。\n\n"
"四．辟邪劍法不可通過拜師或自己鍛鍊來長進，只能通過研習《葵花寶典》\n"
"    來提高。\n\n"
"         祝你早日成為武林第一高手，稱霸天下！\n");
        }
        me->improve_skill("bixie-jian", (int)me->query_skill("literate", 1)/3+1);
        write("你研讀《葵花寶典》，頗有心得。\n");
        return 1;
}

        
int do_join()
{
        if( query("rank_info/respect", this_player()) == "公公"){
                     write("你已經加入東廠了，不需要重新加入。\n");
                return 1;
        }

        if( !query_temp("pending/join", this_player()) )
        return 0;

        set("rank_info/respect", "公公", this_player());
        set("rank_info/rude", "閹賊", this_player());
        write("恭喜你成為朝廷最重要的機關東廠的一員！\n");
        delete_temp("pending/join", this_player());
        return 1;
}
int query_autoload() { return 1; }
