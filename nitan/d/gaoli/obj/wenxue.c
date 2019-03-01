
inherit ITEM;

void create()
{
   set_name("《三字經》", ({ "san zi jing","jing","book" }));
   set_weight(600);
   set("unit", "本");
   set("long","這是為了提高文化修養的書.\n");
   set("value", 300);
   set("skill", ([
     "name":      "literate",    
     "exp_required":   0, 
                         
     "sen_cost":     10,   
     "difficulty":   1, 
     "max_skill":   20,          
   ]) );
}
