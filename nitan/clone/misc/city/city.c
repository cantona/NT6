// Last Modified by sir on 4.10.2002
// 要開發某個城市，必須聖旨任命官職。官吏
// 除了知府外，別的副官只能開發某部分指數。
// 可以任命一些巡撫，專門來挑刺。降低指數。
// 自然災害，破壞城市指數。
// topten定期朝廷來個評價。
// title激勵玩家。
// city : 綜合評價    city_level  巨型都市   大型都市  中型都市  小型都市
//         人口       people       800萬      500萬    300萬     100萬
//                   五項指數最大   8000       5000     3000      1000
//         農業       farming     力量 + 耐力   增加人口 減低民忠
//         治安       peace       身法 + 膽識   增加民忠 
//         水利       water       根骨 + 定力   增加民忠 
//         商業       business    福緣 + 容貌   增加人口 減低民忠
//         技術       technology  悟性 + 靈性   增加開發速度
//         税率       tax_rate    0-100 之間    
//                    0-15  之間   非常滿意 增加人口 增加民忠
//                    15-30 之間    滿意    增加人口 民忠不變
//                    30-40 之間   微有怨言 人口不變  減低民忠 農業,治安受到破壞 
//                    40-60 之間   怨聲載道  人口減少 減低民忠 農業,治安,商業受到破壞 
//                    60-80 之間   民怨沸騰  人口大減 民忠狂降 五項指數都受到破壞
//                    80-100之間   流民四起  人心不古 五項指數都狂減 
//         民忠       fealty      0-100之間
//    容貌 per  力量 str 身法 dex 福緣 kar 耐力 sta 
//    悟性 int  膽識 cor 定力 cps 根骨 con 靈性 spi

#ifndef CITYDATA
#define CITYDATA "/data/city/"  //文件存放地址
#endif
#define NAMEOFCITY "yangzhou"  //要開發的城市名
#define CNAMEOFCITY "揚州"     //中文城市名
#define FILE_PATH CITYDATA + NAMEOFCITY
#define LEVEL_OF_CITY "大型都市"  //綜合評價
#define LEVEL 500   //城市的起始規模
#define MAX_LEVEL 800  //城市的最大規模

#include <ansi.h>
inherit ITEM;
inherit F_SAVE;

int do_kaifa(string);

