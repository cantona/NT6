//頑石訣。


inherit SKILL;
#include <ansi.h>

string query_type()
{
  return "knowledge";
}

int valid_learn(object me)
{
  
  if(!me->query("execute_quest/wanshijue",1)&&
     me->query("vocation")!="殺手")
   return notify_fail("你現在無法領會頑石訣的奧祕！\n");
  
  return 1;
  
}

string *query_execute()
{
   return ({"huanmo","wuxing"});
}
