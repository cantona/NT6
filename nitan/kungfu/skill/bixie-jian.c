// bixie-jian.c 辟邪劍法
// Last Modified by sega on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *dodge_msg = ({
        "突然之間，白影急幌，$n向後滑出丈余，立時又回到了原地，躲過了$N這一招。\n",
        "$n手臂回轉，在$N手肘下一推，順勢閃到一旁。\n",
        "$n右手伸出，在$N手腕上迅速無比的一按，順勢跳到一旁。\n",
        "$n身形飄忽，有如鬼魅，轉了幾轉，移步到$N的身後，躲過了$N這一招。\n",
        "$N只覺眼前一花，似乎見到$n身形一幌，但隨即又見$n回到原地，卻似從未離開。\n",
        "$N眼睛一花，$n已沒了蹤影。突然$n從身後拍了一下$N的頭，輕輕躍開。\n",
        "$n嫣然一笑，詭異之極，$N竟不知如何是好，停住了攻擊。\n",
});

mapping *action = ({
([        "action":"突然之間，白影急幌，$N向後滑出丈余，立時又回到了原地",
        "lvl" : 0,
        "skill_name" : "白影急幌"
]),
([        "action":"$N右手伸出，在$n手腕上迅速無比的一按，$n險些擊中自己小腹",
        "lvl" : 10,
        "skill_name" : "自己小腹"
]),
([        "action":"驀地裡$N猱身而上，躥到$n的身後，又躍回原地",
        "lvl" : 25,
        "skill_name" : "猱身而上"
]),
([        "action":"$N突然間招法一變，$w忽伸忽縮，招式詭奇絕倫。$n驚駭之中方寸大亂",
        "lvl" : 35,
        "skill_name" : "招法一變"
]),
([        "action":"$N身形飄忽，有如鬼魅，轉了幾轉，移步到$n的左側",
        "lvl" : 40,
        "skill_name" : "有如鬼魅"
]),
([        "action":"$N一聲冷笑，驀地裡疾沖上前，一瞬之間，與$n相距已不到一尺，$w隨即遞出",
        "lvl" : 45,
        "skill_name" : "疾沖上前"
]),
([        "action":"$N喝道：“好！”，便即拔出$w，反手刺出，跟著轉身離去",
        "lvl" : 45,
        "skill_name" : "反手刺出"
]),
([        "action":"$n只覺眼前一花，似乎見到$N身形一幌，但隨即又見$N回到原地，卻似從未離開",
        "lvl" : 20,
        "skill_name" : "眼前一花"
]),
([        "action":"$N向後疾退，$n緊追兩步，突然間$N閃到$n面前，手中$w直指$n的$l",
        "lvl" : 5,
        "skill_name" : "向後疾退"
]),
([        "action":"$N驀地沖到$n面前，手中$w直刺$n右眼！$n慌忙招架，不想$N的$w突然轉向",
        "lvl" : 45,
        "skill_name" : "直刺右眼"
]),
([        "action":"$N飛身躍起，$n抬眼一望，但見得$N從天直落而下，手中$w刺向$n的$l",
        "lvl" : 64,
        "skill_name" : "飛身躍起"
]),
([        "action":"$N腰枝猛擺，$n眼前仿佛突然出現了七八個$N，七八只$w一起刺向$n",
        "lvl" : 79,
        "skill_name" : "腰枝猛擺"
]),
});
int valid_enable(string usage)
{
        return usage == "sword" || usage == "dodge" || usage == "parry";
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
int valid_learn(object me)
{
        return notify_fail("辟邪劍法只能通過研習《葵花寶典》來學習。\n");
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -40;
        int d_e2 = -20;
        int p_e1 = -60;
        int p_e2 = -40;
        int f_e1 = 150;
        int f_e2 = 230;
        int m_e1 = 240;
        int m_e2 = 340;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("bixie-jian", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "割傷" : "刺傷",
        ]);
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me)
{
        if(me->query_skill("kuihua-xinfa",1) > 10) return 1.0; 
        else return 0.6;
}

string perform_action_file(string action)
{
        return __DIR__"bixie-jian/" + action;
}

