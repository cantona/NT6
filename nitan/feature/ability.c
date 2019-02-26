// This program is a part of NT MudLIB

#include <ansi.h>

// classp ?
// abilities

// 基本能力
string *bas_ability = ({
        "str",
        "int",
        "con",
        "dex",
        "kar",
        "qi",
        "jing",
        "neili",
        "jingli",
        "ref_neili",
        "ref_qi",
        "ref_jing",
        "attack",
        "dodge",
        "parry",
        "fatal",
        "full_self",
        "avoid_busy",
        "avoid_weak",
        "reduce_damage",
});

mapping max_ability = ([
        "str"   : 500,
        "int"   : 500,
        "con"   : 500,
        "dex"   : 500,
        "kar"   : 70,
        "qi"    : 10,
        "jing"  : 10,
        "neili" : 10,
        "jingli": 10,
        "ref_neili": 20,
        "ref_qi"   : 20,
        "ref_jing" : 20,
        "attack": 10,
        "dodge" : 10,
        "parry" : 10,
        "fatal" : 10,
        "full_self" : 10,
        "avoid_busy": 10,
        "avoid_weak": 10,
        "reduce_damage": 10,
]);

string *bas_ability_info = ({
        "角色力量值提高１點\t","角色才智值提高１點\t","角色體質值提高１點\t",
        "角色身法值提高１點\t","角色運氣值提高１點\t","最大氣血值提高１％\t",
        "最大精氣值提高１％\t","最大內力值提高１％\t","最大精力值提高１％\t",
        "恢復氣血提高５０點\t","恢復精氣提高５０點\t","恢復內力提高５０點\t",
        "直接命中機會增１％\t","直接閃避機會增１％\t","直接招架機會增１％\t",
        "觸發暴擊機會增１％\t","戰神附體機會增１％\t","免疫忙亂機會增１％\t",
        "免疫虛弱機會增１％\t","化解傷害比例增１％\t",
});

mapping bas_ability_pot = ([
        "attack":       2,
        "dodge":        2,
        "parry":        2,
        "fatal":        3,
        "full_self":    3,
        "avoid_busy":   3,
        "avoid_weak":   3,
        "reduce_damage":3,
]);

mapping fam_ability = ([
        "武當派":({"reduce_busy", "add_busy", "tjq_defense", "tu_damage", "luan_attack"}),
]);

mapping fam_ability_info = ([
        "少林派": ({
                        "當yijinjing金剛不壞體神功yun jin,且氣血降低到20/25/30/35/40%出現怒目金剛效果",
                        "一拍兩散 命中降低 80/70/60/50/40 %，傷害增加100/200/300/400/500%,同時內力為0，精氣降低 90%",
                        "少林弟子持鈍器或空手時，傷害額外增加 2/4/6/8/10%",
                        "激發招架為金剛不壞體時，增加1/2/3/4/5%的傷害反射",
                        "少林弟子每多修習10種parry skill，戰鬥保護力增加1/2/3/4/5%",
                }),
        "武當派": ({
                        "技能組合化解忙亂機率＋１％",
                        "技能組合忙亂對手機率＋１％",
                        "太極拳的特殊防禦提高＋１％",
                        "絕招太極圖傷害力提高＋１％",
                        "絕招亂環訣命中率提高＋１％",
                }),
        "關外胡家":({
                        "冷月寒氣降低對手閃避  2/4/6/8/10%",            
                        "刀劍七重天倍擊機率增加 6/12/18/24/30%",
                         "破定軍山附帶致死效果機率  2/4/6/8/10%",
                        "妙手驅毒效果增加 (加滿則免疫毒素) 20/40/60/80/100%",
                        "當氣血降低到20/25/30/35/40%出現熱血效果",
                }),
                
]);

string *tf_ability = ({
        "gold_find",
        "double_day",
        "add_zq",
        
        "kingkong",
        "magic_find",
        "ability_delay",
        
        "anti_blow",
        "add_damage",
        "dealer",
        
        "indentily",
        "wushen",
        "qn_lose",
        
        "attack"
        "dodge",
        "add_exp",
        
        "avoid_cd",
        "add_damage",
        "avoid_dodge",
        
        "reduce_damage",
        "add_buff",
        "avoid_busy",
        
        "defense",
        "double_damage",
        "shashen",
        
        "add_blade",
        "add_sword",
        "add_unarmed"
});

