// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// equipmentd.c

#pragma optimize
#pragma save_binary

inherit F_DBASE;
#include <equipment.h>

#define EQUIP_DIR       "/inherit/template/"
#define EQUIP_LIST      CONFIG_DIR "equiplist/"

/*
a 物理攻擊類
增加attack（固定）
增加傷害（隨機）
b  物理防禦
增加氣血抗性（固定）
增加額外氣血和護甲（隨機）
增及氣血恢復（隨機）
c 魔法攻擊
增加attack（固定）
增加魔法傷害（隨機）
d 魔法防禦
增加 魔法抗性（固定）
增加額外心神和精力（隨機）
f 治療輸出
增加療傷比例（固定）
增加法力、靈力（隨機）
增加法力 靈力恢復（隨機）
g 對友方的增強buff
增加buff 持續時間（固定）
增加隊伍羣傷（隨機）
增加隊伍羣抗（隨機）
h 對怪物的debuff
增加buff 持續時間（固定）
減少怪物抗性（隨機）
眩暈        停止對方出手
盲目        降低對方命中30%
定身        降低對方閃避30%
遲緩        降低對方攻擊速度的50%
混亂        在一定回合內攻擊隨機目標，包括己方隊友
*/
// 神佑 戰鬥時當HP=0時，20%的機率出現神佑復活效果，復活以後擁有少量HP
// 破防提高：我的理解是在目前破防的技術上增加一個比例。比如破防提高10％，那麼如果你破防10點，就變成了11點。
// 命中加強：説實話，我看不出它有什麼作用來。
// 雙倍打擊：在你造成傷害的基礎上，加2倍，重要的一個屬性。比例越高越好。
// 致命打擊：非常重要的屬性，造成比例打血效果。
// 比如火代表眩暈 水代表招式變慢 金代表持續傷害命中 木代表致盲
// 殺戮-攻擊時有機率對當前房間所有人進行一次攻擊
// 還有 5行可以是 急速 暴擊 格擋（減免傷害） 精通  命中
// 急速就是增加出招的機率 暴擊是雙倍傷害機率 格擋是減免30%傷害機率。命中是無視閃避招架的機率 精通是perform傷害加成
// 7個防具5孔，2個兵器7孔，3個飾品3孔
// 所有屬性
mapping value_2_props = ([
        "consistence"   : "耐久度",     // 基本屬性           a
        "damage"        : "兵器傷害力", // 基本屬性           a
        "unarmed_damage": "空手傷害力", // 基本屬性           a
        "armor"         : "保護力",     // 基本屬性           a
        "damage1"       : "附加傷害",   // weapon             a
        "armor1"        : "附加保護",   // armor              a
       
        "str"           : "臂力",       // weapon/armor/rings a
        "int"           : "悟性",       // weapon/armor/rings a
        "con"           : "根骨",       // weapon/armor/rings a
        "dex"           : "身法",       // weapon/armor/rings a
        "kar"           : "福緣",       // weapon/armor/rings a
        "per"           : "容貌",       // rings              a
        "gold_find"     : "獲取黃金機率",     // weapon/rings a
        

        "max_jingli"    : "精力最大值", // weapon/armor/rings a
        "max_jing"      : "精氣最大值", // weapon/armor/rings a
        "max_potential" : "潛能上限",   // weapon/armor/rings a
        "max_experience": "體會上限",   // weapon/armor/rings a

        "sword"         : "劍法",       // weapon             a
        "blade"         : "刀法",       // weapon             a
        "club"          : "棍法",       // weapon             a
        "hammer"        : "錘法",       // weapon             a
        "staff"         : "杖法",       // weapon             a
        "whip"          : "鞭法",       // weapon             a
        "unarmed"       : "拳腳",       // weapon             a
        "strike"        : "掌法",       // weapon             a
        "cuff"          : "拳法",       // weapon             a
        "hand"          : "手法",       // weapon             a
        "finger"        : "指法",       // weapon             a
        "claw"          : "爪法",       // weapon             a

        "attack"        : "攻擊",       // weapon             a
        "parry"         : "招架",       // armor              a
        "dodge"         : "躲閃",       // armor              a
        "defense"       : "防禦",       // armor              a

        "research_times": "研究次數",   // weapon/armor/rings a
        "learn_times"   : "學習次數",   // weapon/armor/rings a
        "practice_times": "練習次數",   // weapon/armor/rings a
        "study_times"   : "讀書次數",   // weapon/armor/rings a
]);        
        
mapping value_3_props = ([        
        "attribute"     : "所有屬性",   // rings              b
        "max_neili"     : "內力最大值", // weapon/armor/rings b
        "max_qi"        : "氣血最大值", // weapon/armor/rings b
        "ref_neili"     : "內力恢復",   // armor/rings        b
        "ref_qi"        : "生命恢復",   // armor/rings        b
        "ref_jing"      : "精氣恢復",   // armor/rings        b

        "add_poison"    : "毒傷害",     // weapon                           b
        "add_metal"     : "金傷害",     // weapon                           b
        "add_wood"      : "木傷害",     // weapon                           b
        "add_water"     : "水傷害",     // weapon                           b
        "add_fire"      : "火傷害",     // weapon                           b
        "add_earth"     : "土傷害",     // weapon                           b
        "reduce_metal"  : "抗金",       // armor                            b
        "reduce_wood"   : "抗木",       // armor                            b
        "reduce_water"  : "抗水",       // armor                            b
        "reduce_fire"   : "抗火",       // armor                            b
        "reduce_earth"  : "抗土",       // armor                            b
        "reduce_poison" : "抗毒",       // armor                            b
        "avoid_poison"  : "忽視中毒",   // armor/rings                      b

        "research_effect"       : "研究效果",   // weapon/armor/rings       b
        "practice_effect"       : "練習效果",   // weapon/armor/rings       b
        "study_effect"          : "讀書效果",   // weapon/armor/rings       b
        "learn_effect"          : "學習效果",   // weapon/armor/rings       b
        "derive_effect"         : "汲取效果",   // weapon/armor/rings       b
        "derive_times"          : "汲取消耗",   // weapon/armor/rings       b

        "add_pot"       : "獲取額外潛能",       // weapon/rings   b
        "add_mar"       : "獲取額外體會",       // weapon/rings   b
]);    

mapping value_5_props = ([             
        "magic_find"    : "尋寶率(MF值)",       // weapon/rings             c
        "ap_power"      : "絕招攻擊力",         // weapon/rings             c
        "dp_power"      : "絕招防禦力",         // armor                    c
        "da_power"      : "絕招傷害力",         // weapon/rings             c
        "avoid_defense" : "攻擊無視目標防禦",   // weapon/rings             c
        "avoid_parry"   : "攻擊無視目標招架",   // weapon/rings             c
        "avoid_dodge"   : "攻擊無視目標躲閃",   // weapon/rings             c
        "avoid_force"   : "攻擊無視內功防禦",   // weapon/rings             c
        "avoid_attack"  : "無視目標特殊攻擊",   // armor                    c
        "suck_neili"    : "偷取內力",           // weapon 命中偷取內力機率：命中敵人時按傷害值的10%率回覆內力   c
        "suck_qi"       : "偷取生命",           // weapon 命中偷取生命機率：命中敵人時按傷害值的10%比率回覆生命 c
        "double_damage" : "雙倍傷害",           // weapon/rings 增加殺氣：加一點殺氣，暴擊（雙倍傷害）的概率增加1%  c
        "through_armor" : "破甲",               // weapon/rings 破甲-攻擊時無視目標防具的保護力through_armor        c        
        "qi_vs_neili"   : "受損的生命轉為內力", // rings 30%的機會受損的生命x%轉換為內力  c   
        "absorb_blood"  : "天魔附體",           // weapon/rings 提高自身戰鬥力30%         c

        "add_reward"    : "獲取額外獎勵",       // weapon/rings   c
        "add_exp"       : "獲取額外經驗",       // weapon/rings   c
        "add_force"     : "獲取額外先天真氣",   // weapon/rings   c        
        "add_blind"     : "致盲",               // weapon 終極兵器 致盲-讓對手失明 c
        "avoid_blind"   : "忽視致盲",           // armor/rings 終極防具            c
]);

