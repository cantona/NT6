// By zjb@ty 2002-5-15

#include <ansi.h> 
inherit ROOM; 
int do_dan(object me,object obj);
int do_yao(object me,object obj);
void create()
{
        set("short", HIY"煉丹房"NOR);
        set("long", @LONG
這裡是華佗的煉丹室,房間中央放著一個煉丹爐,
玩家們可以拿著自己挖掘來的草藥練出自己所需的丹丹藥!
LONG
        );
        set("exits", ([
  "east" : "/d/changan/ca14",
        ]));
        set("no_fight",1);
        set("no_beg",1);
        set("no_steal",1);
        setup();
}

void init()
{ 
        add_action("do_zhuyao","zhuyao");
        add_action("do_fangdan","fangyao");
        add_action("do_liandan","liandan"); 
}

int do_fangdan(string arg)
{
    object obj;
    object ob;
    object me = this_player();

    if(!arg) return notify_fail("你要放什麼藥進去？\n");

    if( !query_temp("zhuyao", me) )
    return notify_fail("練丹要先放主藥,要不然練不出好丹!\n");

    if( !objectp(obj = present(arg, me)) )
    return notify_fail("你身上並沒有這樣東西!\n");

    return do_dan(me, obj);

}

int do_zhuyao(string arg)
{
    object obj;
    object ob;
    object me = this_player();

    if(!arg) return notify_fail("你要拿什麼東西當主藥？\n");

    if( !objectp(obj = present(arg, me)) )
    return notify_fail("你身上並沒有這樣東西!\n");

  if(me->is_busy())
  return notify_fail("您現在正忙,等一下再挖吧!\n");


    return do_yao(me, obj);

}

int do_liandan(string arg)
{
    int shoubi,tui,all,zhuyao,all2,zjb,liandan;
    object dan;
    object me = this_player();
    shoubi=query_temp("liandan/shoubi", me);
    tui=query_temp("liandan/tui", me);
    all=query_temp("liandan/all", me);
    all2=query_temp("liandan/random", me);
    zhuyao=query_temp("zhuyao", me);
    zjb=query_temp("zjb_dan", me);
    liandan = me->query_skill("liandan-shu",1);

    if (!arg) return notify_fail("你要練哪個種類的丹？\n");

    if( !query_temp("liandan", me) )
    return notify_fail("你沒放丹,你練個屁!\n");


// By zjb@ty 以下都是治療殘廢的藥的練法
    if (arg == "shoubi") {
    addn("combat_exp", 1000, me);
    delete_temp("zhuyaoname", me);
    delete_temp("danname", me);

    
// By zjb@ty 煉丹的額外獎勵!
    addn("combat_exp", zjb*1000+random(1000), me);
    addn("potential", zjb*100+random(500), me);
    me->start_busy(5);
    write(HIR"你在煉丹的時候不知不覺經驗也隨著上去了!\n"NOR);

    if (shoubi==32 && zhuyao==1) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    dan=new("/d/zjb/yao/shoubi1");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"你練出了治療臂傷的良藥傷藥丸!\n"NOR);
    }
    if (shoubi==26 && zhuyao==2) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/shoubi2");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIB"你練出了治療臂傷的良藥補傷丸!\n"NOR);
    }
    if (shoubi==27 && zhuyao==3) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/shoubi3");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"你練出了治療臂傷的良藥先復湯!\n"NOR);
    }
    if (shoubi==33 && zhuyao==4) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/shoubi4");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"你練出了治療臂傷的良藥復方血竭酊!\n"NOR);
    }

    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/chayao");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIW"你的配方好象不對,練出一個無名藥品!\n"NOR);
    }

    if (arg == "tui") {
    addn("combat_exp", 1000, me);
    delete_temp("zhuyaoname", me);
    delete_temp("danname", me);
    
// By zjb@ty 煉丹的額外獎勵!
    addn("combat_exp", zjb*1000+random(1000), me);
    addn("potential", zjb*100+random(500), me);
    me->start_busy(5);
    write(HIR"你在煉丹的時候不知不覺經驗也隨著上去了!\n"NOR);

    if (tui==74 && zhuyao==11) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/tui1");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIC"你練出了治療腿傷的良藥--活血止痛湯!\n"NOR);
    }
    if (tui==151 && zhuyao==12) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/tui2");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"你練出了治療腿傷的良藥--宋氏接骨散!\n"NOR);
    }

    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/chayao");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIW"你的配方好象不對,練出一個無名藥品!\n"NOR);
    }
    
    if (arg == "all") {
    addn("combat_exp", 1000, me);
    delete_temp("zhuyaoname", me);
    delete_temp("danname", me);

// By zjb@ty 煉丹的額外獎勵!
    addn("combat_exp", zjb*1000+random(1000), me);
    addn("potential", zjb*100+random(500), me);
    me->start_busy(5);
    write(HIR"你在煉丹的時候不知不覺經驗也隨著上去了!\n"NOR);

    if (all==51 && zhuyao==21) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/all1");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"你練出了療傷聖藥--袪腐生肌散!\n"NOR);
    }
    if (all==64 && zhuyao==22) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/all2");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"你練出了療傷聖藥--七厘丹!\n"NOR);
    }
    if (all==40 && zhuyao==23) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/all3");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"你練出了療傷聖藥--壯筋續骨丹!\n"NOR);
    }
    if (all==55 && zhuyao==24) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/all4");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"你練出了療傷聖藥--朱砂沒藥散!\n"NOR);
    }
    
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/chayao");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIW"你的配方好象不對,練出一個無名藥品!\n"NOR);
    }

