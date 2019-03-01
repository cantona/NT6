//tangfeng@SJ 
//story紀錄
//add 連城訣 by tangfeng 2004/11/1
//add 射雕英雄傳 by redhat@Sjmud 2009/4/8

#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);
string get_string(string str);

//feihu
string quest_feihu(object me); 
string feihu_skill(object me);
//tlbb
string quest_tlbb(object me); 
string tlbb_skill(object me); 
//lchj
string quest_lchj(object me); 
string lchj_skill(object me); 
//shediao
string quest_shediao(object me); 
string shediao_skill(object me); 
//tulong
string quest_tulong(object me);
string tulong_skill(object me);

int main(object me, string arg)
{
        object ob;
        string arg1,arg2,str;
        int i_all=0,i_feihu=0,i_tlbb=0,i_lchj=0,i_shediao=0,i_tulong=0;

        str="\n";
        if (!arg)
        {
                ob = me;
                i_all=1;
        }
        else if (sscanf(arg, "%s form %s", arg1,arg2)) 
        {     
                switch (arg1)
                {
                case "feihu" : i_feihu=1;break;
                case "tlbb"  : i_tlbb=1;break;
                case "lchj"  : i_lchj=1;break;//連城訣
                case "shediao"  : i_shediao=1;break;//射雕英雄傳
                case "tulong": i_tulong=1;break;//倚天屠龍記
                default :
                        return notify_fail("目前只開放雪山飛狐、天龍八部、連城訣、射雕英雄傳和倚天屠龍記。詳細內容請查閱幫助。\n");
                }
                if (wizardp(me))
                {
                        ob = present(arg2, environment(me));
                        if (!ob) ob = LOGIN_D->find_body(arg2);
                        if (!ob) ob = find_living(arg2);
                        if (!ob || !me->visible(ob)) return notify_fail("你要察看誰的狀態？\n");
                } 
                else
                        return notify_fail("只有巫師能察看別人的狀態。\n");
        }
        else
        {
                ob = me;
                switch (arg)
                {
                        case "feihu" : i_feihu=1;break;
                        case "tlbb"  : i_tlbb=1;break;
                        case "lchj"  : i_lchj=1;break;//連城訣
                        case "shediao"  : i_shediao=1;break;//射雕英雄傳
                        case "tulong": i_tulong=1;break;
                        default :
                                if (wizardp(me))
                                {
                                        ob = present(arg, environment(me));
                                        if (!ob) ob = LOGIN_D->find_body(arg);
                                        if (!ob) ob = find_living(arg);
                                        if (!ob || !me->visible(ob)) return notify_fail("你要察看誰的狀態？\n");
                                        i_all=1;
                                } 
                                else
                                        return notify_fail("目前只開放雪山飛狐、天龍八部、連城訣、射雕英雄傳和倚天屠龍記。詳細內容請查閱幫助。\n");
                }
        }


        if (!wizardp(me) && me->is_busy())
                return notify_fail("你正忙著呢。\n");
        
        if(wizardp(me) && userp(ob)&& me!=ob)
        {
                str =   "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
                str +=get_string(YEL"【你正在查詢"+query("name", ob)+"的紀錄】"NOR);
                tell_object(me,str);
        }

        if(i_all==1)  
        {
                str =  "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
                str +=get_string(HIY"【十四天書任務紀錄】"NOR);
                str += "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
                if(query("mana", ob)||wizardp(me))
                {   
                        str +=sprintf("%30s",HIG"姓名：")+query("name", ob);
                        str +="\n";
                        str +=sprintf("%30s",HIG"聲望：")+chinese_number(query("mana", ob))+NOR;
                        str +="\n";
                }
                if(wizardp(me) && query("id", me)=="lonely")
                {
                        str +=sprintf("%30s",HIG"富源：")+chinese_number(ob->query_kar())+NOR;
                        str +="\n";
                        str +=sprintf("%30s",HIG"悟性：")+chinese_number(ob->query_int())+NOR;
                        str +="\n";
                }
                str += quest_feihu(ob);
                str += quest_tlbb(ob);
                str += quest_lchj(ob);
                str += quest_shediao(ob);
                str += quest_tulong(ob);
        }
        else if(i_feihu==1)        
                str = quest_feihu(ob);
        else if(i_tlbb==1)
                str = quest_tlbb(ob);
        else if(i_lchj==1)
                str = quest_lchj(ob);
        else if(i_shediao==1)
                str = quest_shediao(ob);
        else if(i_tulong==1)
                str = quest_tulong(ob);
        else return notify_fail("目前只開放雪山飛狐、天龍八部、連城訣、射雕英雄傳和倚天屠龍記。詳細內容請查閱幫助。\n");

        str +=   "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
        tell_object(me,str);
        return 1;
}

