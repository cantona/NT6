// This program is a part of NT MudLIB
// 教會玩家熟悉遊戲

#include <ansi.h>

inherit F_DBASE;

#define LINE   "------------------------------------------------------------------"

string *keys_gift_list;

mapping gift_name = ([
        "exp"         :  "經驗",
        "pot"         :  "潛能",
        "mar"         :  "體會",
        "neili"       :  "內力",
        "jingli"      :  "精力",
        "gold"        :  "黃金（存銀行)",
        "gongxian"    :  "門派貢獻",
        "fuzhong"     :  "負重",
        "riding"      :  "騎術",
        "training"    :  "馭獸術",     
        "hunting"     :  "狩獵技巧",
        "weiwang"     :  "威望",
        "score"       :  "閱歷",
        "tianfu"      :  "先天天賦",
        "horse"       :  "騎馬記錄點",
        "quitsave"    :  "下線保存所有物品",
]);

mapping gift_list = ([

        "1"   :   ([ "達成條件" : "了解如何開始玩遊戲",
                     "條件標識" : "newbie_mygift/help",
                     "條件數值" : 1,
                     "條件描述" : "輸入指令 help start 查看相關資訊",
                     "獎勵描述" : "/clone/goods/zhufu_cloth:1,neili:1000",
                     "下個獎勵" : "2", ]),

        "2"   :   ([ "達成條件" : "查看自己的方位",
                     "條件標識" : "newbie_mygift/map",
                     "條件數值" : 1,    
                     "條件描述" : "輸入指令 map 查看自己所在方位\n"
                                  HIR "              提示：地圖中藍色底色位置為你當前所在位置。" NOR,
                     "獎勵描述" : "/clone/goods/zhufu_boots:1,jingli:1000",
                     "下個獎勵" : "3", ]),

        "3"   :   ([ "達成條件" : "在線2分鐘",
                     "條件標識" : "mud_age",
                     "條件數值" : 120,
                     "條件描述" : "在線達到兩分鐘",
                     "獎勵描述" : "/clone/goods/zhufu_armor:1,/clone/gift/xiandan:8",
                     "下個獎勵" : "4", ]),
                     
        "4"   :   ([ "達成條件" : "查看新聞",
                     "條件標識" : "newbie_mygift/news",
                     "條件數值" : 1,    
                     "條件描述" : "輸入指令 news 查看遊戲新聞",
                     "獎勵描述" : "/clone/goods/zhufu_head:1,/clone/gift/xisuidan:8",
                     "下個獎勵" : "5", ]),

        "5"   :   ([ "達成條件" : "閱讀文選",
                     "條件標識" : "newbie_mygift/wenxuan",
                     "條件數值" : 1,
                     "條件描述" : "輸入指令 wenxuan 顯示年度文選信息",
                     "獎勵描述" : "/clone/goods/zhufu_waist:1,/clone/gift/shenliwan:8",
                     "下個獎勵" : "6", ]),
                     
        "6"   :   ([ "達成條件" : "查看 msg 功能",
                     "條件標識" : "newbie_mygift/msg",
                     "條件數值" : 1,
                     "條件描述" : "輸入指令 msg 顯示最近收到的信息",
                     "獎勵描述" : "/clone/goods/zhufu_wrists:1,/clone/gift/unknowdan:8",
                     "下個獎勵" : "7", ]),

        "7"   :   ([ "達成條件" : "查詢新手導師",
                     "條件標識" : "newbie_mygift/who",
                     "條件數值" : 1,
                     "條件描述" : "輸入指令 who -v 顯示所有的新手導師",
                     "獎勵描述" : "/clone/goods/zhufu_surcoat:1,/clone/item/magicfruit:8",
                     "下個獎勵" : "8", ]),
                     
        "8"   :   ([ "達成條件" : "查詢所有的附加屬性",
                     "條件標識" : "newbie_mygift/istat",
                     "條件數值" : 1,
                     "條件描述" : "輸入指令 istat 顯示所有的附加屬性",
                     "獎勵描述" : "/clone/goods/zhufu_sword:1,quitsave:8035200,exp:100000,pot:50000",
                     "下個獎勵" : "9", ]),
                     
        "9"   :   ([ "達成條件" : "了解能力點作用",
                     "條件標識" : "newbie_mygift/ability",
                     "條件數值" : 1,
                     "條件描述" : "輸入指令 help ability 了解能力點作用",
                     "獎勵描述" : "/clone/goods/zhufu_blade:1,tianfu:4,/adm/npc/obj/gift:1",
                     "下個獎勵" : "10", ]),
                                          
        "10"  :   ([ "達成條件" : "闖盪江湖",
                     "條件標識" : "newbie_quest_completed/can_out",
                     "條件數值" : 1,    
                     "條件描述" : "從古村離開（完成所有古村任務並離開）\n" 
                                  HIR "              提示：根據導師--老村長的提示先完成古村任務後才能出村。\n"
                                      "              在世界之樹輸入指令" HIY "ask lao 出村" HIR "，根據提示完成任務才能出村。\n" NOR,
                     "獎勵描述" : "/clone/goods/dizangshi:1,pot:50000,riding:100,training:100,fuzhong:1",
                     "下個獎勵" : "12", ]),
                     
        "12"  :   ([ "達成條件" : "制造如意乾坤袋",
                     "條件標識" : "can_summon/qiankun",
                     "條件數值" : 1,    
                     "條件描述" : "制造如意乾坤袋\n" 
                                  HIR "              提示：在揚州城醉仙樓找到狂風，ask kuang about all，制作如意乾坤袋。\n" NOR,
                     "獎勵描述" : "/clone/fam/gift/int3:3,gold:2",
                     "下個獎勵" : "14", ]),

        "14"  :   ([ "達成條件" : "與魔幻獸簽訂血之盟約",
                     //"條件標識" : "newbie_mygift/warcraft",
                     "條件標識" : "can_whistle",
                     "條件數值" : 1,    
                     "條件描述" : "與魔幻獸簽訂血之盟約\n" 
                                  HIR "              提示：在揚州城醉仙樓找到狂風，打聽魔幻獸的事。\n" NOR,
                     "獎勵描述" : "/clone/fam/gift/str3:3,horse:1",
                     "下個獎勵" : "16", ]),
                     
        "16"  :   ([ "達成條件" : "利用坐騎瞬間到達北京",  
                     "條件標識" : "newbie_mygift/rideto",
                     "條件數值" : 1,
                     "條件描述" : "利用坐騎瞬間達到北京\n" 
                                  HIR "              提示：ride 魔幻獸，使用指令"HIY" rideto beijing " NOR,
                     "獎勵描述" : "/clone/fam/gift/con3:3",
                     "下個獎勵" : "18", ]),

        "18"  :   ([ "達成條件" : "使用 recall back 回到揚州",  
                     "條件標識" : "newbie_mygift/recall",
                     "條件數值" : 1,
                     "條件描述" : "使用指令 recall back 回到揚州客店\n",
                     "獎勵描述" : "/clone/fam/gift/dex3:3",
                     "下個獎勵" : "20", ]),
                     
        "20"  :   ([ "達成條件" : "了解 bug 回報",  
                     "條件標識" : "newbie_mygift/bug",
                     "條件數值" : 1,
                     "條件描述" : "使用指令 help bug 了解bug回報\n",
                     "獎勵描述" : "/clone/goods/study-emblem:1",
                     "下個獎勵" : "25", ]),     

        "25"   :   ([ "達成條件" : "使用 do 串連指令",
                     "條件標識" : "newbie_mygift/do",
                     "條件數值" : 1,
                     "條件描述" : "輸入 do <串連指令>\n"
                                  HIR "              提示：輸入"HIY"help do2"HIR"查看幫助，然後使用指令"HIY" do w,w 或 do 2 w " NOR,
                     "獎勵描述" : "/clone/goods/bigu-fu:1",
                     "下個獎勵" : "30", ]),

        "30"  :   ([ "達成條件" : "使用儲物櫃",
                     "條件標識" : "newbie_mygift/cangku",
                     "條件數值" : 1,
                     "條件描述" : "到揚州錢莊的儲物櫃看看吧，了解下怎麼使用儲物櫃\n" 
                                  HIR "              提示：揚州錢莊，輸入指令"HIY"cw help"HIR"查看即可。" NOR,
                     "獎勵描述" : "/clone/armor/jinsi-shoutao2:1",
                     "下個獎勵" : "35", ]),
                                                  
        "35"  :   ([ "達成條件" : "拜師成功",
                     "條件標識" : "family/family_name",
                     "條件數值" : 1,
                     "條件描述" : "加入一個喜歡的門派,\n" 
                                  HIR "              提示：有關門派詳情參見 help family" NOR,
                     "獎勵描述" : "gongxian:10000,score:3000,weiwang:50",
                     "下個獎勵" : "40", ]),

        "40"  :   ([ "達成條件" : "查詢技能絕招",
                     "條件標識" : "newbie_mygift/skill",
                     "條件數值" : 1,
                     "條件描述" : "輸入指令 skill lonely-sword 顯示獨孤九劍絕招信息",
                     "獎勵描述" : "neili:1000,gongxian:5000",
                     "下個獎勵" : "45", ]),
                     
        "45"  :   ([ "達成條件" : "造訪海龜",
                     "條件標識" : "newbie_mygift/haigui",
                     "條件數值" : 1,
                     "條件描述" : "造訪一下新手練功法寶海龜\n" 
                                  HIR "              提示：輸入"HIY"rideto"HIR"查看騎馬可到達地方，然後"HIY"do rideto nanhai,n,e"HIR"前往。" NOR,
                     "獎勵描述" : "neili:1000,gongxian:2000",
                     "下個獎勵" : "50", ]),

        "50"  :   ([ "達成條件" : "造訪神雕",
                     "條件標識" : "newbie_mygift/shendiao",
                     "條件數值" : 1,
                     "條件描述" : "造訪新人練功法寶神雕\n" 
                                  HIR "              提示：輸入"HIY"rideto"HIR"查看騎馬可到達地方，然後"HIY"rideto shendiao"HIR"前往。" NOR,
                     "獎勵描述" : "neili:1500,jingli:1000,gongxian:2000",
                     "下個獎勵" : "55", ]),

        "55"  :   ([ "達成條件" : "加入幫派",
                     "條件標識" : "bunch",
                     "條件數值" : 1,
                     "條件描述" : "加入任意幫派\n" 
                                  HIR "              提示：可以在聊天頻道"HIY"chat 想說的話"HIR"找人入幫，詳情查看 help bunch.2\n"
                                      "                    如果沒有玩家幫派可以參加npc幫派，詳情查看help bunch_quest" NOR,
                     "獎勵描述" : "pot:20000,weiwang:5000,neili:500,jingli:500",
                     "下個獎勵" : "60", ]),

        "60"  :   ([ "達成條件" : "完成幫派任務",
                     "條件標識" : "bunch_quest",
                     "條件數值" : 1,
                     "條件描述" : "完成所在的幫派發布的幫派任務\n" 
                                  HIR "              提示：有關幫派任務詳情參見 help bunch_quest" NOR,
                     "獎勵描述" : "exp:20000,weiwang:2000,neili:500,jingli:500",
                     "下個獎勵" : "65", ]),
                                          
        "65"  :   ([ "達成條件" : "完成師門任務",
                     "條件標識" : "quest_count",
                     "條件數值" : 1,
                     "條件描述" : "找到門派掌門或任務發布師傅領取師門任務並完成\n" 
                                  HIR "              提示：有關師門任務的詳情參見 help quest" NOR,
                     "獎勵描述" : "exp:10000,pot:10000,gongxian:5000",
                     "下個獎勵" : "70", ]),

        "70"  :   ([ "達成條件" : "尋找帝王符圖",
                     "條件標識" : "quest_tuteng",
                     "條件數值" : 1,
                     "條件描述" : "到南賢處打聽尋找帝王符圖\n"
                                  HIR "              提示：有關尋找帝王符圖任務的詳情參見 help tuteng" NOR,
                     "獎勵描述" : "exp:10000,pot:10000,mar:10000",
                     "下個獎勵" : "75", ]), 

        "75"  :   ([ "達成條件" : "進入【原始森林】副本",
                     "條件標識" : "newbie_mygift/fuben",
                     "條件數值" : 1,
                     "條件描述" : "進入【原始森林】副本，從副本中走出\n" 
                                  HIR "              提示：騎馬到昆明，找到沼澤邊緣輸入"HIY"enter door"HIR"進入副本。" NOR,
                     "獎勵描述" : "exp:20000,pot:20000",
                     "下個獎勵" : "80", ]),
                     
        "80"  :   ([ "達成條件" : "造訪幹將、莫邪",
                     "條件標識" : "newbie_mygift/ganjiang",
                     "條件數值" : 1,
                     "條件描述" : "拜訪一下幹將莫邪吧，以後還得經常到這裡改造兵器\n" 
                                  HIR "              提示：輸入"HIY"rideto"HIR"查看騎馬可到達地方，然後"HIY"rideto ganjiang"HIR"前往。" NOR,
                     "獎勵描述" : "exp:20000,pot:20000,/clone/money/gold:1",
                     "下個獎勵" : "85", ]),

        "85"  :   ([ "達成條件" : "裝備簽名",
                     "條件標識" : "newbie_mygift/makeweapon",
                     "條件數值" : 1,
                     "條件描述" : "是時候擁有一把屬于自己的裝備了，裝備簽名說明參見help weapon", 
                     "獎勵描述" : "/clone/armor/shuijing-guan:1",
                     "下個獎勵" : "90", ]),

        "90"  :   ([ "達成條件" : "找張天師開光",
                     "條件標識" : "newbie_mygift/kaiguang",
                     "條件數值" : 1,
                     "條件描述" : "將剛簽名的裝備開光吧，這樣隨時可以召喚(summon)回來\n" 
                                  HIR "              提示：幹將附近找到張天師，使用指令"HIY"show <武器ID>"HIR"，按\n"
                                      "                    照後續提示操作即可進行開光。" NOR,
                     "獎勵描述" : "/clone/armor/zhanyao-xunzhang:1",
                     "下個獎勵" : "95", ]),

        "95"  :  ([ "達成條件" : "博學多才（一）",
                     "條件標識" : "newbie_mygift/certosina",
                     "條件數值" : 1,
                     "條件描述" : "學習鑲嵌技藝到一百級\n" 
                                  HIR "              提示：到魯班處學習，指令"HIY"xue lu ban certosina"HIR"學習。" NOR,
                     "獎勵描述" : "/clone/armor/moling-zhiyi:1,/clone/armor/sheyao-ring:1",
                     "下個獎勵" : "100", ]),

        "100"  :  ([ "達成條件" : "裝備開孔",
                     "條件標識" : "newbie_mygift/notch",
                     "條件數值" : 1,
                     "條件描述" : "將裝備進行開孔，開孔後可以鑲嵌寶石\n" 
                                  HIR "              提示：幹將處notch <裝備>，開孔需要的符文詳情參見 help rune" NOR,
                     "獎勵描述" : "exp:1000000,pot:1000000,/clone/armor/wushi-pifeng:1",
                     "下個獎勵" : "110", ]),
                                          
        "110"  :   ([ "達成條件" : "合成任意物品",
                     "條件標識" : "newbie_mygift/combine",
                     "條件數值" : 1,
                     "條件描述" : "查看物品合成公式，合成出一個任意物品\n" 
                                  HIR "              提示：有關合成物品的詳情參見 help combine" NOR,
                     "獎勵描述" : "exp:10000,pot:10000,gongxian:5000",
                     "下個獎勵" : "120", ]),

        "120"  :  ([ "達成條件" : "成為一品煉藥師",
                     "條件標識" : "is_alchemy",
                     "條件數值" : 1,
                     "條件描述" : "提升煉丹術到300級\n" 
                                  HIR "              提示：煉丹術到300級後，到平一指那裡鑒定煉藥師品級。" NOR,
                     "獎勵描述" : "exp:100000,pot:100000,/clone/armor/shuijing-guan:1",
                     "下個獎勵" : "130", ]),

        "130"  :  ([ "達成條件" : "武學宗師",
                     "條件標識" : "opinion/ultra",
                     "條件數值" : 1,
                     "條件描述" : "挑戰成為武學大宗師，說明可參見help feature\n" 
                                  HIR "              提示：騎馬依次造訪四大宗師，使用指令"HIY"ask <宗師NPC ID> about 評價"HIR"後，根據提示\n"
                                      "                    再輸入指令"HIY"fight <宗師NPC ID>"HIR"進行挑戰。" NOR,
                     "獎勵描述" : "exp:2000000,pot:2000000,mar:2000000",
                     "下個獎勵" : "140", ]),
                     
        "140"  :  ([ "達成條件" : "博學多才（二）",
                     "條件標識" : "newbie_mygift/jingluoxue",
                     "條件數值" : 1,
                     "條件描述" : "學習經絡學到一百級",
                     "獎勵描述" : "pot:5000000,neili:500,jingli:500,gold:500",
                     "下個獎勵" : "150", ]),

        "150"  :  ([ "達成條件" : "打通陰蹺脈",
                     "條件標識" : "newbie_mygift/yinqiaomai",
                     "條件數值" : 1,
                     "條件描述" : "購買陰蹺脈所有銅人，打通第一條小周天經脈--陰蹺脈\n" 
                                  HIR "              提示：在英雄商店購買陰蹺脈所有銅人，詳情參見 help chongxue" NOR,
                     "獎勵描述" : "/clone/goods/tianshi-charm:1",
                     "下個獎勵" : "160", ]),
                                          
        "160"  :  ([ "達成條件" : "打通大小周天經脈",
                     "條件標識" : "breakup",
                     "條件數值" : 1,
                     "條件描述" : "沖穴打通大小周天經脈，你的能力將更大提升。\n" 
                                  HIR "              提示：閉關說明可參見 help zhoutian" NOR,
                     "獎勵描述" : "mar:3000000,neili:1000,jingli:1000",
                     "下個獎勵" : "170", ]),
                     
        "170"  :  ([ "達成條件" : "裝備強化",
                     "條件標識" : "newbie_mygift/qianghua",
                     "條件數值" : 1,
                     "條件描述" : "將裝備進行強化，強化後的裝備屬性大幅度提升\n" 
                                  HIR "              提示：幹將處先shou <裝備>，看完要求後qianghua <裝備>，強化裝備詳情參見 help qianghua" NOR,
                     "獎勵描述" : "pot:3000000,neili:1000,jingli:1000",
                     "下個獎勵" : "180", ]),

        "180"  :  ([ "達成條件" : "裝備綠化",
                     "條件標識" : "newbie_mygift/dosuit",
                     "條件數值" : 1,
                     "條件描述" : "將裝備進行綠化，綠化後的裝備組成套裝，擁有極品屬性\n" 
                                  HIR "              提示：先給幹將王者之心，然後dosuit <裝備>，綠化裝備詳情參見 help suit" NOR,
                     "獎勵描述" : "exp:5000000,pot:5000000,mar:5000000,/clone/armor/yecha1:1",
                     "下個獎勵" : "190", ]),
        /*
        "170"  :  ([ "達成條件" : "修煉元嬰出世",
                     "條件標識" : "animaout",
                     "條件數值" : 1,
                     "條件描述" : "提升你的能力，閉關修煉元嬰出世\n" 
                                  HIR "              提示：閉關說明可參見 help closed" NOR,
                     "獎勵描述" : "pot:3000000,neili:1000,jingli:1000",
                     "下個獎勵" : "180", ]),
            
        "180"  :  ([ "達成條件" : "打通生死玄關",
                     "條件標識" : "death",
                     "條件數值" : 1,
                     "條件描述" : "提升你的能力，閉關打通生死玄關\n" 
                                  HIR "              提示：閉關說明可參見 help closed" NOR,
                     "獎勵描述" : "exp:5000000,pot:5000000,mar:5000000,/clone/armor/yecha1:1",
                     "下個獎勵" : "190", ]),                 
        */
        "190"  :  ([ "達成條件" : "轉世重生",
                     "條件標識" : "reborn/times",
                     "條件數值" : 1,
                     "條件描述" : "武學無止境，唯轉世重生突破瓶頸\n" 
                                  HIR "              提示：轉世說明可參見 help reborn" NOR,
                     "獎勵描述" : "exp:10000000,pot:10000000,mar:10000000",
                     "下個獎勵" : "200", ]),

        "200"  :  ([ "達成條件" : "等待下一個挑戰", // 這個版本開發至此，後續開發則從這裡開始
                     "條件標識" : "newbie_mygift/waitfor_next1",
                     "條件數值" : 1,
                     "條件描述" : "等待下一個挑戰吧，敬請留意後續挑戰內容！\n" 
                                  HIR "              提示：任務告一段落，請留意後續任務的通告！" NOR,
                     "獎勵描述" : "pot:10000000",
                     "下個獎勵" : "210", ]),
]);


