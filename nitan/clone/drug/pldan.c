//破立丹
//snowlf  by 2001.10.10



#include <ansi.h>

inherit ITEM;
inherit F_SAVE;
inherit F_CLEAN_UP;

int cure_ob(string);
int do_esf(string argg);
int do_egg(string argg);
int do_ewx(string argg);
int do_ebl(string argg);


int intgg;
int intsf;
int intbl;
int intnl;
int intwx;

void init();

void create()
{
        set_name(HIB "破立丹" NOR, ({"poli dan", "puoli", "dan"}));
        set("long", HIW"     一顆淡藍色的小藥丸，閃爍著晶瑩的光澤，這就是傳說中能夠讓
人脫胎換骨，洗心革面，重新做人的破立丹了。如想了解更多關于破
立丹的祥情，請看幫助(help help_pldan)"NOR"\n\n");
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("value", 50000);
                set("no_sell", 1);
                set("medicine", 1);
        }

        setup();
}

int cure_ob(object me)
{
//    object me;
//   me = this_player();
    
    if( query("fupldan", me) == "yes" )
    {
                    write(HIR "破立丹每人最多只能服用一次，你以前服用過，不可以再次服用了！\n");
                    return 1;
    }
    else
    {  
                    write(HIW "\n\n\n\n\n\n破立丹 V 2.0A\n
                    ------------------------------------\n
                   1. 某一項先天天賦增加兩點。\n
                    2. 重新分配所有的先天天賦，但是總值減少二。\n
                    3. 增加四十級的基本內功。\n
                    4. 還俗。（限非全真派的道士，非少林派的和尚，非雪山派的喇嘛）\n
                    5. 重新制定自己的神。\n
                    6. 破立丹每人最多只能服用一次，服用過則永遠不可以再次服用，
                       如果你想等以後再服，請選6 \n
                    ------------------------------------\n\n
                    你想要發生哪種效果呢？（請輸入對應的數字代碼）\n
                    " NOR);

                    add_action("do_one", "1");
                    add_action("do_two", "2");
                    add_action("do_three", "3");
                    add_action("do_four", "4");
                    add_action("do_five", "5");
                    add_action("do_six", "6");

                 return 1;
    }
}



int do_one()
{
    object me;
    me = this_player();


    remove_action("do_one", "1");
    remove_action("do_two", "2");
    remove_action("do_three", "3");
    remove_action("do_four", "4");
    remove_action("do_five", "5");

    write(HIW "\n\n\n\n\n破立丹\n
    1. 膂力，增加兩點先天膂力。\n
    2. 根骨，增加兩點先天根骨。\n
    3. 身法，增加兩點先天身法。\n
    4. 悟性，增加兩點先天悟性。\n\n
    請選擇\n
    " NOR);

    add_action("do_bl", "1");
    add_action("do_gg", "2");
    add_action("do_sf", "3");
    add_action("do_wx", "4");

    return 1;

}


           int do_bl()
           {
               int cbl;
               int fbl;

               object me;
               me = this_player();

               remove_action("do_bl", "1");
               remove_action("do_gg", "2");
               remove_action("do_sf", "3");
               remove_action("do_wx", "4");


               cbl=query("str", me);
               fbl = cbl + 2;

               set("str", fbl, me);
               set("jingli",query("max_jingli",  me), me);
               set("fupldan", "yes", me);
               message_vision(HIY "先天盈弱的$N服下破立丹，只覺得渾身是勁，頓時顯得強壯了許多！\n" NOR, me);
        
//             me->unconcious();
               destruct(this_object());
               return 1;
           }





           int do_gg()
           {
               int cgg;
               int fgg;
               object me;
               me = this_player();


               remove_action("do_bl", "1");
               remove_action("do_gg", "2");
               remove_action("do_sf", "3");
               remove_action("do_wx", "4");

               cgg=query("con", me);
               fgg = cgg + 2;

               set("con", fgg, me);
               set("fupldan", "yes", me);
               message_vision(HIY "$N服下了一枚破立丹，身體似乎悄悄的發生了些變化。\n $N只感覺渾身脛脈之處如蟲蟻咬嚼般難受，慚慚渾身疼痛，意識模糊....\n" NOR, me);
               me->unconcious();
               destruct(this_object());
               return 1;
           }



           int do_sf()
           {
               int csf;
               int fsf;

               object me;
               me = this_player();

               remove_action("do_bl", "1");
               remove_action("do_gg", "2");
               remove_action("do_sf", "3");
               remove_action("do_wx", "4");


               csf=query("dex", me);
               fsf = csf + 2;

               set("dex", fsf, me);
               set("fupldan", "yes", me);
               message_vision(HIY "$N服下了一枚破立丹，骨節啪啪作響，頓覺身輕如燕，\n$N有一很想飛起來的感覺！\n" NOR, me);
//             me->unconcious();
               destruct(this_object());
               return 1;
           }



           int do_wx()
           {
               int cwx;
               int fwx;

               object me;
               me = this_player();

               remove_action("do_bl", "1");
               remove_action("do_gg", "2");
               remove_action("do_sf", "3");
               remove_action("do_wx", "4");


               cwx=query("int", me);
               fwx = cwx + 2;

               set("int", fwx, me);
               set("fupldan", "yes", me);
               message_vision(HIY "$N服下了一枚破立丹，有點意識恍惚.... \n$N猛的打了一下激凌，腦中突然一片空明，人看上去顯得靈慧了許多。\n" NOR, me);
//             me->unconcious();
               destruct(this_object());

               return 1;
           }






int do_two()
{
int cwx;
int cgg;
int cbl;
int cst;


int arg;
object me;
me = this_player();

    remove_action("do_one", "1");
    remove_action("do_two", "2");
    remove_action("do_three", "3");
    remove_action("do_four", "4");
    remove_action("do_five", "5");

        cwx=query("int", me);
        cgg=query("con", me);
        cbl=query("str", me);
        cst=query("dex", me);


    printf(BOLD "%s" NOR "%s\n\n", RANK_D->query_rank(me), me->short(1));

    write("你的原來的先天天賦為："HIW" 膂力：" + cbl+" 悟性："+ cwx+" 根骨："+ cgg+" 身法："+ cst+"\n\n");
    write(HIW "\n請輸入天賦 (格式： enter <臂力> <悟性> <根骨> <身法>\n");
    write(HIW "(注意：每項天賦數限在15至30之間，且四項天賦的總和應比你原來四項天賦之和少2.\n");
    write(HIW " 例子：enter 20 20 20 20\n");
    add_action("do_ebl", "enter");
    return 1;
}



               int do_ebl(string argg)
               {  
                int cwx;
                int cgg;
                int cbl;
                int cst;
                                             
                int arg;
                int cinttotal;
                int inttotal;
                object me;
                me = this_player();
                       
                cwx=query("int", me);
                cgg=query("con", me);
                cbl=query("str", me);
                cst=query("dex", me);
     
                                
                               sscanf(argg,"%d %d %d %d", intbl,intwx,intgg,intsf);
                               cinttotal = cwx + cgg + cbl + cst - 2;
                               inttotal = intbl + intgg + intwx + intsf;
                          
                        if (intbl < 15 ||intbl > 30 || intgg < 15 || intgg > 30 || intwx < 15 || intwx > 30 || intsf < 15 || intsf > 30 || inttotal > cinttotal ||inttotal < cinttotal)
                        {
                                       write(HIW "\n你輸入的資料有誤, 請再輸入一次\n");
                                       write(HIW "注意：每項天賦數限在15至30之間，且四項天賦的總和應為 "+ cinttotal+"(即比你原來四項天賦之和少2)\n");
                                       add_action("do_ebl", "enter");
                                       return 1;

                        }

                               else
                        {

                                      set("int", intwx, me);
                                set("con", intgg, me);
                                set("str", intbl, me);
                                set("dex", intsf, me);
                                set("fupldan", "yes", me);
                                message_vision(HIY "$N服下破立仙丹，身體發生了翻天覆地的變化，\n整個人脫胎換骨，好象變成了另外一個人。\n" NOR, me);
                                me->unconcious();
                                destruct(this_object());
                                return 1;
                         }
                }



int do_three()
{
    int ccforce;
    int fforce;
    object me;
    me = this_player();


    ccforce = me->query_skill("force",1);
    fforce = ccforce + 40;

    me->set_skill("force", fforce);
    set("fupldan", "yes", me);
    message_vision(HIY "$N服下破立仙丹，打通了常人須數十年修為方能打通的{任],{督]二脈。功力大進！\n$N的基本內功徒然增進了40級！\n" NOR, me);
    me->unconcious();
    destruct(this_object());
    return 1;
}



int do_four()
{
    object me;
    me = this_player();

    remove_action("do_one", "1");
    remove_action("do_two", "2");
    remove_action("do_three", "3");
    remove_action("do_four", "4");
    remove_action("do_five", "5");
    
    
    
    if( query("class", me) == "taoist" || query("class", me) == "bonze" || query("class", me) == "lama" )
    {
   
                    if( query("family/family_name", me) == "全真教" )
                    {
                    
                        write(HIW "你是全真教的道士，不能使用破立還俗，還是去找掌教真人吧！\n");
                        return 1;
                    }
                    
                    else if( query("family/family_name", me) == "少林派" )
                    {
                    
                        write(HIW "阿彌陀佛！你是少林派的和尚，不能使用破立還俗！\n");
                        return 1;
                    }
                    
                    else if( query("family/family_name", me) == "雪山派" )
                     {
                            write(HIW "阿彌陀佛！你是雪山派的喇嘛，不能使用破立還俗！\n");
                        return 1;
                   }  
                    
                    else 
                    {
                        delete("class", me);
                        set("fupldan", "yes", me);
                        message_vision(HIY "$N改換裝束，重新成為了凡間俗人中的一員，不用再受清規戒律的約束。\n" NOR, me);
                        me->unconcious();
                        destruct(this_object());
                        return 1;
                    }   
    }
    else
    {
                 write(HIW "這位"+RANK_D->query_respect(me)+" 未曾出家，還什麼俗啊？\n 開玩笑可以，別浪費了這麼珍貴的東西！\n");
                 return 1;
    }
    

}



int do_five()
{
    int cshen;
    int fshen;
    object me;
    me = this_player();

    remove_action("do_one", "1");
    remove_action("do_two", "2");
    remove_action("do_three", "3");
    remove_action("do_four", "4");
    remove_action("do_five", "5");

    cshen=query("shen", me);
    fshen = cshen * -1;

    set("shen", fshen, me);
    if(fshen < 0)
    {
    
                    message_vision(HIY "原本一向善良淳厚，古道熱腸，俠骨錚錚的$N ，自服了破\n立丹之後，恍若惡魔附身般，變成了一個無惡不作，讓人只想敬而遠之的大魔頭。\n" NOR, me);
    }
    else
    {
                message_vision(HIY "$N服下一枚破立仙丹，恍若受了神明點一般，大徹大悟，\n從此洗心革面，重新做人了，善哉善哉！\n" NOR, me);
  
    }
    set("fupldan", "yes", me);
    me->unconcious();
    destruct(this_object());

    return 1;
}


int do_six()
{
    object me;
    me = this_player();
    message_vision(HIY "因為考慮到破立丹每人只能服用一次，$N最終取消了現在服用破立丹的念頭，打算留到最關鍵的時候再服。\n" NOR, me);
    return 1;
}
