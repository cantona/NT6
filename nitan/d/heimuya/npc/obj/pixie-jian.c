// pixie-jian.c 辟邪劍法
// Jay 4/5/96

inherit SKILL;

string *dodge_msg = ({
        "突然之間，白影急幌，$n向後滑出丈餘，立時又回到了原地，躲過了$N這一招。\n",
        "$n手臂迴轉，在$N手肘下一推，順勢閃到一旁。\n",
        "$n右手伸出，在$N手腕上迅速無比的一按，順勢跳到一旁。\n",
        "$n身形飄忽，有如鬼魅，轉了幾轉，移步到$N的身後，躲過了$N這一招。\n",
        "$N只覺眼前一花，似乎見到$n身形一幌，但隨即又見$n回到原地，卻似從未離開。\n",
        "$N眼睛一花，$n已沒了蹤影。突然$n從身後拍了一下$N的頭，輕輕躍開。\n",
        "$n嫣然一笑，詭異之極，$N竟不知如何是好，停住了攻擊。\n",
});

string *parry_msg = ({
        "突然之間，白影急幌，$n向後滑出丈餘，立時又回到了原地，格開了$N這一招。\n",
        "$n手臂迴轉，在$N手肘下一推，順勢閃到一旁。\n",
        "$n右手伸出，在$N手腕上迅速無比的一按，順勢跳到一旁。\n",
        "$n身形飄忽，有如鬼魅，轉了幾轉，移步到$N的身後，架過了$N這一招。\n",
        "$N只覺眼前一花，似乎見到$n身形一幌，但隨即又見$n回到原地，卻似從未離開。\n",
        "$N眼睛一花，$n已沒了蹤影。突然$n從身後拍了一下$N的頭，輕輕躍開。\n",
        "$n嫣然一笑，詭異之極，$N竟不知如何是好，停住了攻擊。\n",
});

mapping *action = ({
([      "action":"突然之間，白影急幌，$N向後滑出丈餘，立時又回到了原地",
        "force" : 80,
        "dodge" : 40,
        "damage": 40,
        "lvl" : 0,
        "skill_name" : "白影急幌",
        "damage_type":  "刺傷"
]),
([      "action":"$N右手伸出，在$n手腕上迅速無比的一按，$n險些擊中自己小腹",
        "force" : 90,
        "dodge" : 30,
        "damage": 50,
        "lvl" : 0,
        "skill_name" : "自己小腹",
        "damage_type":  "刺傷"
]),
([      "action":"驀地裏$N猱身而上，躥到$n的身後，又躍回原地",
        "force" : 80,
        "dodge" : 60,
        "damage": 70,
        "lvl" : 25,
        "skill_name" : "猱身而上",
        "damage_type":  "刺傷"
]),
([      "action":"$N突然間招法一變，$w忽伸忽縮，招式詭奇絕倫。$n驚駭之中方寸大亂",
        "force" : 80,
        "dodge" : 40,
        "damage": 50,
        "lvl" : 5,
        "skill_name" : "招法一變",
        "damage_type":  "刺傷"
]),
([      "action":"$N身形飄忽，有如鬼魅，轉了幾轉，移步到$n的左側",
        "force" : 90,
        "dodge" : 40,
        "damage": 90,
        "lvl" : 10,
        "skill_name" : "有如鬼魅",
        "damage_type":  "刺傷"
]),
([      "action":"$N一聲冷笑，驀地裏疾衝上前，一瞬之間，與$n相距已不到一尺，$w隨即遞出",
        "force" : 140,
        "dodge" : -5,
        "damage": 100,
        "lvl" : 10,
        "skill_name" : "疾衝上前",
        "damage_type":  "刺傷"
]),
([      "action":"$N喝道：“好！”，便即拔出$w，反手刺出，跟着轉身離去",
        "force" : 80,
        "dodge" : 30,
        "damage": 50,
        "lvl" : 0,
        "skill_name" : "反手刺出",
        "damage_type":  "刺傷"
]),
([      "action":"$n只覺眼前一花，似乎見到$N身形一幌，但隨即又見$N回到原地，卻似從未離開",
        "force" : 140,
        "dodge" : 80,
        "damage": 100,
        "lvl" : 20,
        "skill_name" : "眼前一花",
        "damage_type":  "刺傷"
]),
([      "action":"$N向後疾退，$n緊追兩步，突然間$N閃到$n面前，手中$w直指$n的$l",
        "force" : 60,
        "dodge" : 10,
        "damage": 40,
        "lvl" : 5,
        "skill_name" : "向後疾退",
        "damage_type":  "刺傷"
]),
([      "action":"$N驀地衝到$n面前，手中$w直刺$n右眼！$n慌忙招架，不想$N的$w突然轉向",
        "force" : 200,
        "dodge" : 4,
        "damage": 100,
        "lvl" : 45,
        "skill_name" : "直刺右眼",
        "damage_type":  "刺傷"
]),
([      "action":"$N飛身躍起，$n抬眼一望，但見得$N從天直落而下，手中$w刺向$n的$l",
        "force" : 340,
        "dodge" : 20,
        "damage": 105,
        "lvl" : 64,
        "skill_name" : "飛身躍起",
        "damage_type":  "刺傷"
]),
([      "action":"$N腰枝猛擺，$n眼前彷彿突然出現了七八個$N，七八隻$w一起刺向$n",
        "force" : 380,
        "dodge" : 60,
        "damage": 130,
        "lvl" : 79,
        "skill_name" : "腰枝猛擺",
        "damage_type":  "刺傷"
]),
});


int valid_enable(string usage) 
{ 
    return usage == "sword" || usage == "dodge" || usage == "parry"; 
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("pixie-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int valid_learn(object me)
{
        return notify_fail("辟邪劍法只能通過研習《葵花寶典》來學習。\n");
}