// 外部調用，用于判斷是否有指定任務且觸發了完成任務條件檢測
public void check_mygift(object me, string quest_flag)
{
        string nquest;
        if( !me || !quest_flag ) return;
        if( !nquest = query("newbie_mygift/cur_quest_number", me) )
                return ;
        
        if( gift_list[nquest]["條件標識"] == quest_flag )
        {
                if( gift_list[nquest]["條件數值"] > 1 )
                        addn(gift_list[nquest]["條件標識"], 1, me);
                else
                        set(gift_list[nquest]["條件標識"], 1, me);
                
                me->save();
        }
        return;
}

void create()
{
        seteuid(getuid());
        set("channel_id", "新人獎勵精靈");   
        set("no_clean_up", 1);
        CHANNEL_D->do_channel(this_object(), "sys", "新人獎勵系統已經啟動。");

        keys_gift_list = keys(gift_list);
}

// 判斷字符串是否是物品獎勵
int is_obgift(string arg)
{
        if( strsrch(arg, "/") == -1 )
                return 0;
                
        return 1;
}

// 返回 exp:3334 格式的獎勵描述
string sub_gift_desc(string arg)
{
        string sdesc, sgift;
        object ob;
        int ncount;
        
        sscanf(arg, "%s:%d", sgift, ncount);
        
        sdesc = "";
        // 判斷是否是物品
        if( is_obgift(sgift) )
        {
                if( !objectp(ob = find_object(sgift)) )
                        ob = load_object(sgift);
                        
                if( !ob ) return "error:" + sgift;

                sdesc = filter_color(ob->name()) + "x" + sprintf("%d",ncount);
        }
        else
        {
                sdesc = gift_name[sgift] + "+" + 
                        (ncount >= 10000 ? sprintf("%d萬", ncount / 10000):sprintf("%d", ncount));
        }       
        
        return sdesc;
}

