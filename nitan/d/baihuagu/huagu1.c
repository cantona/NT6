// Room: /d/baihuagu/huagu1.c
// Last Modified by Winder on Mar. 5 2001

#include <ansi.h>;
inherit ROOM;
void create()
{
        set("short", MAG"百花谷"NOR);
        set("long", 
HIR"來到此處，你突然眼前一亮，但覺青青翠谷，點綴着或紅或紫，
或黃或白的鮮花，竟是換了一個世界。道旁有一株桃樹，開得正豔。\n"NOR);  
        set("outdoors", "baihuagu");
        set("exits", ([
                "enter": __DIR__"huagu2",
                "south": __DIR__"bhgent",
        ]));
        set("objects", ([
        ]));
        set("no_clean_up", 0);
        set("coor/x", -450);
        set("coor/y", -370);
        set("coor/z", 0);
        setup();
}
void init()
{
        if(interactive(this_player()))
        {
                remove_call_out("dropleaf");
                call_out("dropleaf",random(10)+10,this_player());
        }
}
int dropleaf(object me)
{
        object leaf;
        if(me)
        if(environment(me) == this_object())
        {
                tell_object(me,HIM"一枝桃花隨風飄下．．．．\n"NOR);
                leaf = new(__DIR__"obj/leaf");
                leaf->move(this_object());      
        }
}