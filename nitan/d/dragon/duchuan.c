inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "渡船");
        set("long",
"[1;32m一葉小舟，最多也就能載七個人。一名精靈族的老艄公，手\n"
"持長竹篙，正在船尾吃力地撐著船。\n"
);
        set("no_clean_up", 0);
        set("no_magic", 1);
        setup();
        replace_program(ROOM);
}
