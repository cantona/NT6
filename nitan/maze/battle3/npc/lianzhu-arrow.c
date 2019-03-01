inherit SKILL;

int valid_enable(string usage) { return  usage=="arrow"; }
int valid_learn(object me)
{
  return notify_fail("連珠箭法只能向郭靖請教(qingjiao)來學習！\n");    
}

string perform_action_file(string action)
{
        return __DIR__"lianzhu-arrow/" + action;
}                 
