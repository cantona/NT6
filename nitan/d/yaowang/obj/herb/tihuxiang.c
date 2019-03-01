#include "herb.h" 
void create() 
  {
      set_name(NOR + HIW "醍醐香" NOR, ({ "tihu xiang", "tihu", "xiang","herb_tihuxiang" })); 
          if (clonep())      
                 set_default_object(__FILE__); 
          else { 
                  set("long", NOR + HIW "一朵白色的小花，發出陣陣濃烈的醉人香氣。\n" NOR); 
                  set("base_unit", "朵");
                  set("base_value", 50); 
                  set("base_weight", 20);
               }
               setup();
  }