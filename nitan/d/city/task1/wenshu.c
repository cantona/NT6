// wenshu.c
#include <ansi.h>
inherit ITEM;
string target;

void create()
{
        set_name(WHT "海捕文書" NOR, ({ "wenshu", "wen",}));
        set("weight", 100);
        if(clonep()) set_default_object(__FILE__);
        else{
                set("unit", "張");
                set("long", WHT"這是一張海捕文書，上面有一個畫像，底下有一行小字，你可以仔細看看。\n" NOR);
                set("value", 0);
                set("no_get", 1);
                set("no_drop", 1);
        }
        setup();
}
 
 
#include "wenshu.h"
