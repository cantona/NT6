// dadian.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIR "閻羅大殿" NOR);
         set("long",HIW @LONG
這裡是酆都大帝的宮殿，是陰曹地府的正殿，酆都大帝，也稱閻羅
大帝，就是民間傳說中的閻王；他高高地坐在大殿正中華麗的寶座上，
兩邊立著賞善司，罰惡司，陰律司和查察司四大判官，負責協助閻王審
查鬼魂們的生前善惡，以便決定是令其輪回轉世，還是打入地獄永世受
苦。每個鬼魂來到這裡，都是戰戰兢兢的。
LONG NOR 
        );
        set("no_fight", 1);
        set("exits", ([ 
                "south" : __DIR__"difu2",
                "east"  : __DIR__"tai",
        ]));
        set("objects", ([
                __DIR__"npc/king": 1,
                __DIR__"npc/shan": 1,
                __DIR__"npc/er"  : 1,
                __DIR__"npc/yinlu" :1,
                __DIR__"npc/chacha" :1,
        ]) );

        setup();
        replace_program( ROOM );
}