mapping value_10_props = ([          
        "clear_force"   : "破氣",                       // weapon 破除對手所有內力，讓對手內力為0 d       
        "add_freeze"    : "冰凍",                       // weapon 終極兵器 冰凍-遲緩，減緩對方攻擊，攻擊pfm速度降低，無任何防禦，無躲閃，無招架，就是捱打 d
        "add_dizziness" : "眩暈",                       // weapon 終極兵器 眩暈，不能進行任何行動，受到攻擊會醒來，否則5秒內一直不動，解除戰鬥狀態 d
        "add_forget"    : "遺忘",                       // weapon 終極防具 遺忘-使對方忘記所有技能的絕招add_oblivion    d
        "add_weak"      : "虛弱",                       // weapon 終極兵器 讓對手攻防傷害減半，包括絕招                 d
        "add_busy"      : "忙亂",                       // weapon 終極兵器                                              d

        "avoid_freeze"  : "忽視冰凍",                   // armor/rings 終極防具 d
        "avoid_dizziness": "忽視眩暈",                  // armor/rings 終極防具 d
        "avoid_forget"  : "忽視遺忘",                   // armor/rings 終極兵器 d
        "avoid_weak"    : "忽視虛弱",                   // armor/rings 終極防具 d
        "avoid_busy"    : "忽視忙亂",                   // armor/rings 終極防具 d
        "reduce_busy"   : "化解忙亂",                   // armor/rings 終極防具 d

        "fatal_blow"    : "必殺率",                     // weapon 終極兵器 必殺率-擁有20%的機率損傷目標的生命x%     d                                    d
        "slaughter"     : "殺戮",                       // weapon 殺戮-攻擊時有機率對當前房間所有敵人進行一次攻擊   d  
        "add_skill"     : "提升技能",                   // weapon/rings 終極兵器                                    d
        "add_damage"    : "追加傷害",                   // weapon 終極兵器                                          d
        "reduce_damage" : "化解傷害",                   // armor 終極防具                                           d
        "full_self"     : "戰神附體",                   // armor 終極防具 戰神附體-氣血內力自動恢復                 d
        "avoid_die"     : "浴血重生",                   // armor/ring 鳳凰涅槃，浴血重生，忽視死亡                  d
        "counter_damage": "傷害反射",                   // armor 終極防具 傷害反射受到傷害時30%機率的傷害x%反射給對方 d
]);

// 所有屬性
mapping all_props = ([
        "consistence"   : "耐久度",     // 基本屬性
        "damage"        : "兵器傷害力", // 基本屬性
        "unarmed_damage": "空手傷害力", // 基本屬性
        "armor"         : "保護力",     // 基本屬性
        "damage2"       : "改造傷害",   // weapon
        "armor2"        : "改造保護",   // armor
        "damage1"       : "附加傷害",   // weapon
        "armor1"        : "附加保護",   // armor
       
        "str"           : "臂力",       // weapon/armor/rings
        "int"           : "悟性",       // weapon/armor/rings
        "con"           : "根骨",       // weapon/armor/rings
        "dex"           : "身法",       // weapon/armor/rings
        "kar"           : "福緣",       // weapon/armor/rings
        "per"           : "容貌",       // rings
        "attribute"     : "所有屬性",   // rings
        
        "max_neili"     : "內力最大值", // weapon/armor/rings
        "max_qi"        : "氣血最大值", // weapon/armor/rings
        "max_jingli"    : "精力最大值", // weapon/armor/rings
        "max_jing"      : "精氣最大值", // weapon/armor/rings
        "max_potential" : "潛能上限",   // weapon/armor/rings
        "max_experience": "體會上限",   // weapon/armor/rings

        "sword"         : "劍法",       // weapon
        "blade"         : "刀法",       // weapon
        "club"          : "棍法",       // weapon
        "hammer"        : "錘法",       // weapon
        "staff"         : "杖法",       // weapon
        "whip"          : "鞭法",       // weapon
        "unarmed"       : "拳腳",       // weapon
        "strike"        : "掌法",       // weapon
        "cuff"          : "拳法",       // weapon
        "hand"          : "手法",       // weapon
        "finger"        : "指法",       // weapon
        "claw"          : "爪法",       // weapon

        "attack"        : "攻擊",       // weapon
        "parry"         : "招架",       // armor
        "dodge"         : "躲閃",       // armor
        "defense"       : "防禦",       // armor

        "ref_neili"     : "內力恢復",   // armor/rings
        "ref_qi"        : "生命恢復",   // armor/rings
        "ref_jing"      : "精氣恢復",   // armor/rings
        "suck_neili"    : "偷取內力",   // weapon 命中偷取內力機率：命中敵人時按傷害值的10%率回覆內力
        "suck_qi"       : "偷取生命",   // weapon 命中偷取生命機率：命中敵人時按傷害值的10%比率回覆生命

        "gold_find"     : "獲取黃金機率",       // weapon/rings
        "magic_find"    : "尋寶率(MF值)",       // weapon/rings
                
        // 火焰傷害，冷凍傷害，閃電傷害，毒素傷害，抗火，抗寒，抗閃電，抗毒
        "add_poison"    : "毒傷害",     // weapon
        "add_metal"     : "金傷害",     // weapon
        "add_wood"      : "木傷害",     // weapon
        "add_water"     : "水傷害",     // weapon
        "add_fire"      : "火傷害",     // weapon
        "add_earth"     : "土傷害",     // weapon   
        "reduce_metal"  : "抗金",       // armor
        "reduce_wood"   : "抗木",       // armor
        "reduce_water"  : "抗水",       // armor
        "reduce_fire"   : "抗火",       // armor
        "reduce_earth"  : "抗土",       // armor
        "reduce_poison" : "抗毒",       // armor
        "avoid_poison"  : "忽視中毒",   // armor/rings

        "research_effect"       : "研究效果",   // weapon/armor/rings
        "practice_effect"       : "練習效果",   // weapon/armor/rings
        "study_effect"          : "讀書效果",   // weapon/armor/rings
        "learn_effect"          : "學習效果",   // weapon/armor/rings
        "derive_effect"         : "汲取效果",   // weapon/armor/rings
        "research_times"        : "研究次數",   // weapon/armor/rings
        "learn_times"           : "學習次數",   // weapon/armor/rings
        "practice_times"        : "練習次數",   // weapon/armor/rings
        "study_times"           : "讀書次數",   // weapon/armor/rings
        "derive_times"          : "汲取消耗",   // weapon/armor/rings
        // 以上都是基本屬性 
        
        "ap_power"      : "絕招攻擊力",         // weapon/rings
        "dp_power"      : "絕招防禦力",         // armor
        "da_power"      : "絕招傷害力",         // weapon/rings
        "avoid_defense" : "攻擊無視目標防禦",   // weapon/rings
        "avoid_parry"   : "攻擊無視目標招架",   // weapon/rings
        "avoid_dodge"   : "攻擊無視目標躲閃",   // weapon/rings
        "avoid_force"   : "攻擊無視內功防禦",   // weapon/rings
        "avoid_attack"  : "無視目標特殊攻擊",   // armor
        
        //"trace"         : "擒蹤",       // weapon/rings 無視對方招架
        //"escape"        : "遁隱",       // armor 躲閃機率
        //"proficient"    : "精通",       // weapon/rings 精通是perform傷害加成
        //"fatal_chance"  : "暴擊",       // weapon/rings 會心一擊
        //"antifatal_chance": "防暴擊",   // armor
   
        "attack_chance" : "連擊率",             // weapon/rings 急速就是增加出招的機率
        "double_damage" : "雙倍傷害",           // weapon/rings 增加殺氣：加一點殺氣，暴擊（雙倍傷害）的概率增加1%
        "through_armor" : "破甲",               // weapon/rings 破甲-攻擊時無視目標防具的保護力through_armor
        
        "qi_vs_neili"   : "受損的生命轉為內力", // rings 30%的機會受損的生命x%轉換為內力
        "clear_force"   : "破氣",               // weapon
        
        //"block_heal"    : "防止對手自療",       // weapon
        "absorb_blood"  : "天魔附體",           // weapon/rings 提高自身戰鬥力30%

        "add_reward"    : "獲取額外獎勵",       // weapon/rings
        "add_exp"       : "獲取額外經驗",       // weapon/rings
        "add_pot"       : "獲取額外潛能",       // weapon/rings
        "add_mar"       : "獲取額外體會",       // weapon/rings
        "add_force"     : "獲取額外先天真氣",   // weapon/rings

        // 對友方的增強buff
        // 羣體治療
        // 對怪物的debuff
        
        "add_blind"     : "致盲",                       // weapon 終極兵器 致盲-讓對手失明
        "add_freeze"    : "冰凍",                       // weapon 終極兵器 冰凍-遲緩，減緩對方攻擊，攻擊pfm速度降低，無任何防禦，無躲閃，無招架，就是捱打
        //"add_burning"   : "灼燒",                       // weapon 終極兵器 灼燒-一定時間內目標不停的減少內力和氣血condition
        "add_dizziness" : "眩暈",                       // weapon 終極兵器 眩暈，不能進行任何行動，受到攻擊會醒來，否則5秒內一直不動，解除戰鬥狀態
        "add_forget"    : "遺忘",                       // weapon 終極防具 遺忘-使對方忘記所有技能的絕招add_oblivion   
        "add_weak"      : "虛弱",                       // weapon 終極兵器
        "add_busy"      : "忙亂",                       // weapon 終極兵器

        "avoid_blind"   : "忽視致盲",                   // armor/rings 終極防具
        "avoid_freeze"  : "忽視冰凍",                   // armor/rings 終極防具
        //"avoid_burning" : "忽視灼燒",                   // armor/rings 終極防具
        "avoid_dizziness": "忽視眩暈",                  // armor/rings 終極防具
        "avoid_forget"  : "忽視遺忘",                   // armor/rings 終極兵器
        "avoid_weak"    : "忽視虛弱",                   // armor/rings 終極防具
        "avoid_busy"    : "忽視忙亂",                   // armor/rings 終極防具
        "reduce_busy"   : "化解忙亂",                   // armor/rings 終極防具

        "fatal_blow"    : "必殺率",                     // weapon 終極兵器 必殺率-擁有20%的機率損傷目標的生命x%     
        "anti_fatal"    : "忽視必殺",                   // armor/rings
        "slaughter"     : "殺戮",                       // weapon 殺戮-攻擊時有機率對當前房間所有敵人進行一次攻擊     
        "add_skill"     : "提升技能",                   // weapon/rings 終極兵器
        "add_damage"    : "追加傷害",                   // weapon 終極兵器
        "reduce_damage" : "化解傷害",                   // armor 終極防具 
        "full_self"     : "戰神附體",                   // armor 終極防具 戰神附體-氣血內力自動恢復
        "avoid_die"     : "浴血重生",                   // armor/ring 鳳凰涅槃，浴血重生，忽視死亡
        "counter_damage": "傷害反射",                   // armor 終極防具 傷害反射，受到傷害時30%機率的傷害x%反射給對方
]);