// 格式化後的獎勵描述
// exp:10000000_pot:10000000_mar:10000000_/clone/armor/zhanyao-xunzhang:1
string gift_desc(string arg)
{
        object ob;
        string sdesc, *keys_list;
        int i;
        
        sdesc = "";
        
        // 判斷是否是單個獎勵
        if( strsrch(arg, ",") == -1 )
        {       
                sdesc = sub_gift_desc(arg);
        }
        else // 多個獎勵
        {
                keys_list = explode(arg, ",");
                
                for( i = 0; i < sizeof(keys_list); i ++ )
                {
                        sdesc += sub_gift_desc(keys_list[i]);
                        if( i < sizeof(keys_list) - 1 )
                                sdesc += "、";
                }
        }
        
        return sdesc;
}

// 顯示任務描述
string mygift_string(mapping mygift_map)
{
        string squest, sgift_desc;
        
        squest = HIC + LINE + "\n";
        
        squest += "【任務名稱】：" + mygift_map["達成條件"] + "\n";
        squest += "【達成條件】：" + mygift_map["條件描述"] + "\n";
        squest += HIY "【任務獎勵】：" + gift_desc(mygift_map["獎勵描述"]) + "\n";
        squest += HIC + LINE + "\n" NOR;
        
        return squest;
}