string quest_feihu(object me)
{
        string str= "\n";

        if(!query("quest/雪山飛狐",me))
        {
                str = "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
                str +=get_string(HIW"【目前關于雪山飛狐，沒有任何紀錄】"NOR);
                return str;
        }

        str =   "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
        str +=get_string(HIW"【雪山飛狐】"NOR);
        str +=  "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
        if(query("quest/雪山飛狐/time",me))
        {
                if(!query("quest/雪山飛狐/解藥篇/over",me) )
                        str +=get_string(WHT"遊戲紀錄時間差："+CHINESE_D->chinese_time(time()-query("quest/雪山飛狐/time",me))+"。"NOR);
                else str +=get_string(WHT"遊戲紀錄時間："+CHINESE_D->chinese_date(query("quest/雪山飛狐/time",me),1)+"。"NOR);
        }
        if(query("quest/雪山飛狐/combat_exp", me))
        {
                        if(!query("quest/雪山飛狐/解藥篇/over",me) )
                                str +=get_string(WHT"遊戲紀錄經驗差："+chinese_number(query("combat_exp",me)-query("quest/雪山飛狐/combat_exp",me))+"。"NOR);
                        else str +=get_string(WHT"遊戲紀錄經驗："+query("quest/雪山飛狐/combat_exp",me)+"。"NOR);
                        str +="\n";
        }
        if(!query("quest/雪山飛狐/兩頁刀法篇",me))
        {
                str +=get_string(HBRED"遊戲紀錄混亂。你還需要努力。"NOR);
                str +=feihu_skill(me);
                return str;
        }
        if(!query("quest/雪山飛狐/兩頁刀法篇/over",me))
        {
                if(random(2)) str +=get_string(HBRED"下一步，如何幫助胡斐進一步完善胡家刀法。"NOR);
                else str +=get_string(HBRED"下一步探索：如何尋找失落的最後兩頁刀法。"NOR);
                str +=feihu_skill(me);
                return str;
        }

        str +=get_string(YEL"你已經幫助胡斐完善胡家刀法，獲得一些獎勵。"NOR);
        
        if(!query("quest/雪山飛狐/復仇篇",me))
        {
                if(random(2)) str +=get_string(HBRED"從閻基處你獲得過一些舊事，下一步：辨真假。"NOR);
                else          str +=get_string(HBRED"兇手是苗人鳳嗎？下一步：闖苗家莊。"NOR);
                str +=feihu_skill(me);
                return str;
        }
        
        if(!query("quest/雪山飛狐/復仇篇/over",me))
        {
                if(random(2)) str +=get_string(HBRED"當年苗、胡之爭，似乎已經明了，只是果真如此嗎？"NOR);
                else          str +=get_string(HBRED"看來仇人已經明了，只是真正的兇手真的是苗人風嗎？"NOR);
                str +=feihu_skill(me);
                return str;
        }   
        str +=get_string(YEL"你已經還原給苗人風和胡斐一個真相，獲得一些獎勵。"NOR);
        
        if(!query("quest/雪山飛狐/解藥篇",me))
        {
                if(random(2)) str +=get_string(HBRED"但是受小人暗算，苗人風中毒生死未明。"NOR);
                else          str +=get_string(HBRED"20年前的舊事已經明了，復仇之說也算一個完結。"NOR);
                str +=feihu_skill(me);
                return str;
        }
        
        if(!query("quest/雪山飛狐/解藥篇/over",me))
        {
                if(random(2)) str +=get_string(HBRED"真相已經明了，而苗人風中毒生死未明。下一步：尋找解藥。"NOR);
                else          str +=get_string(HBRED"20年前的往事已經明了，目前關鍵是如何尋找治療苗人風的解藥。"NOR);
                str +=feihu_skill(me);
                return str;
        }

        str +=get_string(YEL"五毒教，你成功幫助程靈素奪得七星海棠。"NOR);
        str +=get_string(YEL"藥王谷，你成功地煉制解藥成功，獲得一些獎勵。"NOR);
        
        if(!query("quest/雪山飛狐/寶藏",me))
        {
                str +=get_string(HBRED"你已經完成雪山飛狐的基本情節，最後涉及到一個寶藏。"NOR);
                str +=feihu_skill(me);
                return str;
        }

        str +=   "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
        str +=get_string(HIB"【闖王寶藏】"NOR);
        str +=   "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
        if(query("quest/雪山飛狐/寶藏/time",me))
                str +=get_string(WHT"尋寶紀錄時間："+CHINESE_D->chinese_date(query("quest/雪山飛狐/寶藏/time",me),1)+"。"NOR);
        if(query("quest/雪山飛狐/寶藏/combat_exp",me))
        {
                str +=get_string(WHT"尋寶紀錄經驗："+query("quest/雪山飛狐/寶藏/combat_exp",me)+"。"NOR);
                str +="\n";
        }
        if(!query("quest/雪山飛狐/寶藏/start",me))
        {
                str +=get_string(HBRED"你正在尋找傳說中的闖王寶藏。"NOR);
                str +=feihu_skill(me);
                return str;
        }

        str +=get_string(YEL"你已經開始尋找傳說中的闖王寶藏。"NOR);
        if(query("quest/雪山飛狐/寶藏/jinku",me))
                str +=get_string(YEL"你已經從闖王寶藏獲得大量的財寶，包括黃金等等。"NOR);
        if(query("quest/雪山飛狐/寶藏/yaoku", me))
                str +=get_string(YEL"你發現了闖王藥庫，並在藥庫獲得增長內力的神奇靈藥。"NOR);
        if(query("quest/雪山飛狐/寶藏/bingqiku",me))
                str +=get_string(YEL"你已經挖掘出闖王兵器庫的寶物，獲得"+chinese_number(query("quest/雪山飛狐/寶藏/bingqiku",me))+"個寶玉。"NOR);
        if(query("quest/雪山飛狐/寶藏/shuku",me))
                str +=get_string(YEL"你從書房發現到一個密室，並在這裡尋找到增長經驗的神奇靈藥。"NOR);
        if(query("quest/雪山飛狐/武功/lengquanshengong",me))
                str +=get_string(YEL"你竟然從一顆靈藥裡找到一個紙團，並發現冷泉神功秘籍的地點。"NOR);
        else if(query("quest/雪山飛狐/寶藏/shuku",me)>=3)
                str +=get_string(YEL"你從一顆靈藥裡找到一個似乎是修煉武功的紙團，目前只是未得要領。"NOR);
        str +=feihu_skill(me);
        return str;
}
string feihu_skill(object me)
{
        string str= "";

        if(me->query("quest/雪山飛狐/兩頁刀法篇/over"))
        {
                str =   "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
                str +=get_string(HIC"【飛狐武功】"NOR);
                str +=  "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
                if(query("quest/雪山飛狐/武功/time",me))
                        str +=get_string(WHT"武功紀錄時間："+CHINESE_D->chinese_date(query("quest/雪山飛狐/武功/time",me),1)+"。"NOR);
                if(query("quest/雪山飛狐/武功/combat_exp",me))
                {
                        str +=get_string(WHT"武功紀錄經驗："+query("quest/雪山飛狐/武功/combat_exp",me)+"。"NOR);
                        str +="\n";
                }
                if(query("quest/雪山飛狐/武功/fight_hu",me))
                {
                   if(query("quest/雪山飛狐/武功/win_hu",me))
                           str +=get_string(HIC"你曾與胡斐進行過"+chinese_number(query("quest/雪山飛狐/武功/fight_hu",me))+"次較量，並獲得"+chinese_number(query("quest/雪山飛狐/武功/win_hu",me))+"次勝利。"NOR);
                   else
                           str +=get_string(HIC"你曾與胡斐進行過"+chinese_number(query("quest/雪山飛狐/武功/fight_hu",me))+"次較量，可惜一次也沒有勝出。"NOR);
                }

                if(query("quest/雪山飛狐/武功/hujiadaofa",me))
                        str +=get_string(HBYEL"你已經學到了胡家刀法，這門刀法令你的江湖威名大增。"NOR);
                else if(query("quest/雪山飛狐/武功/hujiadaofa_fail",me)>=3 && query("registered",me)<3) // 這個標記有點重復
                        str +=get_string(YEL"你失去了學習胡家刀法的機會，但如果參入VIP，你將獲得新的機會。"NOR);
                else if(query("quest/雪山飛狐/武功/hujiadaofa_fail",me) && query("quest/雪山飛狐/武功/hujiadaofa_fail",me)<3 && query("registered",me)<3)
                        str +=get_string(YEL"你失去了學習胡家刀法的"+chinese_number(query("quest/雪山飛狐/武功/hujiadaofa_fail",me))+"次機會，但你還有"+chinese_number(3-query("quest/雪山飛狐/武功/hujiadaofa_fail",me))+"機會。"NOR);
                else if(query("quest/雪山飛狐/武功/hujiadaofa_fail",me))
                        str +=get_string(YEL"你失去了學習胡家刀法的"+chinese_number(query("quest/雪山飛狐/武功/hujiadaofa_fail",me))+"次機會，但你還有無限機會。"NOR);
                else
                        str +=get_string(HBRED"你現在擁有學習胡家刀法的機會。你可以在適當的時候請教胡斐。"NOR);
       
           if(query("quest/雪山飛狐/解藥篇/over",me))
           {
                   if(query("quest/雪山飛狐/武功/fight_miao",me))
                   {
                           if(query("quest/雪山飛狐/武功/win_miao",me))
                                   str +=get_string(HIC"你曾與苗人鳳進行過"+chinese_number(query("quest/雪山飛狐/武功/fight_miao",me))+"次較量，並獲得"+chinese_number(query("quest/雪山飛狐/武功/win_miao",me))+"次勝利。"NOR);
                           else str +=get_string(HIC"你曾與苗人鳳進行過"+chinese_number(query("quest/雪山飛狐/武功/fight_miao",me))+"次較量，可惜一次也沒有勝出。"NOR);
                   }
                   if(query("quest/雪山飛狐/武功/miaojiajianfa",me))
                           str +=get_string(HBYEL"你已經學到了苗家劍法，很明顯這門劍法對你行走江湖幫助很大。"NOR);
                   else if(query("quest/雪山飛狐/武功/miaojiajianfa_fail",me)>=3 && query("registered",me)<3)
                           str +=get_string(YEL"你浪費了學習苗家劍法的機會，但如果參入VIP，你將獲得新的機會。"NOR);
                   else if(query("quest/雪山飛狐/武功/miaojiajianfa_fail",me) && query("quest/雪山飛狐/武功/miaojiajianfa_fail",me)<3 && query("registered",me)<3)
                           str +=get_string(YEL"你失去了學習苗家劍法的"+chinese_number(query("quest/雪山飛狐/武功/miaojiajianfa_fail",me))+"次機會，但你還有"+chinese_number(3-query("quest/雪山飛狐/武功/miaojiajianfa_fail",me))+"機會。"NOR);
                   else if(query("quest/雪山飛狐/武功/miaojiajianfa_fail",me))
                           str +=get_string(YEL"你失去了學習苗家劍法的"+chinese_number(query("quest/雪山飛狐/武功/miaojiajianfa_fail",me))+"次機會，但你還有無限機會。"NOR);
                   else str +=get_string(HBRED"你現在擁有學習苗家劍法的機會。你可以在適當的時候請教苗人風。"NOR);

                   if(query("quest/雪山飛狐/武功/lengquanshengong_teach",me))
                           str +=get_string(HBYEL"你已經發現苗、胡上代的秘密，並從苗人鳳處領悟到冷泉神功。"NOR);
                   else if(query("quest/雪山飛狐/武功/lengquanshengong",me))
                           str +=get_string(YEL"你似乎馬上要獲得冷泉神功的領悟機會。"NOR);
                   else if(query("quest/雪山飛狐/武功/shuku",me)<3 )
                           str +=get_string(YEL"你還有學習冷泉神功的機會。神功據說在寶藏之中。"NOR);
                   else if(query("quest/雪山飛狐/武功/shuku",me)==3 )
                           str +=get_string(YEL"你遇到過一次學習冷泉神功的機會。可惜沒有成功。"NOR);
                   else if(query("quest/雪山飛狐/武功/shuku",me)>=4 && query("registered",me)>=3)
                           str +=get_string(YEL"你遇到過兩次學習冷泉神功的機會。可惜沒有成功。"NOR);
           }
        }
        return str;
}
string quest_lchj(object me)
{
        string str= "\n";

        if(!query("quest/連城訣",me))
        {
                str =    "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
                str +=get_string(HIW"【目前關于連城訣，沒有任何紀錄】"NOR);
                return str;
        }

        str =   "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
        str +=get_string(HIW"【連城訣】"NOR);
        str +=  "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";

        if(query("quest/連城訣/time",me))
        {
                if(!query("quest/連城訣/武館探密篇/over",me))
                        str +=get_string(WHT"遊戲紀錄時間差："+CHINESE_D->chinese_time(time()-query("quest/連城訣/time",me))+"。"NOR);
                else str +=get_string(WHT"遊戲紀錄時間："+CHINESE_D->chinese_date(query("quest/連城訣/time",me),1)+"。"NOR);
        }
        if(query("quest/連城訣/combat_exp",me))
        {
                if(!query("quest/連城訣/武館探密篇/over",me) && !query("quest/連城訣/武館探密篇/over",me))
                {
                        if(query("combat_exp",me)> query("quest/連城訣/combat_exp",me))
                                str +=get_string(WHT"遊戲紀錄經驗差："+chinese_number(query("combat_exp",me)-query("quest/連城訣/combat_exp",me))+"。"NOR);
                        else if(query("combat_exp",me)== query("quest/連城訣/combat_exp",me))
                                str +=get_string(WHT"遊戲紀錄經驗差沒有任何變化。"NOR);
                        else str +=get_string(WHT"遊戲紀錄經驗超出目前經驗："+chinese_number(query("quest/連城訣/combat_exp",me)-query("combat_exp",me))+"。"NOR);
                }
                else str +=get_string(WHT"最後遊戲紀錄經驗："+query("quest/連城訣/combat_exp",me)+"。"NOR);
                str +="\n";
        }

        if(!query("quest/連城訣/雪谷激鬥篇",me))
        {
                str +=get_string(HBRED"你正在努力中........"NOR);
                str +=lchj_skill(me);
                return str;
        }
        if(!query("quest/連城訣/雪谷激鬥篇/over",me))
        {
                if(random(2)) str +=get_string(HBRED"提示：解密烏蠶衣，尋找雪谷狄雲。"NOR);
                else str +=get_string(HBRED"一段冤案，一段往事，一段驚奇，一段悲情。"NOR);
                str +=lchj_skill(me);
                return str;
        }

        str +=get_string(YEL"你從丁典獲得烏蠶衣，並在雪谷得遇狄雲。"NOR);

        if(!query("quest/連城訣/武館探密篇/over",me))
        {               
                if(random(2)) str +=get_string(HBRED"下一步：密探武館。也許真相永遠將是一個謎。"NOR);
                else          str +=get_string(HBRED"又是傳說中的絕世武功和連城財寶，到底真相如何？"NOR);
                str +=lchj_skill(me);
                return str;
        }
        str +=get_string(YEL"你密探武館，揭開當年冤情，也獲得唐詩選輯。"NOR);
        if(query("quest/連城訣/武館探密篇/baozang",me))
        {
                str +=get_string(YEL"你發現連城寶藏，並從狄雲處得知一切。"NOR);
                str +=get_string(YEL"雖然沒有身外之財，你從中還是獲得部分經驗獎勵。"NOR);
                str +=lchj_skill(me);
                return str;
        }
        str +=lchj_skill(me);
        return str;
}
string lchj_skill(object me)
{
        string str= "";

        if(query("quest/連城訣/雪谷激鬥篇/start",me))
        {
                str =   "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
                str +=get_string(HIB"【連城武功】"NOR);
                str +=  "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
                if(query("quest/連城訣/武功/time",me))
                        str +=get_string(WHT"武功紀錄時間："+CHINESE_D->chinese_date(query("quest/連城訣/武功/time",me),1)+"。"NOR);
                if(query("quest/連城訣/武功/combat_exp",me))
                {
                        str +=get_string(WHT"武功紀錄經驗："+query("quest/連城訣/武功/combat_exp",me)+"。"NOR);
                        str +="\n";
                }
                if(query("quest/連城訣/武功/shenzhao",me)>=2)
                {
                        str +=get_string(HBYEL"你從丁典學到神照經，並更能靈活使用神照絕技。"NOR);
                        str +=get_string(HBYEL"你又從狄雲處獲得一些經驗，對神照經有著更深層次的領悟。"NOR);
                }       
                else if(query("quest/連城訣/武功/shenzhao",me)==1)
                {
                        str +=get_string(HBYEL"你從丁典學到神照經，並更能靈活使用神照絕技。"NOR);
                        if(query("quest/連城訣/雪谷激鬥篇/over",me))
                        {
                           if(query("quest/連城訣/武功/shenzhao_fail2",me)>=3 && query("registered",me)<3)
                           {
                                   str +=get_string(YEL"但是你失去了從狄雲處學習神照經更高層次的領悟機會。"NOR);
                                   str +=get_string(YEL"當然，如果你參入VIP，你將獲得新的領悟機會。"NOR);
                           }
                           else if(query("quest/連城訣/武功/shenzhao_fail2",me) && query("quest/連城訣/武功/shenzhao_fail2",me) <3 && query("registered",me)<3)
                                   str +=get_string(YEL"你失去了狄雲處領悟神照經的"+chinese_number(query("quest/連城訣/武功/shenzhao_fail2",me))+"次機會，但你還有"+chinese_number(3-query("quest/連城訣/武功/shenzhao_fail2",me))+"機會。"NOR);
                           else if(query("quest/連城訣/武功/shenzhao_fail2",me))
                                   str +=get_string(YEL"你失去了狄雲處領悟神照經的"+chinese_number(query("quest/連城訣/武功/shenzhao_fail2",me))+"次機會，但你還有無限機會。"NOR);
                           else str +=get_string(HBRED"你現在擁有從狄雲處領悟更高層次神照經的機會。你可以在適當的時候請教狄雲。"NOR);
                   }
                } 
                else if(query("quest/連城訣/武功/shenzhao_fail",me)>=3 && query("registered",me)<3)
                        str +=get_string(YEL"你失去從丁典領悟神照經的機會，但如果參入VIP，你將獲得新的機會。"NOR);
                else if(query("quest/連城訣/武功/shenzhao_fail",me) && query("quest/連城訣/武功/shenzhao_fail",me)<3 && query("registered",me)<3)
                        str +=get_string(YEL"你失去從丁典領悟神照經的"+chinese_number(query("quest/連城訣/武功/shenzhao_fail",me))+"次機會，但你還有"+chinese_number(3-query("quest/連城訣/武功/shenzhao_fail",me))+"機會。"NOR);
                else if(query("quest/連城訣/武功/shenzhao_fail",me))
                        str +=get_string(YEL"你失去從丁典領悟神照經的"+chinese_number(query("quest/連城訣/武功/shenzhao_fail",me))+"次機會，但你還有無限機會。"NOR);
                else str +=get_string(HBRED"你現在擁有領悟神照經的機會。你可以在適當的時候請教丁典。"NOR);
        
                if(query("quest/連城訣/雪谷激鬥篇/over",me))
                {
                        if(query("quest/連城訣/武功/sword",me))
                                str +=get_string(HBYEL"你從狄雲學習到躺屍劍法，並更能靈活各種絕技。"NOR);
                        else if(query("quest/連城訣/武功/sword_fail",me)>=3 && query("registered",me)<3)
                        {
                                str +=get_string(YEL"但是你失去學習從狄雲處躺屍劍法的機會。\n"NOR);
                                str +=get_string(YEL"當然，如果你參入VIP，你將獲得新的領悟機會。"NOR);
                        }
                        else if(query("quest/連城訣/武功/sword_fail",me) && query("quest/連城訣/武功/sword_fail",me) <3 && query("registered",me)<3)
                                str +=get_string(YEL"你失去學習躺屍劍法的"+chinese_number(query("quest/連城訣/武功/sword_fail",me))+"次機會，但你還有"+chinese_number(3-query("quest/連城訣/武功/sword_fail",me))+"機會。"NOR);
                        else if(query("quest/連城訣/武功/sword_fail",me))
                                str +=get_string(YEL"你失去學習躺屍劍法的"+chinese_number(query("quest/連城訣/武功/sword_fail",me))+"次機會，但你還有無限機會。"NOR);
                        else str +=get_string(HBRED"你現在擁有學習躺屍劍法的機會。你可以在適當的時候請教狄雲。"NOR);
                }
        }
        return str;
}
string quest_tlbb(object me)
{
        string str= "\n";

        if(!query("quest/天龍八部",me))
        {
                str =    "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
                str +=get_string(HIW"【目前關于天龍八部，沒有任何紀錄】"NOR);
                return str;
        }

        str =   "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
        str +=get_string(HIW"【天龍八部】"NOR);
        str +=  "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";

        if(query("quest/天龍八部/time",me))
        {
                if(!query("quest/天龍八部/復興天下篇/over",me) && !query("quest/天龍八部/大遼救援篇/over",me))
                        str +=get_string(WHT"遊戲紀錄時間差："+CHINESE_D->chinese_time(time()-query("quest/天龍八部/time",me))+"。"NOR);
                else str +=get_string(WHT"遊戲紀錄時間："+CHINESE_D->chinese_date(query("quest/天龍八部/time",me),1)+"。"NOR);
        }
        if(query("quest/天龍八部/combat_exp",me))
        {
                if(!query("quest/天龍八部/復興天下篇/over",me) && !query("quest/天龍八部/大遼救援篇/over",me))
                {
                        if(query("combat_exp",me)> query("quest/天龍八部/combat_exp",me))
                                str +=get_string(WHT"遊戲紀錄經驗差："+chinese_number(query("combat_exp",me)-query("quest/天龍八部/combat_exp",me))+"。"NOR);
                        else if(query("combat_exp",me)== query("quest/天龍八部/combat_exp",me))
                                str +=get_string(WHT"遊戲紀錄經驗差沒有任何變化。"NOR);
                        else str +=get_string(WHT"遊戲紀錄經驗超出目前經驗："+chinese_number(query("quest/天龍八部/combat_exp",me)-query("combat_exp",me))+"。"NOR);
                }
                else str +=get_string(WHT"最後遊戲紀錄經驗："+query("quest/天龍八部/combat_exp",me)+"。"NOR);
                str +="\n";
        }

        if(!query("quest/天龍八部/凌波微步篇",me))
        {
                str +=get_string(HBRED"你正在努力中........"NOR);
                str +=tlbb_skill(me);
                return str;
        }
        if(!query("quest/天龍八部/凌波微步篇/over",me))
        {
                if(!query("quest/天龍八部/凌波微步篇/wuliangover",me))
                {
                        if(random(2)) str +=get_string(HBRED"如何尋找段譽，據說在無量山。正在探索中。"NOR);
                        else str +=get_string(HBRED"尋找失蹤的段譽中，注意別忘記隨便解密凌波微步和北溟神功。"NOR);
                }
                else
                {
                        if(random(2)) str +=get_string(HBRED"從無量山回來的段譽卻被劫持到萬劫谷。正在探索中。"NOR);
                        else str +=get_string(HBRED"尋找失蹤的段譽中，注意小心有高手阻截。"NOR);
                }
                return str;
        }

        str +=get_string(YEL"你已經將段譽從萬劫谷救回，並獲得一些獎勵。"NOR);

        if(!query("quest/天龍八部/天龍營救篇/over",me))
        {               
                if(random(2)) str +=get_string(HBRED"下一步：天龍寺大戰。倒霉的段譽又牽涉其中，當然只有你來幫忙。"NOR);
                else          str +=get_string(HBRED"西夏第一佛法高僧，武功也是深不可測，能阻止他的只有你了。"NOR);
                str +=tlbb_skill(me);
                return str;
        }

        str +=get_string(YEL"你阻大輪高手于殿外，救段譽于西夏，並獲得一些獎勵。"NOR);

        if(!query("quest/天龍八部/蕭峰身世篇/over",me))
        {
                if(random(2)) str +=get_string(HBRED"誰是小人，誰是英雄，中原舊事，究竟多少秘密被湮滅。"NOR);
                else          str +=get_string(HBRED"竹林驚變，聚閒莊大戰，頌摩崖遺魂，歷史還我真相..."NOR);
                str +=tlbb_skill(me);
                return str;
        }
        str +=get_string(YEL"聚閒莊，你解救了蕭峰成功脫離現場；"NOR);
        str +=get_string(YEL"頌摩崖，你成功揭開崖壁遺書的秘密。"NOR);
        if(query("quest/天龍八部/蕭峰身世篇/good",me))
                str +=get_string(YEL"你更是成功說服了蕭峰歸隱江湖，獲得部分獎勵。"NOR);
        if(query("quest/天龍八部/蕭峰身世篇/bad",me))
                str +=get_string(YEL"你更是成功了擊退了契丹人蕭峰，獲得部分獎勵。"NOR);

        if(query("quest/天龍八部/復興天下篇/start",me))
        {
                if(!query("quest/天龍八部/復興天下篇/over",me))
                        str +=get_string(HBRED"為獨霸武林，聯手慕容，江湖上，畢竟還是得看拳頭的。"NOR);
                else 
                        str +=get_string(YEL"你獨闖少林大敗群丐，擊退無名神僧與蕭峰聯手，為天下第一。"NOR);
                str +=tlbb_skill(me);
                return str;
        }
        if(query("quest/天龍八部/大遼救援篇/start",me))
        {
                if(!query("quest/天龍八部/大遼救援篇/over",me))
                        str +=get_string(HBRED"蕭峰為百姓找想，誓不戰爭，此人當要救的。只是危險重重。"NOR);
                else 
                        str +=get_string(YEL"你完勝中原群雄，並潛入大遼，成功營救蕭峰，為俠義豪傑。"NOR);
                str +=tlbb_skill(me);
                return str;
        }
        str +=tlbb_skill(me);
        return str;
}
string tlbb_skill(object me)
{
        string str= "";

        if(query("quest/天龍八部/武功", me))
        {
                str =   "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
                str +=get_string(HIC"【天龍武功】"NOR);
                str +=  "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
                if(query("quest/天龍八部/武功/time",me))
                        str +=get_string(WHT"最後學習紀錄時間："+CHINESE_D->chinese_date(query("quest/天龍八部/武功/time",me),1)+"。"NOR);
                if(query("quest/天龍八部/武功/combat_exp",me))
                {
                        str +=get_string(WHT"最後學習紀錄經驗："+query("quest/天龍八部/武功/combat_exp",me)+"。"NOR);
                        str +="\n";
                }
                if(query("quest/天龍八部/武功/yuxiang",me))
                {            
                        if(query("quest/天龍八部/凌波微步篇/over",me))
                                str +=get_string(YEL"你找到MM的玉像，並獲得一些提示。你獲得記載凌波微步的帛卷。"NOR);
                        else
                                str +=get_string(YEL"你找到MM的玉像，並獲得一些提示。"NOR);
                }
                if(query("quest/天龍八部/北冥神功/pass",me))
                        str +=get_string(HBYEL"在無量山洞中你已經學到了北冥神功絕學。"NOR);
                else if(query("quest/天龍八部/北冥神功/fail",me)>=3 && query("registered",me)<3)
                {
                        str +=get_string(YEL"但是你浪費了學習北冥神功的機會。"NOR);
                        str +=get_string(YEL"當然，如果你參入VIP，你將獲得新的領悟機會。"NOR);
                }
                else if(query("quest/天龍八部/北冥神功/fail",me))
                {
                        str +=get_string(YEL"但是你失去了學習北冥神功的"+chinese_number(query("quest/天龍八部/北冥神功/fail",me))+"次機會。"NOR);
                        str +=get_string(YEL"但你還有機會學習，新的帛卷可以從玉像處重新獲得。"NOR);
                }
                else str +=get_string(HBRED"你現在擁有學習北冥神功的機會。"NOR);
        
                if(query("quest/天龍八部/武功/pass",me))
                        str +=get_string(HBYEL"並從中已經學到了凌波微步。"NOR);
                else if(query("quest/天龍八部/武功/fail",me)>=3 && query("registered",me)<3)
                {
                        str +=get_string(YEL"但是你浪費了學習凌波微步的機會。"NOR);
                        str +=get_string(YEL"當然，如果你參入VIP，你將獲得新的領悟機會。"NOR);
                }
                else if(query("quest/天龍八部/武功/fail",me))
                {
                        str +=get_string(YEL"但是你失去了學習凌波微步的"+chinese_number(query("quest/天龍八部/武功/fail",me))+"次機會。"NOR);
                        str +=get_string(YEL"但你還有機會學習，新的帛卷可以從玉像處重新獲得。"NOR);
                }
                else str +=get_string(HBRED"你現在擁有學習凌波微步的機會。"NOR);
        }
        if(query("quest/tonglao/quest",me))
        {
                if(query("quest/tonglao/pass",me))
                        str +=get_string(YEL"你曾"+chinese_number(query("quest/tonglao/quest",me))+"次見到天山燈火，偶救天山童姥，並學到絕世武功。"NOR);
                else if(query("quest/tonglao/second",me))
                        str +=get_string(YEL"你曾"+chinese_number(query("quest/tonglao/quest",me))+"次見到天山燈火，偶救天山童姥。"NOR); 
                else str +=get_string(YEL"你曾"+chinese_number(query("quest/tonglao/quest",me))+"次見到天山燈火，但什麼也沒發現。"NOR);
        }

        if(query("quest/天龍八部/武功/quanli",me))
                str +=get_string(HBYEL"你從蕭峰那裡領悟到“返璞歸真”的武功真諦。"NOR);
        return str;
}