// 寶石分為4個等級，碎片，完好1，稀有1+1，神之1+2
// 一個固定的屬性(金木水火土)+1-2個隨機屬性

// 百分比的屬性
string *percent_props = ({
        "gold_find", "magic_find", "add_metal", "add_wood", "add_water", "add_fire", "add_earth", 
        "add_poison", "reduce_metal", "reduce_fire", "reduce_wood", "reduce_water", "reduce_earth",
        "reduce_poison", "avoid_poison", "research_effect", "learn_effect", "practice_effect", 
        "derive_effect", "study_effect", "ap_power", "dp_power", "da_power", "avoid_attack", 
        "avoid_defense", "avoid_parry", "avoid_dodge", "avoid_force", "trace,escape", "attack_chance",
        "double_damage", "through_armor", "qi_vs_neili", "block_heal", "absorb_blood", "add_reward",
        "add_exp", "add_pot", "add_mar", "add_force", "add_blind", "add_freeze", "add_dizziness",
        "add_forget", "add_weak", "avoid_blind", "avoid_freeze", "avoid_dizziness", "clear_force",
        "avoid_forget", "avoid_weak", "avoid_busy", "fatal_blow", "anti_fatal", "slaughter",
        "add_damage", "reduce_damage", "full_self", "avoid_die", "counter_damage", "suck_neili", "suck_qi",
});

// 寶石屬性值
mapping prop_values = ([
        "damage1"       : ({ 600, 800, 1000, 1200, 1400, 1600, 2000, }),
        "armor1"        : ({ 300, 400, 500, 600, 700, 800, 900, }),
        "damage2"       : ({ 4600, 6600, 9600, 13600, 18600, 24600, 31600, 39600, 50000, }),
        "armor2"        : ({ 2200, 2900, 3700, 4600, 5600, 7700, 8900, 10200, 11500, }),
        
        "str,con,dex,int,kar,per"     : ({ 1, 2, 3, }),         // 200
        "attribute"     : ({ 1, 2, 3, }),       // 27
        
        "max_qi"        : ({ 2500, 3500, 4500, }),              // 200000
        "max_jing"      : ({ 1200, 1700, 2200, }),              // 100000
        "max_jingli"    : ({ 2500, 3500, 4500, }),              // 200000
        "max_neili"     : ({ 6000, 8000, 10000, }),             // 500000
        "max_potential,max_experience"  : ({ 30000, 40000, 50000, }),   // 2000000
        
        "attack,sword,blade,hammer,staff,club,whip,unarmed,strike,cuff,hand,finger,claw": ({ 100, 150, 200, }),        // 500
        "defense,parry,dodge"  : ({ 50, 60, 70, }),

        "ref_jing,ref_qi"       : ({ 10, 15, 20, }),    // 1000
        "ref_neili"     : ({ 20, 30, 40, }),
        "suck_qi,suck_neili"  : ({ 2, 3, 4, }),   // 1000
        
        "gold_find"     : ({ 2, 3, 4, }),       // 92
        "magic_find"    : ({ 1, 2, 3, }),       // 70
        
        "add_metal,add_wood,add_water,add_fire,add_earth"    : ({ 1, 2, 3, }),       // 42
        "add_poison"    : ({ 1, 2, 3, }),       // 42
        "reduce_metal,reduce_fire,reduce_wood,reduce_water,reduce_earth"     : ({ 1, 1, 1, }), // 35
        "reduce_poison,avoid_poison"    : ({ 1, 1, 1, }),       // 44
        
        "research_times,learn_times,practice_times,derive_times,study_times"    : ({ 5, 10, 15, }),    // 1000
        "research_effect,learn_effect,practice_effect,derive_effect,study_effect"       : ({ 1, 2, 3, }), // 180
                
        "ap_power,dp_power,da_power"    : ({ 1, 2, 3, }),       // 70
        "avoid_attack,avoid_defense,avoid_parry,avoid_dodge,avoid_force": ({ 1, 2, 3, }),       // 70
        
        "trace,escape"  : ({ 1, 2, 3, }),       
        "attack_chance" : ({ 1, 2, 3, }),       // 70
        "double_damage,through_armor"   : ({ 1, 2, 3, }),       // 70
        "qi_vs_neili"   : ({ 5, 6, 7, }),       // 63
        "block_heal"    : ({ 3, 4, 5, }),       // 63
        "clear_force"   : ({ 1, 2, 3, }),
        "absorb_blood"  : ({ 1, 2, 3, }),       // 70
        
        "add_reward"    : ({ 1, 2, 3, }),       // 70
        "add_exp,add_pot,add_mar,add_force"     : ({ 2, 3, 4, }),       // 92
        
        "add_blind,add_freeze,add_dizziness,add_forget,add_weak,add_busy"   : ({ 1, 2, 3 }),        // 42 
        "avoid_blind,avoid_freeze,avoid_dizziness,avoid_forget,avoid_weak,avoid_busy,reduce_busy" : ({ 1, 1, 1, }), // 44
        "fatal_blow"    : ({ 3, 4, 5, }),       // 60
        "anti_fatal"    : ({ 1, 1, 1 }),        
        "slaughter"     : ({ 1, 2, 3 }),        // 42
        "add_skill"     : ({ 10, 15, 20, }),    // 500
        "add_damage"    : ({ 3, 4, 5, }),       // 60
        "reduce_damage" : ({ 1, 1, 1, }),       // 35
        "full_self"     : ({ 1, 1, 1, }),       // 35
        "avoid_die"     : ({ 1, 1, 1, }),       // 44
        "counter_damage": ({ 1, 1, 1, }),       // 70
]);