// By zjb@ty 以下是隨機煉丹的程序!    
    if (arg == "random") {
    addn("combat_exp", 1000, me);
    delete_temp("zhuyaoname", me);
    delete_temp("danname", me);
    
// By zjb@ty 煉丹的額外獎勵!
    me->improve_skill("liandan-shu", me->query_int()*300+random(100));
    addn("combat_exp", zjb*1000+random(1000), me);
    addn("potential", zjb*100+random(500), me);
    me->start_busy(5);
    write(HIR"你在煉丹的時候不知不覺經驗也隨著上去了!\n"NOR);

    if ( liandan > 500 && zjb > 15) {
    if ( zjb>15 && zjb<20 && all2 < 211 &&all2 > 100 
    && random(10000)>9995) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan11");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(BLINK HIR"你竟然練出了可以使人重生的還魂丹!!!\n"NOR);
    }
    }

   if ( liandan > 300 && zjb > 10 && random(100)>70) {

    if ( zjb < 15 && zjb>10 && all2 < 200 && all2 > 100 
    && random(100)>90) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan19");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIC"你練出了可以增加全部武功的技能丹!!!\n"NOR);
    }

    if ( zjb < 15 && zjb>3 && all2 < 200 && all2 > 30 
    && random(100)>60) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan12");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIB"你練出了可以使人返老還童的仙丹!!!\n"NOR);
    }

    if ( zjb < 15 && zjb>10 && all2 < 150 && all2 > 40 
    && random(100)>95) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan6");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"你練出了可以增加先天臂力的臂力丹!!!\n"NOR);
    }

    if ( zjb < 15 && zjb>10 && all2 < 150 && all2 > 40 
    && random(100)>95) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan7");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"你練出了可以增加先天身法的身法丹!!!\n"NOR);
    }

    if ( zjb < 15 && zjb>10 && all2 < 150 && all2 > 40 
    && random(100)>95) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan8");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"你練出了可以增加先天根骨的根骨丹!!!\n"NOR);
    }

    if ( zjb < 15 && zjb>10 && all2 < 150 && all2 > 40 
    && random(100)>95) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan9");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"你練出了可以增加先天悟性的悟性丹!!!\n"NOR);
    }

   if ( zjb < 15 && zjb>10 && all2 < 150 && all2 > 40 
    && random(100)>20) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan23");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"你練出了可以增加奇功的奇功丸!!!\n"NOR);
    }

    if ( zjb < 15 && zjb>10 && all2 < 150 && all2 > 40 
    && random(100)>95) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan10");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"你練出了可以增加先天容貌的養顏丹!!\n"NOR);
    }

    }

    if ( zjb==2 &&all2 < 100 && all2 > 1 ) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/city/npc/obj/yangjing");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIY"你練出了療精用的養精丹!\n"NOR);
    }


    if ( zjb < 4 && zjb > 1 && all2 < 100  && all2 > 5 ) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/city/npc/obj/jinchuang");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIY"你練出了療傷用的金創藥!\n"NOR);
    }

    if ( zjb < 8 && zjb>3 && all2 < 100 && all2 > 30 && random(10)>4
    && zhuyao >= 1 && zhuyao < 5) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan2");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"你練出了可使自己使自己脫離busy的疾風丹\n"NOR);
    }
    
    if ( zjb < 6 && zjb > 3 && all2 < 100 && all2 > 20 
    && random(10)>4&& zhuyao >= 21 && zhuyao < 25) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan3");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIW"你練出了少林聖藥菩提子!\n"NOR);
    }
    
    if ( zjb < 10 && zjb > 4 && all2 < 100 && all2 > 20 
    && random(10)>4&& zhuyao >= 11 && zhuyao < 15) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan4");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIW"你練出了少林聖藥大還丹!\n"NOR);
    }

    if ( zjb < 6 && zjb > 3 && all2 < 100 && all2 > 20 
    && random(10)>4&& zhuyao >= 21 && zhuyao < 25) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan5");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIW"你練出了補精聖藥,腎寶!!!\n"NOR);
    }

    if ( zjb < 10 && zjb > 2 && all2 < 100 && all2 > 10 
    && random(10)>3 && zhuyao >= 1 && zhuyao < 5) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan13");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"你練出了可解百毒的解毒丸!!!\n"NOR);
    }

    if ( zjb < 10 && zjb > 2 && all2 < 100 && all2 > 10 
    && random(10)>3 && zhuyao >= 21 && zhuyao < 25) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan14");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"你練出了可增加攻擊力的戰神丸!!!\n"NOR);
    }

    if ( zjb < 15 && zjb > 2 && all2 < 100 && all2 > 30 
    && random(10)>8 && zhuyao >= 21 && zhuyao < 25) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan15");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIG"你練出了可增加技能的龍丹!!!\n"NOR);
    }

    if ( zjb < 7&& zjb > 2 && all2 < 100 && all2 > 20 &&random(10)>4
    && zhuyao >= 21 && zhuyao < 25) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan1");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"你練出了可使自己狀態恢復滿的血氣丹!\n"NOR);
    }

    if ( zjb < 10 && zjb > 3 && all2 < 100 && all2 > 10 
    && random(10)>2 && zhuyao >= 1 && zhuyao < 5) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan16");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIB"你練出了可增加正氣的正氣丸!!!\n"NOR);
    }

    if ( zjb < 15 && zjb > 3 && all2 < 150 && all2 > 30 
    && random(10)>3 && zhuyao >= 21 && zhuyao < 25) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan17");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"你練出了可增加基本內功的太級丹!!!\n"NOR);
    }

    if ( zjb < 15 && zjb > 1 && all2 < 150 && all2 > 10 
    && random(10)>3 && zhuyao >= 1 && zhuyao < 5) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan18");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"你練出了可增加基本負神的邪神丸!!!\n"NOR);
    }

    if ( zjb < 15 && zjb > 3 && all2 < 150 && all2 > 30 
    && random(10)>8 && zhuyao >= 11 && zhuyao < 15) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan20");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"你練出了可增加基本輕功的驚風丸!!!\n"NOR);
    }

    if ( zjb < 15 && zjb > 3 && all2 < 150 && all2 > 30 
    && random(10)>3 && zhuyao >= 1 && zhuyao < 5) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan21");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"你練出了可增加基本拳腳的神力丸!!!\n"NOR);
    }

    if ( zjb < 10 && zjb > 4 && all2 < 150 && all2 > 50 
    && random(10)>3 && zhuyao >= 21 && zhuyao < 25) {
    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/dan22");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIR"你練出了可增加讀書寫字的智力丸!!!\n"NOR);
    }

    delete_temp("liandan", me);
    delete_temp("zhuyao", me);
    delete_temp("zjb_dan", me);
    dan = new("/d/zjb/yao/chayao");
    set("zhuren", ""+query("id", me)+"", dan);
    dan->move(me);
    return notify_fail(HIW"你此次煉丹失敗,練出一個無名藥品!\n"NOR);
}
    }