// 分派一個任務
void give_mygift(object me, string s)
{
        string squest;
        
        set("newbie_mygift/cur_quest_number", s, me);
        
        // 提示
        squest = HIR "【你獲得新的輔助任務】 指令 " HIY "mygift" HIR" 查看當前輔助任務" + BLINK + HIC "    新任務" + NOR "\n" ;
        squest += mygift_string(gift_list[s]);
        
        tell_object(me, squest);
        
        return;
}


// 給予獎勵子功能調用
string sub_gift_send(object me, string arg)
{
        string sdesc, sgift;
        object ob;
        int ncount, i;
        
        sscanf(arg, "%s:%d", sgift, ncount);
        
        sdesc = "";
        // 判斷是否是物品
        if( is_obgift(sgift) )
        {
                if( !objectp(ob = find_object(sgift)) )
                        ob = load_object(sgift);

                if( !ob )
                {
                        write(HIR + sgift + "讀取錯誤！\n");
                        log_file("mygiftd", "來自mygiftd：" + sgift + "物品錯誤！\n");
                        return;
                }
                
                // 給予物品。。。
                // 不能分開使用的物品單獨處理
                ob = new(sgift);
                if( !objectp(ob) )
                {
                        write(HIR + sgift + "讀取錯誤-2！\n");
                        log_file("mygiftd", "來自mygiftd：" + sgift + "復制物品錯誤！\n");
                        return;                 
                }
                if( !ob->query_amount() )
                {
                        for (i = 1; i <= ncount; i ++)
                        {
                                reset_eval_cost();
                                ob->move(me, 1);
                                set("bindable", 3, ob);
                                set("bind_owner", query("id", me), ob);
                                set("set_data", 1, ob);
                                set("auto_load", 1, ob);
                                ob = new(sgift);                                                
                        }
                }
                else
                {
                        ob->set_amount(ncount);
                        ob->move(me, 1);
                        set("bindable", 3, ob);
                        set("bind_owner", query("id", me), ob);
                        set("no_sell", 1, ob);
                        set("set_data", 1, ob);
                        set("auto_load", 1, ob);
                }
                
                
                sdesc = HIY "-獲得物品：" +  filter_color(ob->name()) + "x" + sprintf("%d",ncount) + "\n" NOR;
        }
        else
        {
                // 獎勵。。。
                switch(sgift)
                {
                        case "exp":
                                addn("combat_exp", ncount, me);
                        break;
                        
                        case "pot":
                                addn("potential", ncount,  me);
                        break;

                        case "mar":
                                addn("experience", ncount, me);
                        break;
                                                
                        case "gongxian":
                                addn("family/gongji", ncount, me);
                        break;
                        
                        case "gold":
                                addn("balance", ncount*10000, me);
                        break;

                        case "neili":
                                addn("drug_addneili", ncount, me);
                                addn("max_neili", ncount,  me);
                                if( query("neili", me)<query("max_neili", me) )
                                        set("neili",query("max_neili",  me), me);
                        break;
                
                        case "jingli":
                                addn("drug_addjingli", ncount, me);
                                addn("max_jingli", ncount, me);
                                if( query("jingli", me)<query("max_jingli", me) )
                                        set("jingli",query("max_jingli", me), me);
                        break;

                        case "fuzhong":
                                addn("add_max_encumbrance", 50000, me);
                        break;
                        
                        case "riding":
                                if( me->query_skill("riding") < ncount )
                                        me->set_skill("riding", ncount);
                        break;
                        
                        case "hunting":
                                if( me->query_skill("hunting") < ncount )
                                        me->set_skill("hunting", ncount);
                        break;

                        case "training":
                                if( me->query_skill("training") < ncount )
                                        me->set_skill("training", ncount);
                        break;
                        
                        case "weiwang":
                                addn("weiwang", ncount, me);
                        break;

                        case "score":
                                addn("score", ncount, me);
                        break;

                        case "tianfu":
                                addn("tianfu", ncount, me);
                        break;
                        
                        case "horse":
                                addn("horse/stone", 1, me);
                        break;
                        
                        case "quitsave":
                                me->set_srv("quit_save", 8035200);
                        break;
                        
                        default:
                                write("類型錯誤。\n");
                                return;
                        break;
                }
                
                sdesc = HIY "-獲得獎勵" + gift_name[sgift] + "+" + sprintf("%d",ncount) + "\n" NOR;
        }
        
        return sdesc;
}

