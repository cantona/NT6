/*  <SecCrypt CPL V3R05>  */
 
//  by  snowcat  on  7/5/1997  
inherit  NPC;

int  random2  (int  i)
{
    return  (random(i)+uptime())  %  i;
}

void  create()
{
    set_name("賽龜",  ({  "sai  gui",  "gui"  })  );
    set("race",  "野獸");
    set("gender",  "雄性");
    set("age",  2);
    set("long",  "一隻慢騰騰的賽龜。\n");
    set("attitude",  "friendly");
    set("str",  20+random2(2));
    set("spi",  20+random2(2));
    set("cor",  20+random2(2));
    set("con",  20);
    set("cor",  20);
    set("cps",  20);
    set("dex",  20);
    set("per",  20);
    set("limbs",  ({  "頭部",  "爪子",  "尾巴"  })  );
    set("verbs",  ({  "bite"})  );

    setup();
}
