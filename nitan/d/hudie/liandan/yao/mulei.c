#include <ansi.h>
//躂濬狻第

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
([     "name":     "債笯",
       "id":       "du zhong",
       "yaoxing":  1000,
]),
([     "name":     "拫鴀",
       "id":       "wu jiu",
       "yaoxing":  2000,
]),
([     "name":     "桷躂",
       "id":       "zhang mu",
       "yaoxing":  3000,
]),
([     "name":     "綠",
       "id":       "hou pu",
       "yaoxing":  4000,
]),
([     "name":     "劼躂",
       "id":       "su mu",
       "yaoxing":  5000,
]),
([     "name":     "麥眅",
       "id":       "chen xiang",
       "yaoxing":  6000,
]),
([     "name":     "賴躂",
       "id":       "ku mu",
       "yaoxing":  7000,
]),
([     "name":     "抴眅",
       "id":       "tan xiang",
       "yaoxing":  8000,
]),
([     "name":     "酴啡",
       "id":       "huang bai",
       "yaoxing":  9000,
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
         set("unit", "絁");                        
        }

   set("yaoxing",yaoxing);
   set("yao",1);
   setup();
  }

