//tmbingqi.c

#include "/d/tangmen/npc/job1.h";

void create()
{
        set("short", "兵器舖");
        set("long",
"這是唐門開的兵器舖，中心擺著一個展覽台，台上有許多暗器，不過\n"
"這些暗器有些古怪，不是一般武林人士會用的。它們是專門為唐門弟子提\n"
"供的，但都是個普通的暗器，對于唐門弟子來說。一位唐門弟子正滿頭大\n"
"汗接待著往來的客人。\n"
);
        set("exits", ([
                "west" : __DIR__"ndajie",
        ]));
        set("objects", ([
                __DIR__"npc/dizi2": 1,
        ]));
        set("no_clean_up", 1);
        set("no_fight", 1);
        setup();
        
}