/*
void double_attack(object me, object victim)
{
        int i,j;
        object other=offensive_target(me);
        if (objectp(other)) victim = other;

        i = me->query_skill("bixie-jian",1)/15; // taiji lian的每招遞增 sword/15
        j = (me->query_skill("bixie-jian",1)-1)/100; // 100 = 0 101 = 1 200 = 1 201 = 2 

  if( j>1 && !query_temp("bixie/guimei", me) && userp(me))j=1;
  
        if (userp(me))
        j = 1; //多于平時的double attack改成pfm出招
                                 //注意變量 query_temp("bixie_hit")表示即將出手的是第多少招
         //不如這樣，對于npc直接在單招中使用 對于玩家在pfm中使用
        if( query_temp("bixie_hit", me)<j && 
  objectp(query_temp("weapon", me)) && 
  (query_temp("weapon",query("skill_type",  me))) == "sword" && 
  me->query_skill_mapped("sword") == "bixie-jian" &&
  me->is_fighting(victim) )
        {
                addn_temp("bixie_hit", 1, me);
                addn_temp("apply/attack", i, me);
          set_temp("action_flag", 1, me);
                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),2);
                set_temp("action_flag", 0, me);
                addn_temp("apply/attack", -i, me);
                addn_temp("bixie_hit", -1, me);
        }
}
*/
int double_attack() { return 1; }

int help(object me)
{
        write(HIC"\n辟邪劍法："NOR"\n");
        write(@HELP

    要說辟邪劍法，就要從《葵花寶典》談起。

    《葵花寶典》是一位宦官所作。這樣一位大高手，為什麼在皇
宮中做太監，那是誰也不知道。至於寶典中所載的武功，卻是精深
之極，三百多年來，始終無一人能據書練成。百余年前，這部寶典
為福建莆田少林寺下院所得。其時莆田少林寺方丈紅葉禪師，乃是
一位大智大慧的了不起人物，依照他的武功悟性，該當練成寶典上
所載武功才是。但他研究多年，直到逝世，始終沒有起始練寶典中
的武功。

    一日華山派的岳肅和蔡子峰到莆田少林寺作客，偷看到《葵花
寶典》。其時匆匆之際，二人不及同時閱遍全書，當下二人分讀，
一人讀一半，後來回到華山，共同三悟研討。不料二人將書中功夫
一加印証，竟然牛頭不對馬嘴，全然合不上來。二人都深信對方讀
錯了書，只有自己所記的才是對的。華山的劍氣二宗之分由此而起。

    紅葉禪師不久發現此事，他知道這部寶典所載武學不僅博大精
深，且蒹兇險之極。這最難的還是第一關，只消第一關能打通，到
後來也沒什麼。第一關只要有半點岔差，立時非死即傷。紅葉當下
派遣得意弟子渡元禪師前往華山，勸論岳蔡二位，不可修習寶典中
的武學。

    渡元禪師上得華山，岳蔡二人對他好生相敬，承認私閱《葵花
寶典》，一面深致歉意，一面卻以經中所載武學向他請教。殊不知
渡元雖是紅葉的得意弟子，寶典中的武學卻未蒙傳授。當下渡元禪
師並不點明，聽他們背誦經文，隨口加以解釋，心中卻暗自記下。
渡元禪師武功本極高明，又是絕頂機智之人，聽到一句經文，便己
意演繹幾句，居然也說來頭頭是道。

    不過岳蔡二人所記的本已不多，經過這麼一轉述，不免又打了
折扣。渡元禪師在華山上住了八日，這才作別，但從此卻也沒再回
到莆田少林寺去。不久紅葉禪師就收到渡元禪師的一通書信，說道
他凡心難抑，決意還俗，無面目再見師父雲雲。

    由於這一件事，華山派弟子偷窺《葵花寶典》之事也流傳於外。
過不多時，魔教十長老來攻華山，在華山腳下一場大戰。魔教十長
老多身受重傷，大敗而去。但岳肅和蔡子峰兩人均在這一役中斃命，
而二人所錄《葵花寶典》也被魔教奪了去。

    渡元禪師還俗之後，復了原姓，將法名顛倒過來取名遠圖，娶
妻生子，創立鏢局，在江湖上轟轟烈烈幹了一番事業。

    莆田少林寺的紅葉禪師園寂之時，召集門人弟子，說明這部寶
典的前因後果，便即將其投如爐中火化。紅葉說：這部武學秘笈精
妙奧妙，但其中許多關鍵之處，當年的撰作人並未能妥為三通解透，
留下的難題太多。尤其是第一關難過，不但難過，簡直是不能過不
可過，流傳後世，實非武林之福。

    林遠圖的辟邪劍法，是從《葵花寶典》殘篇中悟出的武功，兩
者系出同源。辟邪劍法有七十二路，但一來從不外傳，二來使用此
劍法之人個個動作迅捷詭異，外間無人得知其招法的名目，只知道
其招式乃匪夷所思。林遠圖所自錄的《辟邪劍譜》加了許多自己的
解釋，故較魔教所藏的《葵花寶典》易入門，但少了些內容。所以
玩家欲習此功，當遵循先易後難之序。致於如何得到這兩部武林秘
笈，則一直是江湖上避而不談的秘密。如泄露此秘，會招來殺身之
禍。

        學習要求：
                自宮做太監
HELP
        );
        return 1;
}