int do_dan(object me,object obj)
{
    object ob;
    string arg=obj->short(1);
  
    foreach ( ob in all_inventory(me)){
    if (ob->short(1)!=arg) continue;
    if( !query("yao", ob)){
    write("這樣東西並不能拿來練藥!\n");
    return 1;
    }

    if( query_temp("danname/"+query("id", ob, me)+"") )
    return notify_fail("你已經把"+ob->name()+"放進練丹爐了!\n");

    if( query("shoubi", ob) )
    addn_temp("liandan/shoubi",query("shoubi",  ob), me);

    if( query("tui", ob) )
    addn_temp("liandan/tui",query("tui",  ob), me);

    if( query("all", ob) )
    addn_temp("liandan/all",query("all",  ob), me);

    if( query("random", ob) )
    addn_temp("liandan/random",query("random",  ob), me);

    set_temp("danname/"+query("id", ob)+"", 1, me);
    addn_temp("zjb_dan", 1, me);
    write(HIR"你把"+ob->name()+HIR"放進了煉丹爐!\n"NOR);
    destruct(ob);
    return 1;
    }
}

int do_yao(object me,object obj)
{
    object ob;
    string arg=obj->short(1);
    me = this_player();
 
    if( query_temp("zhuyao", me) )
    return notify_fail("對不起你已經拿"+query_temp("zhuyaoname", me)+"做主藥了!\n");

    foreach ( ob in all_inventory(me)){
    if (ob->short(1)!=arg) continue;
    if( !query("zhuyao", ob)){
    write("這樣東西並不能做主藥!\n");
      return 1;
    }
    write(HIR"你拿"+ob->name()+HIR"做主藥!\n"NOR);
    set_temp("zhuyao",query("zhuyao",  ob), me);
    set_temp("zhuyaoname", ""+ob->name()+"", me);
    destruct(ob);
    return 1;
    }
}