// 屬性強化值1-9星
mapping steady_values = ([
        "damage1,damage2"       : ({ 4600,6600,9600,13600,18600,24600,31600,39600,50000 }),
        "armor1,armor2"         : ({ 2200,2900,3700,4600,5600,7700,8900,10200,11500 }),
        
        "str,con,dex,int,kar,per,attribute"     : ({ 5, 7, 9, 11, 14, 17, 20, 25, 30, }),
        
        "max_qi"        : ({ 1000, 2000, 3000, 5000, 7000, 9000, 12000, 15000, 20000, }),
        "max_jing"      : ({ 500, 1000, 1500, 2500, 3500, 4500, 6000, 7500, 10000, }),
        "max_jingli"    : ({ 1000, 2000, 3000, 5000, 7000, 9000, 12000, 15000, 20000, }),
        "max_neili"     : ({ 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 100000, }),
        "max_potential,max_experience"  : ({ 200000, 400000, 600000, 1000000, 1500000, 2000000, 3000000, 4000000, 6000000, }),
        
        "attack,sword,blade,hammer,staff,club,whip,unarmed,strike,cuff,hand,finger,claw": ({ 20, 30, 40, 60, 80, 110, 150, 200 }),
        "dodge,parry,defense"   : ({ 10, 15, 20, 25, 30, 35, 40, 45, 60 }),

        "ref_jing,ref_qi"       : ({ 60, 70, 80, 100, 120, 140, 160, 180, 200, }),
        "ref_neili"     : ({ 120, 140, 160, 180, 240, 280, 320, 360, 500, }),
        "suck_qi,suck_neili"  : ({ 2, 4, 6, 8, 10, 12, 14, 16, 20, }),
        
        "gold_find"     : ({ 2, 4, 6, 8, 10, 12, 14, 16, 20, }),
        "magic_find"    : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        
        "add_poison,add_metal,add_wood,add_water,add_fire,add_earth"    : ({ 6, 8, 10, 13, 16, 19, 22, 25, 28, }),
        "reduce_poison,avoid_poison,reduce_metal,reduce_fire,reduce_wood,reduce_water,reduce_earth"     : ({ 1, 2, 3, 4, 5, 5, 5, 5, 5, }),
        
        "research_times,learn_times,practice_times,derive_times,study_times"    : ({ 10, 15, 20, 25, 30, 35, 40, 45, 50 }),
        "research_effect,learn_effect,practice_effect,derive_effect,study_effect"       : ({ 8, 10, 12, 15, 18, 21, 25, 35, 40, }),
                
        "ap_power,da_power"    : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "dp_power"      : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "avoid_defense,avoid_parry,avoid_dodge,avoid_force": ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "avoid_attack"  : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        
        "trace,escape"  : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "attack_chance" : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "double_damage,through_armor"   :  ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "qi_vs_neili"   : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "block_heal"    : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "absorb_blood"  : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        
        "add_reward"    : ({ 1, 2, 3, 5, 7, 9, 11, 13, 15, }),
        "add_exp,add_pot,add_mar,add_force"     : ({ 5, 7, 9, 12, 15, 18, 22, 26, 30, }),
        
        "add_blind,add_freeze,add_dizziness,add_forget,add_weak,add_busy"   : ({ 3, 5, 7, 9, 12, 15, 18, 21, 25, }),
        "avoid_blind,avoid_freeze,avoid_dizziness,avoid_forget,avoid_weak,avoid_busy,reduce_busy" : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "fatal_blow"    : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "anti_fatal"    : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "slaughter"     : ({ 6, 8, 10, 13, 16, 19, 22, 25, 29, }),
        "clear_force"   : ({ 6, 8, 10, 13, 16, 19, 22, 25, 29, }),
        "add_skill"     : ({ 20, 30, 40, 60, 80, 110, 150, 250 }),
        "add_damage"    : ({ 3, 5, 7, 9, 12, 15, 18, 21, 25, }),
        "reduce_damage" : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "full_self"     : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "avoid_die"     : ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
        "counter_damage": ({ 1, 2, 3, 4, 5, 6, 7, 8, 10, }),
]);

// 裝備的品級有6級，前2個品級屬性沒有特殊，從稀有（第三個）品級開始有特殊屬性
// 寶石的等級有3級，寶石的屬性應該和裝備前2個品級的屬性一樣
// qlvl1只有基本屬性，qlvl2才有寶石屬性，qlvl3擁有寶石屬性，qlvl4擁有史詩屬性，qlvl5擁有傳説屬性，qlvl6擁有神奇屬性
mixed weapon_props = ({
        ({ "damage1", "int", "str", "con", "dex", "kar", "skill", "attack", 
           "suck_neili", "suck_qi", "gold_find", "magic_find", "add_poison",
           "research_times", "learn_times", "practice_times", "derive_times",
           "study_times", "research_effect", "learn_effect", "practice_effect",
           "derive_effect", "study_effect", "ap_power", "da_power", "avoid_defense",
           "avoid_parry", "avoid_dodge", "avoid_force", "double_damage",
           "through_armor", "absorb_blood", "add_exp", "add_pot", "add_mar", "add_force",
           "add_reward", "add_blind", "add_freeze", "add_dizziness", "add_weak", "clear_force",
           "add_forget", "add_busy", "fatal_blow", "slaughter", "add_skill", "add_damage", 
           "max_neili", "max_qi", "max_jing", "max_jingli", "max_potential", "max_experience",
        }),
        ({ "research_effect", "practice_effect", "study_effect", "learn_effect", "derive_effect", "damage1",
           "attack", "ap_power", "da_power", "avoid_defense", "avoid_parry", "avoid_dodge", "suck_qi", "clear_force",
           "suck_neili", "avoid_force", "add_exp", "add_pot", "add_mar", "add_force", "through_armor", "skill", // skill特殊處理 
        }), 
        ({ "through_armor", "slaughter", "double_damage", "add_reward", "absorb_blood", 
           "add_blind", "suck_qi", "suck_neili", "add_exp", "add_pot", "add_mar", "add_force",
           "research_effect", "practice_effect", "derive_effect", "add_reward", "clear_force",
           "ap_power", "da_power",
        }),
        ({ "add_reward", "add_blind", "add_freeze", "add_weak", 
           "add_forget", "add_busy", "fatal_blow", "slaughter", "add_skill", "add_damage",
           "ap_power", "da_power", 
        }),
});

mixed armor_props = ({
        ({ "armor1", "int", "str", "con", "dex", "kar", "max_neili", "max_qi", "max_jing",
           "max_jingli", "max_potential", "max_experience", "parry", "dodge", "defense",
           "ref_neili", "ref_jing", "ref_qi", "reduce_poison", "avoid_poison", "research_times",
           "learn_times", "practice_times", "derive_times", "study_times", "research_effect",
           "learn_effect", "practice_effect", "derive_effect", "study_effect", "dp_power", "avoid_attack",
           "avoid_blind", "avoid_freeze", "avoid_dizziness", "avoid_forget", "avoid_weak",
           "avoid_busy", "reduce_busy", "reduce_damage", "full_self", "avoid_die", "counter_damage",
        }),
        ({ "research_effect", "practice_effect", "study_effect", "learn_effect", "derive_effect", 
           "reduce_poison", "avoid_poison", "max_qi", "max_jing", "parry", "dodge", "defense", "armor1",
        }),
        ({ "ref_neili", "ref_jing", "ref_qi", "avoid_attack", "dp_power", "avoid_blind",
           "research_effect", "practice_effect", "derive_effect", "avoid_die", "counter_damage",
        }),
        ({ "avoid_blind", "avoid_freeze", "avoid_forget", "avoid_weak", "research_effect",
           "avoid_busy", "reduce_busy", "reduce_damage", "full_self", "counter_damage",
           "dp_power", "avoid_die",
        }),
});

// 項鍊amulet、戒指ring、護身符屬性charm
mixed ring_props = ({
        ({ "per", "attribute", "max_neili", "max_qi", "max_jing", "max_jingli", "max_potential",
           "max_experience", "ref_neili", "ref_jing", "ref_qi", "gold_find",
           "magic_find", "avoid_poison", "research_times", "learn_times", "practice_times", "derive_times",
           "study_times", "research_effect", "learn_effect", "practice_effect", "derive_effect", "study_effect",
           "ap_power", "da_power", "avoid_defense", "avoid_parry", "avoid_dodge", "avoid_force", 
           "double_damage", "through_armor", "qi_vs_neili", "add_exp", "add_pot", "add_mar", "add_force",
           "add_reward", "avoid_blind", "avoid_freeze", "avoid_dizziness", "avoid_forget", "avoid_weak",
           "through_armor", "avoid_busy", "reduce_busy", "add_skill", "avoid_die",
        }),
        ({ "attribute", "gold_find", "research_effect", "practice_effect", "study_effect", "learn_effect", "derive_effect", 
           "reduce_poison", "avoid_poison", "max_qi", "max_jing", "add_exp", "add_pot", "add_mar", "add_force", 
        }),
        ({ "through_armor", "magic_find", "qi_vs_neili", "research_effect", "practice_effect", "derive_effect",
           "ap_power", "da_power", "avoid_defense", "avoid_parry", "avoid_dodge", "avoid_force",
           "add_exp", "add_pot", "add_mar", "add_force", "add_reward", "avoid_die",
        }),
        ({ "add_reward", "avoid_blind", "avoid_freeze", "avoid_forget", "avoid_weak", "avoid_die",
           "avoid_busy", "reduce_busy", "add_skill", "magic_find", "research_effect", "double_damage",
           "add_exp", 
        }),
});