// 給予獎勵
void give_gift(object me, string arg)
{
        int i, count;
        object ob;
        string *keys_list, sgift, sdesc;
                
        
        set("newbie_mygift/is_running_gift_list_send", 1, me);

        sdesc = "";
        // 判斷是否是單個獎勵
        if( strsrch(arg, ",") == -1 )
        {       
                sdesc += sub_gift_send(me, arg);
        }
        else // 多個獎勵
        {
                keys_list = explode(arg, ",");
                
                for( i = 0; i < sizeof(keys_list); i ++ )
                {
                        sdesc += sub_gift_send(me, keys_list[i]);
                }
        }
        
        delete("newbie_mygift/is_running_gift_list_send", me);
        me->save();
        
        write(sdesc);
        
        return;
}

// /cmds/usr/mygift 調用 
int mygift(object me, string arg)
{
        string squest, nquest;
        string splayer;
        object ob;
        
        int i;
        
        // 顯示當前任務
        if( !objectp(me) )return 0;
                
        if( !arg )
        {
                if( !nquest=query("newbie_mygift/cur_quest_number", me) )
                        return notify_fail("你當前沒有輔助任務信息！\n");
                
                squest = mygift_string(gift_list[nquest]);
        
                squest = HIG "【當前輔助任務如下】\n" + squest; 
                
                me->start_more(squest);
                
                return 1;               
        }
        
        if( arg == "list" )
        {
                if( !wizardp(me) ) return 0;
                
                // 顯示所有獎勵任務的詳細內容，主要用于校驗
                squest = "【校驗所有任務】\n";

                for( i = 0; i < sizeof(keys_gift_list); i ++ )
                {
                        squest += mygift_string(gift_list[keys_gift_list[i]]) + "\n";
                }
                
                write(squest);
                
                return 1;
        }
        else if( sscanf(arg, "give %s %s", splayer, nquest) == 2 )
        {
                if( !wizardp(me) ) return 0;
                
                // 手動給玩家分派指定編號的任務
                if( !objectp(ob = find_player(splayer)) )
                        return notify_fail("目標玩家不在線！\n");
                
                if( member_array(nquest, keys_gift_list) == -1 )
                        return notify_fail("沒有指定編號的任務，使用 mygift list 查看所有任務列表。\n");
                
                give_mygift(ob, nquest);
                
                return 1;
                
        }
        

        return 1;
        
}

// 外部調用，檢查當前是否存在已經完成的任務，來自玩家心跳調用
public void check_curgift(object me)
{
        mapping tmap;
        string nquest;
        
        if( !objectp(me) ) return;
        
        if( !query("newbie_mygift/cur_quest_number", me) )
                return;

        // 正在處理獎勵中則返回
        if( query("newbie_mygift/is_running_gift_list_send", me) ) return ;
        
        // 判斷是否完成
        nquest=query("newbie_mygift/cur_quest_number", me);
        tmap = gift_list[nquest];
        
        if( !intp(query(tmap["條件標識"], me)) || query(tmap["條件標識"], me) >= tmap["條件數值"] )
        {
                // 發放獎勵
                write(HIG + "【" + tmap["達成條件"]+ "】" BLINK + HIM "任務達成：\n" NOR);
                give_gift(me, tmap["獎勵描述"]);

                // 給予下一個任務
                give_mygift(me, tmap["下個獎勵"]);
        }
        
        return;
}
