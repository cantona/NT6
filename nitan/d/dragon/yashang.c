inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "疊嶂峯");
        set("long",
"[1;32m這裏羣峯疊嶂，都是一根而出，看似羣峯，也難説清究竟該\n"
"有多少。然而，山峯雖眾，卻唯此一峯獨尊。一株奇異的小草長在山峯絕\n"
"高之處，瑞氣祥雲皆由此而來。\n"
);
        set("exits", ([ 
             "down" : __DIR__"mountain",
]));
        set("objects", ([ 
        "/quest/tulong/obj/drug1" : 1,
        "/quest/tulong/npc/spirit2" : 1,
                        ]) );
        set("no_magic", 1);
        setup();
//      replace_program(ROOM);
}

void grass_grow()
{
        object grass;
        seteuid(getuid());
        if(grass=new("/quest/tulong/obj/drug1")){
                grass->move(this_object());
                grass->invocation();
        }
        return;
}