// 套化的兵器屬性 
string *suit_weapon_props = ({
        "double_damage", "avoid_forget", "add_damage", "add_skill", "fatal_blow", "add_busy", "add_weak", "add_dizziness",
        "add_freeze",
        
});
// 套化的防具屬性 
string *suit_armor_props = ({
        "reduce_busy", "avoid_busy", "avoid_weak", "avoid_dizziness", "avoid_die", 
        "counter_damage", "avoid_forget", "full_self", "reduce_damage", "research_effect",
});
// 套化的護身符屬性
string *suit_ring_props = ({
        "magic_find", "add_exp", "add_pot", "add_mar", "add_force", "avoid_die",
        "add_reward", "full_self", "avoid_busy", "avoid_forget", "research_effect",
});

void create()
{
        seteuid(getuid());
        set("name", "裝備精靈");
        set("id", "equipmentd");
}

// 為屬性名稱匹配中文
varargs string chinese(string prop, int value)
{
        string desc;

        if( !undefinedp(all_props[prop]) )
                desc = all_props[prop];
        else
                desc = to_chinese(prop);

        if( !value ) return desc;

        if( member_array(prop, percent_props) != -1 )
                desc = sprintf("%s %s%d%s", desc,
                               value > 0 ? "+" : "-", abs(value), "%");
        else
                desc = sprintf("%s %s%d", desc,
                               value > 0 ? "+" : "-", abs(value));

        return desc;
}

// 獲取裝備部件的屬性
varargs int query_prop_value(string prop, int ilvl, int s)
{
        int i, j, flag;
        int *value;
        mapping data;
        string *ks;
        string *temp_str;

        flag = 0;
        if( s ) data = copy(steady_values); // 強化屬性
        else data = copy(prop_values);
        ks = keys(data);
        for( i=0; i<sizeof(ks); i++ ) {
                //reset_eval_cost();
                temp_str = explode(ks[i], ",");
                for( j=0; j<sizeof(temp_str); j++ )
                        if( temp_str[j] == prop ) {
                                value = data[ks[i]];
                                flag = 1;
                                break;
                        }
                if( flag ) break;
        }
        if( !flag || !value ) return 0;
        if( ilvl ) {
                if( ilvl > sizeof(value) )
                        ilvl = sizeof(value);

                return value[ilvl-1];
        }
        return value[random(sizeof(value))];
}

// 裝備綠化時候獲得的屬性
mapping apply_ultimate_prop(object ob, string type, int ilvl)
{
        string *props;
        string prop;
        mapping apply;
        int value, n;

        apply = ([]);

        if( type == "weapon"
        ||  type == "sword"
        ||  type == "xsword"
        ||  type == "blade"
        ||  type == "whip"
        ||  type == "hammer"
        ||  type == "staff"
        ||  type == "club"
        ||  type == "throwing"
        ||  type == "hands"
        ||  type == "finger" )
                props = suit_weapon_props;
        else
        if( type == "rings"
        ||  type == "charm"
        ||  type == "myheart"   // 護身符·左
        ||  type == "myheart2"  // 護身符·右
        ||  type == "neck" )
                props = suit_ring_props;
        else
                props = suit_armor_props;

        n = 1;
        if( random(10000) == 1 )
                n = 2;
        while( n > 0 )
        {
                prop = props[random(sizeof(props))];
                props -= ({ prop });

                value = (int)query_prop_value(prop, ilvl);
                apply[prop] = value;

                n--;
        }
        return apply;
}

// 生成寶石屬性
varargs mapping apply_gem_prop(string type, int ilvl, int n)
{
        string *props;
        string prop;
        mapping apply;
        int value;

        apply = ([]);
      
        if( type == "weapon"
        ||  type == "sword"
        ||  type == "xsword"
        ||  type == "blade"
        ||  type == "whip"
        ||  type == "hammer"
        ||  type == "staff"
        ||  type == "club"
        ||  type == "throwing"
        ||  type == "hands"
        ||  type == "finger" )
                props = weapon_props[0]; // 獲取對應的品質屬性
        else
        if( type == "rings"
        ||  type == "charm"
        ||  type == "myheart"   // 護身符·左
        ||  type == "myheart2"  // 護身符·右
        ||  type == "neck" )
                props = ring_props[0];
        else
                props = armor_props[0];
        
        if( type == "weapon" ) props -= ({ "skill" });
        if( !n ) n = 1 + random(3);

        while( n > 0 )
        {
                prop = props[random(sizeof(props))];
                props -= ({ prop });

                if( prop == "skill" ) // skill特殊分析
                {
                        int rate;
                        rate = random(100);
                        if( type == "finger" )
                        {
                                if( rate < 50 )
                                        prop = "claw";
                                else
                                        prop = "finger";
                        } else
                        if( type == "hands" )
                        {
                                if( rate < 25 )
                                        prop = "unarmed";
                                else if( rate < 50 )
                                        prop = "cuff";
                                else if( rate < 75 )
                                        prop = "hand";
                                else
                                        prop = "strike";
                        } else
                                prop = type;
                }
                value = (int)query_prop_value(prop, ilvl);
                apply[prop] = value;

                n--;
        }
        return apply;
}

// 設置裝備屬性
mapping apply_props(string type, int ilvl, int n)
{
        mapping applied_prop;
        mapping enchase_prop;
        mapping data = ([]);
        string *apply;
        mixed insert;
        int i, j;

        applied_prop = ([]);
        insert = ([]);
        
        if( !n ) return data;
        for( i=1; i<=n; i++ ) // 凹槽數
        {
                enchase_prop = copy(apply_gem_prop(type, ilvl));
                apply = keys(enchase_prop);
                for( j=0; j<sizeof(apply); j++ )
                {
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[apply[j]]) )
                                applied_prop[apply[j]] = enchase_prop[apply[j]];
                        else
                                applied_prop[apply[j]] += enchase_prop[apply[j]];
                }
                insert[to_string(i)] = (["name" : HIM"玄石"NOR, "id" : "magic stone", "apply_prop" : enchase_prop]);
        }
        
        data["apply_prop"] = applied_prop;
        data["insert"] = insert;
        return data;
}