string *tf_ability_info = ({
        /*
戰鬥回精：戰鬥時自動恢復精氣。
     戰鬥回氣：戰鬥時自動恢復氣血。
        第一境界

財運（1）：可在完成任務後獲得額外的金錢。
練氣（1）：可增加每天雙倍經驗時間1小時。
神佑（1）：每級獲得的先天真氣值增加1點。
神佑
戰鬥時當HP=0時，20%的機率出現神佑復活效果，復活以後擁有少量HP
第二境界

金剛（2）：增加對boss級別怪物的絕對防禦5%、10%點。
強運（2）：掉落裝備機率增加5%、10%點。
心音（2）：輔助武功ability效果持續時間增加25%、50%。
必中
普通物理攻擊命中100%
武器
急速就是增加出招的機率 暴擊是雙倍傷害機率 格擋是減免30%傷害機率。命中是無視閃避招架的機率 精通是perform傷害加成
第三境界

明鏡（3）：使玩家有20%、40%、60%的機率防止怪物的必殺技。
伏魔（2）：增加對boss怪物的絕對傷害5%、10%點。
商才（2）：經商利潤提高10%，買東西價格降低10%。
迷蹤
逃跑機率增加
靴
第四境界

神眼（3）：鑑定時有33%、66%、100%機率能讓寶石和裝備的等級提高一級。
武神（3）：攻擊和防禦效果增加3%、6%、10%。
天賜（4）：死亡時有5%、10%、15%、20%的機率不掉潛能。
力量祝福
提升自身及隊友的傷害力，消耗憤怒值40。
戰神祝福
全體隊友傷害力上升，消耗憤怒值70。
防禦祝福
提升自身及隊友的防禦力，消耗憤怒值40。
守護祝福
全體隊友物理防禦力上升，消耗憤怒值80。
第五境界

鷹眼（3）：攻擊中有50%機率觸發，命中增加5%、10%、15%（BUFF類）。
輕靈（3）：攻擊中有50%機率觸發，躲閃增加5%、10%、15%（BUFF類）。
神藴（3）：任務中獲取的5%、10%、15%的額外經驗。

第六境界

歸真（2）：特殊武功，物品（天賦技能，飾品）的冷卻時間降低10%、20% 。
通明（5）：每一次攻擊有4%、5%、6%、7%、8%的機率進入通明狀態，造成的傷害增加 (對方等級*4%、8%、12%、20%)點（BUFF類）。
強襲（5）：每一次攻擊有5%、10%、15%、20%、25%的機率讓敵方除凌波微步之外的所有輕功的特殊防禦均無效。
破防提高：我的理解是在目前破防的技術上增加一個比例。比如破防提高10％，那麼如果你破防10點，
       就變成了11點。
   命中加強：説實話，我看不出它有什麼作用來。
   雙倍打擊：在你造成傷害的基礎上，加2倍，重要的一個屬性。比例越高越好。
   致命打擊：非常重要的屬性，造成比例打血效果。
致命打擊：非常重要的屬性，造成比例打血效果。
第七境界

鐵布杉（3）：有3%、6%、10%的機率在受到攻擊時抵抗一半的傷害。
極境（5）：當生命值低於40%時，獲得基本屬性（無裝備時候的屬性）增加4%、8%、12%、16%、20%的效果
逍遙（3）：戰鬥中有10%、20%、30%的機率消除忙亂。

第八境界

武煉（5）：受到暴擊傷害後有20%、40%、60%、80%、100%機率增加防禦（等級*5%）。
頓悟（3）：攻擊時增加5%、10%、15%的雙倍攻擊機率。
殺神（3）：無視目標抗性，直接造成30%、40%、50%的二次攻擊傷害。
殺戮-攻擊時有機率對當前房間所有人進行一次攻擊
清心咒
解除各種異常狀態，如被封物理、魔法、中毒、混亂等，消耗憤怒值50。
me->query_craze() < 1000
消耗憤怒burning
me->cost_craze()
berserk增加憤怒
第九境界

刀皇（5）：使用刀法武功增加4%、8%、12%、16%、20%的命中及傷害效果。
劍聖（5）：使用劍法武功增加4%、8%、12%、16%、20%的命中及傷害效果。
拳王（5）：使用拳法武功增加4%、8%、12%、16%、20%的命中及傷害效果。
*/
});
        
