#include "herb.h" 
void create() 
  {
      set_name(NOR + HIY "七星海棠" NOR, ({ "qixing haitang", "qixing", "haitang","herb_qixing-haitang" })); 
          if (clonep())      
                 set_default_object(__FILE__); 
          else { 
                  set("long", NOR + HIG "這株花的葉子也和尋常海棠無異，花瓣緊貼枝幹而生，花枝如鐵，花瓣上有七個小小的黃點。\n" NOR); 
                  set("base_unit", "株");
                  set("base_value", 5000); 
                  set("base_weight", 20);
               }
               setup();
  }