protected mapping trans_data(string mark)
{
        int     i;
        mixed   temp_value;
        string  temp_str, temp_str2;
        string *temp_arr, *temp_val;
        string  temp_key, key;
        mapping temp_status;
        mapping temp_map, temp_map2;

        temp_status = ([ ]);

        // 解析insert
        if( sscanf(mark, "%s<insert>%s</insert>", mark, temp_str2) == 2 ) 
        {
                temp_map2 = ([ ]);
                while (sscanf(temp_str2, "%*s[%s]%s[/%s]%s", key, temp_str, key, temp_str2) > 3)
                {
                        temp_map = ([ ]);
                        temp_arr = explode(temp_str, "\n");
                        if( sizeof(temp_arr) < 2 ) {
                                if( atoi(temp_str) )
                                        temp_map2[key] = atoi(temp_str);
                                else
                                        temp_map2[key] = temp_str;

                        } else {
                                for ( i=0; i<sizeof(temp_arr); i++ ) {
                                        //temp_arr[i] = replace_string(temp_arr[i], " ", "");
                                        if( sscanf(temp_arr[i], "%s:%d", temp_key, temp_value) != 2 )
                                                sscanf(temp_arr[i], "%s:%s", temp_key, temp_value);

                                        // 解析VALUE
                                        if( stringp(temp_value) && strsrch(temp_value, '/') != -1 ) {
                                                temp_val = explode(temp_value, "/");
                                                temp_value = ({});
                                                for (i = 0; i <sizeof(temp_val); i++)
                                                        if( atoi(temp_val[i]) )
                                                                temp_value += atoi(temp_val[i]);
                                                        else
                                                                temp_value += temp_val[i];
                                        }
                                        // 解析KEY
                                        if( stringp(temp_key) && strsrch(temp_key, '/') != -1 )
                                                _set( temp_map, explode(temp_key, "/"), temp_value );
                                        else
                                                temp_map[temp_key] = temp_value;
                                        
                                        if( !undefinedp(temp_map["name"]) )
                                                temp_map["name"] = trans_color(temp_map["name"], 3);
                                }
                                temp_map2[key] = temp_map;                             
                        }
                }
                temp_status["insert"] = temp_map2;
        }   
        
        // 開始解析
        while (sscanf(mark, "%*s<%s>%s</%s>%s", key, temp_str, key, mark) > 3)
        {
                temp_map = ([ ]);
                temp_arr = explode(temp_str, "\n");
                if( sizeof(temp_arr) < 2 ) {
                        if( sscanf(temp_arr[0], "%s:%d", temp_key, temp_value) == 2 ||
                            sscanf(temp_arr[0], "%s:%s", temp_key, temp_value) == 2 ) {
                               // 解析VALUE
                                if( stringp(temp_value) && strsrch(temp_value, '/') != -1 ) {
                                        temp_val = explode(temp_value, "/");
                                        temp_value = ({});
                                        for (i = 0; i <sizeof(temp_val); i++)
                                                if( atoi(temp_val[i]) )
                                                        temp_value += atoi(temp_val[i]);
                                                else
                                                        temp_value += temp_val[i];
                                }
                                // 解析KEY
                                if( stringp(temp_key) && strsrch(temp_key, '/') != -1 )
                                        _set( temp_map, explode(temp_key, "/"), temp_value );
                                else
                                        temp_map[temp_key] = temp_value;
                                        
                                temp_status[key] = temp_map;
                        } 
                        else if( atoi(temp_str) )
                                temp_status[key] = atoi(temp_str);
                        else
                                temp_status[key] = temp_str;

                } else {
                        for ( i=0; i<sizeof(temp_arr); i++ ) {
                                temp_arr[i] = replace_string(temp_arr[i], " ", "");
                                if( sscanf(temp_arr[i], "%s:%d", temp_key, temp_value) != 2 )
                                        sscanf(temp_arr[i], "%s:%s", temp_key, temp_value);

                                // 解析VALUE
                                if( stringp(temp_value) && strsrch(temp_value, '/') != -1 ) {
                                        temp_val = explode(temp_value, "/");
                                        temp_value = ({});
                                        for (i = 0; i <sizeof(temp_val); i++)
                                                if( atoi(temp_val[i]) )
                                                        temp_value += atoi(temp_val[i]);
                                                else
                                                        temp_value += temp_val[i];
                                }
                                // 解析KEY
                                if( stringp(temp_key) && strsrch(temp_key, '/') != -1 )
                                        _set( temp_map, explode(temp_key, "/"), temp_value );
                                else
                                        temp_map[temp_key] = temp_value;
                        }
                        temp_status[key] = temp_map;
                }
        }
        
        if( !undefinedp(temp_status["name"]) )
                temp_status["name"] = trans_color(temp_status["name"], 3);

        if( !undefinedp(temp_status["mod_name"]) )
                temp_status["mod_name"] = trans_color(temp_status["mod_name"], 3);
                
        if( !undefinedp(temp_status["long"]) )
                temp_status["long"] = trans_color(temp_status["long"], 3) + "\n";

        return temp_status;
}

// 創造一個固定物件，根據序號
varargs mixed create_object(string num, int level)
{
        string *list;
        string  mark, part, rec;
        string  type, str;
        string  filename, this_file;
        mapping temp_status;
        mapping temp_function;
        object  ob;

        if( !num || num == "" ) {
                if( !level ) level = random(3);

                switch( random(3) )
                {
                case 0 :
                        rec = "W";
                        if( level == 0) filename = EQUIP_LIST+"basic.weapon";
                        else if( level == 1) filename = EQUIP_LIST+"advance.weapon";
                        else if( level == 2) filename = EQUIP_LIST+"expert.weapon";
                        break;
                case 1 :
                        rec = "A";
                        if( level == 0) filename = EQUIP_LIST+"basic.armor";
                        else if( level == 1) filename = EQUIP_LIST+"advance.armor";
                        else if( level == 2) filename = EQUIP_LIST+"expert.armor";
                        break;
                default:
                        rec = "G";
                        if( level == 0) filename = EQUIP_LIST+"basic.gem";
                        else if( level == 1) filename = EQUIP_LIST+"advance.gem";
                        else if( level == 2) filename = EQUIP_LIST+"expert.gem";
                        break;
                }

                this_file = read_file(filename);
                str = sprintf("%s%d", rec, level);
                list = ({});
                while (sscanf(this_file, "%*s<"+str+part+">%*s</"+str+part+">%*s"))
                {
                        rec = sprintf("%s%s", str, part);
                        list += ({ rec });
                }
                if( !sizeof(list) ) return 0;
                num = list[random(sizeof(list))];
        } else {
                if( num[0] == 'W' ) {
                        if( num[1] == '0' && strlen(num) == 5 )
                                filename = EQUIP_LIST+"basic.weapon";
                        else if( num[1] == '1' && strlen(num) == 5 )
                                filename = EQUIP_LIST+"advance.weapon";
                        else if( num[1] == '2' && strlen(num) == 5 )
                                filename = EQUIP_LIST+"expert.weapon";
                } else if( num[0] == 'A' ) {
                        if( num[1] == '0' && strlen(num) == 5)
                                filename = EQUIP_LIST+"basic.armor";
                        else if(  num[1] == '1' && strlen(num) == 5)
                                filename = EQUIP_LIST+"advance.armor";
                        else if(  num[1] == '2' && strlen(num) == 5)
                                filename = EQUIP_LIST+"expert.armor";
                } else if( num[0] == 'G' ) {
                        if(  num[1] == '0' && strlen(num) == 5)
                                filename = EQUIP_LIST+"basic.gen";
                        else if(  num[1] == '1' && strlen(num) == 5)
                                filename = EQUIP_LIST+"advance.gen";
                        else if(  num[1] == '2' && strlen(num) == 5)
                                filename = EQUIP_LIST+"expert.gen";
                }

                if( !filename )
                        return 0;

                this_file = read_file(filename);
        }

        // 解析序號對應的字符串
        if( sscanf(this_file, "%*s<"+num+">%s</"+num+">%*s", mark) ) {
                sscanf(mark, "%*s<type>%s</type>%s", type, mark);
                filename = EQUIP_DIR + type;
                temp_status = trans_data(mark);
                temp_function = temp_status["function"];
                if( temp_function )
                        map_delete(temp_status, "function");
                else
                        temp_function = allocate_mapping(0);

                ob = TEMPLATE_D->create_object(filename, temp_status["id"], temp_status, 0, temp_function);
                set("mod_mark", num, ob);
                set("can_sign", 1, ob); // 裝備簽名
                if( temp_status["mod_level"] )
                        set("mod_level", temp_status["mod_level"], ob);

                return ob;
        } else {
                CHANNEL_D->do_channel(this_object(),"sys", "創造一個錯誤的物件。");
                return 0;
        }
}

// 創造一個固定套裝部件，根據序號
varargs object create_module(string num, int level)
{
        string mark, part, str, rec;
        string *list;
        string type;
        string filename, this_file;
        mapping temp_status;
        mapping temp_function;
        object ob;

        if( !num || num == "" ) {
                if( !level ) level = random(4);

                if( level == 0 ) filename = EQUIP_LIST+"basic.mod";
                else if( level == 1 ) filename = EQUIP_LIST+"advance.mod";
                else if( level == 2 ) filename = EQUIP_LIST+"expert.mod";
                else if( level == 3 ) filename = EQUIP_LIST+"boss.mod";

                this_file = read_file(filename);
                str = sprintf("A%d", level);
                list = ({});
                while (sscanf(this_file, "%*s<"+str+part+">%*s</"+str+part+">%*s"))
                {
                        rec = sprintf("%s%s", str, part);
                        list += ({ rec });
                }
                if( !sizeof(list) ) return 0;
                num = list[random(sizeof(list))];
        } else {
                if(  num[1] == '0' && strlen(num) == 5 )
                        filename = EQUIP_LIST+"basic.mod";
                else if(  num[1] == '1' && strlen(num) == 5 )
                        filename = EQUIP_LIST+"advance.mod";
                else if(  num[1] == '2' && strlen(num) == 5 )
                        filename = EQUIP_LIST+"expert.mod";
                else if(  num[1] == '3' && strlen(num) == 5 )
                        filename = EQUIP_LIST+"boss.mod";

                this_file = read_file(filename);
        }
        //解析序號對應的字符串
        if( sscanf(this_file, "%*s<"+num+">%s</"+num+">%*s", mark) )
        {
                sscanf(mark, "%*s<type>%s</type>%s", type, mark);
                filename = EQUIP_DIR + type;
                temp_status = trans_data(mark);
                temp_function = temp_status["function"];
                if( temp_function )
                        map_delete(temp_status, "function");
                else
                        temp_function = allocate_mapping(0);

                ob = TEMPLATE_D->create_object(filename, temp_status["id"], temp_status, 0, temp_function);
                set("mod_mark", num, ob);
                //set("can_sign", 1, ob); // 裝備簽名
                //if( temp_status["mod_level"] )
                //        set("mod_level", temp_status["mod_level"], ob);

                return ob;
        } else {
                CHANNEL_D->do_channel(this_object(), "sys", "創造一個套裝部件錯誤。");
                return 0;
        }
}

