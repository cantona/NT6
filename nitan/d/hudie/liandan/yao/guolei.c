#include <ansi.h>
//果類藥材

inherit ITEM; 
mapping *ansi= ({
([     "yanse":    HIC,]),
([     "yanse":    HIG,]),
([     "yanse":    HIR,]),
([     "yanse":    HIB,]),
([     "yanse":    HIM,]),
([     "yanse":    HIY,]),
([     "yanse":    RED,]),
([     "yanse":    YEL,]), 
([     "yanse":    MAG,]),
([     "yanse":    CYN,]),

});
mapping *yao= ({
([     "name":     "枸杞",
       "id":       "gou qi",
       "yaoxing":  10,
]),
([     "name":     "羅漢果",
       "id":       "luohan guo",
       "yaoxing":  20,
]),
([     "name":     "穿心蓮",
       "id":       "chuanxin lian",
       "yaoxing":  30,
]),
([     "name":     "陳皮",
       "id":       "chen pi",
       "yaoxing":  40,
]),
([     "name":     "豆蔻",
       "id":       "dou kou",
       "yaoxing":  50,
]),
([     "name":     "巴豆",
       "id":       "ba dou",
       "yaoxing":  60,
]),
([     "name":     "山楂",
       "id":       "shan zha",
       "yaoxing":  70,
]),
([     "name":     "茴香",
       "id":       "hui xiang",
       "yaoxing":  80,
]),
([     "name":     "枳實",
       "id":       "zhi shi",
       "yaoxing":  90,
]),
});
void create()
{
    string name,id;
    int yaoxing,yaoo,yanse;

    yanse = random(sizeof(ansi));

    yaoo = random(sizeof(yao)); 

    name = yao[yaoo]["name"];

    id = yao[yaoo]["id"]; 

    yaoxing = yao[yaoo]["yaoxing"]; 

     //set_name(ansi[yanse]["yanse"]+name+NOR,({id}) );  
     set_name(name,({id}) );  

    set_weight(100);
    if( clonep() )
    set_default_object(__FILE__);
    else {
         set("unit", "顆");                        
        }

   set("yaoxing",yaoxing);
   set("yao",1);
   setup();
  }

