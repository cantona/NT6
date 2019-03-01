// parry_book.c

inherit ITEM;
inherit F_UNIQUE;
void create()
{
        set_name("羊皮", ({ "yang pi", "pi" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("unique", 1);
                set("long", "這是一張羊皮，上面寫著密密麻麻的文字，好象很難看(read)懂。\n");
                set("value", 2000);
                set("material", "paper");
                set("no_drop", "這樣東西不能離開你。\n");
                set("treasure",1);
        }
}
void init()
{
        add_action("do_du", "read");
}
int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
//        object ob;
//        mapping skill;
        int qklevel,neili_lost,lit, med;
        lit = me->query_skill("literate", 1);
        med = me->query_skill("medicine", 1);
        qklevel = me->query_skill("qiankun-danuoyi", 1);
        if (!(arg=="yang pi" ||arg=="pi"))
        return 0;

        if( query("family/master_name", me) != "張無忌" )
             return notify_fail("只有教主親傳弟子才可以修習乾坤大挪移神功！\n");
        if( !query_temp("marks/挪移", me) )
             return notify_fail("沒有教主允許任何人都不可以擅自修習乾坤大挪移神功！\n");
        if( query("pigging", where) )
             return notify_fail("你還是專心拱豬吧！\n");
        if(me->is_busy())
             return notify_fail("你現在正忙著呢。\n");
        if(me->is_fighting())
             return notify_fail("你無法在戰鬥中專心下來研讀新知！\n");
        if(!id(arg))
             return notify_fail("你要讀什麼？\n");
        if(!lit)
             return notify_fail("你是個文盲，先學點文化(literate)吧。\n");
        if(me->query_int() < (qklevel/10)+20)
             return notify_fail("你的頭腦不夠用，恐怕不能修習乾坤大挪移神功。\n");
        if( query("combat_exp", me)<350000 )
             return notify_fail("你的實戰經驗不足，不能修習乾坤大挪移神功。\n");
        if( query("max_neili", me)<1200 )
             return notify_fail("你的內力不足，不能修習乾坤大挪移神功。\n");
        if(me->query_skill("force") < 200)
             return notify_fail("你的內功等級不足，不能修習乾坤大挪移神功。\n");
        if(!me->query_skill("shenghuo-shengong",1) &&
           !me->query_skill("jiuyang-shengong",1) &&
           !me->query_skill("jiuyin-zhengong",1))
             return notify_fail("你發覺你的內功路子和乾坤大挪移走的路子不同，再練下去沒有多大的好處。\n");
        if( query("jing", me)<30 )
             return notify_fail("你現在過于疲倦，無法專心下來研讀新知。\n");
        if(me->query_skill("qiankun-danuoyi",1) > (me->query_skill("force",1)+10))
             return notify_fail("由于你的內功的火侯不夠，不能再進行更高一層的提高。\n");
        if( query("neili", me)<neili_lost )
            return notify_fail("你內力不夠，無法鑽研這麼高深的武功。\n");
        if( query("combat_exp", me)<qklevel*qklevel*qklevel/10 )
             return notify_fail("你的實戰經驗不足，再怎麼讀也沒用。\n");
        if(qklevel > 400)
             return notify_fail("你練乾坤大挪移第七層心法時，發覺一共有一十九句心法沒能練成，結果沒能再長了。\n");
        if(qklevel > 60 && qklevel > lit+50)
             return notify_fail("你的讀書寫字等級不夠，認不完羊皮上的字。\n");
//        if(qklevel > 60 && qklevel > med+40)
//             return notify_fail("你的本草術理等級不夠，理解不完羊皮上的字的意思。\n");

        switch(random(3)) {
          case 0: message("vision", me->name() + "半邊臉孔脹得血紅，半邊臉頰卻發鐵青。\n", environment(me), me); break;
          case 1: message("vision", me->name() + "臉上忽然變紅，額頭汗如雨下，如墮碳火。\n", environment(me), me); break;
          case 2: message("vision", me->name() + "臉上忽然變青，身子微顫，如墮寒冰。\n", environment(me), me); break;
          }

        if(qklevel > 190){
                neili_lost = 30;
                me->receive_damage("jing", 55);
                set("neili",query("neili",  me)-neili_lost, me);
                me->improve_skill("qiankun-danuoyi", lit/3+1);
                write("你正在研習乾坤大挪移的第七層心法，似乎有點心得。\n");
                return 1;
                }
        if(qklevel > 180){
                neili_lost = 25;
                me->receive_damage("jing", 50);
                set("neili",query("neili",  me)-neili_lost, me);
                me->improve_skill("qiankun-danuoyi", lit/3+1);
                write("你正在研習乾坤大挪移的第六層心法，似乎有點心得。\n");
                return 1;
                }
        if(qklevel > 150){
                neili_lost = 20;
                me->receive_damage("jing", 45);
                set("neili",query("neili",  me)-neili_lost, me);
                me->improve_skill("qiankun-danuoyi", lit/3+1);
                write("你正在研習乾坤大挪移的第五層心法，似乎有點心得。\n");
                return 1;
                }
        if(qklevel > 120){
                neili_lost = 15;
                me->receive_damage("jing", 40);
                set("neili",query("neili",  me)-neili_lost, me);
                me->improve_skill("qiankun-danuoyi", lit/3+1);
                write("你正在研習乾坤大挪移的第四層心法，似乎有點心得。\n");
                return 1;
                }
        if(qklevel > 90){
                neili_lost = 10;
                me->receive_damage("jing", 35);
                set("neili",query("neili",  me)-neili_lost, me);
                me->improve_skill("qiankun-danuoyi", lit/3+1);
                write("你正在研習乾坤大挪移的第三層心法，似乎有點心得。\n");
                return 1;
                }
        if(qklevel > 60){
                neili_lost = 6;
                me->receive_damage("jing", 30);
                set("neili",query("neili",  me)-neili_lost, me);
                me->improve_skill("qiankun-danuoyi", lit/3+1);
                write("你正在研習乾坤大挪移的第二層心法，似乎有點心得。\n");
                return 1;
                }
        else{
                neili_lost = 5;
                me->receive_damage("jing", 25);
                set("neili",query("neili",  me)-neili_lost, me);
                me->improve_skill("qiankun-danuoyi", lit/3+1);
                write("你正在研習乾坤大挪移的第一層心法，似乎有點心得。\n");
                return 1;
                }
}