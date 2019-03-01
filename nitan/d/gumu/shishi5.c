// Room: /d/gumu/shishi5.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>
inherit ROOM;

void create()
{ 
        set("short",HIB"石室"NOR);
        set("long", @LONG
你突然覺得眼前一亮，前方石室透過來一絲微弱的光，給了你一絲
希望。但還是只聽見遠遠傳來你腳步的回音，空盪盪的感覺使你心中只
有恐懼，甚至忘記孤獨。四周如此寂然無聲。只能靠摸索前行。
LONG        );
        set("exits", ([
                "west"  : __DIR__"shishi4",
                "enter" : __DIR__"lingshi",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3200);
        set("coor/y", -40);
        set("coor/z", 80);
        setup();
}

int get_object(object ob)
{
        if(userp(ob)) return 1;
        return 0;
}

int valid_leave(object me,string dir)
{
        object *inv = deep_inventory(me);
        object *obj;
        if((int)me->query_skill("yunv-xinfa",1) < 101 && dir == "enter")
                return notify_fail(HIR"\t古墓重地，一般弟子不得入內。\n"NOR);
        obj = filter_array(inv,(:get_object:));
        if( sizeof(obj) && dir =="enter")
                return notify_fail(HIR"\t古墓重地，不得隨意帶他人進入！\n"NOR);
        return ::valid_leave(me, dir);
}