string quest_shediao(object me)
{
        string str= "\n";

        if(!me->query("quest/射雕英雄傳"))
        {
                str =    "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
                str +=get_string(HIW"【目前關于射雕英雄傳，沒有任何紀錄】"NOR);
                return str;
        }

        str =   "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
        str +=get_string(HIW"【射雕英雄傳】"NOR);
        str +=  "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";

        if(query("quest/射雕英雄傳/time",me))
        {
                if(!query("quest/射雕英雄傳/風雪驚變/over",me) )
                        str +=get_string(WHT"遊戲紀錄時間差："+CHINESE_D->chinese_time(time()-query("quest/射雕英雄傳/time",me))+"。"NOR);
                else str +=get_string(WHT"遊戲紀錄時間："+CHINESE_D->chinese_date(query("quest/射雕英雄傳/time",me),1)+"。"NOR);
        }
        if(query("quest/射雕英雄傳/combat_exp",me))
        {
                if(!query("quest/射雕英雄傳/風雪驚變/over",me) )
                {
                        if(query("combat_exp",me)> query("quest/射雕英雄傳/combat_exp",me))
                                str +=get_string(WHT"遊戲紀錄經驗差："+chinese_number(query("combat_exp",me)-query("quest/射雕英雄傳/combat_exp",me))+"。"NOR);
                        else if(query("combat_exp",me)== query("quest/射雕英雄傳/combat_exp",me))
                                str +=get_string(WHT"遊戲紀錄經驗差沒有任何變化。"NOR);
                        else str +=get_string(WHT"遊戲紀錄經驗超出目前經驗："+chinese_number(query("quest/射雕英雄傳/combat_exp",me)-query("combat_exp",me))+"。"NOR);
                                str +=get_string(HIC"你已經成功救下楊鐵心、郭嘯天兩位大俠，並獲得一些獎勵。"NOR);
                }
                else str +=get_string(WHT"最後遊戲紀錄經驗："+query("quest/射雕英雄傳/combat_exp",me)+"。"NOR);
                str +="\n";
        }
        else
        {

        }

        str +=shediao_skill(me);
        return str;
}