void create()
{        set_name(HIY"官府通告"NOR, ({ "guanfu tonggao", "tonggao"}) );
        set("long","這是一張記錄"+CNAMEOFCITY+"開發情況的官府通告。\n
想查看目前的情況，請先 help ms_city 瞭解具體操作。\n");
        set("LAST_KAIFA_PLAYER","none of us"); //最後開發過城市的玩家
        set("city_name", NAMEOFCITY); //城市名
        set("city_level", LEVEL_OF_CITY);// 綜合評價
        set("fealty", LEVEL/10);  // 民忠
        set("tax_rate",LEVEL/10); // 税率
        set("people", LEVEL*10000);        // 人口
        set("water", LEVEL*10); // 水利 
        set("water_pro", LEVEL*2); // 水利熟練度  
        set("peace", LEVEL*10);  // 治安
        set("peace_pro", LEVEL*2);
        set("farming", LEVEL*10); // 城防
        set("farming_pro", LEVEL*2);
        set("business", LEVEL*10); // 商業
        set("business_pro", LEVEL*2);
        set("technology", LEVEL*10); // 技術
        set("technology_pro", LEVEL*2);
        set("no_get", 1);
        set("unit", "張");
        restore();
}
        
        
        
string query_save_file()
{
        return FILE_PATH;        
}


void init()
{
        add_action("do_kaifa", "kaifa"); 
        add_action("do_chakan","chakan");
        add_action("do_tax","tax");                        
}
//int do_chakan()
string long()
{

        string msg;
        object ob;
        ob=this_object();
        msg=HIC"這個一張官府通告上面介紹了本城的開發情況: \n"+
        HIY"─────────────────────────────────────\n"NOR;
        msg+=sprintf(HIC"\n 城市:" HIY "%8s" NOR HIC"\t\t城市規模: " HIY "%8s\n" NOR,
        CNAMEOFCITY,query("city_level", ob),);
        msg+=sprintf(HIC"\n 税率:  " HIW "%5d" NOR HIC"\t\t城中人口: " HIG "%8d\n" NOR,
        query("tax_rate", ob),query("people", ob),);
        msg+=sprintf(HIC"\n 治安: " HIW "%8d" NOR HIC"\t\t治安指數: " HIG "%8d\n" NOR,
        query("peace", ob),query("peace_pro", ob),);
        msg+=sprintf(HIC"\n 商業: " HIW "%8d" NOR HIC"\t\t商業指數: " HIG "%8d\n" NOR,
        query("business", ob),query("business_pro", ob),);
        msg+=sprintf(HIC"\n 農業: " HIW "%8d" NOR HIC"\t\t農業指數: " HIG "%8d\n" NOR,
        query("farming", ob),query("farming_pro", ob),);
        msg+=sprintf(HIC"\n 水利: " HIW "%8d" NOR HIC"\t\t水利指數: " HIG "%8d\n" NOR,
        query("water", ob),query("water_pro", ob),);
        msg+=sprintf(HIC"\n 技術: " HIW "%8d" NOR HIC"\t\t技術指數: " HIG "%8d\n" NOR,
        query("technology", ob),query("technology_pro", ob),);
        msg+=HIY"─────────────────────────────────────\n"NOR;
        return msg;
}

int do_kaifa(string arg)
{
        
        object ob = this_object();
        object me = this_player();
        string msg;
        int pro_num, lvl_num,add_num,me_score,me_balance;
        int ob_people,ob_taxrate,ob_technology,ob_fealty;
//        kaifa,money,i;

        me_score=query("score", me);
        me_balance=query("balance", me);
        ob_people=query("people", ob);
        ob_taxrate=query("tax_rate", ob);
        ob_technology=query("technology", ob)/100;
/*
        if( !query("CITY_KAIFA", me)) )
                return notify_fail("你沒有得到康親王的許可，無法協助開發朝廷所屬地盤。\n");
        if( query("CITY_KAIFA/name", me) != query("city_name", ob) )
                return notify_fail("你要協助開發的城市好像不是這裏吧？\n");
*/
//江湖閲歷小於1000就不讓繼續開發        
         
        if (me_score<1000)
                return notify_fail("你的江湖閲歷不夠，還是多積累點閲歷再來吧!\n");
//存款小於100 gold 就不讓繼續開發
        if(me_balance<1000000)
                return notify_fail("你的存款不夠，無法滿足開發所需要的資金要求!\n");
        if( query_temp("busy", ob) )
                return notify_fail("有人剛下過開發命令，稍候........\n");
        if( !arg || ( arg!= "水利" && arg!="農業"
                  && arg!="治安" && arg!="商業" && arg!="技術"))
                return notify_fail("你要開發什麼？\n"); 
//   商業 business    福緣 + 容貌 + 本城技術值  增加人口 減低民忠
        if( arg=="商業")
           { 
              tell_object(me,"你思慮再三，決定開始協助官府開發"+CNAMEOFCITY+"的商業，請等候結果吧！\n");
              pro_num=query("business_pro", ob);
              lvl_num=query("business", ob);
              if(lvl_num >= MAX_LEVEL*10)
                { 
                 return notify_fail(CNAMEOFCITY+"的商業已經足夠發達了，你可以試着去開發其他項目了！\n"); 
                }
              else
              { 
                      add_num=query("per", me)+query("kar", me);
                add_num = add_num + random(ob_technology);
                pro_num=pro_num+add_num;
                if (pro_num>=lvl_num)
                    {
                     lvl_num+=1;
                     pro_num = pro_num - lvl_num;
                     message("channel:sys",HIY"【風聞】"HIG+CNAMEOFCITY+"的商業在"+query("name", me)+"的協助開發下變的越來越繁華了！\n"NOR,users());
                     ob_people=ob_people+lvl_num*(1+random(3));
                     if(ob_fealty>=5) ob_fealty-=random(5);
                     }
//                 ob->set("people",ob_people);
//                 ob->set("fealty",ob_fealty);
                 set("business_pro", pro_num, ob);
                 set("business", lvl_num, ob);
                 message_vision( HIW"城市的商業指數提高了。\n"NOR,me);
                } 
           }
//    農業       farming     力量 + 耐力+ 本城技術值   增加人口 減低民忠
        if( arg=="農業")
           { 
              tell_object(me,"你思慮再三，決定開始協助官府開發"+CNAMEOFCITY+"的農業，請等候結果吧！\n");
              pro_num=query("farming_pro", ob);
              lvl_num=query("farming", ob);
              if(lvl_num >= MAX_LEVEL*10)
                { 
                 return notify_fail(CNAMEOFCITY+"的農業已經足夠發達了，你可以試着去開發其他項目了！\n"); 
                }
              else
              { 
                      add_num=query("str", me)+query("sta", me);
                add_num = add_num + random(ob_technology);
                pro_num=pro_num+add_num;
                if (pro_num>=lvl_num)
                    {
                     lvl_num+=1;
                     pro_num = pro_num - lvl_num;
                     message("channel:sys",HIY"【風聞】"HIG+CNAMEOFCITY+"的農田在"+query("name", me)+"的協助開墾下變的越來越肥沃了！\n"NOR,users());
                     ob_people=ob_people+lvl_num*(1+random(3));
                     if(ob_fealty>=5) ob_fealty-=random(5);;
                     }
//                 ob->set("people",ob_people);
//                 ob->set("fealty",ob_fealty);
                 set("farming_pro", pro_num, ob);
                 set("farming", lvl_num, ob);
                 message_vision( HIY"城市的農業指數提高了。\n"NOR,me);
                }         
           }           
//   治安   peace   身法 + 膽識+ 本城技術值   增加民忠 
        if( arg=="治安")
           { 
              tell_object(me,"你思慮再三，決定開始協助官府開發"+CNAMEOFCITY+"的治安，請等候結果吧！\n");
              pro_num=query("peace_pro", ob);
              lvl_num=query("peace", ob);
              if(lvl_num >= MAX_LEVEL*10)
                { 
                 return notify_fail(CNAMEOFCITY+"的治安已經足夠發達了，你可以試着去開發其他項目了！\n"); 
                }
              else
              { 
                      add_num=query("dex", me)+query("cor", me);
                add_num = add_num + random(ob_technology);
                pro_num=pro_num+add_num;
                if (pro_num>=lvl_num)
                    {
                     lvl_num+=1;
                     pro_num = pro_num - lvl_num;
                     message("channel:sys",HIY"【風聞】"HIG+CNAMEOFCITY+"的治安在"+query("name", me)+"的協助治理下變的越來越安定了！\n"NOR,users());
                     if(ob_fealty<100) ob_fealty+=random(5);
                     if(ob_fealty>100) ob_fealty=100;
                     }
//                 ob->set("fealty",ob_fealty);
                 set("peace_pro", pro_num, ob);
                 set("peace", lvl_num, ob);
                 message_vision( HIC"城市的治安指數提高了。\n"NOR,me);
                }         
           }         
//    水利  water       根骨 + 定力+ 本城技術值   增加民忠 
        if( arg=="水利")
           { 
              tell_object(me,"你思慮再三，決定開始協助官府開發"+CNAMEOFCITY+"的水利，請等候結果吧！\n");
              pro_num=query("water_pro", ob);
              lvl_num=query("water", ob);
              if(lvl_num >= MAX_LEVEL*10)
                { 
                 return notify_fail(CNAMEOFCITY+"的水利已經足夠發達了，你可以試着去開發其他項目了！\n"); 
                }
              else
              { 
                      add_num=query("con", me)+query("cps", me);
                add_num = add_num + random(ob_technology);
                pro_num=pro_num+add_num;
                if (pro_num>=lvl_num)
                    {
                     lvl_num+=1;
                     pro_num = pro_num - lvl_num;
                     message("channel:sys",HIY"【風聞】"HIG+CNAMEOFCITY+"的水利在"+query("name", me)+"的協助開發下變的越來越發達了！\n"NOR,users());
                     if(ob_fealty<100) ob_fealty+=random(5);
                     if(ob_fealty>100) ob_fealty=100;
                     }
//                 ob->set("fealty",ob_fealty);
                 set("water_pro", pro_num, ob);
                 set("water", lvl_num, ob);
                 message_vision( HIC"城市的水利指數提高了。\n"NOR,me);
                }         
           }        
//  技術   technology  悟性 + 靈性   增加開發速度        
        if( arg=="技術")
           { 
              tell_object(me,"你思慮再三，決定開始協助官府開發"+CNAMEOFCITY+"的技術，請等候結果吧！\n");
              pro_num=query("technology_pro", ob);
              lvl_num=query("technology", ob);
              if(lvl_num >= MAX_LEVEL*10)
                { 
                 return notify_fail(CNAMEOFCITY+"的技術已經足夠發達了，你可以試着去開發其他項目了！\n"); 
                }
              else
              { 
                      add_num=query("int", me)+query("spi", me);
                add_num = add_num + random(ob_technology);
                pro_num=pro_num+add_num;
                if (pro_num>=lvl_num)
                    {
                     lvl_num+=1;
                     pro_num = pro_num - lvl_num;
                     message("channel:sys",HIY"【風聞】"HIG+CNAMEOFCITY+"的技術在"+query("name", me)+"的協助研究下變的越來越先進了！\n"NOR,users());
                     }
                 set("technology_pro", pro_num, ob);
                 set("technology", lvl_num, ob);
                 message_vision( HIB"城市的技術指數提高了。\n"NOR,me);
                 
                }         
           }                                   
//每次執行開發指令，都要考慮到城市税率對本輪開發的影響 這樣感覺才有點動態性 呵呵
//         0-15  之間   非常滿意 增加人口 增加民忠
//         15-30 之間    滿意    增加人口 民忠不變
//      30-40 之間   微有怨言 人口不變  減低民忠 農業,治安受到破壞 
//      40-60 之間   怨聲載道  人口減少 減低民忠 農業,治安,商業受到破壞
//      60-80 之間   民怨沸騰  人口大減 民忠狂降 五項指數都受到破壞
//      80-100之間   流民四起  人心不古 五項指數都狂減 
       if( ob_taxrate>=0&&ob_taxrate<=15) 
           { 
             if(ob_fealty<100) ob_fealty+=random(5);
             if(ob_fealty>100) ob_fealty=100;
             if(ob_people<MAX_LEVEL*10000)
             ob_people=ob_people+(100-ob_taxrate)*(10+random(5));
             message_vision( MAG"由於城市的税率定的相當低，這裏百姓非常滿意，並有很多外地的人口來這裏謀生。\n"NOR,me);
            }
           
       else if( ob_taxrate>=16&&ob_taxrate<=30)
            {  
             if(ob_people<MAX_LEVEL*10000)
             ob_people=ob_people+(100-ob_taxrate)*(10+random(5));
             message_vision( GRN"由於城市的税率定的相對較低，百姓還算滿意，經常有一些外地的人口來這裏謀生。\n"NOR,me);
             }

       else if( ob_taxrate>=31&&ob_taxrate<=40)
             {
               if(ob_fealty>=5) ob_fealty-=random(5);
               pro_num=query("farming_pro", ob);
               lvl_num=query("farming", ob);
               if (pro_num > 100)
                   { 
                      pro_num = (int)pro_num-random(100);
                      set("farming_pro", pro_num, ob);
                    }                                      
               pro_num=query("peace_pro", ob);
               if (pro_num > 100)
                   { 
                      pro_num = (int)pro_num-random(100);
                      set("peace_pro", pro_num, ob);
                    }      
               message_vision( CYN"城中的一些人認為官府的税率定的不太合理，微有怨言，有人在城裏發現小偷和一些不願種田的農民。\n"NOR,me);
               }
        else if( ob_taxrate>=41&&ob_taxrate<=60)
             {
                     if(ob_fealty>=5) ob_fealty-=random(5);
                     ob_people=ob_people-ob_taxrate*(10+random(3));
                     pro_num=query("farming_pro", ob);
                     if (pro_num > 100)
                   { 
                      pro_num = (int)pro_num-random(100);
                      set("farming_pro", pro_num, ob);
                    }  
                 pro_num=query("peace_pro", ob);
                 if (pro_num > 100)
                    { 
                      pro_num = (int)pro_num-random(100);
                      set("peace_pro", pro_num, ob);
                     }    
                 pro_num=query("business_pro", ob);
                 if (pro_num > 100)
                     { 
                      pro_num = (int)pro_num-random(100);
                      set("business_pro", pro_num, ob);
                     }     
                     message_vision( YEL"城中百姓怨聲載道，大部分商人也認為官府收的税太高了，有人在城中搞起小破壞，來抱怨對官府的不滿。\n"NOR,me);
                     }
         else if( ob_taxrate>=61&&ob_taxrate<=80)
             {
                     if(ob_fealty>=5) ob_fealty-=random(5); 
                     ob_people=ob_people-ob_taxrate*(10+random(6));                    
                     if( query("farming", ob)>5 && random(2) == 1 )
                          addn("farming", -1, ob);
                if( query("water", ob)>5 && random(2) == 1 )
                          addn("water", -1, ob);
                     if( query("business", ob)>5 && random(2) == 1 )
                          addn("business", -1, ob);
                     if( query("technology", ob)>5 && random(2) == 1 )
                          addn("technology", -1, ob);
                     if( query("peace", ob)>5 && random(2) == 1 )
                          addn("peace", -1, ob);
                     message_vision( BLU"城中民怨沸騰，百姓一致認為官府收的税太高了，並逐漸對這裏的地方官員失去信心。\n"NOR,me);
             }  
        else
             {
                     if(ob_fealty>=5) ob_fealty-=random(5);
                     ob_people=ob_people-ob_taxrate*(10+random(9));                     
                     if( query("farming", ob)>5 && random(2) == 1 )
                          addn("farming", -2, ob);
                if( query("water", ob)>5 && random(2) == 1 )
                          addn("water", -2, ob);
                     if( query("business", ob)>5 && random(2) == 1 )
                          addn("business", -2, ob);
                     if( query("technology", ob)>5 && random(2) == 1 )
                          addn("technology", -2, ob);
                     if( query("peace", ob)>5 && random(2) == 1 )
                          addn("peace", -2, ob);
                     message_vision( RED"苛政猛於虎，城中百姓無法忍受官府的盤剝，紛紛背井離鄉。\n"NOR,me);
                     }  
// 每次執行指令消耗50的江湖閲歷 和一定的存款（與本城的税率有關 如果税率達100就不花錢）
        me_score = me_score-50;
        me_balance = me_balance-2000*(100-ob_taxrate);
        set("score", me_score, me);
        set("balance", me_balance, me);
//防止執行過程中出現負人口 和民忠值超過範圍
        if( ob_people<0) ob_people=1;
        set("people", ob_people, ob);
        if (ob_fealty<0) ob_fealty=0;
        if (ob_fealty>100) ob_fealty=100;
        set("fealty", ob_fealty, ob);
        save();
        set_temp("busy", 1, ob);
        remove_call_out("enough_rest");
//1秒後取消busy
        call_out("enough_rest", 1);
        return 1;
}
int do_tax(string arg)
{  int ob_taxrate,taxrate;
   object ob=this_object();
   if( query_temp("busy", ob) )
        return notify_fail("有人剛下過開發命令，稍候........\n");
   if( !arg
        ||      !sscanf(arg, "%d", taxrate) )
      return notify_fail("你想將税率定為多少？\n");
   if(taxrate>100||taxrate<0)
      return notify_fail("税率只能在0到100之間！\n");
   ob_taxrate=taxrate;
   set("tax_rate", ob_taxrate, ob);
   save();
   set_temp("busy", 1, ob);
   remove_call_out("enough_rest");
//1秒後取消busy
   call_out("enough_rest", 1);
   return 1;
}
    
void enough_rest()
{
        delete_temp("busy");
}