// 創造一個動態的物件
public varargs object create_dynamic(string obj_type, int ilvl, int mf, int flag)
{
        mapping temp_status, all_list, data;
        mapping applied_prop = ([]);
        mapping insert;
        string *all_id, *types;
        string id;
        string *file;
        string color, filename;
        string base_type;
        object ob;
        int qlvl;
        int rate, rate2, n, uf, sf, rf;
        string prop, *props;

        if( !ilvl || ilvl < 1 )
                return 0;

        if( !obj_type || obj_type == "" ) { // 隨機生成裝備種類或寶石
                rate = random(100);
                if( rate < 30 ) obj_type = "weapon";
                else if( rate < 70 ) obj_type = "armor";
                else if( rate < 90 ) obj_type = "rings";
                else obj_type = "gem";
                flag = 0;
        }

        if( flag ) { // 指定的兵器類型、防具類型或寶石類型
                if( flag == 1 ) {
                        if( member_array(obj_type, weapon_type) != -1 )
                                base_type = "weapon";
                        else if( member_array(obj_type, armor_type) != -1 )
                                base_type = "armor";
                        else if( member_array(obj_type, rings_type) != -1 )
                                base_type = "rings";
                        else    base_type = "gem";
                } else {
                        // 系統固定的名稱和ID的裝備
                        all_list = type_list[obj_type];
                        all_id = values(all_list);
                        id = all_id[random(sizeof(all_id))];
                }
        } else {
                base_type = obj_type;
                types = all_type[obj_type];
                obj_type = types[random(sizeof(types))]; // 隨機一種
        }

        if( flag && flag > 1 ) // 用模型文件，需要檢查寫法
                filename = sprintf("%s%s/%s.c", TEMPLATE_DIR, base_type, obj_type);
        else
                filename = sprintf("%s%s/%s.c", EQUIP_DIR, base_type, obj_type);

        data = ([]);
        temp_status = ([]);
        rate = random(100);
        if( rate < 40 ) data["str"] = ilvl*2 + random(ilvl);
        else if( rate < 60 ) data["con"] = ilvl*2 + random(ilvl);
        else if( rate < 80 ) data["dex"] = ilvl*2 + random(ilvl);
        else data["int"] = ilvl*2 + random(ilvl);

        data["level"] = ilvl;
        temp_status["require"] = copy(data); // 設置裝備要求

        if( base_type != "gem" ) // 掉落裝備，非寶石
        {
                // 凹槽數量：普通0、精製1、珍稀2、史詩3、傳説4、神器5
                // 武器6孔，防具4孔，護身符3孔，盾牌4孔
                
                if( mf < 2 ) mf = 2;
                
                uf = mf*10/(mf+10);  // 傳説品級
                sf = mf*30/(mf+30);  // 史詩品級
                rf = mf*500/(mf+500);  // 珍稀品級
                                     
                rate = random(100);
                /*
                rate2 = random(100);
                rate = (rate + rate2) / 2;
                */
                if( mf >= 600 )
                {
                        if( base_type == "weapon" || obj_type == "hands" || obj_type == "finger" )
                                n = 5;       // 凹槽數量
                        else if( base_type == "armor" )
                                n = 3;
                        else // 護身符
                                n = 3;
                        qlvl = 6; 
                        color = HBRED+HIW; // 神話
                } else 
                if( mf >= 500 )
                {
                        if( base_type == "weapon" || obj_type == "hands" || obj_type == "finger" )
                                n = 4;       // 凹槽數量
                        else if( base_type == "armor" )
                                n = 3;
                        else // 護身符
                                n = 3;
                        if( (mf >= 540 && random(300) == 1) || random(1000) == 1 )
                        {
                                //qlvl = 5+random(2); 
                                qlvl = 6; 
                                if( qlvl == 6 ) color = HBRED+HIW; else color = HIY;
                        }
                        else
                        {
                                qlvl = 5;
                                color = HIY; // 傳説以上
                        }
                } else  
                if( mf >= 400 )
                {
                        n = 3;
                        if( !random(5) )
                        {
                                if( random(10000) == 1 )
                                        qlvl = 6; 
                                else
                                        qlvl = 4+random(2);
                                if( qlvl == 6 ) color = HBRED+HIW; else if( qlvl == 5 ) color = HIY; else color = HIM;
                        }
                        else
                        {
                                qlvl = 4;
                                color = HIM; // 史詩
                        }
                } else             
                if( mf >= 300 )
                {
                        n = 2;
                        if( !random(3) )
                        {
                                qlvl = 3+random(3); 
                                if( qlvl == 5 ) color = HIY; else if( qlvl == 4 ) color = HIM; else color = HIR;
                        }
                        else
                        {
                                qlvl = 3;
                                color = HIR; // 珍稀以上
                        }
                } else           
                if( rate < uf && !random(100) )
                {
                        if( base_type == "weapon" || obj_type == "hands" || obj_type == "finger" )
                                n = 4;       // 凹槽數量
                        else if( base_type == "armor" )
                                n = 3;
                        else // 護身符
                                n = 3;
                        qlvl = 5; 
                        color = HIY; // 傳説
                } else
                if( rate < sf && !random(50) )
                {
                        n = 3;
                        qlvl = 4;
                        color = HIM; // 史詩
                } else
                if( rate < rf )
                {
                        n = 2;
                        qlvl = 3;
                        color = HIR; // 珍稀
                }
                else
                if( rate < mf )
                {
                        n = 1;
                        qlvl = 2;
                        color = HIB; // 精製
                }
                else
                {
                        n = 0;
                        qlvl = 1;
                        color = HIW; // 普通
                }
                data = ([]);
                if( n > 1 )
                        n = random(n); // 隨機凹槽數
                if( n > 0 )
                {
                        data = apply_props(obj_type, ilvl/10, n);
                        data["flute"] = n; //socket
                        data["used"] = n;
                        insert = data["insert"];
                        map_delete(data, "insert");
                        temp_status["enchase"] = copy(data); // 設置裝備屬性 buff/enchase ?
                        temp_status["insert"] = insert;      // 插槽寶石屬性
                }
                if( qlvl > 5 ) // 神器
                {
                        if( base_type == "weapon" || obj_type == "hands" || obj_type == "finger" )   
                                props = weapon_props[3];
                        else if( base_type == "armor" )  
                                props = armor_props[3];
                        else 
                                props = ring_props[3];
                                
                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl/10);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl/10);       
                        
                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl/10);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl/10);   
                        
                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl/10);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl/10);   
                        
                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl/10);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl/10);           
                } else {
                if( qlvl > 4 ) // 傳説
                {
                        if( base_type == "weapon" || obj_type == "hands" || obj_type == "finger" )   
                                props = weapon_props[2];
                        else if( base_type == "armor" )  
                                props = armor_props[2];
                        else 
                                props = ring_props[2];
                                
                        prop = props[random(sizeof(props))];                
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl/10);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl/10);  
                }
                if( qlvl > 3 ) // 史詩
                {
                        if( base_type == "weapon" || obj_type == "hands" || obj_type == "finger" )   
                                props = weapon_props[1];
                        else if( base_type == "armor" )  
                                props = armor_props[1];
                        else 
                                props = ring_props[1];
                                
                        prop = props[random(sizeof(props))];
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl/10);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl/10);  
                } 
                if( qlvl > 2 ) // 珍稀
                {
                        if( base_type == "weapon" || obj_type == "hands" || obj_type == "finger" )   
                                props = weapon_props[0];
                        else if( base_type == "armor" )  
                                props = armor_props[0];
                        else 
                                props = ring_props[0];
                                
                        prop = props[random(sizeof(props))];    
                        if( !sizeof(applied_prop) || undefinedp(applied_prop[prop]) )
                                applied_prop[prop] = query_prop_value(prop, ilvl/10);
                        else
                                applied_prop[prop] += query_prop_value(prop, ilvl/10);         
                } 
                }
                        
                if( base_type == "weapon" )
                {
                        temp_status["weapon_prop"] = ([ "damage" : (ilvl+15)*qlvl*10 ]); // 基本屬性-傷害                        
                        if( applied_prop )
                                temp_status["weapon_prop"] += applied_prop;
                }
                else if( base_type == "armor" )
                {
                        if( obj_type == "hands"
                        ||  obj_type == "finger" )
                        {
                                temp_status["armor_prop"] = ([ "armor" : 10 ]);
                                temp_status["armor_prop"]+= ([ "unarmed_damage" : (ilvl+15)*qlvl*10 ]);
                                if( applied_prop )
                                        temp_status["armor_prop"] += applied_prop;
                        }
                        else
                        {
                                temp_status["armor_prop"] = ([ "armor" : (ilvl+15)*qlvl*2 ]); // 基本屬性-保護
                                if( applied_prop )
                                        temp_status["armor_prop"] += applied_prop;
                        }    
                }
                else // 護身符
                {
                        temp_status["armor_prop"] = ([ "armor" : 10 ]);
                        if( applied_prop )
                                temp_status["armor_prop"] += applied_prop; 
                }
                
                ob = TEMPLATE_D->create_object(filename, obj_type, temp_status);
                set("quality_level", qlvl, ob); // 品質
                set("can_sign", 1, ob); // 裝備簽名
                set("auto_load", 1, ob); // 下線不掉
                if( color )
                        ob->set_color(color); // 設置顏色,x_name中已經處理顏色了？
        }
        else // 掉落寶石
        {
                // 寶石分為4個等級，碎片，完好1，稀有1+1，神之1+2，寶石擁有兵器和防具以及飾品3種屬性？
                // 掉落未鑑定的寶石代替
                ob = new("/clone/tessera/gem.c");
                //file = map_array(get_dir("/inherit/template/gem/"), (: "/inherit/template/gem/" + $1 :)); 
                //filename = file[random(sizeof(file))]; 
                //ob = new(filename);
        }

        return ob;
}