string shediao_skill(object me)
{
        string str= "";

        if(query("quest/射雕英雄傳/yangjiaqiang",me))
        {
                str =   "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
                str +=get_string(HIC"【射雕武功】"NOR);
                str +=  "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
                if(query("quest/射雕英雄傳/yangjiaqiang/time",me))
                        str +=get_string(WHT"最後學習紀錄時間："+CHINESE_D->chinese_date(query("quest/射雕英雄傳/yangjiaqiang/time",me),1)+"。"NOR);
                if(query("quest/射雕英雄傳/yangjiaqiang/combat_exp",me))
                {
                        str +=get_string(WHT"最後學習紀錄經驗："+query("quest/射雕英雄傳/yangjiaqiang/combat_exp",me)+"。"NOR);
                        str +="\n";
                }
                if(query("quest/射雕英雄傳/風雪驚變/over",me))
                {            
                                str +=get_string(YEL"你成功救援郭嘯天、楊鐵心兩家，並獲得一些獎勵。"NOR);
                }
                if(query("quest/射雕英雄傳/yangjiaqiang/pass",me))
                        str +=get_string(HBYEL"並從中已經學到了楊家槍。"NOR);
                else if(query("quest/射雕英雄傳/yangjiaqiang/fail",me)>=3 && query("registered",me)<3)
                {
                        str +=get_string(YEL"但是你浪費了學習楊家槍的機會。"NOR);
                        str +=get_string(YEL"當然，如果你參入VIP，你將獲得新的學習機會。"NOR);
                }
                else if(query("quest/射雕英雄傳/yangjiaqiang/fail",me))
                {
                        str +=get_string(YEL"但是你失去了學習楊家槍的"+chinese_number(query("quest/射雕英雄傳/yangjiaqiang/fail",me))+"次機會。"NOR);
                        str +=get_string(YEL"但你還有機會學習，在適當的時候可以去尋找楊鐵心請教。"NOR);
                }
                else str +=get_string(HBRED"你現在擁有學習楊家槍的機會。"NOR);
        }
        if(query("quest/jiuyin1/pass",me))
                str +=get_string(HBYEL"你從周伯通處獲得了聞名天下九陰真經上卷。"NOR);
        if(query("quest/jiuyin2/pass",me))
                str +=get_string(HBYEL"你從陳玄風處獲得了臭名昭著九陰真經下卷。"NOR);
        return str;
}

string quest_tulong(object me)
{
        string str= "";
        return str;
}

string tulong_skill(object me)
{
        string str= "";
        return str;
}

string get_string(string str)
{
        return sprintf("%|60s",str)+"\n";
}
int help(object me)
{
        write("
□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
             指令格式 : "+YEL"story <......>"NOR"
□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
"HIW"這個命令可以讓你很清楚地了解你story已經揭開的程度。你也可以使
用這個命令得到一點下一步的提示。"NOR"
□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□"YEL"
                story  獲得所有紀錄
          story feihu  獲得雪山飛狐紀錄
           story tlbb  獲得天龍八部記錄
           story lchj  獲得連城訣記錄
         story tulong  獲得倚天屠龍記錄
         story <玩家>  巫師專用查詢命令
 story ...<form 玩家>  巫師專用查詢命令"NOR"
□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
"HIC"目前只開放雪山飛狐、天龍八部、連城訣、射雕英雄傳和倚天屠龍記。"NOR"
□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□
                  \n"NOR);
return 1;
}