mapping max_ability3 = ([
        "str"   : 1,
        "int"   : 1,
        "con"   : 2,
        "dex"   : 2,
        "kar"   : 2,
        "qi"    : 10,
        "jing"  : 10,
        "neili" : 10,
        "jingli": 10,
        "ref_neili": 20,
        "ref_qi"   : 20,
        "ref_jing" : 20,
        "attack": 10,
        "dodge" : 10,
        "parry" : 10,
        "fatal" : 10,
        "full_self" : 10,
        "avoid_busy": 10,
        "avoid_weak": 10,
        "reduce_damage": 10,
]);        
        

int do_ability_cost(object ob, string arg, int flag);
int check_ability(object me,string arg, int flag);
int improve_ability(object me,string arg, int flag);
int valid_ability_improve(object me, string arg, int flag);
string get_ability_idf(object me,string arg, int flag);
string get_ability_info(object ob, string arg, int flag);

int valid_ability_improve(object me, string arg, int flag)
{
        int level;
        int a_lvl;

        a_lvl = check_ability(me, arg, flag);
        level = max_ability[arg];
        if( a_lvl >= level ) 
                return 0;
 
        return 1;
}

varargs int check_ability(object me,string arg, int flag)
{
        int result;
        
        // Ability 門派
        result=query("ability2/"+query("family/family_name", me)+"/"+arg, me)+query("ability1/"+arg, me);
                
        return result;
}

int check_ability_cost(object me, string arg, int flag) 
{
        int cost;

        if( flag == 1 ) {
                cost = 2;
        } else {
                if( member_array(arg, bas_ability) == -1 ) {
                        return 0;
                }
                cost = bas_ability_pot[arg];
                if( !cost ) {
                        cost = 1;
                }
        }
        return cost;
}

// 每次耗費一點能力點
int do_ability_cost(object me, string arg, int flag)
{
        int cost;

        cost = check_ability_cost(me, arg, flag);
        
        if( flag == 1 || flag == 0 ) {
                if( cost>query("ability", me)-query("learned_ability", me)){
                        return 0;
                }
                addn("learned_ability", cost, me);
        }
        
        return 1;
}

int improve_ability(object me,string arg, int flag)
{
        int lv;
        string myclass;

        myclass = query("family/family_name", me);
        if( !flag ) {
                addn("ability1/"+arg, 1, me);
        } else if( flag == 1 ) {
                addn("ability2/"+myclass+"/"+arg, 1, me);
        } 
        return 1;
}

string get_ability_info(object ob, string arg, int flag)
{
        int lv, cost, n;
        string desc, msg, myclass;

        //lv = check_ability(ob, arg, flag);
        cost = check_ability_cost(ob, arg, flag);
        desc = get_ability_idf(ob,arg,flag);
        if( flag == 1 ) {
                // ability's 門派技能
                myclass=query("family/family_name", ob);
                if( arrayp(fam_ability[myclass]) ) {
                        n = member_array(arg,fam_ability[myclass]);
                        if( n != -1 ) {
                                msg = fam_ability_info[myclass][n];
                                msg = sprintf(msg+"\t%-12s"HIC"%5d\n"NOR,desc, cost);
                                return msg;
                        }
                }
                return "";
        }
        
        n = member_array(arg, bas_ability);
        if( n != -1 ) {
                msg = bas_ability_info[n];
                msg = sprintf(msg+"\t%-12s"HIC"%5d\n"NOR, desc, cost);
                return msg;
        }
        return "";
}


string get_ability_idf(object me,string arg, int flag)
{
        int level = max_ability[arg];
        int lev = check_ability(me,arg,flag);       
        // 1,2,3,4 Basic
        // 5,6,7 Advanced
        // 8,9: Master
        // 10: Grand Master
        string *tough_level_desc = ({
                YEL "一無所知" NOR,//0
                HIB "初窺門徑" NOR,//1
                HIB "略知一二" NOR,//2
                HIB "粗通皮毛" NOR,//3
                HIB "馬馬虎虎" NOR,//4
                CYN "瞭然於胸" NOR,//5
                CYN "出類拔萃" NOR,//6
                CYN "登峯造極" NOR,//7
                HIC "一代宗師" NOR,//8
                HIC "舉世無雙" NOR,//9
                HIW "深不可測" NOR,//10
        });
        string desc = sprintf(HIM"%3d/%3d"NOR, lev, level);
        if( lev >= 10 ) lev = 10;
        return (tough_level_desc[lev]+"（"+ desc+"）");
}

