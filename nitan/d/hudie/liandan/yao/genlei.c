#include <ansi.h>
//根類藥材

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
([     "name":     "丹參",
       "id":       "dan shen",
       "yaoxing":  1,
]),
([     "name":     "黨參",
       "id":       "dang shen",
       "yaoxing":  2,
]),
([     "name":     "當歸",
       "id":       "dang gui",
       "yaoxing":  3,
]),
([     "name":     "人參",
       "id":       "ren shen",
       "yaoxing":  4,
]),
([     "name":     "白芷",
       "id":       "bai zhi",
       "yaoxing":  5,
]),
([     "name":     "三七",
       "id":       "san qi",
       "yaoxing":  6,
]),
([     "name":     "麥冬",
       "id":       "mai dong",
       "yaoxing":  7,
]),
([     "name":     "柴胡",
       "id":       "chai hu",
       "yaoxing":  8,
]),
([     "name":     "甘草",
       "id":       "gan cao",
       "yaoxing":  9,
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
         set("unit", "個");                        
        }

   set("yaoxing",yaoxing);
   set("yao",1);
   setup();
  }

