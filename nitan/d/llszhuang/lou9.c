#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"接 天 樓"NOR);
        set("long",
"這是接天樓的極頂，在這最接近虛空的地方，一場最絢爛的決戰正在\n"
"進行！一位是名震天下數十年的魔師，一位是已成為傳奇的覆雨劍。他們\n"
"的決戰已經遠遠超出了生死勝負，達到了另外一個層面。他們的身形似動\n"
"實靜，舉手投足間莫不隱隱蘊含著天地間的至法。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "down": __DIR__"lou8",
        ]));
        set("no_magic", "1");

        set("objects", ([
               __DIR__"npc/kuangren1" : 2,
               __DIR__"npc/edward" : 1,
        ]));

        setup();
}
