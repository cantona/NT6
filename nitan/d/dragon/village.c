inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "精靈村落");
        set("long",
"[1;32m眼前是幾處極為普通的村舍，幾個精靈族的小孩子正在屋外\n"
"追逐打鬧，幾只肥肥的大白鵝，看見你來，伸長了脖子嘎嘎的叫，似乎奇\n"
"怪你居然找到了這裡。這裡每當夕陽西下的時候，厚厚的茅草氈成的屋頂\n"
"便會被淡淡的炊煙罩住，整個村裡彌漫著一股誘人的米飯的香味。\n"
);
        set("exits", ([ /* sizeof() == 4 */
   "south" : __DIR__"lake",
   "west" : __DIR__"spirit10",
   "east" : __DIR__"zhanglao",
   ]));

        set("no_magic", 1);
        setup();
        replace_program(ROOM);

}