public varargs void killer_reward(object killer, object victim, mapping drops)
{
        object ob, *obs;
        string *ks, key, str;
        string ob_file, ob_quality, ob_num, ob_typ;
        int i, n, value, level, team_size, mf;
        int rand, times, score;
        object where;

        if(  !mapp(drops) || !sizeof(drops) )
                return;

        where = environment(victim);
        obs = pointerp(killer->query_team()) ? killer->query_team() : ({ killer });
        team_size = sizeof(filter_array(obs, (: objectp($1) && environment($1) == environment($(killer)) :)));

        times = ACTION_D->query_action("boss_reward");
        if( !times ) times = ACTION_D->query_action("fuben_reward");
        if( !times ) times = 1;
        //if( killer->is_vip() ) times = times * 2;
        mf=query_temp("apply/magic_find", killer);
        if( query("jingmai/finish", killer) ) 
                mf += ZHOUTIAN_D->query_jingmai_effect("magic_find");
        else
                mf += query("jingmai/magic_find", killer); 
        
        score = 0;
        ks = keys(drops);
        for( i=0; i<sizeof(ks); i++ ) {
                key = ks[i];
                score += drops[ks[i]];
        }
        for( i=0; i<sizeof(ks); i++ ) {
                key = ks[i];              
                value = drops[ks[i]];
                value += value * mf/100;
                
                // 掉落機率公式                
                if( team_size >= 5 )
                        value = value * 220 / 100;
                else if( team_size == 4 )
                        value = value * 182 / 100;
                else if( team_size == 3 )
                        value = value * 152 / 100;
                else if( team_size == 2 )
                        value = value * 121 / 100;
                for( n=0; n<times; n++ ) {
                        //rand = random(100);
                        rand = random(score);
                        if( rand < value) {
                                str = key[0..1];
                                // 掉落陣列關鍵字以 F I 起頭表示為掉落某個物品
                                if( str == "FI" ) {
                                        if( sscanf(key, "FI&%s", ob_file) )
                                                ob = new(ob_file);

                                }
                                // 掉落陣列關鍵字以 N U 起頭表示為掉落某個序號的物品
                                else if( str == "NU" ) {
                                        if(  sscanf(key, "NU&%s", ob_num) )
                                                ob = create_object(ob_num);

                                }
                                // 掉落陣列關鍵字以 T Y 起頭表示為掉落某個類型的物品
                                else if( str == "TY" ) {
                                        if(  sscanf(key, "TY&%s%d", ob_typ, level) == 2 )
                                                ob = create_dynamic(ob_typ, level, mf);

                                }
                                // 掉落陣列關鍵字以 M O 起頭表示為掉落某個序號的套裝部件
                                else if( str == "MO" ) {
                                        if( sscanf(key, "MO&%s", ob_num) )
                                                ob = create_module(ob_num);

                                }
                                // 掉落陣列關鍵字以 R A 起頭表示為掉落某類品質的的隨機物品或者隨機的某級裝備
                                else if( str == "RA" ) {
                                        if( sscanf(key, "RA&%s%d", ob_quality, level) == 2 ) {
                                                switch (ob_quality)
                                                {
                                                case "MODULE"   :
                                                        ob = create_module("", level);
                                                        break;
                                                case "NUMBER"   :
                                                        ob = create_object("", level);
                                                        break;
                                                case "RANDOM"   :
                                                        ob = create_dynamic("", level, mf);
                                                        break;
                                                case "RARE"     :
                                                        ob = create_dynamic("", level, 300);
                                                        break;
                                                case "EPIL"     :
                                                        ob = create_dynamic("", level, 400);
                                                        break;
                                                case "LEGEND"   :
                                                        ob = create_dynamic("", level, 500+mf/5);
                                                        break;
                                                case "MYTH"     :
                                                        ob = create_dynamic("", level, 600);
                                                        break;
                                                default         :
                                                        break;
                                                }
                                        }
                                }
                                if( objectp(ob) ) {
                                        // HIW+treasure_level+NOR" 級"HIC"稀"NOR CYN"有"NOR"物品
/*
                                        if( query("quality_level", ob) == 3 ) // 珍稀
                                                CHANNEL_D->channel_broadcast("news",  
                                                        killer->name() + "殺死" + victim->name() + NOR YEL"，從其身上掉出一"+query("unit", ob)+HIR" 珍"NOR RED"稀"HIW"級 "NOR YEL+ob->name()+YEL"。\n"NOR);
                                        else if( query("quality_level", ob) == 4 ) // 史詩
*/
                                        if( query("quality_level", ob) == 4 ) // 史詩
                                                CHANNEL_D->channel_broadcast("news",  
                                                        killer->name() + "殺死" + victim->name() + NOR YEL"，從其身上掉出一"+query("unit", ob)+HIM" 史"NOR MAG"詩"HIW"級 "NOR YEL+ob->name()+YEL"。\n"NOR);
                                        else if( query("quality_level", ob) == 5 ) // 傳説
                                                CHANNEL_D->channel_broadcast("news",  
                                                        killer->name() + "殺死" + victim->name() + NOR YEL"，從其身上掉出一"+query("unit", ob)+HIY" 傳"NOR YEL"説"HIW"級 "NOR YEL+ob->name()+YEL"。\n"NOR);
                                        else if( query("quality_level", ob) == 6 ) // 神器
                                        {
                                                CHANNEL_D->channel_broadcast("news",  
                                                        //killer->name() + "殺死" + victim->name() + NOR YEL"，從其屍體上撿起了一"+query("unit", ob)+HIY" 神"NOR YEL"器"HIW"級 "NOR YEL+ob->name()+YEL"。\n"NOR);
                                                        killer->name() + "殺死" + victim->name() + NOR YEL"，從其身上掉出一"+query("unit", ob)+" "+HBRED+HIW"神器"NOR+HIW"級 "NOR YEL+ob->name()+YEL"。\n"NOR);
                                                log_file("myth", sprintf("%s have get a %s(%s) of myth equip at %s.\n",killer->query_idname(),query("name",ob),query("id",ob),TIME_D->replace_ctime(time())));
                                        }
                                                        
                                        message_vision(HIC "當~~一聲，從$N" HIC "身上掉出" + ob->name() + NOR + HIC "，落在地上。\n" NOR, victim);
                                        if( query("quality_level", ob) > 2 ) {
                                                set("who_get/id", query("id", killer), ob);
		                                set("who_get/time", time() + 10, ob); // 10秒內別人都不能撿取
                                        }
                                        ob->move(where);                   
                                }
                        }
                }
        }
        mf=query_temp("apply/gold_find", killer);
        if( random(100) < mf )
        {
                ob = new("/clone/money/gold");
                ob->set_amount(random(20)+20);
                /*
                set("who_get/id", query("id", killer), ob);
	        set("who_get/time", time() + 10, ob); // 10秒內別人都不能撿取
	        */
                ob->move(where);
                message_vision(HIC "叮~~一聲，從$N" HIC "身上掉出" + ob->name() + NOR + HIC "，落在地上。\n" NOR, victim);
        }

        // 特殊活動爆物品，統一調用giftd接口
        //GIFT_D->boss_drops(this_object());

        return;
}

